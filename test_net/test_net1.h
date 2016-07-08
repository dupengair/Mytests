#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/prctl.h>
#include <sys/syscall.h>

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <sstream>
#include <memory>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::ostringstream;


#define DEBUG_LINE cout << __func__ << ", " << __LINE__ << endl

namespace Test {
    namespace Ex {
        class Arg_InputError: public std::logic_error {
            public:
                explicit Arg_InputError(const string &s): std::logic_error(s) {}
        };

        class Arg_VerifyError: public std::logic_error {
            public:
                explicit Arg_VerifyError(const string &s): std::logic_error(s) {}
        };

        class Arg_LogicError: public std::logic_error {
            public:
                explicit Arg_LogicError(const string &s): std::logic_error(s) {}
        };

        class Run_ConnError: public std::runtime_error {
            public:
                explicit Run_ConnError(const string &s): std::runtime_error(s) {}
        };

        class Run_SysError: public std::runtime_error {
            public:
                explicit Run_SysError(const string &s): std::runtime_error(s) {}
        };

    }

    namespace Args {



        class ArgBase {
            private:
                string Param;
                
            public:
                ArgBase(string arg): Param(arg) {
                } 
                string GetParam(void) {
                    return Param;
                }
        };

        typedef std::pair<string, int> TAddr;
        typedef string TVerfDefault;

        
        template<typename T>
        class ParamsTraits;

   
        #define ARG_DEF(Name, ArgType, VerfType)  \
                class Name: public ArgBase { \
                    public: \
                        Name(string arg): ArgBase(arg) { \
                        } \
                }; \
                 \
                template<>\
                class ParamsTraits<Name> { \
                    public: \
                        typedef ArgType TOpt; \
                        typedef VerfType TVerf; \
                }
                

        // TODO: add arguments here:
        ARG_DEF(Server, int, int);
        ARG_DEF(Client, TAddr, TVerfDefault);
        ARG_DEF(Bind, TAddr, TVerfDefault);
        ARG_DEF(Protocol, string, vector<string>);


        
        // TODO: add parse method here:
        class ParseString {
            public:
                template <typename T>
                static void Get(string param, T& opt) {
                    if(param.empty()) {
                        string ex("no input: ");
                        throw Ex::Arg_InputError(ex);
                    }
                    
                    opt = param;
                }
        };

        class ParseNum {
            public:
                template <typename T>
                static void Get(string param, T& opt) {
                    if(param.empty()) {
                        string ex("no input: ");
                        throw Ex::Arg_InputError(ex);
                    }
                    
                    opt = atoi(param.c_str());;
                }
        };

        class ParsePort {
            public:
                template <typename T>
                static void Get(string param, T& opt) {
                    if(param.empty()) {
                        string ex("no input: ");
                        throw Ex::Arg_InputError(ex);
                    }
                
                    string::size_type idx_eq = param.find("=");
                    if(idx_eq == string::npos) {
                        ostringstream ex;
                        ex << "not like: 'port=xxx' (" << param << ")";
                        throw Ex::Arg_InputError(ex.str());
                    }

                    string k = param.substr(0, idx_eq);
                    string v = param.substr(idx_eq + 1); 
                   
                    if(k == "port") {
                        if(v.empty()) {
                                ostringstream ex;
                                ex << "port is empty";
                                throw Ex::Arg_InputError(ex.str());
                            }
                        
                        opt = atoi(v.c_str());
                    } else {
                        ostringstream ex;
                        ex << "not a port (" << k << ")";
                        throw Ex::Arg_InputError(ex.str());
                    }
                }
        };

