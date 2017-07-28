object Form1: TForm1
  Left = 195
  Top = 108
  Width = 500
  Height = 272
  Caption = 'CPU_TEST'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 240
    Top = 3
    Width = 121
    Height = 137
    TabOrder = 0
    object RadioButton1: TRadioButton
      Left = 8
      Top = 8
      Width = 97
      Height = 25
      Caption = 'CPU(Main Seat)'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 40
      Width = 105
      Height = 25
      Caption = 'SAM(Affixed Seat)'
      TabOrder = 1
      OnClick = RadioButton2Click
    end
    object RadioButton3: TRadioButton
      Left = 8
      Top = 72
      Width = 81
      Height = 25
      Caption = 'SAM1'
      TabOrder = 2
      OnClick = RadioButton3Click
    end
    object RadioButton4: TRadioButton
      Left = 8
      Top = 104
      Width = 81
      Height = 25
      Caption = 'SAM2'
      TabOrder = 3
      OnClick = RadioButton4Click
    end
  end
  object List1: TListBox
    Left = 0
    Top = 8
    Width = 233
    Height = 233
    ImeName = #20013#25991' ('#31616#20307') - '#26234#33021' ABC'
    ItemHeight = 13
    TabOrder = 1
  end
  object Button1: TButton
    Left = 256
    Top = 152
    Width = 73
    Height = 25
    Caption = 'IC_INIT'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 256
    Top = 184
    Width = 73
    Height = 25
    Caption = 'IC_TEST'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 256
    Top = 216
    Width = 73
    Height = 25
    Caption = 'IC_EXIT'
    TabOrder = 4
    OnClick = Button3Click
  end
end
