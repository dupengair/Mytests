#include <algorithm>

#include <netdb.h>
#include <fcntl.h>
#include <pthread.h>

#include "test_net1.h"

using namespace Test;

/****************************************************
*                   TEST CASE :
*  No. |Proto |Action
*   1.      TCP   TIME_WAIT 2MSL   
*   2.      TCP   syn timeout & slow start & window [ & Fast Restransmit & Fast recovery ]
*   3.      TCP   connect timeout & refused & icmp unreached
*   4.      TCP   bind  IP
*                                     client             server           
*                    bind IP       src IP             src IP from listen
*                    not bind      by kernel       by client syn dist
*   5.      TCP  bind port     specified & 0
*   6.      TCP   listen      syn time out when queue full
*
****************************************************/


/*******************
  *
  * manage input options
  *
  *******************/
Args::TestParams::TestParams(int argc, char **argv)
{
    try {
        ParseCmdline(argc, argv);
    } catch (const Test::Ex::Arg_InputError &ex) {
        cout << "input error < " << ex.what() << " >" << endl;
        goto Exit;
    }

    try {
        VerifyParams();
    } catch (const Test::Ex::Arg_VerifyError &ex) {
        cout << "illegal parameter: < " << ex.what() << " >" << endl;
        goto Exit;
    }

    try {
        VerifyLogic();
    } catch (const Test::Ex::Arg_LogicError &ex) {
        cout << "argument conflict: < " << ex.what() << " >" << endl;
        goto Exit;
    }

Exit:
    exit(-1);
}

void Args::TestParams::ParseCmdline(int argc, char **argv) 
{
    static const char opts[] = "hs:c:b:t:";
    int optchar;
    
    while((optchar = getopt(argc, argv, opts)) != -1) {
        switch(optchar) {
            case 'h':
                cout << endl << "Usage: " << argv[0] << " [option] [params]" << endl;
                cout << "options:" << endl;
                cout << "   -h Display this help and exit" << endl;
                cout << "   -s run as server" << endl;
                cout << "   -c run as client: ip=xxx.xxx.xxx.xxx port=xxx'" << endl;
                cout << "   -b bind: 'ip=xxx.xxx.xxx.xxx port=xxx' " << endl;
                cout << endl;
                exit(0);
                break;
            case 's':       
                Test::Args::ParseParams<Test::Args::Server, Test::Args::ParsePort>::GetOpt(optarg, ServerPort);
                //Test::Args::Parse<Test::Args::ParsePort>(optarg, ServerPort);
                IsServer = true;
                cout << "run as server, port: " << ServerPort << endl;
                break;
            case 'c':
                Test::Args::ParseParams<Test::Args::Client, Test::Args::ParseAddr>::GetOpt(optarg, CliInfo);
                IsClient = true;
                cout << "run as client, ip: " << CliInfo.first << " , port: " << CliInfo.second << endl;
                break;
            case 'b': 
                Test::Args::ParseParams<Test::Args::Bind, Test::Args::ParseAddr>::GetOpt(optarg, BindInfo);
                IsBind = true;
                cout << "bind, ip: " << BindInfo.first << " , port: " << BindInfo.second << endl;                
                break;
            case 't': 
                Test::Args::ParseParams<Test::Args::Protocol>::GetOpt(optarg, Proto);
                cout << "Protocol: " << Proto << endl;                
                break;
            case '?':
                exit(-1);
                break;
            }
        }           
}

void Args::TestParams::VerifyParams(void) 
{    
    Test::Args::VerifyParams<Test::Args::Server, Test::Args::VerifyLarger>::Verify(ServerPort, 0);
    Test::Args::VerifyParams<Test::Args::Client, Test::Args::VerifyAddr>::Verify(CliInfo, "");
    Test::Args::VerifyParams<Test::Args::Bind, Test::Args::VerifyAddr>::Verify(BindInfo, "");
    Test::Args::VerifyParams<Test::Args::Protocol, Test::Args::VerifyDict>::Verify(Proto, SupportedProto);
}

