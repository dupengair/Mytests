#ifndef CLASSDEF_H
#define CLASSDEF_H


//#include "udp.h"
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/time.h>

union  val{
	int i_val;
	long l_val;
	struct linger linger_val;
	struct timeval timeval_val;
};

char *sock_str_flag(union val *, int);
char *sock_str_int(union val *, int);
char *sock_str_linger(union val *, int);
char *sock_str_timeval(union val *, int);

typedef struct  {
	const char *opt_str;
	const char *opt_fillblack;
	int	opt_level;
	int	opt_name;
	char *(*opt_val_str)(union val *, int);
}sock_opts_t;

//#define HAS_SO_REUSEPORT
		
		

extern void get_result(const char *opt_name);
extern  void get_all_results();



#endif