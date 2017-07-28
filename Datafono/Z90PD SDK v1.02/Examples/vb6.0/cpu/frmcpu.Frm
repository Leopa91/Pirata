VERSION 5.00
Begin VB.Form frmcpu 
   Appearance      =   0  'Flat
   AutoRedraw      =   -1  'True
   BackColor       =   &H00C0C0C0&
   Caption         =   "CPU TEST"
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
   Begin VB.Frame Frame1 
      BackColor       =   &H00C0C0C0&
      Height          =   2175
      Left            =   5680
      TabIndex        =   4
      Top             =   120
      Width           =   1695
      Begin VB.OptionButton Option4 
         Caption         =   "SAM2"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   1680
         Width           =   1095
      End
      Begin VB.OptionButton Option3 
         Caption         =   "SAM1"
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   1200
         Width           =   1095
      End
      Begin VB.OptionButton Option2 
         Caption         =   "SAM(附卡座)"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   720
         Width           =   1455
      End
      Begin VB.OptionButton Option1 
         Caption         =   "CPU(主卡座)"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Value           =   -1  'True
         Width           =   1455
      End
   End
   Begin VB.CommandButton cpu 
      Caption         =   "CPU"
      Height          =   495
      Left            =   6000
      TabIndex        =   3
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CommandButton Command3 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "End"
      Height          =   495
      Left            =   6000
      TabIndex        =   2
      Top             =   3480
      Width           =   1215
   End
   Begin VB.ListBox List1 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFF00&
      Height          =   3735
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   5535
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Init Ic"
      Height          =   495
      Left            =   6000
      TabIndex        =   0
      Top             =   2520
      Width           =   1215
   End
End
Attribute VB_Name = "frmcpu"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim st%
Dim cardtype As Integer
Dim cardcircle As Integer '循环次数


Private Sub Command1_click()
   icdev = IC_InitComm(0) 'Init COM1
    If icdev <= 0 Then
      List1.AddItem ("Init COM Error!")
      List1.Selected(List1.ListCount() - 1) = True
      Exit Sub
    End If
     List1.AddItem ("Init COM OK!")
    '''''''''''''''''''''''''''''''''''''''''''''''''
    'ic_inittype.
    st = IC_InitType(ByVal icdev&, cardtype)
    If st < 0 Then
        List1.AddItem "ic_inittype() is error! Return: " + Str(st)
      List1.Selected(List1.ListCount() - 1) = True
        Exit Sub
    Else
        List1.AddItem "ic_inittype() is ok!"
    End If
    
      List1.Selected(List1.ListCount() - 1) = True
End Sub



Private Sub Command3_click()
If icdev > 0 Then
st = IC_ExitComm(icdev)
icdev = 0
End If
End
End Sub

Private Sub cpu_Click()
Dim data1 As String * 100
Dim data2 As String * 100
Dim key As String * 100
Dim slen As Byte
Dim rlen As Byte
List1.AddItem "Begin test,please waiting...."
List1.Selected(List1.ListCount() - 1) = True

st = IC_Status(ByVal icdev&)
If st < 0 Then
    List1.AddItem "0: ic_status is error! Return: " + Str(st)
    List1.Selected(List1.ListCount() - 1) = True
    Exit Sub
Else
    List1.AddItem "0: ic_status is ok!"
End If

cardcircle = 20
For i = 0 To cardcircle
List1.AddItem Str(i)
List1.Selected(List1.ListCount() - 1) = True
DoEvents
st = IC_CpuReset_Hex(ByVal icdev, rlen, data1)
If st <> 0 Then
      List1.AddItem ("调用 IC_CpuReset函数出错")
      List1.Selected(List1.ListCount() - 1) = True
      Exit Sub
End If
List1.AddItem ("调用 IC_CpuReset()函数成功")
List1.AddItem data1


slen = 5
data1 = "0084000006"
st = IC_CpuApdu_Hex(icdev, ByVal slen, ByVal data1, rlen, ByVal data2)
If st <> 0 Then
      List1.AddItem ("调用 IC_CpuApdu函数出错")
      List1.Selected(List1.ListCount() - 1) = True
      Exit Sub
End If
List1.AddItem ("调用 IC_CpuApdu()函数成功")
List1.AddItem data2
Next i

key = "5741544348444155"
st = IC_Decrypt_Hex(key, data2, 8, data1)
If st = 0 Then
List1.AddItem data2
List1.AddItem data1
Else
List1.AddItem "decrypt error"
List1.Selected(List1.ListCount() - 1) = True
Exit Sub
End If
st = IC_Encrypt_Hex(key, data1, 8, data2)
If st = 0 Then
List1.AddItem data1
List1.AddItem data2
Else
List1.AddItem "encrypt error"
List1.Selected(List1.ListCount() - 1) = True
Exit Sub
End If

'
'key = "4154696d65434f55"
'st = IC_Decrypt_Hex(key, data2, 8, data1)
'If st = 0 Then
'List1.AddItem data2
'List1.AddItem data1
'Else
'List1.AddItem "decrypt error"
'List1.Selected(List1.ListCount() - 1) = True
'Exit Sub
'End If


st = IC_Down(icdev)
If st <> 0 Then
      List1.AddItem ("调用 IC_Down 函数出错")
      List1.Selected(List1.ListCount() - 1) = True
      Exit Sub
End If
List1.AddItem ("调用 IC_Down 函数成功")
List1.Selected(List1.ListCount() - 1) = True
End Sub

Private Sub Form_Load()

cardtype = 12

End Sub

Private Sub Form_Unload(Cancel As Integer)
If icdev > 0 Then
   st = IC_ExitComm(icdev)
End If
End Sub

Private Sub List1_DblClick()
List1.Clear
List1.Refresh

End Sub

Private Sub Option1_Click()
cardtype = 12
End Sub

Private Sub Option2_Click()
cardtype = 13
End Sub

Private Sub Option3_Click()
cardtype = 14
End Sub

Private Sub Option4_Click()
cardtype = 15
End Sub
