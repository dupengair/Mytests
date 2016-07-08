#include <stdio.h>
#include <error.h>
#include <string.h>

#include "classdef.h"

static char strres[128];


sock_opts_t sock_opts[] = {
		{ "SO_BROADCAST", "",	SOL_SOCKET,		SO_BROADCAST,	sock_str_flag },
		{ "SO_DEBUG", "    ", 		SOL_SOCKET, 	SO_DEBUG,		sock_str_flag },
		{ "SO_DONTROUTE", "", 	SOL_SOCKET, 	SO_DONTROUTE,	sock_str_flag },
		{ "SO_ERROR", "    ", 		SOL_SOCKET, 	SO_ERROR,		sock_str_int },
		{ "SO_KEEPALIVE", "", 	SOL_SOCKET, 	SO_KEEPALIVE,	sock_str_flag },
		{ "SO_LINGER", "   ", 		SOL_SOCKET, 	SO_LINGER,		sock_str_linger },
		{ "SO_OOBINLINE", "", 	SOL_SOCKET, 	SO_OOBINLINE,	sock_str_flag },
		{ "SO_RCVBUF", "   ", 	SOL_SOCKET, 	SO_RCVBUF,		sock_str_int },
		{ "SO_SNDBUF", "   ", 	SOL_SOCKET, 	SO_SNDBUF,		sock_str_int },
		{ "SO_RCVLOWAT", " ", 	SOL_SOCKET, 	SO_RCVLOWAT,	sock_str_int },
		{ "SO_SNDLOWAT", " ", 	SOL_SOCKET, 	SO_SNDLOWAT,	sock_str_int },
		{ "SO_RCVTIMEO", " ", 	SOL_SOCKET, 	SO_RCVTIMEO,	sock_str_timeval },
		{ "SO_SNDTIMEO", " ", 	SOL_SOCKET, 	SO_REUSEADDR,	sock_str_timeval },
		{ "SO_REUSEADDR", "", 	SOL_SOCKET, 	SO_REUSEADDR,	sock_str_flag },
	#ifdef HAS_SO_REUSEPORT
		{ "SO_REUSEPORT", 	SOL_SOCKET, 	SO_REUSEPORT,	sock_str_flag },	
	#endif
		{ "SO_TYPE", "     ", 		SOL_SOCKET, 	SO_TYPE,		sock_str_int },
//		{ "SO_USELOOPBACK", SOL_SOCKET,		SO_USELOOPBACK,	sock_str_flag },
		{ "IP_TOS", "      ", 		IPPROTO_IP, 		IP_TOS,			sock_str_int },
		{ "IP_TTL", "      ", 		IPPROTO_IP, 		IP_TTL,			sock_str_int },
	#ifdef IPV6
		{ "IPV6_DONTFRAG", "", 	IPPROTO_IPV6, 	IPV6_DONTFRAG,	sock_str_flag },
		{ "IPV6_UNICAST_HOPS", "", 	IPPROTO_IPV6, 	IPV6_UNICAST_HOPS,	sock_str_int },
		{ "IPV6_V6ONLY", "   ", 	IPPROTO_IPV6, 	IPV6_V6ONLY,		sock_str_flag },
	#endif
		{ "TCP_MAXSEG", "  ", 	IPPROTO_TCP, 	TCP_MAXSEG,		sock_str_int },
		{ "TCP_NODELAY", " ", 	IPPROTO_TCP, 	TCP_NODELAY,	sock_str_flag },
		{ NULL, NULL, 	0, 	0,	NULL }
};


char* sock_str_flag(union val *ptr, int len)
{
	if (len != sizeof(int))
			snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
			snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off" : "on");
	
	return (strres);
}


char* sock_str_int(union val *ptr, int len)
{
	if (len != sizeof(int))
			snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
			snprintf(strres, sizeof(strres), "%ld", ptr->l_val);
	
	return (strres);
}


char* sock_str_linger(union val *ptr, int len)
{
	if ((unsigned int)len > sizeof(struct linger))
			snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct linger)", len);
	else
			snprintf(strres, sizeof(strres), "%s %d", (ptr->linger_val.l_onoff == 0) ? "off" : "on", ptr->linger_val.l_linger);
	
	return (strres);
}


char* sock_str_timeval(union val *ptr, int len)
{
	if ((unsigned int)len > sizeof(struct timeval))
			snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct timeval)", len);
	else
			snprintf(strres, sizeof(strres), "%ld, %ld", ptr->timeval_val.tv_sec, ptr->timeval_val.tv_usec);
	
	return (strres);
}


int get_new_socket(int opt_level)
{
	switch(opt_level)
		{
		case SOL_SOCKET:
		case IPPROTO_IP:
		case IPPROTO_TCP:
			return socket(AF_INET, SOCK_STREAM, 0);
			break;
	#ifdef IPV6
		case IPPROTO_IPV6:
			return socket(AF_INET6, SOCK_STREAM, 0);
			break;
	#endif
		default:
			{
			printf("can't create socket for level %d\n", opt_level);	
			return -1;
			}
		}
}

void get_result(const char *opt_name)
{
	sock_opts_t *ptr;
	socklen_t len;
	union  val Val;
	int fd = -1;
	
	for(ptr = sock_opts; ptr->opt_str != NULL; ptr++)
		{	
		if(!strcmp(ptr->opt_str, opt_name))
			{	
			printf("%s:  ", ptr->opt_str);
			if(ptr->opt_val_str == NULL)
				{
				printf("(undefined)\n");
				return;
				}

			fd = get_new_socket(ptr->opt_level);
			len = sizeof(Val);
			if (getsockopt(fd, ptr->opt_level, ptr->opt_name, &Val, &len) == -1)
				perror("getsockopt error:");
			else
				printf("default = %s\n", (*ptr->opt_val_str)(&Val, len));

			close(fd); 
			return;
			}
		}	

	printf("undefined opt : %s\n", opt_name);
}

void get_all_results()
{
	sock_opts_t *ptr;
	socklen_t len;
	union  val Val;
	int fd = -1;
	
	for(ptr = sock_opts; ptr->opt_str != NULL; ptr++)
		{	
		printf("%s%s:  ", ptr->opt_str, ptr->opt_fillblack);
		if(ptr->opt_val_str == NULL)
			{
			printf("(undefined)\n");
			return;
			}
			
		len = sizeof(Val);
		fd = get_new_socket(ptr->opt_level);
		if (getsockopt(fd, ptr->opt_level, ptr->opt_name, &Val, &len) == -1)
			perror("getsockopt error:");
		else
			printf("default = %s\n", (*ptr->opt_val_str)(&Val, len));

		close(fd);
		}	
}