void Args::TestParams::VerifyLogic(void) 
{    
    
    if (IsClient == true && IsServer == true) {
        string ex("could not be both client and server ");
        throw Test::Ex::Arg_LogicError(ex);
    }

    if (IsClient == false && IsServer == false) {
        string ex("neither client nor server specified");
        throw Test::Ex::Arg_LogicError(ex);
    }

    if (IsServer == true&& IsBind == false) {
        string ex("server should bind");
        throw Test::Ex::Arg_LogicError(ex);
    }
    
}



/*******************
  *
  * manage System
  *
  *******************/
std::vector<System::TThreadPtr> System::Thread::Threads;

System::Thread::Thread() 
{
    pthread_cond_init(&Cond, NULL);
    pthread_mutex_init(&Lock, NULL);
}

System::Thread::~Thread() 
{
    pthread_cond_destroy(&Cond);
    pthread_mutex_destroy(&Lock);
}

void System::Thread::Wait(void)
{
    pthread_mutex_lock(&Lock);
    while(stat != Status::RUNNING)
        pthread_cond_wait(&Cond, &Lock);
    pthread_mutex_unlock(&Lock);
}

void System::Thread::Notify(void)
{
    pthread_mutex_lock(&Lock);
    pthread_cond_signal(&Cond);
    pthread_mutex_unlock(&Lock);
}

void* System::Thread::Hook(void *tparam)
{
    TThreadPtr thread = *((TThreadPtr *)tparam);
    THREAD_FUN func = thread->Func;
    void *param = thread->Param;

    thread->Tid = thread->GetTid();
    thread->Pid = thread->GetPid();
    thread->stat = Status::RUNNING;    
    Thread::Threads.push_back(thread);
    thread->Notify(); 

    
    // execution
    void *ret = func(param);

    thread->stat = Status::TERMINATING;
    Thread::Threads.erase(std::remove(Threads.begin(), Threads.end(), thread));
    
    return ret;
}

// create thread
int System::Thread::Create(THREAD_FUN func, void *param, std::string name, size_t stacksize, bool detached)
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, stacksize);

    size_t curstacksize = 0;
    if(pthread_attr_getstacksize(&attr, &curstacksize)) {
        perror("set stacksize failed in Thread::Create");
        return -1;
    }

    if(detached && (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))) {
        perror("set detacked failed in Thread::Create");
        return -1;
    }
    
    pthread_t id;   
    TThreadPtr curthread(new Thread());
    curthread->Func = func;
    curthread->Param = param;
    curthread->Name = name;
    curthread->Stacksize = stacksize;
    curthread->Detached = detached;
    curthread->stat = Status::CREATING;
    
    if(pthread_create(&id, &attr, Hook, &curthread)) {
        perror("create thread failed in Thread::Create");
        pthread_attr_destroy(&attr);
        return -1;
    } else 
        curthread->Wait();

    pthread_attr_destroy(&attr);
    return 0;
}



/*******************
  *
  * manage socket
  *
  *******************/

// create
int Net::TestSock::sock_connect(const string& ip, int port, const string& proto, vector<int>& connfds, vector<int>& waitfds)
{    
    struct addrinfo hints, *res, *ressave;
    bzero(&hints, sizeof(struct addrinfo));

    // check the protocol
    if(proto == "tcp")
        hints.ai_socktype = SOCK_STREAM;
    else if(proto == "udp")
        hints.ai_socktype = SOCK_DGRAM;
    else {
        string ex("sock_connect: protocol unknow");
        throw Test::Ex::Run_ConnError(ex);
    }

    // check if IPv4 or IPv6 specified
    struct in_addr ip4addr;
    struct in6_addr ip6addr;
    
    if(ip.empty())
        hints.ai_family = AF_UNSPEC;
    else if(inet_pton(AF_INET, ip.c_str(), &ip4addr)) {
        cout << "IPv4 specified: " << ip4addr.s_addr << endl;
        hints.ai_family = AF_INET;
    } else if(inet_pton(AF_INET6, ip.c_str(), &ip6addr)) {
        cout << "IPv6 specified: " << ip6addr.s6_addr << endl;
        hints.ai_family = AF_INET6; 
    } else {
        string ex("sock_connect: ip family unknow");
        throw Test::Ex::Run_ConnError(ex);
    }    

    // get available address to create socket
    ostringstream sport;
    sport << port;
    if(getaddrinfo(ip.c_str(), sport.str().c_str(), &hints, &res)) {
        ostringstream ex;
        ex << "sock_connect: getaddrinfo failed: ip = " << ip << ", port = " << port;
        throw Test::Ex::Run_ConnError(ex.str());
    }

    if(!res) {
        string ex("sock_connect: impossible, getaddrinfo returns NULL!");
        throw Test::Ex::Run_ConnError(ex);
    } 

    // start connect
    ressave = res;
    int flags, sockfd;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(sockfd < 0)
            continue;

        // use non-block connect for efficiency
        flags = fcntl(sockfd, F_GETFL, 0);
        fcntl(sockfd, F_SETFL, flags|O_NONBLOCK);

        // non-block connect could probably be successful
        if(!connect(sockfd, res->ai_addr, (int)res->ai_addrlen)) {
            connfds.push_back(sockfd);
        } else {
            // the sockfd in handshaking will be wait in select
            if(errno == EINPROGRESS)
                waitfds.push_back(sockfd);
            else {
                perror("sock_connect: connect failed");
                close(sockfd);      // really need ?
                continue;
            }
        }
    } while((res = res->ai_next) != NULL);

    freeaddrinfo(ressave);

    if(connfds.empty() && waitfds.empty()) {
        cout << "sock_connect: no socket found to connect!" << endl;
        return -1;
    } 

    return 0;
}


