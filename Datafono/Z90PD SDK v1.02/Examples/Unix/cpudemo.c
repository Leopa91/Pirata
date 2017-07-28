/* a sample for cpu card */
/* author jlm            */
/* copy right 2000-2002  */ 
/*example: cpudemo /dev/tty1a    //open com1*/
#include <stdio.h>
#include "dcunix.h"
void h2a(unsigned char *strasc,unsigned char *strhex,int length);
void dispstr(unsigned char slen,unsigned char *buff)
{
   int i;
   for(i=0;i<slen;i++)
       printf("%02X",buff[i]);
   printf("\n");
   return;

}
int main(int argc,char *argv[])
{
	int st,i,fd;
        unsigned char slen,rlen;
	unsigned char sendbuff[256],recbuff[256],sel;	
  	
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
        
         printf("fd=%d\n",fd);	
         	

         while(1){
           printf("        0.get card status\n");     /* this command first */           
           printf("        1.set card type\n");     /* this command must */
           printf("        2.reset card\n");
           printf("        3.get randrom data (use ic_cpuapdu) for T=0 and T=1\n");
           printf("        4.get randrom data (use ic_cpuapdusource) for T=1 exam\n");
           printf("        5.send command to cpu card\n");
           printf("        6.cpu card ic_down\n");
           printf("        7.exit\n");
           scanf("%c",&sel);
           /* choice 0 ,set card type */
           if(sel==48){
             st=IC_Status(fd); 
	     if(st<0)printf("get status error!err code=%d\n",st);
             else if(st==0)
              printf("have card in reader!\n");
             else if(st==1)
              printf("no card in reader!\n");
           }
           /* choice 1 ,set card type */
           if(sel==49){
             st=IC_InitType(fd,12); 
	     if(st!=0)printf("Set card type error!err code=%d\n",st);
             else printf("set card type ok!\n");
           }
           
           /*choice 2 ,reset card */
           if(sel==50){
              st=IC_CpuReset(fd,&rlen,recbuff);
              if(st!=0)printf("reset card error!err code=%d\n",st);
              else{
                printf("reset card ok data is ");
                dispstr(rlen,recbuff);
                  
               } 
           }

           /*choice 3 ,send get randrom command */
           /* use ic_apuapdu() ,auto differ T=0 and T=1, don't send NAD PCB*/
           /* T=0 and T=1 all can use */
           if(sel==51){
              sendbuff[0]=0x00;sendbuff[1]=0x84;sendbuff[2]=0x00;
              sendbuff[3]=0x00;sendbuff[4]=0x04;
              slen=5;
              st=IC_CpuApdu(fd,slen,sendbuff,&rlen,recbuff);
              if(st!=0)printf("Get random error!err code=%d\n",st);  
              else {
                printf("Get random data ok data is ");
                dispstr(rlen,recbuff);
               }         

            }

           /*choice 4 ,send get randrom command */
           /* use ic_apuapdusource() ,send source data ,if card T=1 need send NAD PCB ...*/
           /* if card t=0 ,do't need send NAD,PCB ...*/
           /* this is  for T=1 exam ,if card is T=0 remove NAD,PCB...*/
           if(sel==52){
              sendbuff[0]=0x00;  //NAD
              sendbuff[1]=0x00;  //PCB
              sendbuff[2]=0x5;   //LEN
              sendbuff[3]=0x00;
              sendbuff[4]=0x84;
              sendbuff[5]=0x00;
              sendbuff[6]=0x00;
              sendbuff[7]=0x04;
              sendbuff[8]=0x00;  //fill 0
              for(i=0;i<sendbuff[2]+3;i++)
                    sendbuff[8]=sendbuff[8]^sendbuff[i];              
              slen=sendbuff[2]+4;
              st=IC_CpuApduSource(fd,slen,sendbuff,&rlen,recbuff);
              if(st!=0)printf("Get random error!err code=%d\n",st);  
              else {
                printf("Get random data ok data is ");
                dispstr(rlen,recbuff);
               }         

        }
           if(sel==53)
           {
            printf("please input command string:(ep 0084000008)\n");
            scanf("%s",recbuff);
            slen=strlen((char *)recbuff);
            h2a(recbuff,sendbuff,slen);
            slen=slen/2;
            st=IC_CpuApdu(fd,slen,sendbuff,&rlen,recbuff);
            if(st!=0)printf("send command error!err code=%d\n",st);  
            else 
            {
                printf("send command ok, return data is ");
                dispstr(rlen,recbuff);
               }                     
           
           }	
        
           /*choice 6 ,cpu card ic down */
           if(sel==54){
             st=IC_Down(fd);
	     if(st!=0)printf("Ic down error!err code=%d\n",st);
             else printf("cpu card ic_down ok!\n"); 
           }


           /*choice 7 ,you exit this demo */
           if(sel==55)break;    
  
           scanf("%c",&sel);
         }
                 
         st=IC_ExitComm(fd);	
         exit(0);
}