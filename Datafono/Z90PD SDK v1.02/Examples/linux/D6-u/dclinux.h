typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef  int           HANDLE;
typedef  int           __int16;


#define uchar    unsigned char
#define BYTE     unsigned char
#define bool int
#define false 0
#define true  1


int    IC_ReadVer(int idComDev,unsigned char *Ver);
int    IC_Encrypt( char *key,char *ptrSource, unsigned int msgLen, char *ptrDest);
int    IC_Decrypt( char *key,char *ptrSource, unsigned int msgLen, char *ptrDest);
int    IC_Encrypt_Hex( char *key,char *ptrSource, unsigned int msgLen, char *ptrDest);
int    IC_Decrypt_Hex( char *key,char *ptrSource, unsigned int msgLen, char *ptrDest);
int    IC_Encrypt_Neu( char *key,char *ptrSource, unsigned int msgLen, char *ptrDest);
int    IC_Decrypt_Neu( char *key,char *ptrSource, unsigned int msgLen, char *ptrDest);
int    IC_InitComm(int port);
int    IC_InitComm_Para(int PORT,char * SET,char * ENABLE,char *DISEABLE,char * WR_BEGIN,char * WR_END,char *FIXSET,char PREFIX,char SUFFIX,char *DIRECT);
int    IC_ExitComm(int idComDev);
int    IC_Status(int idComDev);
int    IC_Down(int idComDev);
int    IC_Beep(int idComDev,unsigned char delaytime,unsigned char beeptime);
int    IC_ReadDevice(int idComDev,int offset,int len,unsigned char * databuffer);
int    IC_WriteDevice(int idComDev,int offset,int len,unsigned char * writebuffer);
int    IC_ReadDevice_Hex(int idComDev,int offset,int len,unsigned char * databuffer);
int    IC_WriteDevice_Hex(int idComDev,int offset,int len,unsigned char * writebuffer);
int    IC_CpuReset(int idComDev,unsigned char *rlen, unsigned char *databuffer);
int    IC_CpuApdu(int idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
int    IC_CpuApduSource(int idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
int    IC_CpuReset_Hex(int idComDev,unsigned char *rlen, unsigned char *databuffer);
int    IC_CpuApdu_Hex(int idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
int    IC_CpuApduSource_Hex(int idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
int    IC_CpuGetProtocol(int idComDev);
int    IC_CpuApduRespon(int idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
int    IC_CpuSetProtocol(int idComDev,unsigned char cardp);
int    IC_Pushout(int idComDev);
int    IC_InitType (int idComDev,int type);
int    IC_Read(int idComDev,int offset,int len,unsigned char * databuffer);
int    IC_Read_Float(int idComDev,int offset,float *fdata);
int    IC_Read_Int(int idComDev,int offset,long *fdata);
int    IC_Write_Int(int idComDev,int offset,long fdata);
int    IC_ReadProtection(int idComDev,int offset,int len,unsigned char* protbuffer);
int    IC_ReadProtection_Hex(int idComDev,int offset,int len,unsigned char* protbuffer);
int    IC_ReadWithProtection(int idComDev,int offset,int len,unsigned char* protbuffer);
int    IC_ReadWithProtection_Hex(int idComDev,int offset,int len,unsigned char* protbuffer);
int    IC_Write(int idComDev,int offset,int len,unsigned char *writebuffer);
int    IC_Write_Float(int idComDev,int offset,float fdata);
int    IC_WriteProtection(int idComDev,int offset,int len,unsigned char *protbuffer);
int    IC_WriteWithProtection(int idComDev,int offset,int len,unsigned char *writebuffer);
int    IC_WriteProtection_Hex(int idComDev,int offset,int len,unsigned char *protbuffer);
int    IC_WriteWithProtection_Hex(int idComDev,int offset,int len,unsigned char * writebuffer);
int    IC_ReadCount_SLE4442(int idComDev);
int    IC_CheckPass_SLE4442(int idComDev,unsigned char* password);
int    IC_ChangePass_SLE4442(int idComDev,unsigned char*password);
int    IC_CheckPass_4442hex(int idComDev,unsigned char*password);
int    IC_ChangePass_4442hex(int idComDev,unsigned char*password);
int    IC_ReadCount_SLE4428(int idComDev);
int    IC_CheckPass_SLE4428(int idComDev,unsigned char* password);
int    IC_ChangePass_SLE4428(int idComDev,unsigned char* password);
int    IC_CheckPass_4428hex(int idComDev,unsigned char* password);
int    IC_ChangePass_4428hex(int idComDev,unsigned char* password);
int    IC_Erase(int idComDev,int offset,int len);
int    IC_Erase_102(int idComDev,int offset,int len);
int    IC_Fuse_102(int idComDev);
int    IC_ReadCount_102(int idComDev);
int    IC_CheckPass_102(int idComDev,unsigned char*password);
int    IC_ChangePass_102(int idComDev,unsigned char*password);
int    IC_CheckAZPass_102(int idComDev,int zone, unsigned char*password);
int    IC_ChangeAZPass_102(int idComDev,int zone,unsigned char*password);
int    IC_CheckPass_102hex(int idComDev,unsigned char*password);
int    IC_ChangePass_102hex(int idComDev,unsigned char*password);
int    IC_CheckAZPass_102hex(int idComDev,int zone, unsigned char*password);
int    IC_ChangeAZPass_102hex(int idComDev,int zone,unsigned char*password);
int    IC_Fuse_1604(int idComDev);
int    IC_ReadCount_1604(int idComDev,int area);
int    IC_CheckPass_1604(int idComDev,int area,unsigned char*password);
int    IC_ChangePass_1604(int idComDev,int area,unsigned char*password);
int    IC_CheckPass_1604hex(int idComDev,int area,unsigned char*password);
int    IC_ChangePass_1604hex(int idComDev,int area,unsigned char*password);
int    IC_Fuse_4404(int icdev);
int    IC_ReadCount_4404(int icdev);
int    IC_CheckPass_4404(int idComDev,unsigned char *password);
int    IC_ChangePass_4404(int idComDev,unsigned char *password);
int    IC_CheckAZPass_4404(int idComDev,unsigned char *password);
int    IC_ChangeAZPass_4404(int idComDev,unsigned char*password);
int    IC_CheckPass_4404hex(int idComDev,unsigned char *password);
int    IC_ChangePass_4404hex(int idComDev,unsigned char *password);
int    IC_CheckAZPass_4404hex(int idComDev,unsigned char *password);
int    IC_ChangeAZPass_4404hex(int idComDev,unsigned char*password);
int    IC_ReadCount_4406(int icdev);
int    IC_CheckPass_4406(int idComDev,unsigned char *password);
int    IC_Erase_4406(int idComDev,unsigned char offset);
int    IC_CheckPass_4406hex(int idComDev,unsigned char *password);
int    IC_Write24(int idComDev,int offset,int len,unsigned char *writebuffer);
int    IC_Write64(int idComDev,int offset,int len,unsigned char *writebuffer);
int    IC_Write_Hex(int idComDev,int offset,int len,unsigned char *writebuffer);
int    IC_Read_Hex(int idComDev,int offset,int len,unsigned char * databuffer);
int    IC_Write24_Hex(int idComDev,int offset,int len,unsigned char *writebuffer);
int    IC_Write64_Hex(int idComDev,int offset,int len,unsigned char *writebuffer);
int    IC_DirectRead(int idComDev,int page,int offset,int bytes,unsigned char *buff);
int    IC_DirectWrite(int idComDev,int page,int offset,int bytes,unsigned char *buff);
int    IC_DirectRead_Hex(int idComDev,int page,int offset,int bytes,unsigned char *buff);
int    IC_DirectWrite_Hex(int idComDev,int page,int offset,int bytes,unsigned char *writebuffer);
int    IC_Fuse_1604B(int idComDev);
int    IC_ReadCount_1604B(int idComDev,int area);
int    IC_ChangePass_1604B(int idComDev,int area,unsigned char*password);
int    IC_CheckPass_1604B(int idComDev,int area,unsigned char*password);
int    IC_ChangePass_1604Bhex(int idComDev,int area,unsigned char*password);
int    IC_CheckPass_1604Bhex(int idComDev,int area,unsigned char*password);
int    IC_Read_1101(int idComDev,int page,int offset,int bytes,unsigned char *buff);
int    IC_Write_1101(int idComDev,int page,int offset,int bytes,unsigned char *buff);
int    IC_Read_1101hex(int idComDev,int page,int offset,int bytes,unsigned char *buff);
int    IC_Write_1101hex(int idComDev,int page,int offset,int bytes,unsigned char *buff);
int    hex2asc(unsigned char *strhex,unsigned char *strasc,int length);
int    asc2hex(unsigned char *strasc,unsigned char *strhex,int length);


int  IC_GetInputPass(HANDLE idComDev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass);
int IC_Request(int idComDev,BYTE _bMode,
						   int *_wTagType);
int IC_Anticoll(int idComDev,BYTE _bBcnt,
							DWORD *_dwSnr);
int IC_Select(int idComDev,DWORD _dwSnr,
						  BYTE *_bSize);
int IC_Authentication(int idComDev,BYTE _bMode,
								  BYTE _bSecNr);
int IC_Halt(int idComDev);
int IC_ReadMifare(int idComDev,BYTE _bAdr,
						BYTE *_bData);
int IC_ReadMifare_Hex(int idComDev,BYTE _bAdr,
								BYTE *_bData);
int IC_WriteMifare(int idComDev,BYTE _bAdr,
						 BYTE *_bData);
int IC_WriteMifare_Hex(int idComDev,BYTE _bAdr,
								 BYTE *_bData);
int IC_Transfer(int idComDev,BYTE _bAdr);
int IC_Restore(int idComDev,BYTE _bAdr);
int IC_Increment(int idComDev,BYTE _bAdr,
							 DWORD _dwValue);
int IC_Decrement(int idComDev,BYTE _bAdr,
							 DWORD _dwValue);
int IC_Load_Key(int idComDev,BYTE _bMode,BYTE _bSecNr,unsigned char *_bNKey);
int IC_Load_Keyhex(int idComDev,BYTE _bMode,BYTE _bSecNr,unsigned char *_bNKey);
int IC_ResetMifare(int idComDev,int _wMsec);
int IC_Init_Value(int idComDev,BYTE _bAdr);
int IC_Read_Value(int idComDev,BYTE _bAdr,
							  long *_lValue);
int IC_Card(int icdev,unsigned char _Mode,unsigned long *_Snr);
int IC_Card_Hex(int icdev,unsigned char _Mode,unsigned char *snrstr);
int IC_Authentication_Passaddr(int icdev,unsigned char _Mode,
											 unsigned char _Addr,unsigned char *passbuff);
int IC_Authentication_Passaddrhex(int icdev,unsigned char _Mode,
												 unsigned char _Addr,unsigned char *passbuff);
int  IC_ReadReaderSnr(int idComDev,unsigned char *snr);
int  IC_ResetDevice(int idComDev);
int  IC_ReadMagCard(int idComDev, unsigned char ctime, unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
int  IC_PosBeep(int idComDev,unsigned char beeptime);
int  IC_DispInfoEn(int idComDev,unsigned char line,unsigned char offset,char *data);
int  IC_DispInfo(int idComDev,unsigned char line,unsigned char offset,char *data);
int IC_DispLcd(int icdev,unsigned char type);
int  IC_ReadDevSnr(int idComDev,unsigned char *snr);
int  IC_GetReaderTime(int idComDev,
									 unsigned char *year,
									 unsigned char *month,
									 unsigned char *date,
									 unsigned char *hour,
									 unsigned char *minute,
									 unsigned char *second);


int  IC_GetDeviceTime(int idComDev,
									 unsigned char *year,
									 unsigned char *month,
									 unsigned char *date,
									 unsigned char *hour,
									 unsigned char *minute,
									 unsigned char *second);


int IC_LcdClrScrn(HANDLE idComDev, unsigned char cLine);
__int16    IC_DispMainMenu(HANDLE idComDev);
__int16    IC_PassIn(HANDLE idComDev,unsigned char ctime);
__int16    IC_PassGet(HANDLE idComDev,unsigned char *rlen,unsigned char * cpass);
__int16    IC_PassCancel(HANDLE idComDev);
int  IC_DispMainInfo(int idComDev,unsigned char offset,char *data);
__int16    IC_GetInputKey(HANDLE idComDev,unsigned char disptype,unsigned char line,
						unsigned char ctime,unsigned char *rlen,unsigned char * ckeydata);
__int16  IC_SetKbKeyID(HANDLE idComDev,unsigned char keyID)	;

__int16  IC_Pro_Reset(HANDLE icdev,unsigned char *rlen,unsigned char *receive_data);
__int16  IC_Pro_Commandsource(HANDLE idComDev,unsigned char slen,
									   unsigned char * sendbuffer,unsigned char *rlen,
									   unsigned char * databuffer,unsigned char timeout);

__int16  IC_Anticoll2(HANDLE idComDev,BYTE _bBcnt,
							DWORD *_dwSnr);
__int16  IC_Select2(HANDLE idComDev,DWORD _dwSnr,
						  BYTE *_bSize);
__int16  IC_Pro_Resethex(HANDLE icdev,unsigned char *rlen,unsigned char *receive_data);
__int16  IC_Pro_Commandsourcehex(HANDLE idComDev,unsigned char slen,
									   unsigned char * sendbuffer,unsigned char *rlen,
									   unsigned char * databuffer,unsigned char timeout);

__int16  IC_Request_Bhex(HANDLE icdev,unsigned char _Mode,
							   unsigned char AFI, 
							   unsigned char N, 
							   unsigned char *ATQB);
__int16  IC_Attrib_Hex(HANDLE icdev,unsigned char *PUPI, unsigned char CID);
__int16  IC_Pro_Commandlink(HANDLE idComDev,unsigned int slen,
								 unsigned char * sendbuffer,unsigned int *rlen,
								 unsigned char * databuffer,unsigned  char timeout,
								 unsigned char FG);

int IC_CtlBackLight(int icdev, unsigned char cOpenFlag);
									  
									   
	
								   




															 
