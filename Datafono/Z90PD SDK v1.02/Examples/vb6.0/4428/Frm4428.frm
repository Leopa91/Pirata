VERSION 5.00
Begin VB.Form Frm4428 
   Appearance      =   0  'Flat
   AutoRedraw      =   -1  'True
   BackColor       =   &H00C0C0C0&
   Caption         =   "SLE4428 TEST"
   ClientHeight    =   4020
   ClientLeft      =   1275
   ClientTop       =   1680
   ClientWidth     =   7365
   FillColor       =   &H00C0C0C0&
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00C0C0C0&
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
Attribute VB_Name = "Frm4428"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim st As Integer
Dim le As Long
Dim data As String * 32
Dim offset As Integer
Private Sub Command1_click()
   icdev = IC_InitComm(100) 'Init USB
    If icdev <= 0 Then
        List1.AddItem ("Init COM Error!")
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    End If
     List1.AddItem ("Init COM OK!")
     
    st = IC_InitType(icdev, 4)
    If st = 0 Then
        List1.AddItem "Init Card Type OK!"
    Else
        List1.AddItem "Init Card Type Error!"
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    End If
    List1.Selected(List1.ListCount() - 1) = True
End Sub

Private Sub Command2_Click()
Dim Password As String * 20
Dim readstr As String * 2048
Dim writestr As String * 2048

List1.AddItem "Begin test,please waiting.........."
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
    List1.Selected(List1.ListCount() - 1) = True
    Exit Sub
End If

st = IC_ReadCount_SLE4428(ByVal icdev&)
If st < 0 Then
   List1.AddItem ("Read Card Count Error!") + Str(st)
  List1.Selected(List1.ListCount() - 1) = True
   Exit Sub
Else
   List1.AddItem ("Read Card Count OK!The Count is " + Str(st))
End If
DoEvents

Password = "67C6" 'you may be use different password
st = IC_CheckPass_4428hex(ByVal icdev&, ByVal Password$)
If st < 0 Then
   List1.AddItem ("Check Card Password Error!" + Str(st))
  List1.Selected(List1.ListCount() - 1) = True
   Exit Sub
Else
   List1.AddItem ("Check Card Password OK!")
End If
DoEvents

writestr = String$(224 * 10, "3")
le = 64 '956
offset = 64
st = IC_Write_Hex(ByVal icdev&, offset, le, Left$(writestr$, le * 2))
If st = 0 Then
 List1.AddItem "Write Card OK!"
Else
 List1.AddItem "Write Card Error!"
  List1.Selected(List1.ListCount() - 1) = True
  Exit Sub
End If
DoEvents

st = IC_Read_Hex(ByVal icdev, offset, le, ByVal readstr$)
If st = 0 Then
 List1.AddItem "Read Card OK!"
 List1.AddItem readstr
Else
 List1.AddItem "Read Card Error!"
  List1.Selected(List1.ListCount() - 1) = True
  Exit Sub
End If
DoEvents

If Mid(readstr, 1, le * 2) = Mid(writestr, 1, le * 2) Then
  List1.AddItem "Comp Read Data and Write Data OK!" + Str(le)
Else
  List1.AddItem "Comp Read Data and Write Data Error!"
  Exit Sub
End If
DoEvents

'''''''''Exit Sub

'**********写随机数据**********8
Dim wrdata(1000) As Byte, redata(1000) As Byte
Dim length As Long, wrdatastr As String * 20000, redatastr As String * 20000
Dim i As Integer
offset = 64
length = 956
For i = 0 To length - 1
wrdata(i) = Rnd(-Rnd * Timer) * 255
Next i
st = IC_Writehex(icdev, offset, length, wrdata(0))
If st = 0 Then
 List1.AddItem "Writehex Card OK!"
 st = asc2hex(wrdata(0), wrdatastr, length)
 If st <> 0 Then
 List1.AddItem "asc2hex error"
  List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
 End If
Else
 List1.AddItem "Writehex Card Error!"
  List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
End If
DoEvents
st = IC_Readhex(icdev, offset, length, redata(0))
If st = 0 Then
 List1.AddItem "Readhex Card OK!"
 st = asc2hex(redata(0), redatastr, length)
 If st <> 0 Then
 List1.AddItem "asc2hex error"
  List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
 End If
 List1.AddItem redatastr
Else
 List1.AddItem "Read Card Error!"
  List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
End If
DoEvents

If Mid(redatastr, 1, length * 2) = Mid(wrdatastr, 1, length * 2) Then
  List1.AddItem "Comp Read Data and Write Data OK!,in rnd,length:" + Str(length)
Else
  List1.AddItem "Comp Read Data and Write Data Error!"
  List1.Selected(List1.ListCount() - 1) = True
  Exit Sub
End If
Open "c:\4428.txt" For Output As #1
Write #1, redatastr
Close #1

'******************带保护位写*******
offset = 48
le = 6
data = "decard"
''st = IC_WriteWithProtection(icdev, offset, le, Left(data, 6))   ''!!!!注意： 此函数得慎用，因为此写数据是不可逆得
If st < 0 Then
List1.AddItem "WriteWithProtection Error"
Exit Sub
Else
List1.AddItem "WriteWithProtection Ok"
List1.AddItem data
End If
'****************************带保护位读

'offset = 0
'le = 8
st = IC_ReadWithProtection_Hex(icdev, offset, le, data)
If st < 0 Then
List1.AddItem "readwithprotection Error"
Exit Sub
Else
List1.AddItem "readwitgprotection Ok"
List1.AddItem data
End If
'chang password

Password = "67C6"
st = IC_ChangePass_4428hex(ByVal icdev&, ByVal Password$)
If st < 0 Then
    List1.AddItem "Change Card Password Error!"
    Exit Sub
Else
    List1.AddItem "Change Card Password OK!"
End If

st = IC_Down(ByVal icdev)
If st < 0 Then
    List1.AddItem "IC_Down Error!"
  List1.Selected(List1.ListCount() - 1) = True
    Exit Sub
Else
    List1.AddItem "IC_Down OK!"
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