// get local & peer infomation
int Net::TestSock::sock_getconninfo(const vector<int>& cnfds, const string& proto)
{
    // get connection info for connected
    if(cnfds.empty()) {
        return -1;
    }

    struct sockaddr_storage ssp, ssl;
    socklen_t len = sizeof(struct sockaddr_storage);
        
    TConnInfo conn;
    char ip[128];
    for(const auto& i : cnfds) {
        // only get those connected
        if(!getpeername(i, (struct sockaddr*)&ssp, &len)) {
            perror("sock_client: getpeername failed");
            close(i);
            continue;
        }
     
        if(!getsockname(i, (struct sockaddr*)&ssl, &len)) {
            perror("sock_client: getlocalname failed");
             close(i);
            continue;
        }

        conn.sockfd = i;
        conn.proto = proto;
        struct sockaddr_in *addr;
        struct sockaddr_in6 *addr6;
        
        // get local address
        memset(ip, 0, sizeof(ip));
        if(ssl.ss_family == AF_INET) {
            addr = (struct sockaddr_in *)&ssl;
            if(!inet_ntop(ssl.ss_family, (void *)&(addr->sin_addr), ip, sizeof(ip))) {                        
                perror("sock_client: convert local ipv4 failed");
                close(i);
                continue;
            }

            conn.srcport = ntohs(addr->sin_port);
        } else if(ssl.ss_family == AF_INET6) {
            addr6 = (struct sockaddr_in6 *)&ssl;
            if(!inet_ntop(ssl.ss_family, (void *)&(addr6->sin6_addr), ip, sizeof(ip))) {                        
                perror("sock_client: convert local ipv6 failed");
                close(i);
                continue;
            }

            conn.srcport = ntohs(addr6->sin6_port);
        }
        conn.srcip = ip;          

        // get peer address
        memset(ip, 0, sizeof(ip));
        if(ssp.ss_family == AF_INET) {
            addr = (struct sockaddr_in *)&ssp;
            if(!inet_ntop(ssp.ss_family, (void *)&(addr->sin_addr), ip, sizeof(ip))) {                        
                perror("sock_client: convert peer ipv4 failed");
                close(i);
                continue;
            }

            conn.dstport = ntohs(addr->sin_port);
        } else if(ssp.ss_family == AF_INET6) {
            addr6 = (struct sockaddr_in6 *)&ssp;
            if(!inet_ntop(ssp.ss_family, (void *)&(addr6->sin6_addr), ip, sizeof(ip))) {                        
                perror("sock_client: convert peer ipv6 failed");
                close(i);
                continue;
            }
            
            conn.dstport = ntohs(addr6->sin6_port);
        }
        conn.dstip = ip;

        ConnInfo.push_back(conn);
        cout << "connection info: [ local ip: " << conn.srcip << ", port: " << conn.srcport 
            << ", peer ip: " << conn.dstip << ", port: " << conn.dstport << " ]" << endl;
    }

    return 0;
}


