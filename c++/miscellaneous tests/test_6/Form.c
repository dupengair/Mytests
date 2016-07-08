
#include <iostream>
#include <map>

#include "CGIProtocol.h"
#include "Form.h"

using namespace TEST;


#ifdef USE_EXTERN_C
//extern "C" {
#endif
int DefineEgiForm(void *http, char *name, CGIHandler form)
{
    std::cout << name << " : " << SYM << " , var = " << xxx;
    form(http);

    return 0;
}

#ifdef USE_EXTERN_C
//}
#endif
