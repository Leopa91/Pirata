unit Test24c64;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFrm24c64 = class(TForm)
    List1: TListBox;
    Button1: TButton;
    Button3: TButton;
    Button4: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);

  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  icdev:longint;
  st:smallint;
  Frm24c64:TFrm24c64;
  outbuff:pchar; //���������
  inbuff:string; //���뻺����
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm24c64.Button1Click(Sender: TObject);
begin
 icdev := IC_InitComm(0);                                         //��ʼ������һ
  If icdev < 0 Then begin
      List1.items.Add('IC_InitComm() error!');
     exit;
 end;
 List1.Items.add('IC_InitComm() ok!');

 st := IC_InitType(icdev, 192);
 If st <> 0 Then begin                                                //�����ͺ�
     List1.Items.add('IC_InitType error');
     Exit;
 End;
 List1.Items.add('IC_InitType ok');

end;


procedure TFrm24c64.Button3Click(Sender: TObject);

begin
 st := IC_Status(icdev);
 If st <0 Then begin
      List1.items.add('Communication error!');
      exit;
 end;
 List1.items.add('IC_Status() ok!');

 If st = 1 Then
      List1.items.add('No card!')
 else
       List1.items.add('Card in Reader!');
                                                                             ///д����
 inbuff:='0011223344556677';
 st := IC_Write64_Hex(icdev, 10,8,pchar(inbuff));
 If st <> 0 Then begin
     List1.Items.add('IC_Write64_Hex error');
     Exit;
 End;
 List1.Items.add('IC_Write64_Hex ok'+inbuff);

 getmem(outbuff,18);
 st := IC_Read_hex(icdev, 10,8,outbuff);                                //������
 If st <> 0 Then begin
     List1.Items.add('IC_Read_Hex error');
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('IC_Read_Hex ok');
 outbuff[16]:=chr(0);
 List1.items.add('Data:'+outbuff);
 if copy(inbuff,1,16)<>copy(outbuff,1,16) then begin
 list1.Items.Add('comapa data error');
 FreeMem(outbuff);
 Exit;
 end;
 list1.Items.Add('compa data ok');
 freemem(outbuff);

 List1.Items.add('Test Reader ok!');

end;

procedure TFrm24c64.Button4Click(Sender: TObject);
begin
if icdev>0 then begin
 st := IC_ExitComm(icdev);                                            //�رմ���
 icdev:=0;
 end;
 close;
end;

end.
