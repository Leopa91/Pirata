#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include   <unistd.h>
#include "dclinux.h"

#define MAXSIZE 256

int main(int argc,char *argv[])
{
	int fd,st,i,j,_wTagType;
	unsigned char len[MAXSIZE];
	unsigned char rbuff[MAXSIZE];
	unsigned char buf[256]={"okj"},rbuf[256],spass[5];
	unsigned char slen,rlen,offset;
	DWORD _dwSnr;
	BYTE _bSize; 

	memset(len,'\0',sizeof(len));
	memset(rbuff,'\0',sizeof(rbuff));
	if((fd = IC_InitComm(100) ) <= 0) 
	{
		printf("Cannot open \n");
		exit(-2);
	}

	st = IC_ReadReaderSnr(fd,rbuf);
	if(st<0)
	{
		printf("error snr %d\n ",st);
	}
	printf("%s", rbuf);
	printf("\n");

	st = IC_InitType(fd, 16);
	printf("IC_InityType st : %d\n", st);

	st = IC_Status(fd);
	printf("IC_Status st : %d\n", st);

	if(0 == st)
	{
		unsigned char buf[1024] = "\0";
		st = IC_Read(fd, 0, 8, buf);
		printf("IC_Read st : %d\n", st);
		if(0 == st)
		{
			int i;
			for(i = 0; i < 8; i ++)
				printf("%02X ", buf[i]);
			printf("\n");
		}
	}

	IC_ExitComm(fd);

	return 0;
}
