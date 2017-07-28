unit Test45d041;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFrm45d041 = class(TForm)
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
  Frm45d041:TFrm45d041;
  outbuff:pchar; //输出缓冲区
  inbuff:string; //输入缓冲区
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm45d041.Button1Click(Sender: TObject);
begin
 icdev := IC_InitComm(0);                                         //初始化串口一
  If icdev < 0 Then begin
      List1.items.Add('IC_InitComm() error!');
     exit;
 end;
 List1.Items.add('IC_InitComm() ok!');

 st := IC_InitType(icdev, 65);                                        //给卡型号
 If st <> 0 Then begin
     List1.Items.add('IC_InitType error!');
     Exit;
 End;
 List1.Items.add('IC_InitType ok!');

end;


procedure TFrm45d041.Button3Click(Sender: TObject);

begin
  st := IC_Status(icdev);
 If st <0 Then begin
      List1.items.add('Communcation error!');
      exit;
 end;
 List1.items.add('IC_Status() ok!');

 If st = 1 Then
      List1.items.add('No card!')
 else
       List1.items.add('Card in Reader!');

 inbuff:='0011223344556677';                                            //写数据
 st := IC_DirectWrite_Hex(icdev,0, 10,8,pchar(inbuff));
 If st <> 0 Then begin
     List1.Items.add('IC_WriteByBuffer_Hex error');
     Exit;
 End;
 List1.Items.add('IC_WriteByBuffer_Hex ok');

 getmem(outbuff,18);
 st := IC_DirectRead_Hex(icdev, 0,10,8,outbuff);                        //读数据
 If st <> 0 Then begin
     List1.Items.add('IC_DirectRead_Hex error');
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('IC_DirectRead_Hex ok');
 outbuff[16]:=chr(0);
 List1.items.add('Data:'+outbuff);
 if copy(inbuff,1,16)<>copy(outbuff,1,16) then begin
 list1.Items.Add('Compare data error');
 FreeMem(outbuff);
 exit;
 end;
 list1.Items.Add('Compare data ok');
 freemem(outbuff);
 List1.Items.add('Test Reader ok!');

end;

procedure TFrm45d041.Button4Click(Sender: TObject);
begin
if icdev>0 then begin
 st := IC_ExitComm(icdev);                                          //关闭串口文
 icdev:=0;
 end;
 close
end;

end.
