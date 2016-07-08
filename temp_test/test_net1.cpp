#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


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


using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::find;

vector<string> have_bind = { "none", "both", "port0", "anyip" };
vector<string> have_porto = { "tcp", "udp" };
    
typedef struct optstrut{
    bool serv;
    string proto;
    string ipaddr;
    int     port;
    string btype;
} TOptstrut;

#define INITOPTSTRUT { true, "tcp", "notset", 0, "both"}

typedef struct conninfo {
    string local_ip;
    unsigned int local_port;
    string dst_ip;
    unsigned int dst_port;
    int sockfd;
} TConnInfo;

#define INITCONNINFO { "0.0.0.0", 0, "0.0.0.0", 0, -1}

struct sockaddr_in skad;
TOptstrut opt = INITOPTSTRUT;
TConnInfo conn = INITCONNINFO;

#define DEBUG_LINE cout << __func__ << ", " << __LINE__ << endl

    
void parse_cmdline(int argc, char **argv) 
{
    static const char opts[] = "ht:o:a:p:b:";
    int optchar;
    
    while((optchar = getopt(argc, argv, opts)) != -1) {
        switch(optchar) {
            case 'h':
                cout << endl << "Usage: " << argv[0] << " [-t type] [-o protocol]  [-a ip] [-p port] [-b bind]" << endl;
                cout << "options:" << endl;
                cout << "   -h Display this help and exit" << endl;
                cout << "   -t serv|cli" << endl;
                cout << "   -o tcp|udp" << endl;
                cout << "   -a [ip]" << endl;
                cout << "   -p [port]" << endl;
                cout << "   -b none|both|port0|anyip" << endl; 
                cout << endl;
                exit(0);
                break;
            case 't':
                if(!strcmp(optarg, "cli"))
                    opt.serv = false;
                break;
            case 'o':
                opt.proto = optarg;
                break;
            case 'a':
                opt.ipaddr = optarg;
                break;
            case 'p':
                opt.port = atoi(optarg);
                break;
            case 'b':
                opt.btype = optarg;
                break;
            case '?':
                exit(-1);
                break;
            }
        }           

        cout << "get options: " << endl;
        cout << "run as: " << (opt.serv ? "server" : "client") << endl;
        cout << "protocol: " << opt.proto << endl;
        cout << "ip: " << opt.ipaddr << endl;
        cout << "port: " << opt.port << endl;
        cout << "bind type: " << opt.btype << endl;
}

bool verify_options(vector<string>& options, string input) {
    bool ret = true;
    if(find(options.begin(), options.end(), input) == options.end()) {
        cout << "illegal input: " << input << endl << "supported: ";
        std::for_each(options.begin(), options.end(), [](string& p) {
                cout << p << " ";
            });
        cout << endl;   
        ret = false;
     }

    return ret;
}

bool verify_cmdline(void) {   
    if(!verify_options(have_porto, opt.proto)
        ||!verify_options(have_bind, opt.btype)) 
       return false;
    
    return true;
}


// create
int sock_create(string type, string ipstr, unsigned short port, string btype = "both")
{    
    int fmt = SOCK_STREAM;
    if(type == "udp")
        fmt = SOCK_DGRAM;
    
    int skfd = socket(AF_INET, fmt, 0);
    if(skfd == -1) {
        perror("creat socket failed:");
        return -1;
    }

    conn.sockfd = skfd;

    bzero(&skad, sizeof(skad));
    skad.sin_family = AF_INET;

    if(btype == "both" || btype == "port0" || btype == "none") 
        if(inet_pton(AF_INET, ipstr.c_str(), &skad.sin_addr) <= 0) {
            perror("convert IP string failed:");
            goto err;
        }
     else if(btype == "anyip")
        skad.sin_addr.s_addr = htonl(INADDR_ANY);

    if(btype == "both" || btype == "anyip" || btype == "none") 
        skad.sin_port = htons(port);
    else if(btype == "port0")
        skad.sin_port = htons(0);

    if(btype != "none")
        if(bind(skfd, (sockaddr*)&skad, sizeof(skad))) {
            perror("bind addr failed:");
            goto err;
    }

    return skfd;
       
err:      
    skfd = -1;
    
    return skfd;
}

// listen
int sock_listen(int fd, int conns = SOMAXCONN)
{
    if (fd <= 0)
        return -1;

    return listen(fd, conns);
}

// connect
int sock_connect(int fd)
{
    if (fd <= 0)
        return -1;

    if(connect(fd, (sockaddr*)&skad, sizeof(sockaddr)) == -1) {
        perror("connect error:");
        switch(errno) {
            case ETIMEDOUT:
                cout << "(" << errno << ") connect timeout" << endl;
                break;
            case ECONNREFUSED:
                cout << "(" << errno << ") RST received" << endl;
                break;
            case EHOSTUNREACH:
                cout << "(" << errno << ") ICMP host unreachable" << endl;
                break;
            case ENETUNREACH:
                cout << "(" << errno << ") ICMP net unreachable" << endl;
                break;
            default:
                cout << "unexpected error: " << errno << endl;
                break;
        }
        return -1;
    }
    
    return 0;
}

// accept
int sock_accept(int listenfd)
{
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

    return 0;
}

void sock_close(void) 
{
    if(conn.sockfd > 0)
        close(conn.sockfd);

    bzero(&skad, sizeof(sockaddr_in));
}

int main(int argc, char **argv)
{
    parse_cmdline(argc, argv);
    
    if(!verify_cmdline()) {
        cout << "exit..." << endl;
        return -1;
     }

    if(opt.serv == true) {
        cout << "begin test as server: " << endl;

        int listenfd = sock_create(opt.proto, opt.ipaddr, opt.port, opt.btype);
        if(listenfd <= 0) {
            cout << "create socket failed" << endl;
        } else if(!sock_listen(listenfd) && !sock_accept(listenfd)) {
            cout << "enter server mainloop" << endl;
            //sleep(5);
        } else 
            cout << "listen&accept failed" <<endl;
     } else {
        cout << "begin test as client: " << endl;
        int connfd = sock_create(opt.proto, opt.ipaddr, opt.port, opt.btype);
        if(connfd <= 0) {
            cout << "create socket failed" << endl;
        } else if(!sock_connect(connfd)) {
            cout << "enter client mainloop" << endl;
            sleep(5);
        } else 
            cout << "connect failed" <<endl;
     }

    sock_close();
}
