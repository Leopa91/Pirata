VERSION 5.00
Begin VB.Form Frm1604 
   Appearance      =   0  'Flat
   AutoRedraw      =   -1  'True
   BackColor       =   &H00C0C0C0&
   Caption         =   "at1604 demo"
   ClientHeight    =   4020
   ClientLeft      =   1275
   ClientTop       =   1680
   ClientWidth     =   7365
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form3"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4020
   ScaleWidth      =   7365
   Begin VB.CommandButton Command3 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "End"
      Height          =   495
      Left            =   6000
      TabIndex        =   3
      Top             =   1680
      Width           =   1215
   End
   Begin VB.ListBox List1 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFF00&
      Height          =   3735
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   5655
   End
   Begin VB.CommandButton Command2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Test"
      Height          =   495
      Left            =   6000
      TabIndex        =   1
      Top             =   840
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Init Ic"
      Height          =   495
      Left            =   6000
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "Frm1604"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim st%

Private Sub Command1_click()
    icdev = IC_InitComm(0) 'Init COM1
    If icdev <= 0 Then
        List1.AddItem ("Init COM Error!")
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    End If
    List1.AddItem ("Init COM ok!")
    
    'ic_inittype.
    st = IC_InitType(ByVal icdev&, &HA0)
    If st < 0 Then
        Beep
        Beep
        List1.AddItem "ic_inittype() is error! Return: " + Str(st)
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "ic_inittype() is ok!"
    End If
     
    List1.Selected(List1.ListCount() - 1) = True
End Sub

Private Sub Command2_Click()
    Dim startadd As Integer
    Dim length As Integer
    Dim Databuff As String * 5000
    Dim Password As String * 512
    Dim Writedata As String * 5000
    Dim Password As String * 8
    List1.AddItem "Begin Test,please waiting......."
    List1.Selected(List1.ListCount() - 1) = True
    
     st = IC_Status(icdev) 'Get Reader Status
    If st < 0 Then
         List1.AddItem ("Reader Status Error!")
         List1.Selected(List1.ListCount() - 1) = True
         Exit Sub
    End If
    If st = 0 Then
         List1.AddItem "Card in Reader"
    End If
    If st = 1 Then
        List1.AddItem ("NO Card in Reader")
        Exit Sub
    End If
    
    Password = "F0F0"
    st = IC_CheckPass_1604hex(ByVal icdev&, 0, Password$)
    If st < 0 Then
       Beep
       List1.AddItem "ic_checkpasss(,0,) is error! Return: " + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    Else
       List1.AddItem "ic_checkpasss(,0,) is ok!"
    End If
    'read errorcount
    st = IC_ReadCount_1604(ByVal icdev, 0)
    If st < 0 Then
       List1.AddItem "Error: ic_readcount(,0) is error." + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    Else
       List1.AddItem "ic_readcount(,0) is ok." + Str(st)
    End If
    
    'read password
    st = IC_Read_Hex(ByVal icdev&, 10, 2, ByVal Databuff$)
    x = "F0F0"
    If st = 0 And Left(Databuff, 4) = x Then
       List1.AddItem "ic_read() and the password is ok."
    Else
       List1.AddItem "Error: ic_read() or password is error."
    List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    End If
    
    'write data
    startadd = 27
    length = 1195
    'ÏÈ²Á³ý
    Writedata = String$(length * 2, "f")
'    st = IC_Write_Hex(ByVal icdev&, startadd, length, Left$(Writedata$, length * 2))
    If st < 0 Then
       List1.AddItem "Error: ²Á³ý is error." + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    Else
       List1.AddItem " ²Á³ý is ok."
    End If
    DoEvents
    Writedata = String$(length * 2, "B")
'    st = IC_Write_Hex(ByVal icdev&, startadd, length, Left$(Writedata$, length * 2))
    If st < 0 Then
       List1.AddItem "Error: ic_write() is error." + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    Else
       List1.AddItem " IC_Write_Hex() is ok."
    End If
    DoEvents
    
'    st = IC_Read_Hex(ByVal icdev, startadd, length, ByVal Databuff$)
    If st < 0 Then
        Beep
        List1.AddItem "Error: ic_read error. Return: " + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem " IC_Read_Hex() is ok!"
    End If
    
    
    DoEvents
    
    If Mid(Databuff$, 1, length * 2) = Mid(Writedata$, 1, length * 2) Then
      List1.AddItem "Comp Read Data and Write Data OK!"
    Else
      List1.AddItem "Comp Read Data and Write Data Error!"
    End If
    DoEvents
    '***********Ð´Ëæ»úÊý
    startadd = 1227
    length = 191           '192Ê±£¬ÓÐÍ¨Ñ¶³¬Ê±´íÎó
    'ÏÈ²Á³ý
    Writedata = String$(length * 2, "f")
    st = IC_Write_Hex(ByVal icdev&, startadd, length, Left$(Writedata$, length * 2))
    If st < 0 Then
       List1.AddItem "Error: ²Á³ý is error." + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    Else
       List1.AddItem " ²Á³ý is ok."
    End If
    DoEvents
    
    
    Dim wrdata(256) As Byte, redata(256) As Byte
    Dim i As Integer
    For i = 0 To length - 1
        wrdata(i) = Rnd(-Rnd * Timer) * 255
    Next i
    st = IC_Writehex(ByVal icdev&, startadd, length, wrdata(0))
    If st < 0 Then
       List1.AddItem "Error: ic_writehex() is error." + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    Else
       List1.AddItem " ic_writehex() is ok."
       st = asc2hex(wrdata(0), Writedata, length)
       If st <> 0 Then
        List1.AddItem "hex2asc error"
    List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
       End If
       
    End If
    DoEvents
    
    st = IC_Readhex(ByVal icdev, startadd, length, redata(0))
    If st < 0 Then
        List1.AddItem "Error: ic_readhex error. Return: " + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem " ic_readhex() is ok!"
       st = asc2hex(redata(0), Databuff, length)
       If st <> 0 Then
        List1.AddItem "hex2asc error"
    List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
       End If
       List1.AddItem Databuff
    End If
    
    
    DoEvents
    
    If Mid(Databuff$, 1, length * 2) = Mid(Writedata$, 1, length * 2) Then
      List1.AddItem "Comp Read Data and Write Data OK!"
    Else
      List1.AddItem "Comp Read Data and Write Data Error!"
    End If
    DoEvents
    'change password
    Password = "F0F0"
    st = IC_ChangePass_1604hex(ByVal icdev&, 0, ByVal Password$)
    If st < 0 Then
        Beep
        List1.AddItem "Error: ic_changepass(0,f0f0) error. Return: " + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem " ic_changepass(1,f0f0) ok!"
    End If
    
   st = IC_Down(ByVal icdev&)
    If st < 0 Then
       List1.AddItem "Error: ic_down is error."
       Exit Sub
    Else
       List1.AddItem " ic_down is ok."
    End If
    List1.Selected(List1.ListCount() - 1) = True
End Sub

Private Sub Command3_click()
If icdev > 0 Then
  st = IC_ExitComm(icdev) 'Close COM
  List1.AddItem "exitCom ok"
    List1.Selected(List1.ListCount() - 1) = True
End If
  'Unload Me
End Sub



Private Sub Form_Unload(Cancel As Integer)
If icdev > 0 Then
     st = IC_ExitComm(icdev) 'Close COM
End If
  Unload Me

End Sub

