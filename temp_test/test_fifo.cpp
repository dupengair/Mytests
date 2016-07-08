#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

using std::string;
using std::cout;
using std::endl;


string fifoname = "unknown";
string mode = "unknown";
bool ffsync = false;
bool verbose = false;
unsigned int tsleep = 0;
std::fstream ff;
const char* buf = "`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'zxcvbnm,./{}:|<>?`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'zxcvbnm,./{}:|<>?`1234567890-=~!@#$%^&*()_+qwertyuiop[]asdfghjkl;'zxcvbnm,./{}:|<>?";


std::string SignalName[65] = {"No Predefined Signal",
		"SIGHUP",
		"SIGINT",
		"SIGQUIT",
		"SIGILL",
		"SIGTRAP",
		"SIGABRT",
		"SIGBUS",
		"SIGFPE",
		"SIGKILL",
		"SIGUSR1",
		"SIGSEGV",
		"SIGUSR2",
		"SIGPIPE",
		"SIGALRM",
		"SIGTERM",
		"SIGSTKFLT",
		"SIGCHLD",
		"SIGCONT",
		"SIGSTOP",
		"SIGTSTP",
		"SIGTTIN",
		"SIGTTOU",
		"SIGURG",
		"SIGXCPU",
		"SIGXFSZ",
		"SIGVTALRM",
		"SIGPROF",
		"SIGWINCH",
		"SIGIO",
		"SIGPWR",
		"SIGSYS",
		"No Predefined Signal",
		"No Predefined Signal",
		"SIGRTMIN",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"No Predefined Signal",
		"SIGRTMAX"};


void HandlePipe(int arg)
{
    std::cout << "HandlePipe: Signal received: "<< SignalName[arg].c_str() << " [" << arg << "]"<< std::endl;
}

void SetSignal(void)
{
    struct sigaction act;

    act.sa_handler = HandlePipe;
    act.sa_flags = 0;
    sigemptyset (&act.sa_mask);
    sigaction(SIGPIPE,&act,NULL);
}

void usage(void)
{
    cout << "Usage:  -f [fifoname] -m [r/w] -s -v -t [sleep in read]" << endl;
}

bool parseCmdline(int argc, char* argv[])
{
    static const char opts[] = "f:m:svt:";
    int optchar;

    while ((optchar = getopt(argc, argv, opts)) != -1)
    {
        switch(optchar)
        {
            case 'm':    
                if((strcmp(optarg, "w") == 0) ||(strcmp(optarg, "r") == 0))
                    mode = optarg;
                else {
                    cout << "illegal mode: (" << optarg << ")" << endl;
                    return false;
                }
                break;
            case 'f':
                fifoname = optarg;
                break;
            case 's':
                cout <<"sync with c I/O" << endl;
                ffsync = true;
                break;
            case 'v':
                cout <<"Verbose" << endl;
                verbose = true;
                break;
            case 't':
                tsleep = atoi(optarg);
                cout <<"sleep time: " << tsleep << endl;
                break;
            case '?':
                usage();
                break;
        }
    }

    return true;
}

bool checkParams(const string& fname, const string& md)
{
    if(fname == "unknown" || md == "unknown") {
        cout << "initialize err: fifoname = " << fname << ", mode = " << md << endl;
        usage();
        return false;
    } else {
        cout << "start with fifo: " << fname << "  (" << md << ")" << endl;
        return true;
    }
}

bool prepareFifo(const string& fname, const string& md)
{
    struct stat ffstat;
    int flag = 0;

    if(stat(fname.c_str(), &ffstat)) {
        perror("prepare fifo error in stat");

        if(md == "w") {
            cout << "open fifo to write: O_WRONLY | O_NONBLOCK | S_IRWXU" << endl; 
            flag = O_WRONLY | O_NONBLOCK | S_IRWXU;
        } else if (md == "r") {
            cout << "open fifo to read: O_RDONLY | O_NONBLOCK | S_IRWXU" << endl; 
            flag = O_RDONLY | O_NONBLOCK | S_IRWXU;
        } else {
            cout << "prepare fifo with mode err: (" << mode << ")" << endl;
            return false;
        }
        
        if(mkfifo(fname.c_str(), flag)) {
            perror("prepare fifo error in mkfifo");
            return false;
        }

        cout << "prepare fifo sucessfully with new: " << fname << endl;
    } else {
        if(!S_ISFIFO(ffstat.st_mode)) {
            cout << fname << " is not a fifo!" << endl;
            return false;
        }
        
        cout << "prepare fifo sucessfully with exist: " << fname << endl;
    }

    return true;
}

bool openFifo(const string& fname, const string& md, bool fsyc)
{
    if(!fsyc) {
        cout <<"open fifo: no sync with c I/O" << endl;
        std::ios_base::sync_with_stdio(false);
     }

    if(md == "w")
        ff.open(fname.c_str(), std::ofstream::out);
    else if(md == "r")
        ff.open(fname.c_str(), std::ifstream::in);
    else {
        cout << "open fifo with error in mode: " << md << endl;
        return false;
    }

    return true;
}

void writeFifo(const char* buf)
{
    struct timeval tv, tv1;
    while(true) {
        gettimeofday(&tv, NULL);
        ff << buf << endl;
        gettimeofday(&tv1, NULL);
        cout << "write time: <" << (tv1.tv_sec - tv.tv_sec) * 1000 + (tv1.tv_usec - tv.tv_usec) / 1000 << ">" << endl;
    }
}

void readFifo(const string& fname, unsigned long ts)
{
    string line;
    unsigned long last, now;
    struct timeval tv;
    
    while(true) {
        while(std::getline(ff, line)) {
            if(verbose)
                cout << line << endl;
            usleep(ts);
            gettimeofday(&tv, NULL);
            now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
            cout << "read time: <" << now - last << ">" << endl;
            last = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        }

        if(ff.eof()) {
            ff.close();
            ff.open(fname.c_str(), std::ifstream::in);
            cout << "open fifo again in read" << endl;
        }
    }  
    
}



int main(int argc, char* argv[])
{
    if(!parseCmdline(argc, argv))
        return -1;

    if(!checkParams(fifoname, mode))
        return -1;

    if (!prepareFifo(fifoname, mode))
        return -1;

    if (!openFifo(fifoname, mode, ffsync))
        return -1;

    SetSignal();

    if(mode == "w")
        writeFifo(buf);
    else if(mode == "r")
        readFifo(fifoname, tsleep * 1000);
    else {
        cout << "mode error, exit..." << endl;
        return -1;
     }

    return 0;
}

