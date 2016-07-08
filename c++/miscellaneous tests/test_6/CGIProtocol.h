#ifndef _TEST_5_H
#define _TEST_5_H

typedef void (* CGIHandler)(void *hnd);
typedef std::map<std::string, CGIHandler> T_CGIPROTOCOL;
typedef int (* DefineEgiFormFunc)(void *http, char *name, CGIHandler form);
namespace TEST {
    #define SYM 1
}

extern int xxx;
class CGIProtocol
{
public:
     T_CGIPROTOCOL varHandler;

public:      
    ~CGIProtocol();   
    void InitForm(DefineEgiFormFunc);

    static CGIProtocol* GetInstance(void);
protected:
    CGIProtocol();
private:
    static CGIProtocol* instance;
};




#define INFINOVACGI_SYS_GET "/cgi/sys_get"
#define INFINOVACGI_SYS_SET "/cgi/sys_set"





#endif