        class ParseAddr {
            public:
                template <typename T>
                static void Get(string param, T& opt) {
                    if(param.empty()) {
                        string ex("no input: ");
                        throw Ex::Arg_InputError(ex);
                    }
                
                    T addr = {"unknown", -1};

                    string::size_type idx_fst_blk = param.find(" ");
                    string::size_type idx_lst_blk = param.rfind(" ");
                    if(idx_fst_blk == string::npos) {
                        ostringstream ex;
                        ex << "lack of arguments: 'ip=xxx.xxx.xxx.xxx port=xxx' (" << param << ")";
                        throw Ex::Arg_InputError(ex.str());
                    }
                    
                    vector<string> toparse = { param.substr(0, idx_fst_blk), param.substr(idx_lst_blk + 1) };
                    string k, v;
                    for_each(toparse.begin(), toparse.end(), [&k, &v, &addr](string item) {
                        string::size_type idx_eq = item.find("=");
                        if(idx_eq == string::npos) {
                            ostringstream ex;
                            ex << "not like: 'ip=xxx.xxx.xxx.xxx port=xxx' (" << item << ")";
                            throw Ex::Arg_InputError(ex.str());
                        }
                        
                        k = item.substr(0, idx_eq);
                        v = item.substr(idx_eq + 1);  

                        if(k == "ip")
                            addr.first = v;
                        else if(k == "port") {
                            if(v.empty()) {
                                ostringstream ex;
                                ex << "port is empty";
                                throw Ex::Arg_InputError(ex.str());
                            }
                            
                            addr.second = atoi(v.c_str());
                        } else {
                            ostringstream ex;
                            ex << "neither ip nor port (" << k << ")";
                            throw Ex::Arg_InputError(ex.str());
                        }
                    });
                    
                    if(addr == T( "unknown" , -1)) { 
                        ostringstream ex;
                        ex << "input error (" << param << ")";
                        throw Ex::Arg_InputError(ex.str());
                    } else 
                        opt = addr;
                }
        };        

      

        template <typename T,      
                          typename ParsePolicy = ParseString, 
                          typename Traits = ParamsTraits<T> >
        class ParseParams {
            public:
                typedef typename Traits::TOpt TOpt;
                static void GetOpt(string param, TOpt& opt) {
                    ParsePolicy::Get(T(param).GetParam(), opt);
                }     
        };  

        /*Can't do this automatic type declaraton, because TOpt is traits, rather than the internal type, which causes deduction failed */        
        /*
        template <typename ParsePolicy, typename T, typename Traits = ParamsTraits<T> >
        void Parse (string param, typename Traits::TOpt& opt) {
            ParseParams<T, ParsePolicy>::GetOpt(param, opt);
        }; */


        // TODO: add validation method here:
        class VerifyEmpty{
            public:
                template <typename T, typename N>
                static void Verify(T& opt, N Refer) {
                    if(opt.empty()) {
                        ostringstream ex;
                        ex << "empty value";
                        throw Ex::Arg_VerifyError(ex.str());
                    }
                }
         };
        
        class VerifyLarger {
            public:
                template <typename T, typename N>
                static void Verify(T& opt, N Refer) {
                    if(opt < Refer) {
                        ostringstream ex;
                        ex << "should > " << Refer << " (" << opt << ")";
                        throw Ex::Arg_VerifyError(ex.str());
                    }
                }
         };

        class VerifyRange {
            public:
                template <typename T, typename N>
                static void Verify(T& opt, N Refer) {
                    if(opt < Refer.first ||opt > Refer.second) {
                        ostringstream ex;
                        ex << "should in Range: [" << Refer.first << "," << Refer.second << "]  (" << opt << ")";
                        throw Ex::Arg_VerifyError(ex.str());
                    }
                }
         };

        class VerifyAddr {
            public:
                template <typename T, typename N>
                static void Verify(T& opt, N Refer) {
                    if(opt.first.empty()) {
                        ostringstream ex;
                        ex << "empty ip";
                        throw Ex::Arg_VerifyError(ex.str());
                     }
                        
                    if(opt.second < 0) {
                        ostringstream ex;
                        ex << "port should not be negative (" << opt.second << ")";
                        throw Ex::Arg_VerifyError(ex.str());
                    }
                }
         };

        class VerifyDict {
            public:
                template <typename T, typename N>
                static void Verify(T& opt, N Refer) {
                    typename N::iterator idx = find(Refer.begin(), Refer.end(), opt);
                    if(idx == Refer.end()) {
                        ostringstream ex;
                        ex << "option not support (" << opt << ")";
                        throw Ex::Arg_VerifyError(ex.str());
                    }
                }
         };


        template <typename T,      
                          typename VerifyPolicy = VerifyEmpty, 
                          typename Traits = ParamsTraits<T> >
        class VerifyParams {
            public:
                typedef typename Traits::TOpt TOpt;
                typedef typename Traits::TVerf TVerf;
                
