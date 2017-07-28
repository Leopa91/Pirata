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

        
        st=IC_Request(fd,0,&_wTagType);
        if(st<0)
       	{
       		printf("error IC_Request \n");
          exit(-2);
       	}  
        st=IC_Anticoll(fd,0,&_dwSnr); 
        if(st<0)
       	{
       		printf("error IC_Anticoll \n");
          exit(-2);
       	}  
       	printf("snr %08x\n",_dwSnr);
       	
        st=IC_Select(fd, _dwSnr,&_bSize)	; 
        if(st<0)
       	{
       		printf("error IC_Select \n");
          exit(-2);
       	}          
        
  
       	st = IC_LcdClrScrn(fd,2);
        if(st<0)
       	{
       		printf("error IC_LcdClrScrn \n");
          exit(-2);
       	}   
       	
       	/*
           memset(rbuf,0x00,sizeof(rbuf));	
       st = IC_GetInputKey(fd,0,1,30,&rlen,rbuf) 	;
       if(st<0)
       	{
       		printf("error IC_GetInputKey \n");
          exit(-2);
       	}   
       printf(rbuf);
       printf("\n"); 
        

     */
       
        st = IC_DispMainInfo(fd,0,"你好大农");

        if(st<0)
       	{
       		  IC_ExitComm(fd);
       		printf("error IC_DispMainInfo\n");
          exit(-2);
       	}	 
         
         
        st = IC_LcdClrScrn(fd,2);
        if(st<0)
       	{
       		printf("error IC_LcdClrScrn \n");
          exit(-2);
       	}   
       	 	 
        st = IC_DispInfo(fd,1,0,"平安人保");
        if(st<0)
       	{
       		  IC_ExitComm(fd);
       		printf("error IC_DispInfo\n");
          exit(-2);
       	}	 

		st = IC_PosBeep(fd,1);
		if(st != 0)
		{
			printf("IC_Beep error.\n");
			exit(1);
		}
		printf("IC_PosBeep success.\n");
		
     /*  
       st = IC_PassIn(fd ,10);
       if(st<0)
       	{
       		printf("error IC_PassIn \n ");
          exit(-2);
       	} 
       	

     	
	     sleep(5);
	     st = IC_PassGet(fd,&len,rbuf);
	      if(st<0)
       	{
       		printf("error IC_PassGet \n ");
          exit(-2);
       	}   
	     printf(rbuf);
       printf("\n");
      
  
        sleep(1);
        st = IC_PassCancel( fd)    ; 
		    if(st<0)
       	{
       		printf("error IC_PassCancel \n ");
          exit(-2);
       	}   
       
    */
	     
       st = IC_ReadReaderSnr(fd,rbuf);
       if(st<0)
       	{
       		printf("error snr %d\n ",st);
          exit(-2);
       	}
       printf("%s", rbuf);
       printf("\n");
 
       
       //srand(time(0));     
       for(i=0;i<128;i++)buf[i]=0;
        
        /*set card type is 4442 */
        st=IC_InitType(fd,12);
        if(st==0)
          printf("IC_InitType ok\n");
        else
        {
           printf("IC_InitType errorst=%i\n",st);
           IC_ExitComm(fd);
           return 1; 
        }    
        for(j=0;j<3;j++)
        {
        printf("test times=%d\n",j);
        st=IC_Status(fd);
        if(st<0)
        {
           printf("IC_Status error st=%i\n",st);
           IC_ExitComm(fd);
           return 1; 
        }    
        if(st==1)
        {
           printf("NO card\n");
           IC_ExitComm(fd);
           return 1; 
        }          
        if(st==0)
           printf("card inster!\n");     

		st = IC_CpuReset(fd,len,rbuff);
		if(st < 0)
		{
			printf("IC_CpuReset error.\n");
			exit(1);
		}
/*        st=IC_ReadCount_SLE4442(fd);
        if(st<0||st>3)
        {
           printf("IC_ReadCount_SLE4442 error\n");
           IC_ExitComm(fd);
           return 1; 
        }    
        if(st==0)
        {
           printf("4442 card count=0,the card is dead!\n");
           IC_ExitComm(fd);
           return 1; 
        }    
        if(st<3)
        {
           printf("4442 card count=%d<3,please on demo check password!\n",st);
           IC_ExitComm(fd);
           return 1; 
        }          
        if(st==3)
           printf("4442 card count is 3 ,ok!\n");     
  */    
      
        spass[0]=0xff;spass[1]=0xff;spass[2]=0xff;  /*please notice my card spass=b62307 ,please change yourself.*/
   /*     st=IC_CheckPass_SLE4442(fd,spass);
        if(st==0)
        {
	        printf("IC_CheckPass_SLE4442 ok!:\n");
        }
        else
        {
           printf("IC_CheckPass_SLE4442 error\n");
           IC_ExitComm(fd);
           return 1;          
        }
*/
        offset=32;
        slen=256-32;
        for(i=0;i<slen;i++)
        {
          buf[i]=rand()/256;
     
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
      

        st=IC_Read(fd,0,256,rbuf);
        if(st==0)
        {
	        st=IC_Down(fd);
          printf("IC_read ok!the data is:\n");
          for(i=0;i<=256;i++)printf("rbuf[%d]=%02x,",i,rbuf[i]);
          printf("\n");
	        
                   
          st=IC_Beep(fd,30,30);
          
          printf("IC_Beep  st=%i\n",st);
         }
        else
        {
           printf("IC_Read error\n");
           IC_ExitComm(fd);
           return 1;          
        } 
      }  
      
    
        
 
           

	return 0;
}
