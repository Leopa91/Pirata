Attribute VB_Name = "Module1"
Global icdev As Long
'example for add_s to DCIC32.DLL
Declare Function add_s Lib "dcic32.dll" (ByVal i%) As Integer
'des
Declare Function IC_Encrypt_Hex Lib "dcic32.dll" (ByVal key$, ByVal s$, ByVal le%, ByVal d$) As Integer
Declare Function IC_Decrypt_Hex Lib "dcic32.dll" (ByVal key$, ByVal s$, ByVal le%, ByVal d$) As Integer
'useful function.
Declare Function IC_InitComm Lib "dcic32.dll" (ByVal Port%) As Long
Declare Function IC_ExitComm% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_Down% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_Pushout% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_InitType% Lib "dcic32.dll" (ByVal icdev As Long, ByVal TypeNo%)
Declare Function IC_Status% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_Erase% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal l%)
Declare Function IC_Read% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal Databuffer$)
Declare Function IC_Read_Hex% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal Databuffer$)
Declare Function IC_Read_Float% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, fdata As Single)
Declare Function IC_Read_Int% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, fdata As Long)
Declare Function IC_Write% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal length%, ByVal Databuffer$)
Declare Function IC_Write_Hex% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal length%, ByVal Databuffer$)
Declare Function IC_Write_Float% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal fdata As Single)
Declare Function IC_Write_Int% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal fdata As Long)
'4442
Declare Function IC_ReadProtection% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_WriteProtection% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_ReadCount_SLE4442% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_CheckPass_SLE4442% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_CheckPass_SLE4442hex% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_SLE4442% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Password$)
'4428
Declare Function IC_ReadWithProtection% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal l%, ByVal ProtBuffer$)
Declare Function IC_WriteWithProtection% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal l%)
Declare Function IC_ReadCount_SLE4428% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_CheckPass_SLE4428% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_SLE4428% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Password$)
'ATMEL24C
Declare Function IC_Write24% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal length%, ByVal Databuffer$)
Declare Function IC_Write24_Hex% Lib "dcic32.dll" (ByVal icdev As Long, ByVal offset%, ByVal length%, ByVal Databuffer$)
'ATMEL102
Declare Function IC_CheckPass_102% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ChangePass_102% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Password$)
Declare Function IC_ReadCount_102% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_CheckAZPass_102% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Zone%, ByVal Password$)
Declare Function IC_ChangeAZPass_102% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Zone%, ByVal Password$)
Declare Function IC_Erase_102% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Zone%, ByVal offset%, ByVal l%)
Declare Function IC_Fuse_102% Lib "dcic32.dll" (ByVal icdev As Long)
'4406
Declare Function IC_RValue% Lib "dcic32.dll" (ByVal icdev As Long)
Declare Function IC_DEValue% Lib "dcic32.dll" (ByVal icdev As Long, ByVal num%)
'ATMEL1604
Declare Function IC_CheckPass_1604% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Area%, ByVal Password$)
Declare Function IC_ChangePass_1604% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Area%, ByVal Password$)
Declare Function IC_ReadCount_1604% Lib "dcic32.dll" (ByVal icdev As Long, ByVal Area As Integer)
Declare Function IC_Fuse_1604% Lib "dcic32.dll" (ByVal icdev As Long)
'45D041
Declare Function IC_DriectRead% Lib "dcic32.dll" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_DriectWrite% Lib "dcic32.dll" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_WriteByBuffer% Lib "dcic32.dll" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_DriectRead_Hex% Lib "dcic32.dll" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_DriectWrite_Hex% Lib "dcic32.dll" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
Declare Function IC_WriteByBuffer_Hex% Lib "dcic32.dll" (ByVal icdev As Long, ByVal page%, ByVal offset%, ByVal bytes%, ByVal buff$)
'
'CPU card
Declare Function IC_CpuReset_Hex Lib "dcic32.dll" (ByVal icdev As Long, ByRef rlen As Byte, ByVal sdata$) As Integer
Declare Function IC_CpuApdu_Hex Lib "dcic32.dll" (ByVal icdev As Long, ByVal slen%, ByVal senddata$, ByRef rlen As Byte, ByVal recdata As String) As Integer