                static void Verify(TOpt& opt, TVerf Verf) {
                   VerifyPolicy::Verify(opt, Verf);
                }     
        };  


        class TestParams {
            private:
                const vector<string> SupportedProto = {"tcp","udp"};

            private:
                ParamsTraits<Server>::TOpt ServerPort = 0;
                ParamsTraits<Client>::TOpt CliInfo = {"0.0.0.0", 0};
                ParamsTraits<Bind>::TOpt BindInfo = {"0.0.0.0", 0};
                ParamsTraits<Protocol>::TOpt Proto = "tcp";
                
                bool IsClient = false;
                bool IsServer = false;
                bool IsBind = false;

            private:
                void VerifyParams(void);
                void VerifyLogic(void);
                
            public:
                TestParams(int argc, char **argv);
                void ParseCmdline(int argc, char **argv);
                bool AsClient(void) { return IsClient; }
                bool AsServer(void) { return IsServer; }
                bool ToBind(void) { return IsBind; }

                template <typename T>
                typename ParamsTraits<T>::TOpt GetParams(void);
                
        };

       
        template<>
        typename ParamsTraits<Server>::TOpt TestParams::GetParams<Server>(void) {
            return ServerPort;
        }

        template<>
        typename ParamsTraits<Client>::TOpt TestParams::GetParams<Client>(void) {
            return CliInfo;
        }

        template<>
        typename ParamsTraits<Bind>::TOpt TestParams::GetParams<Bind>(void) {
            return BindInfo;
        }

        template<>
        typename ParamsTraits<Protocol>::TOpt TestParams::GetParams<Protocol>(void) {
            return Proto;
        }
        
        
    }// end of namespace Args


    namespace System {

        class Thread;
        typedef std::shared_ptr<Thread> TThreadPtr; 
        typedef void* (* THREAD_FUN)(void*);

        class Thread {
            public:
                static constexpr  size_t STACK_SIZE_1K      = 1024;
                static constexpr  size_t STACK_SIZE_128K  = STACK_SIZE_1K * 128;
                static constexpr  size_t STACK_SIZE_512K  = STACK_SIZE_128K * 4;
                static constexpr  size_t STACK_SIZE_1M      = STACK_SIZE_512K * 2; 
                
                enum class Status:int { CREATING, RUNNING, WAITING, TERMINATING};
                
            private:
                static std::vector<TThreadPtr> Threads;

                std::string Name;
                pthread_t Tid;
                pid_t Pid;
                size_t Stacksize;
                bool Detached;
                void *Param;
                Status stat;
                THREAD_FUN Func;
                
                

                pthread_cond_t Cond;
                pthread_mutex_t Lock;
                

            private:
               
                void Wait(void);
                void Notify(void);
                pthread_t GetTid(void) {
                    return pthread_self();
                }

                pid_t GetPid(void) {
                    return syscall(SYS_gettid);
                }

                void SetName(std::string& name) {
                    prctl(PR_SET_NAME, name.c_str(), 0, 0, 0);
                }
                
                static void* Hook(void *param);

            public:
                Thread();                
                ~Thread();
                
                static int Create(THREAD_FUN func, void *param, std::string name="Nick", size_t stack_size = STACK_SIZE_1M, bool detached = false);
                
                
        };
    }
    

    namespace Net {

        typedef struct ConnInfo {
            string proto;
            string srcip;
            int srcport;
            string dstip;
            int dstport;
            int sockfd;
        } TConnInfo;
            
        
        class TestSock {
            private:
                vector<TConnInfo> ConnInfo;                
                vector<int> Listenfds;  

            private:
                int sock_connect(const string& ip, int port, const string& proto, vector<int>& connfds, vector<int>& waitfds);
                int sock_getconninfo(const vector<int>& cnfds, const string& proto);
                int sock_connloop(vector<int>& waitfds, unsigned int  timeout = 0);
                int sock_runclient(TConnInfo& cn);
                static void* sock_clienttsk(void *param);

            public:
                void sock_client(const string& ip, int port, const string& proto);
                int sock_accept(void);
                void sock_close(void);
        };
        
        
    }// end of namespace Net

    
}
