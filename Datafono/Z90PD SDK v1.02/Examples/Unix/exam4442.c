#include <stdio.h>
#include "dcunix.h"
/*if use local com1 you can try "/dev/tty1a"   if use terminal you can try "star510"*/
int main(int argc,char *argv[])
{
	int fd,st,i,j;
	unsigned char buf[256],rbuf[256],spass[5];
        unsigned char slen,rlen,offset;
   
	printf("Begin:\n");
  	
        if(argc<2){
	 printf("Usage: %s deviece name\n",argv[0]);
	 exit(-1);
         }
        else if( (fd= IC_InitComm(argv[1]) ) < 0) 
       {
          printf("Cannot open %s\n",argv[1]);
         exit(-2);
        }
       if(fd<0){printf("Error for init comm.\n");return;}
        
      /* fd=IC_InitComm_Para(200,"\033!0;0;0;0Y","\033[/50h","\033[/50l","\033[/51h","\033[/51l","\033[/53h",'\x0','\x0',"\033[/54l");*/
 
         printf("fd=%d\n",fd);	
       srand(time(0));     
       for(i=0;i<128;i++)buf[i]=0;
        
        /*set card type is 4442 */
        st=IC_InitType(fd,16);
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
           printf("ic_status error st=%i\n",st);
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

        st=IC_ReadCount_SLE4442(fd);
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
      
      
        spass[0]=0xb6;spass[1]=0x23;spass[2]=0x07;  /*please notice my card spass=b62307 ,please change yourself.*/
        st=IC_CheckPass_SLE4442(fd,spass);
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
          for(i=0;i<=255;i++)printf("rbuf[%d]=%02x,",i,rbuf[i]);
	  printf("fd=%i\n",fd);
          sleep(3);
          
          st=IC_Beep(fd,30,30);
          
          printf("IC_Beep  st=%i",st);
         }
        else
        {
           printf("IC_Read error\n");
           IC_ExitComm(fd);
           return 1;          
        }        
  }       
	IC_ExitComm(fd);
	printf("End.\n");
	return 0;
}