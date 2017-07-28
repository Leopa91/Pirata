/*
	该程序的使用方法：
	编译Rd600.java，注意Rd600大小写!
	javac Rd600.java
	即可生成Rd600.class
*/
//package dcic;
public class Rd600
{
	/*一个小例子函数，可以做调试用*/
	public int add_s(int i)
	{
		return i+1;
	}
	public native int IC_InitComm(int port);
	public native int IC_ExitComm(int icdev);
	public native int IC_Status(int icdev);
	public native int IC_InitType(int icdev,int ctype);
	//2003-02-11
	public native int IC_Down(int icdev);
	
	
	//2004-12-8
	public native int IC_InitCommAdvanced(int port);
    public native int IC_Reset(int idComDev);
	public native int IC_DevBeep(int icdev,char beeptime);
	public native int IC_ReadVer(int icdev,char[] Ver);
    public native int IC_ReadDevice(int idComDev,short offset,short len, char[] databuffer);
    public native int IC_WriteDevice(int idComDev,short offset,short len, char[] databuffer);
    public native int IC_ReadDevice_Hex(int idComDev,short offset,short len, char[] databuffer);
    public native int IC_WriteDevice_Hex(int idComDev,short offset,short len, char[] databuffer);
    public native int IC_Encrypt( char[] key,char[] ptrSource, short msgLen, char[] ptrDest);
    public native int IC_Decrypt( char[] key,char[] ptrSource, short msgLen, char[] ptrDest);
    public native int IC_Encrypt_Hex( char[] key,char[] ptrSource, short msgLen, char[] ptrDest);
    public native int IC_Decrypt_Hex( char[] key,char[] ptrSource, short msgLen, char[] ptrDest);
    public native int IC_InitComm_Baud(int port,int combaud);
    public native int IC_SetCommTimeout(int lTime_ms,int sTime_ms);
    //cpu
    public native int IC_CpuReset(int idComDev, char[] rlen, char[] databuffer);
    public native int IC_CpuApdu(int idComDev, char slen, char[] sendbuffer,char[] rlen, char[] databuffer);
    public native int IC_CpuApduSource(int idComDev, char slen, char[] sendbuffer,char[] rlen, char[] databuffer);
    public native int IC_CpuReset_Hex(int idComDev, char[] rlen, char[] databuffer);
    public native int IC_CpuApdu_Hex(int idComDev, char slen, char[] sendbuffer,char[] rlen, char[] databuffer);
    public native int IC_CpuApduSource_Hex(int idComDev, char slen, char[] sendbuffer,char[] rlen, char[] databuffer);
    public native int IC_CpuGetProtocol(int idComDev);
    public native int IC_CpuApduRespon(int idComDev, char slen, char[] sendbuffer,char[] rlen, char[] databuffer);
    public native int IC_CpuSetProtocol(int idComDev,char cardp);
    
			
	//4442
	public native int ReadCount_SLE4442(int icdev);
	public native int CheckPass_4442hex(int icdev,char[] data);
	public native int ChangePass_4442hex(int icdev,char[] data);
	public native int CheckPass_SLE4442(int icdev,char[] data);
	public native int ChangePass_SLE4442(int icdev,char[] data);
	//2004-12-8
	public native int ReadPass_SLE4442(int icdev,char[] data);
	public native int ReadPass_4442hex(int icdev,char[] data);
	public native int ReadWithProtection_SLE4442(int icdev, short offset,short len,char[] data);
	public native int WriteWithProtection_SLE4442(int icdev, short offset,short len,char[] data);	
	//
	
	//4428
	public native int ReadCount_SLE4428(int icdev);
	public native int CheckPass_4428hex(int icdev,char[] data);
	public native int ChangePass_4428hex(int icdev,char[] data);
	public native int CheckPass_SLE4428(int icdev,char[] data);
	public native int ChangePass_SLE4428(int icdev,char[] data);
	//2004-12-8
	public native int ReadWithProtection_SLE4428(int icdev, short offset,short len,char[] data);
	public native int WriteWithProtection_SLE4428(int icdev, short offset,short len,char[] data);	
	//
	
	public native int IC_Read_Hex(int icdev,int offset,int len,char[] databuf);
	public native int IC_Read(int icdev,int offset,int len,char[] databuf);
	public native int IC_Write_Hex(int icdev,int offset,int len,char[] data);
	public native int IC_Write(int icdev,int offset,int len,char[] data);	
	
	//102 2004-12-8
    public native int IC_Erase(int idComDev,short offset,short len);
    public native int IC_Erase_102(int idComDev,short offset,short len);
    public native int IC_Fuse_102(int idComDev);
    public native int IC_ReadCount_102(int idComDev);
    public native int IC_CheckPass_102(int idComDev,char[] password);
    public native int IC_ChangePass_102(int idComDev,char[] password);
    public native int IC_CheckAZPass_102(int idComDev,short zone, char[] password);
    public native int IC_ChangeAZPass_102(int idComDev,short zone, char[] password);
    public native int IC_CheckPass_102hex(int idComDev,char[] password);
    public native int IC_ChangePass_102hex(int idComDev,char[] password);
    public native int IC_CheckAZPass_102hex(int idComDev,short zone, char[] password);
    public native int IC_ChangeAZPass_102hex(int idComDev,short zone, char[] password);


