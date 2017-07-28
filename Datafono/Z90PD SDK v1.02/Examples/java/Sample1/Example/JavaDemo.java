
	
import java.io.*;

class JavaDemo extends Rd600
{
	public static void main( String[] args) throws IOException
	{
		Rd600 obj = new Rd600();
		int icdev,st,i;
		boolean bna;
		char bptime;
		char [] pass =new char [6];
		char [] len = new char [2];
		char [] rdata=new char [33];
		char [] wdata=new char [32];
		char [] rstdata = new char [64];
		int itype;
		short sOffset,sLen,sPage;
		char cLen;
		
		icdev=obj.IC_InitComm(0);
		if (icdev<=0)
		{
			System.out.println("Init comm Error");
			return ;
		}
		else
		{
			System.out.println("Init comm OK");
		}
		bptime=20;
		st=obj.IC_DevBeep(icdev,bptime);
		if (st!=0)
		{
			System.out.println("IC_DevBeep Error");
			return;
		}
		System.out.println("IC_DevBeep OK");
		
		bna=true;
	    st=2;
	    while(st!=0x30)
	    {	    
	        if (bna)
	        {
	            System.out.println("-------------D6 Test-------------");
	            System.out.println("0 Quit System;");
	            System.out.println("1 Test 4442;");
	            System.out.println("2 Test 4428;");
	            System.out.println("3 Test 24C01;");
	            System.out.println("4 Test 24C64");
	            System.out.println("5 Test 45DB041;");
	            System.out.println("6 Test SSF1101;");
	            System.out.println("7 Test 1604;");
	            System.out.println("8 Test 1608;");
	            System.out.println("9 Test CPU;");
	            
	            System.out.println("please input your choice:");
	        }
	        
	        st=System.in.read();
	        if (st==10||st==13) 
	        {
	        	bna=false;
	        }
	        else
	        {
	        	bna=true;
	        }
	        switch (st)
	        {
	        	case 0x30:
	        	    System.out.println("Quit System");
	        	    break;
	        	case 0x31:
					System.out.println("Test 4442");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=16;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype 4442 error");
						continue;
					} 
					System.out.println("Inittype ok");
					st=obj.ReadCount_SLE4442(icdev);
					if (st<0)
					{
						System.out.println("Readcount error");
						continue;
					}
					System.out.println("Readcount OK");
					System.out.println(st);
					pass[0]=0xb6;
					pass[1]=0x23;
					pass[2]=0x07;
					st=obj.CheckPass_SLE4442(icdev,pass);
					if (st!=0)
					{
						System.out.println("Check Pass Error");
						continue;
					}
					System.out.println("Check Pass ok");
		
					for (i=0;i<16;i++)
					{
						wdata[i]=0x32;
					}
					st=obj.IC_Write(icdev,50,16,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_Read_Hex(icdev,50,16,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
					sOffset=30;
					sLen=1;	
					wdata[0]=0xff;				
					st=obj.WriteWithProtection_SLE4442(icdev,sOffset,sLen,wdata);
					if (st!=0)
					{
						System.out.println("WriteWithProtection_SLE4442 Error");
						continue;
					}			
					System.out.println("WriteWithProtection_SLE4442 OK");
					st=obj.ReadWithProtection_SLE4442(icdev,sOffset,sLen,rdata);
					if (st!=0)
					{
						System.out.println("ReadWithProtection_SLE4442 Error");
						continue;
					}
					System.out.println("ReadWithProtection_SLE4442 OK");
					/*
					sLen=1;
					st=obj.hex2asc(rdata,wdata,sLen);
					if (st!=0)
					{
						System.out.println("asc2hex Error");
						continue;
					}
					wdata[2]=0;
					*/
					i = rdata[0];
					System.out.println(i);
					st=obj.ReadPass_4442hex(icdev,pass);
					if (st!=0)
					{
						System.out.println("ReadPass_4442hex Error");
						continue;
					}
					//rdata[6]=0x00;
					System.out.println(pass);
							
	        	    System.out.println("Test 4442 ok\n");
	        	    break;
	        	case 0x32:
					System.out.println("Test 4428");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=4;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype 4428 error");
						continue;
					} 
					System.out.println("Inittype ok");
					st=obj.ReadCount_SLE4428(icdev);
					if (st<0)
					{
						System.out.println("Readcount error");
						continue;
					}
					System.out.println("Readcount OK");
					System.out.println(st);
					pass[0]=0x67;
					pass[1]=0xc6;
					st=obj.CheckPass_SLE4428(icdev,pass);
					if (st!=0)
					{
						System.out.println("Check Pass Error");
						continue;
					}
					System.out.println("Check Pass ok");
		
					for (i=0;i<16;i++)
					{
						wdata[i]=0x34;
					}
					st=obj.IC_Write(icdev,50,16,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_Read_Hex(icdev,50,16,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
					sOffset=20;
					sLen=1;	
					wdata[0]=0x36;				
					st=obj.WriteWithProtection_SLE4428(icdev,sOffset,sLen,wdata);
					if (st!=0)
					{
						System.out.println("WriteWithProtection_SLE4428 Error");
						continue;
					}			
					System.out.println("WriteWithProtection_SLE4428 OK");
					sOffset=0x10;
					sLen=16;	
					st=obj.ReadWithProtection_SLE4428(icdev,sOffset,sLen,rdata);
					if (st!=0)
					{
						System.out.println("ReadWithProtection_SLE4428 Error");
						continue;
					}
					System.out.println("ReadWithProtection_SLE4428 OK");			
					System.out.println(rdata);							
	        	    System.out.println("Test 4428 ok\n");
	        	    break;
	        	    
	        	case 0x33:
	        	    System.out.println("Test 24c01");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=0x40;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype 24c01 error");
						continue;
					} 
					System.out.println("Inittype ok");
		
					for (i=0;i<16;i++)
					{
						wdata[i]=0x56;
					}
					st=obj.IC_Write24(icdev,50,16,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_Read_Hex(icdev,50,16,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
	        	    System.out.println("Test 24c01 ok\n");
	        	    break;
	        	case 0x34:
	        	    System.out.println("Test 24c64");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=0xc0;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype 24c64 error");
						continue;
					} 
					System.out.println("Inittype ok");
		
					for (i=0;i<16;i++)
					{
						wdata[i]=0x64;
					}
					st=obj.IC_Write64(icdev,50,16,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_Read_Hex(icdev,50,16,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
	        	    System.out.println("Test 24c64 ok\n");
	        	    break;
	        	case 0x35:
	        	    System.out.println("Test 45DB041");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=0x41;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype 45DB041 error");
						continue;
					} 
					System.out.println("Inittype ok");
		            
		            sPage=0;
		            sOffset=0;
		            sLen=16;
					for (i=0;i<16;i++)
					{
						wdata[i]=0x34;
					}
					st=obj.IC_DirectWrite(icdev,sPage,sOffset,sLen,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_DirectRead_Hex(icdev,sPage,sOffset,sLen,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
	        	    System.out.println("Test 45DB041 ok\n");
	        	    break;
	        	case 0x36:
	        	    System.out.println("Test SSF1101");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=0x42;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype SSF1101 error");
						continue;
					} 
					System.out.println("Inittype ok");
		            
		            sPage=0;
		            sOffset=0;
		            sLen=16;
					for (i=0;i<16;i++)
					{
						wdata[i]=0x10;
					}
					st=obj.IC_Write_1101(icdev,sPage,sOffset,sLen,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_Read_1101hex(icdev,sPage,sOffset,sLen,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
	        	    System.out.println("Test SSF1101 ok\n");
	        	    break;
	        	case 0x37:
	        	    System.out.println("Test 1604");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=160;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype 1604 error");
						continue;
					} 
					System.out.println("Inittype ok");
					st=obj.ReadCount_1604(icdev,0);
					if (st<0)
					{
						System.out.println("Readcount error");
						continue;
					}
					System.out.println("Readcount OK");
					System.out.println(st);
					pass[0]=0xf0;
					pass[1]=0xf0;
					st=obj.CheckPass_1604(icdev,0,pass);
					if (st!=0)
					{
						System.out.println("Check Pass Error");
						continue;
					}
					System.out.println("Check Pass ok");
					sOffset=50;
					sLen=16;		            
					st=obj.IC_Erase(icdev,sOffset,sLen);
					if (st!=0)
					{
						System.out.println("IC_Erase error");
						continue ;
					}
					for (i=0;i<16;i++)
					{
						wdata[i]=0x16;
					}
					st=obj.IC_Write(icdev,50,16,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_Read_Hex(icdev,50,16,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
	        	    System.out.println("Test 1604 ok\n");
	        	    break;
	        	case 0x38:
	        	    System.out.println("Test 1608");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=208;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype 1608 error");
						continue;
					} 
					System.out.println("Init type ok");
					st=obj.IC_ReadWPasswordCount(icdev,7);
					if (st<0)
					{
						System.out.println("Readcount error");
						continue;
					}
					System.out.println("Readcount OK");
					System.out.println(st);
					pass[0]=0x34;
					pass[1]=0x34;
					pass[2]=0x34;
					st=obj.IC_CheckWPassword(icdev,7,pass);
					if (st!=0)
					{
						System.out.println("Check Pass Error");
						continue;
					}
					System.out.println("Check Pass ok");
					st=obj.IC_SetUserZone(icdev,0);
					if (st!=0)
					{
						System.out.println("IC_SetUserZone Error");
						continue;
					}
					System.out.println("IC_SetUserZone ok");
					sOffset=50;
					sLen=16;
					for (i=0;i<16;i++)
					{
						wdata[i]=0x08;
					}
					st=obj.IC_WriteUserZone(icdev,50,16,wdata);
					if (st!=0)
					{
						System.out.println("write error");
						continue ;
					}
					st=obj.IC_ReadUserZone_Hex(icdev,50,16,rdata);
					if (st!=0)
					{
						System.out.println("Read Error");
						continue ;		
					}
					System.out.println(rdata);
	        	    System.out.println("Test 1608 ok\n");
	        	    break;
	        	case 0x39:
	        	    System.out.println("Test CPU");
					st=obj.IC_Status(icdev);
					if (st!=0)
					{
						if (st==1)
						{
							System.out.println("NO card");
						}
						else
						{
							System.out.println("Status Error");
						}
						continue ;
					}
					System.out.println("Status OK");
					itype=0x0c;
					st = obj.IC_InitType(icdev,itype);
					if (st!=0)
					{
						System.out.println("Inittype CPU error");
						continue;
					} 
					System.out.println("Init type ok");
					st = obj.IC_CpuReset_Hex(icdev, len, rstdata);
					if (st!=0)
					{
						System.out.println("Reset CPU error");
						System.out.println(st);
						continue;
					} 
					System.out.println(rstdata);
					wdata[0]='0';
					wdata[1]='0';
					wdata[2]='8';
					wdata[3]='4';
					wdata[4]='0';
					wdata[5]='0';
					wdata[6]='0';
					wdata[7]='0';
					wdata[8]='0';
					wdata[9]='8';
					cLen = 5;
					st = obj.IC_CpuApdu_Hex(icdev, cLen,wdata,len, rdata);
					if (st!=0)
					{
						System.out.println("Reset CPU error");
						continue;
					} 
					System.out.println(wdata);
					rdata[len[0]*2]=0;
					System.out.println(rdata);
	        	    System.out.println("Test CPU ok\n");
	        	    break;
	        	default:
	        	    break;	        	
	        }   
	    }				
	} 
}