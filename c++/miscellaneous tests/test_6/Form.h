#ifndef _FORM_H
#define _FORM_H

#define USE_EXTERN_C

#ifdef USE_EXTERN_C
#ifdef __cplusplus
extern "C" {
#endif
#endif
extern int DefineEgiForm(void *http, char *name, CGIHandler form);

#ifdef __cplusplus
#ifdef USE_EXTERN_C
}
#endif
#endif


#endif
