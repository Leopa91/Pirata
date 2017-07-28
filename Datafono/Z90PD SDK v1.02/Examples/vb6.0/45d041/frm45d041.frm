VERSION 5.00
Begin VB.Form frm45d041 
   Caption         =   "45D041 DEMO"
   ClientHeight    =   3945
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7365
   FillColor       =   &H00C0C0C0&
   ForeColor       =   &H00C0C0C0&
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   3945
   ScaleWidth      =   7365
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Init Ic"
      Height          =   495
      Left            =   6000
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Test"
      Height          =   495
      Left            =   6000
      TabIndex        =   2
      Top             =   840
      Width           =   1215
   End
   Begin VB.ListBox List1 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFF00&
      Height          =   3540
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   5655
   End
   Begin VB.CommandButton Command3 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "End"
      Height          =   495
      Left            =   6000
      TabIndex        =   0
      Top             =   1560
      Width           =   1215
   End
End
Attribute VB_Name = "frm45d041"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub Command1_Click()
   icdev = IC_InitComm(100) 'Init COM1
    If icdev <= 0 Then
        List1.AddItem ("Init COM Error!")
        List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    End If
     List1.AddItem ("Init COM ok!")
     
    st = IC_InitType(icdev, 65)
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
Dim readstr As String * 600
Dim writestr As String * 600
Dim page As Integer
Dim st As Integer
List1.AddItem "Begin test ,Please waiting......"
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
    

Dim wrdata(264) As Byte, redata(264) As Byte
wtime1 = Timer
Dim length As Integer
''For page = 1 To 1 '2047
length = Rnd(-Rnd * Timer) * 264
'¶ÁÐ´Êý¾Ý
page = Rnd(-Rnd * Timer) * 2047

Dim i As Integer
 For i = 0 To 263
 wrdata(i) = Rnd(-Rnd * Timer) * 255
Next i

st = IC_DirectWritehex(icdev, page, 0, length, wrdata(0))
If st <> 0 Then
 List1.AddItem "Writehex Card Error!page:" + Str(page) + ",length:" + Str(length)
 List1.AddItem Str(st)
 List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
End If
st = asc2hex(wrdata(0), writestr, length)
If st <> 0 Then
 List1.AddItem "asc2hex error" + Str(page)
 List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
End If
st = IC_DirectReadhex(icdev, page, 0, length, redata(0))
If st <> 0 Then
 List1.AddItem "readhex Card Error!" + Str(page) + ",length:" + Str(length)
 List1.AddItem Str(st)
 List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
End If
st = asc2hex(redata(0), readstr, length)
If st <> 0 Then
 List1.AddItem "asc2hex error" + Str(page)
 List1.Selected(List1.ListCount() - 1) = True
 Exit Sub
End If
If Mid(readstr, 1, length * 2) <> Mid(writestr, 1, length * 2) Then
  List1.AddItem "Comp Read Data and Write Data Error!" + Str(page) + ",length:" + Str(length)
    List1.Selected(List1.ListCount() - 1) = True
    Exit Sub
Else
List1.AddItem "Comp Read Data and Write Data Ok!" + Str(page) + ",length:" + Str(length)
    List1.Selected(List1.ListCount() - 1) = True
    
End If
DoEvents
''Next page

wtime2 = Timer

ss = wtime2 - wtime1
'List1.AddItem "write ok"
' List1.AddItem "Read Card OK!"
'List1.AddItem "Comp Read Data and Write Data OK!"
List1.AddItem "time :" + Str(ss)
List1.Selected(List1.ListCount() - 1) = True

End Sub

Private Sub Command3_Click()
    st = IC_ExitComm(icdev) 'Close COM
    Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
st = IC_ExitComm(icdev) 'Close COM
End Sub
