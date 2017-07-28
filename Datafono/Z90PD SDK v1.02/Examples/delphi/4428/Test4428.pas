unit Test4428;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFrm4428 = class(TForm)
    List1: TListBox;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
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
  Frm4428:TFrm4428;
  outbuff:pchar; //输出缓冲区
  inbuff:string; //输入缓冲区
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm4428.Button1Click(Sender: TObject);
begin

 icdev := IC_InitComm(0);                                         //初始化串口一
  If icdev < 0 Then begin
      List1.items.Add('IC_InitComm() error!');
     exit;
 end;
 List1.Items.add('IC_InitComm() ok!');

 st := IC_InitType(icdev, 4);                                         //给卡型号
 If st <> 0 Then begin
     List1.Items.add('IC_InitType error');
     Exit;
 End;
 List1.Items.add('IC_InitType ok');

end;

procedure TFrm4428.Button2Click(Sender: TObject);
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

 st := IC_ReadCount_SLE4428(icdev);
 If st < 0 Then begin
     List1.Items.add('IC_ReadCount_SLE4442 error');
     Exit;
 End;

 List1.Items.add('IC_ReadCount_SLE4428 ok');
 List1.Items.add('Error Counter:'+inttostr(st));


 inbuff:='67c6';                                                      //核对密码
 st := IC_CheckPass_4428hex(icdev,pchar(inbuff));
 If st <> 0 Then begin
     List1.Items.add('IC_CheckPass_4428hex error');
     Exit;
 End;

 List1.Items.add('IC_CheckPass_4428hex  ok');

end;

procedure TFrm4428.Button3Click(Sender: TObject);

begin

 inbuff:='001122334455';
 st := IC_Write_hex(icdev, 64,6,pchar(inbuff));                         //写数据
 If st <> 0 Then begin
     List1.Items.add('IC_Write_Hex error');
     Exit;
 End;
 List1.Items.add('IC_Write_Hex ok');

 getmem(outbuff,15);
 st := IC_Read_hex(icdev, 64,6,outbuff);                                //读数据
 If st <> 0 Then begin
     List1.Items.add('IC_Read_Hex error');
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('IC_Read_Hex ok');
 outbuff[12]:=chr(0);
 List1.items.add('Data:'+outbuff);
 if copy(inbuff,1,12)<>copy(outbuff,1,12) then begin
 list1.Items.Add('Compare data error!');
 freemem(outbuff);
 exit;
 end;
 list1.Items.Add('Compare data ok');
 freemem(outbuff);
 inbuff:='67c6';
 st := IC_WriteWithProtection(icdev,2,4,pchar(inbuff));                    //修改密码
 If st <> 0 Then begin
     List1.Items.add('IC_WriteWithProtection error');
     Exit;
 End;
 List1.Items.add('IC_WriteWithProtection ok');
 
 st := IC_ReadWithProtection(icdev,2,4,pchar(inbuff));                    //修改密码
 If st <> 0 Then begin
     List1.Items.add('IC_readWithProtection error');
     Exit;
 End;
 List1.Items.add('IC_readWithProtection ok');
 list1.Items.Add(inbuff);
 
 inbuff:='67c6';
 st := IC_ChangePass_4428hex(icdev,pchar(inbuff));                    //修改密码
 If st <> 0 Then begin
     List1.Items.add('IC_ChangePass_4428hex error');
     Exit;
 End;
 List1.Items.add('IC_ChangePass_4428hex ok');
 List1.Items.add('password of the card is 67c6');


 List1.Items.add('Test Reader ok!');

end;

procedure TFrm4428.Button4Click(Sender: TObject);
begin
if icdev>0 then begin
 st := IC_ExitComm(icdev);                                            //关闭串口
 icdev:=0;
 end;
 close
end;

end.