void* Net::TestSock::sock_clienttsk(void *param)
{
}


int Net::TestSock::sock_runclient(TConnInfo& cn)
{
    ostringstream name;
    name << cn.dstip << ":" << cn.dstport;
    System::Thread::Create(sock_clienttsk, &cn, name.str());
}

// wait for connect complete
int Net::TestSock::sock_connloop(vector<int>& waitfds, unsigned int  timeout)
{
    if(ConnInfo.empty() && waitfds.empty()) {
        cout << "sock_clientloop: no socket to operate!" << endl;
        return -1;
    } 

    for(auto& i : ConnInfo) {
        sock_runclient(i);
    }

    int maxfd;
    fd_set rfds;
    fd_set wfds;
    fd_set efds;

    do {
        
        maxfd = 0;
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_ZERO(&efds);

        // connections completed
        for(const auto& i : ConnInfo) {
            FD_SET(i.sockfd, &rfds); 
            FD_SET(i.sockfd, &efds);
            if(maxfd < i.sockfd)
                maxfd = i.sockfd;
        }

        // connections to be complete
        for(const auto& i : waitfds) {
            FD_SET(i, &wfds); 
            FD_SET(i, &efds);
            if(maxfd < i)
                maxfd = i;
        }

        struct timeval tv_timeout;
        tv_timeout.tv_sec = timeout / 1000;
        tv_timeout.tv_usec = (timeout - (timeout * 1000)) * 1000;

        int ret = select(maxfd+1, &rfds, &wfds, &efds, &tv_timeout);
        if(ret == 0) {
            cout << "nothing to do for timeout!" << endl;
            continue;
        } else if (ret == -1) {
            if(errno == EINTR)
                continue;
            else 
                return -1;
        } else {
            
        }
        

        
    } while (!ConnInfo.empty());
        

    
    
    
}

// client data exchange
void Net::TestSock::sock_client(const string& ip, int port, const string& proto)
{    
    vector<int> connfds, waitfds;
    // start non block connect
    try {
        if(sock_connect(ip, port, proto, connfds, waitfds)) {
            cout << "start connect failed" << endl;
            return;
        }        
    } catch (const Test::Ex::Run_ConnError &ex) {
        cout << "Runtime error: < " << ex.what() << " >" << endl;
        exit(-1);
    }

    // get connection info for already connected
    sock_getconninfo(connfds, proto);

    // manange connect and data exchange 
    sock_connloop(waitfds, 1);

    
    return;
}


// accept
int Net::TestSock::sock_accept(void)
{
#if 0
    if (listenfd <= 0)
        return -1;

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(listenfd, &rfds);

    if(select(listenfd+1, &rfds, NULL, NULL, NULL) == -1) {
        if(errno == EINTR)
            cout << "interrtupted, will resume..." << endl;
        else {
            perror("select error in accept: ");
            return -1;
        }
    } else {
        struct sockaddr_in cliaddr;
        socklen_t clilen = sizeof(struct sockaddr_in);
        int connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen);
        if(connfd > 0) {
            char buf[128];

            if(inet_ntop(AF_INET, (void *)&cliaddr.sin_addr, buf, sizeof(buf))) 
                conn.dst_ip = buf;
            else {
                perror("ntop in accept:");
                cout << "can't convert dst ip" << endl;
            }

            conn.dst_port = ntohs(cliaddr.sin_port);
                
            cout << "new connection received:" << endl;
            cout << "                ip: " << conn.dst_ip << endl;
            cout << "                port: " << conn.dst_port << endl;

            conn.sockfd = connfd;
        } else {
            perror("accept error: ");
            return -1;
        }
        
    }
#endif
    return 0;
}

void Net::TestSock::sock_close(void) 
{
#if 0
    if(conn.sockfd > 0)
        close(conn.sockfd);

    bzero(&skad, sizeof(sockaddr_in));
#endif
}

int main(int argc, char **argv)
{

    Test::Args::TestParams p(argc, argv);
    Test::Net::TestSock t1;
    
    if(p.AsServer()) {
    } else if(p.AsClient()) {
        t1.sock_client(p.GetParams<Test::Args::Client>().first, p.GetParams<Test::Args::Client>().second, p.GetParams<Test::Args::Protocol>());
    }

}
