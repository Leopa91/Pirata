VERSION 5.00
Begin VB.Form Frm102 
   Appearance      =   0  'Flat
   AutoRedraw      =   -1  'True
   BackColor       =   &H00C0C0C0&
   Caption         =   "AT102 TEST"
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
      Top             =   1560
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
Attribute VB_Name = "Frm102"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim st&

Private Sub Command1_click()
'**********初始化串口一************
    icdev = IC_InitComm(0)
    If icdev <= 0 Then
      List1.AddItem ("Init COM Error!")
      List1.AddItem "icdev=" + Str(icdev)
      List1.Selected(List1.ListCount() - 1) = True
      Exit Sub
    End If
    List1.AddItem ("Init COM ok!")
    
    '*************************告诉读卡器所测卡的型号***************88
    st = IC_InitType(icdev, 32)
    If st = 0 Then
       List1.AddItem "Init Card Type OK!"
    Else
       List1.AddItem "Init Card Type Error!"
       List1.AddItem "st=" + Str(st)
       List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    End If
    
    List1.Selected(List1.ListCount() - 1) = True

End Sub

Private Sub Command2_Click()
    Dim startadd As Integer
    Dim length As Integer
    Dim Password As String * 20
    Dim writestr As String * 512
    Dim readstr As String * 512
    List1.AddItem "开始测试，请等待。。。。。。"
    List1.Selected(List1.ListCount() - 1) = True
    
    st = IC_Status(icdev)                                      'Get Reader Status
    If st < 0 Then
      List1.AddItem ("Reader Status Error!")
      List1.AddItem "st=" + Str(st)
      List1.Selected(List1.ListCount() - 1) = True
      Exit Sub
    End If
    If st = 0 Then
      List1.AddItem "Card in Reader"
    End If
    If st = 1 Then
      List1.AddItem ("NO Card in Reader")
      List1.Selected(List1.ListCount() - 1) = True
      Exit Sub
    End If
    
    DoEvents
     
    st = IC_ReadCount_102(ByVal icdev&)
    If st < 0 Then
       List1.AddItem ("Read Card Count Error!")
       List1.AddItem "st=" + Str(st)
       List1.Selected(List1.ListCount() - 1) = True
      '' Exit Sub
    Else
       List1.AddItem ("Read Card Count OK! The Count is " + Str(st))
    End If
   
    
    Password = "F0F0"
    st = IC_CheckPass_102hex(ByVal icdev&, ByVal Password$)
    If st < 0 Then
       List1.AddItem ("Check Card Password Error!")
       List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    Else
       List1.AddItem ("Check Card Password OK!")
    End If
    
        
    Password = "FFFFFFFFFFFF"
    st = IC_CheckAZPass_102hex(ByVal icdev&, 1, Password)
    If st < 0 Then
        List1.AddItem "Check Card AZ 1 Password Error!"
        List1.Selected(List1.ListCount() - 1) = True
        List1.AddItem "st=" + Str(st)
        Exit Sub
    Else
        List1.AddItem "Check Card AZ 1 Password OK!"
    End If
    '*********************先擦除**********************
    startadd = 23
    length = 63
    writestr = String$(length * 2, "FF")
    st = IC_Write_Hex(ByVal icdev&, startadd, length, Left$(writestr$, length * 2))
    If st < 0 Then
        List1.AddItem "Write Card Error!"
        List1.AddItem "st=" + Str(st)
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Write Card OK!"
    End If
    DoEvents
   '**********************读写数据**********************
    startadd = 23
    length = 63
    writestr = String$(length * 2, "AA")
    st = IC_Write_Hex(ByVal icdev&, startadd, length, Left$(writestr$, length * 2))
    If st < 0 Then
        List1.AddItem "Write Card Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Write Card OK!"
    End If
    DoEvents
    
    st = IC_Read_Hex(ByVal icdev&, startadd, length, readstr)
    If st < 0 Then
        List1.AddItem "Read Card Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Read Card OK!"
        List1.AddItem readstr
    End If
    DoEvents

    If Mid(readstr, 1, length * 2) = Mid(writestr, 1, length * 2) Then
       List1.AddItem "Comp Read Data and Write Data OK!"
    Else
       List1.AddItem "Comp Read Data and Write Data Error!"
       List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    End If
    DoEvents
  
    startadd = 93
    length = 63
    
    Password = "FFFFFFFF"
    st = IC_CheckAZPass_102hex(ByVal icdev&, 2, ByVal Password$)
    If st < 0 Then
        List1.AddItem "Check Card AZ 2 Password Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Check Card AZ 2 Password OK!"
    End If
    DoEvents

    writestr = String$(length * 2, "FF")
    st = IC_Write_Hex(ByVal icdev&, startadd, length, Left$(writestr$, length * 2))
    If st < 0 Then
        List1.AddItem "Write Card Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Write Card OK!"
    End If
    DoEvents
    '*******************在2区写随机数据*******************8
    Dim writedata(63) As Byte
    Dim readdata(63) As Byte
    Dim i As Integer
    For i = 0 To 62
    writedata(i) = Rnd * 255
    Next i
    st = IC_Writehex(ByVal icdev&, startadd, length, writedata(0))
    If st < 0 Then
        List1.AddItem "Write Card Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Write Card OK!"
        st = asc2hex(writedata(0), writestr, length)
        If st <> 0 Then
            List1.AddItem "hex2asc error"
            List1.Selected(List1.ListCount() - 1) = True
            Exit Sub
        End If
    End If
    DoEvents
    Dim readstr1 As String * 512
    st = IC_Readhex(ByVal icdev&, startadd, length, readdata(0))
    If st < 0 Then
        List1.AddItem "Read Card Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Read Card OK!"
        st = asc2hex(readdata(0), readstr, length)
        List1.AddItem readstr
        If st <> 0 Then
            List1.AddItem "hex2asc error"
            List1.Selected(List1.ListCount() - 1) = True
            Exit Sub
        End If
        
    End If
    DoEvents
    
    If Mid(readstr, 1, length * 2) = Mid(writestr, 1, length * 2) Then
       List1.AddItem "Comp Read Data and Write Data OK!"
    Else
       List1.AddItem "Comp Read Data and Write Data Error!"
       List1.Selected(List1.ListCount() - 1) = True
       Exit Sub
    End If
    DoEvents

    Password = "F0F0"
    st = IC_ChangePass_102hex(ByVal icdev&, ByVal Password$)
    If st < 0 Then
        List1.AddItem "Change Card Password Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "Change Card Password Ok!"
    End If
    
    st = IC_Down(ByVal icdev)
    If st < 0 Then
        List1.AddItem "IC_Down Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "IC_Down Ok!"
    End If
    List1.Selected(List1.ListCount() - 1) = True
 
End Sub

Private Sub Command3_click()
If icdev > 0 Then
  st = IC_ExitComm(icdev) 'Close COM
End If
  Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
If icdev > 0 Then
  st = IC_ExitComm(icdev) 'Close COM
End If
End Sub