	/*24系列卡专用*/
	public native int IC_Write24_Hex(int icdev,int offset,int len,char[] data);	
	public native int IC_Write24(int icdev,int offset,int len,char[] data);
	//2004-12-8
	public native int IC_Write64_Hex(int icdev,int offset,int len,char[] data);	
	public native int IC_Write64(int icdev,int offset,int len,char[] data);
	
	
	//45DB041 2004-12-8
	public native int IC_DirectRead(int idComDev,short page,short offset,short bytes,char[] buff);
	public native int IC_DirectWrite(int idComDev,short page,short offset,short bytes,char[] buff);
	public native int IC_DirectRead_Hex(int idComDev,short page,short offset,short bytes,char[] buff);
	public native int IC_DirectWrite_Hex(int idComDev,short page,short offset,short bytes,char[] buff);
	
//SSF1101 2004-12-8
	public native int IC_Read_1101(int idComDev,short page,short offset,short bytes,char[] buff);
	public native int IC_Write_1101(int idComDev,short page,short offset,short bytes,char[] buff);
	public native int IC_Read_1101hex(int idComDev,short page,short offset,short bytes,char[] buff);
	public native int IC_Write_1101hex(int idComDev,short page,short offset,short bytes,char[] buff);
//
	
//4404 2004-12-8
	public native int IC_Fuse_4404(int icdev);
	public native int IC_ReadCount_4404(int icdev);
	public native int IC_CheckPass_4404(int idComDev, char[] password);
	public native int IC_ChangePass_4404(int idComDev, char[] password);
	public native int IC_CheckAZPass_4404(int idComDev, char[] password);
	public native int IC_ChangeAZPass_4404(int idComDev, char[] password);
	public native int IC_CheckPass_4404hex(int idComDev, char[] password);
	public native int IC_ChangePass_4404hex(int idComDev, char[] password);
	public native int IC_CheckAZPass_4404hex(int idComDev, char[] password);
	public native int IC_ChangeAZPass_4404hex(int idComDev, char[] password);
	
	
//4406 2004-12-8
	public native int IC_RValue(int idComDev);
	public native int IC_DEValue(int idComDev,short num);
	public native int IC_Fuse_4406(int icdev, short value);
	public native int IC_ReadCount_4406(int icdev);
	public native int IC_CheckPass_4406(int idComDev, char[] password);
	public native int IC_Erase_4406(int idComDev, char offset);
	public native int IC_CheckPass_4406hex(int idComDev, char[] password);
	public native int IC_CheckPass_4406userhex(int idComDev, char[] password);
	public native int IC_CheckPass_4406user(int idComDev, char[] password);

	/*1604卡专用*/
	public native int IC_Fuse_1604(int icdev);
	public native int ReadCount_1604(int icdev,int area);
	public native int CheckPass_1604hex(int icdev,int area,char[] data);
	public native int ChangePass_1604hex(int icdev,int area,char[] data);
	public native int CheckPass_1604(int icdev,int area,char[] data);
	public native int ChangePass_1604(int icdev,int area,char[] data);	
	
	//1604B 2004-12-8
	public native int IC_Fuse_1604B(int icdev);
	public native int IC_ReadCount_1604B(int icdev,int area);
	public native int IC_CheckPass_1604Bhex(int icdev,int area,char[] data);
	public native int IC_ChangePass_1604Bhex(int icdev,int area,char[] data);
	public native int IC_CheckPass_1604B(int icdev,int area,char[] data);
	public native int IC_ChangePass_1604B(int icdev,int area,char[] data);		
	
	/*1608 卡专用函数*/
	public native int IC_CheckRPassword_Hex(int icdev,int Zone,char[] Pin);
	public native int IC_CheckWPassword_Hex(int icdev,int Zone,char[] Pin);	
	public native int IC_CheckRPassword(int icdev,int Zone,char[] Pin);
	public native int IC_CheckWPassword(int icdev,int Zone,char[] Pin);
	public native int IC_ChangeRPassword_Hex(int icdev,int Zone,char[] Pin);
	public native int IC_ChangeWPassword_Hex(int icdev,int Zone,char[] Pin);	
	public native int IC_ChangeRPassword(int icdev,int Zone,char[] Pin);
	public native int IC_ChangeWPassword(int icdev,int Zone,char[] Pin);			

	public native int IC_WriteFuse(int icdev,int fusetype);
	public native int IC_ReadFuse(int icdev);
	
	public native int IC_WriteUserZone(int icdev,int offset,int len,char[] data);	
	public native int IC_WriteConfigZone(int icdev,int offset,int len,char[] data);		
	public native int IC_WriteUserZone_Hex(int icdev,int offset,int len,char[] data);	
	public native int IC_WriteConfigZone_Hex(int icdev,int offset,int len,char[] data);	
	public native int IC_ReadUserZone(int icdev,int offset,int len,char[] data);	
	public native int IC_ReadConfigZone(int icdev,int offset,int len,char[] data);		
	public native int IC_ReadUserZone_Hex(int icdev,int offset,int len,char[] data);	
	public native int IC_ReadConfigZone_Hex(int icdev,int offset,int len,char[] data);					
	public native int IC_ReadWPasswordCount(int icdev,int Zone);
	public native int IC_ReadRPasswordCount(int icdev,int Zone);		
	public native int IC_SetUserZone(int icdev,int Zone);	
	
	
//2个工具函数，用于字符串格式的转换   2004-12-8
    public native int hex2asc(char[] strhex, char[] strasc,short len);
    public native int asc2hex(char[] strasc, char[] strhex,short len);		
		
	/**/
	public Rd600()
	{
	
	}
	/*
		包含了动态库Rd600.dll的名字,动态库应该放在系统目录（windows\system32）当前目录！
	*/
	static
	{
		System.loadLibrary( "Rd600" );  
	}
}
