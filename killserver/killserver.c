#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	system("killall -9 image_server");
	system("killall -9 encode_server");
	//system("killall -9 softdog");
}

