#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h> 
#include <net/if_arp.h>
#include <net/route.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <linux/sockios.h>
//#include <linux/if.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>

typedef  unsigned int  uint32;
#define LOCAL_HOST_IP 16777343
#define IFRSIZE   ((int)(size * sizeof (struct ifreq)))
    
			int EnumerateNetworkAdapters(int* err)
			{
				err = 0;


				errno = 0;

				int sockfd, size = 1;
				if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) >= 0)
				{
					struct ifconf ifc;
					ifc.ifc_len = IFRSIZE;
					ifc.ifc_req = NULL;

					do 
					{
						++size;
						
						if ((ifc.ifc_req = (struct ifreq*)realloc(ifc.ifc_req, IFRSIZE)) == NULL)
							break;
							
						ifc.ifc_len = IFRSIZE;
						if (ioctl(sockfd, SIOCGIFCONF, &ifc))
							break;
							
					} while (IFRSIZE <= ifc.ifc_len);
					

					struct ifreq* ifr = ifc.ifc_req;
					for (;(char *) ifr < (char *) ifc.ifc_req + ifc.ifc_len; ++ifr) 
					{
						if (ifr->ifr_addr.sa_data == (ifr+1)->ifr_addr.sa_data) 
							continue;  /* duplicate, skip it */

						if (ioctl(sockfd, SIOCGIFFLAGS, ifr))
							continue;  /* failed to get flags, skip it */					
							
						// exclude local
						if (!strcmp(ifr->ifr_name, "lo"))
							continue;

						struct sockaddr_in sa;
						uint32 Ip = *(uint32*)(struct in_addr *)&ifr->ifr_addr.sa_data[sizeof sa.sin_port];

						if (Ip != LOCAL_HOST_IP)
						    {
					            printf("find ETH : %s\n", ifr->ifr_name);
						    }
                                         else
                                            {
                                            printf("Ip == LOCAL_HOST_IP\n");
                                            }
					}

					close(sockfd);
				}

				*err = errno;

				return (*err == 0);
			}


int main(void)
{
    int err = 0;
    EnumerateNetworkAdapters(&err);
    return 0;
}