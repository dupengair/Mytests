#include <stdio.h>
#include <stdlib.h>


#define CONNECTTIONOK "connection ok"
#define CONNECTTIONFULL "connection full"


typedef enum
{
    MJPEG_CONNECTTION_OK = 0,
    MJPEG_CONNECTTION_FULL,     
}Mjpeg_CStatus_e;


typedef struct
{
	char *status;
	int usedlength;
}MJPEG_CONNECT;



static int MjpegAck(int statusFlag)
{
	int ret = -1;
	char cnctok[]=CONNECTTIONOK;
	char cnctfull[]=CONNECTTIONFULL;
	MJPEG_CONNECT cstatus[2];

	if((MJPEG_CONNECTTION_OK != statusFlag) && (MJPEG_CONNECTTION_FULL!= statusFlag))
		{
		printf("int %s : statusFlag should not be %d\n", __func__, statusFlag);
		return -1;
		}
	
	cstatus[MJPEG_CONNECTTION_OK].status = cnctok;
	cstatus[MJPEG_CONNECTTION_OK].usedlength = sizeof(cnctok);
	cstatus[MJPEG_CONNECTTION_FULL].status = cnctfull;
	cstatus[MJPEG_CONNECTTION_FULL].usedlength = sizeof(cnctfull);

	ret = 0;
	printf("cstatus[statusFlag].status = %s, cstatus[statusFlag].usedlength =%d\n", 
		cstatus[statusFlag].status + ret, cstatus[statusFlag].usedlength);
	
	ret = 5;
	printf("cstatus[statusFlag].status = %s, cstatus[statusFlag].usedlength =%d\n", 
		cstatus[statusFlag].status + ret, cstatus[statusFlag].usedlength);
	return 0;
}

int main(void)
{
	MjpegAck(MJPEG_CONNECTTION_OK);
	MjpegAck(MJPEG_CONNECTTION_FULL);
}

