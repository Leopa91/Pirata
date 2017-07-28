#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dclinux.h"

int main(int argc,char *argv[])
{
	int fd;
	int st;
	int i;
	int offset;
	int slen;
	unsigned char buf[256];
	unsigned char rbuf[256];
	unsigned char spass[64];

	memset(buf,'\0',sizeof(buf));
	memset(spass,'\0',sizeof(spass));
	memset(rbuf,'\0',sizeof(rbuf));

	fd = IC_InitComm(100);
	if(fd <= 0)
	{
		printf("IC_InitComm error.\n");
		return 1;
	}
	printf("IC_InitComm ok.\n");
	printf("fd = %d\n",fd);

	/* set card type is 4442*/
	st = IC_InitType(fd,16);
	if(st == 0)
	{
		printf("IC_InitType ok.\n");
	}
	else
	{
		printf("IC_InitType error.\n");
		IC_ExitComm(fd);
		return 1;
	}

	st = IC_Status(fd);
	if(st == 0)
	{
		printf("card inster!\n");
	}
	if(st == 1)
	{
		printf("No card.\n");
		IC_ExitComm(fd);
		return 1;
	}
	if(st < 0)
	{
		printf("IC_Status error.\n");
		IC_ExitComm(fd);
		return 1;
	}

	st = IC_ReadCount_SLE4442(fd);
	if((st < 0) || (st > 3))
	{
		printf("IC_ReadCount_SLE4442 error.\n");
		IC_ExitComm(fd);
		return 1;
	}
	if(st == 0)
	{
		printf("4442 card count = 0,the card is dead.\n");
		IC_ExitComm(fd);
		return 1;
	}
	if(st < 3)
	{
		printf("4442 card count=%d<3,please on demo check password!\n",st);
        IC_ExitComm(fd);
        return 1; 
	}          
    if(st==3)
	{
		printf("4442 card count is 3 ,ok!\n");     
	}

	spass[0]=0xff;spass[1]=0xff;spass[2]=0xff;  /*please notice my card spass=b62307 ,please change yourself.*/
    st=IC_CheckPass_SLE4442(fd,spass);
    if(st==0)
    {
		printf("IC_CheckPass_SLE4442 ok!:\n");
    }
    else
    {
		printf("IC_CheckPass_SLE4442 error\n");
		printf("st = %d\n",st);
        IC_ExitComm(fd);
        return 1;          
    }

     offset=32;
     slen=16;
	 for(i=0;i<slen;i++)
     {
        buf[i]=0x22;	
     }
     st=IC_Write(fd,offset,slen,buf);
     if(st==0)
     {
		 printf("IC_Write ok!\n");
     }
     else
     {
		 printf("IC_Write error\n");
		 IC_ExitComm(fd);
		 return 1;          
     }            
 
     st=IC_Read(fd,32,16,rbuf);
     if(st==0)
     {
		 st=IC_Down(fd);
         printf("IC_read ok!the data is:\n");
         for(i=0;i<16;i++)printf("rbuf[%d]=%02x,",i,rbuf[i]);
         printf("\n");
     }
	 else
	 {
		 printf("IC_Read error\n");
         IC_ExitComm(fd);
         return 1;          
     }         

	return 0;
}