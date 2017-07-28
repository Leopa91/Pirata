unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    lst1: TListBox;
    btn1: TButton;
    procedure btn1Click(Sender: TObject);
  private
    { Private declarations }
      icdev:LongInt;
    st:Integer;
    wMsec:SmallInt;
    mode:SmallInt;
    snr1:pchar;
    secnr:Byte;
    snr2:pchar;
    apdu_slen:SmallInt;
    password:PChar;
    write_data:PChar;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses device;

{$R *.dfm}

procedure TForm1.btn1Click(Sender: TObject);

 var
  read_redata:array [0..32] of char;
  read_redata2:array [0..32] of char;
begin
icdev := IC_Initcomm(100);
if icdev < 0 then
begin
  lst1.Items.Add('IC_InitComm Error');
  Exit;
end;
lst1.Items.Add('IC_InitComm OK');

st:= IC_ResetMifare(icdev, 2);
if st<>0 then
begin
  lst1.Items.Add('IC_ResetMifare Error');
  Exit;
end;
lst1.Items.Add('IC_ResetMifare OK');

GetMem(snr1, 256);
st:= IC_Card(icdev, 0, snr1);
if st<>0 then
begin
  lst1.Items.Add('IC_Card Error');
  exit;
end;
lst1.Items.Add('IC_Card OK');

password:='ffffffffffff' ;
st:=IC_Load_Keyhex(icdev, 0, 0, password);
if st<>0 then
begin
  lst1.Items.Add('IC_Load_Key_Hex Error');
  Exit;
end;
lst1.Items.Add('IC_Load_Key_Hex OK');

 st:= IC_Authentication(icdev, 0, 0);
 if st<>0 then
 begin
   lst1.Items.Add('IC_Authentication Error');
   Exit;
 end;
 lst1.Items.Add('IC_Authentication OK');
GetMem(snr2, 300);
 st:= IC_ReadMifare_Hex(icdev, 0, read_redata);
 if st<>0 then
 begin
   lst1.Items.Add('IC_ReadMifare Error');
   Exit;
 end;
 lst1.Items.Add('IC_ReadMifare OK');
 lst1.Items.Add('the data is:' + read_redata);

 st:= IC_Authentication(icdev, 0, 0);
 if st<>0 then
 begin
   lst1.Items.Add('IC_Authentication Error');
   Exit;
 end;
 lst1.Items.Add('IC_Authentication OK');

 write_data:= '00112233445566778899aabbccddeeff';
 st:=IC_WriteMifare_Hex(icdev, 1, write_data);
 if st<>0 then
 begin
   lst1.Items.Add('IC_WriteMifare_Hex Error');
   Exit;
 end;
 lst1.Items.Add('IC_WriteMifare_Hex OK');

 st:= IC_Authentication(icdev, 0, 0);
 if st<>0 then
 begin
   lst1.Items.Add('IC_Authentication Error');
   Exit;
 end;
 lst1.Items.Add('IC_Authentication OK');

st:= IC_ReadMifare_Hex(icdev, 1, read_redata2);
 if st<>0 then
 begin
   lst1.Items.Add('IC_ReadMifare Error');
   Exit;
 end;
 lst1.Items.Add('IC_ReadMifare OK');
 lst1.Items.Add('the data is:' + read_redata2);

end;
end.

