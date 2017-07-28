Attribute VB_Name = "Module1"
Declare Function IC_InitCommAdvanced Lib "DCIC32.DLL" (ByVal Port%) As Long
Declare Function IC_InitComm Lib "DCIC32.DLL" (ByVal Port%) As Long
Declare Function IC_ExitComm% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_Down% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_Pushout% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_InitType% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal TypeNo%)
Declare Function IC_Status% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_Erase% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%)
Declare Function IC_Read% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal Databuffer$)
Declare Function IC_Read_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal Databuffer$)
Declare Function IC_Read_Float% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, fdata As Single)
Declare Function IC_Read_Int% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, fdata As Long)
Declare Function IC_Write% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByVal Databuffer$)
Declare Function IC_Write_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByVal Databuffer$)
Declare Function IC_Write_Float% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal fdata As Single)
Declare Function IC_Write_Int% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal fdata As Long)

Declare Function IC_Writehex% Lib "DCIC32.DLL" Alias "IC_Write" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByRef Databuffer As Byte)
Declare Function IC_Readhex% Lib "DCIC32.DLL" Alias "IC_Read" (ByVal icdev As Long, ByVal offset%, ByVal Length%, Databuffer As Byte)
Declare Function asc2hex% Lib "DCIC32.DLL" (ByRef asc As Byte, ByVal hex As String, ByVal Length%)
Declare Function hex2asc% Lib "DCIC32.DLL" (ByVal hex As String, ByRef asc As Byte, ByVal Length%)

Declare Function IC_Write_Chinese% Lib "DCIC32.DLL" Alias "IC_Write" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByRef Databuffer$)
Declare Function IC_Read_Chinese% Lib "DCIC32.DLL" Alias "IC_Read" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByRef Databuffer$)

'4442
Declare Function IC_ReadProtection% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_ReadProtection_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_WriteProtection% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_WriteProtection_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_ReadCount_SLE4442% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_CheckPass_SLE4442% Lib "DCIC32.DLL" (ByVal icdev As Long, Password As Byte)
Declare Function IC_CheckPass_4442hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_SLE4442% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_4442hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
'4428
Declare Function IC_ReadWithProtection% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_WriteWithProtection% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal l%)
Declare Function IC_ReadCount_SLE4428% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_CheckPass_SLE4428% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_SLE4428% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_CheckPass_4428hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_4428hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
'ATMEL24C
Declare Function IC_Write24% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByVal Databuffer$)
Declare Function IC_Write24_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByVal Databuffer$)
Declare Function IC_Write64% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByVal Databuffer$)
Declare Function IC_Write64_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal offset%, ByVal Length%, ByVal Databuffer$)

'ATMEL102
Declare Function IC_CheckPass_102% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_102% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_CheckPass_102hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_102hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ReadCount_102% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_CheckAZPass_102% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Zone%, ByVal Password$)
Declare Function IC_ChangeAZPass_102% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Zone%, ByVal Password$)
Declare Function IC_CheckAZPass_102hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Zone%, ByVal Password$)
Declare Function IC_ChangeAZPass_102hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Zone%, ByVal Password$)
Declare Function IC_Erase_102% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Zone%, ByVal offset%, ByVal l%)
Declare Function IC_Fuse_102% Lib "DCIC32.DLL" (ByVal icdev As Long)
'4406
Declare Function IC_RValue% Lib "DCIC32.DLL" (ByVal icdev As Long)
Declare Function IC_DEValue% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal num%)
'ATMEL1604
Declare Function IC_CheckPass_1604% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Area%, ByVal Password$)
Declare Function IC_ChangePass_1604% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Area%, ByVal Password$)
Declare Function IC_CheckPass_1604hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Area%, ByVal Password$)
Declare Function IC_ChangePass_1604hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Area%, ByVal Password$)
Declare Function IC_ReadCount_1604% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal Area As Integer)
Declare Function IC_Fuse_1604% Lib "DCIC32.DLL" (ByVal icdev As Long)
'45D041
Declare Function IC_DirectRead% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_DirectWrite% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_WriteByBuffer% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_DirectRead_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_DirectWrite_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_WriteByBuffer_Hex% Lib "DCIC32.DLL" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
'
Global icdev As Long  'define COM Handle
