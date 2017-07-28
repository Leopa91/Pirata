unit Test24c01;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFrm24c01 = class(TForm)
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
  Frm24c01:TFrm24c01;
  outbuff:pchar; //输出缓冲区
  inbuff:string; //输入缓冲区
  source,dest:array[0..16]of char;
  //dd:array[3.....34] of char;
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm24c01.Button1Click(Sender: TObject);
begin
 icdev := IC_InitComm(0);                                         //初始化串口一
  If icdev < 0 Then begin
      List1.items.Add('IC_InitComm() error!');
     exit;
 end;
 List1.Items.add('IC_InitComm() ok!');

 st := IC_InitType(icdev, 64);                                        //给卡型号
 If st <> 0 Then begin
     List1.Items.add('IC_InitType error');
     Exit;
 End;
 List1.Items.add('IC_InitType ok');

end;


procedure TFrm24c01.Button3Click(Sender: TObject);

begin
  st := IC_Status(icdev);
 If st <0 Then begin
      List1.items.add('Communicatioin error!');
      exit;
 end;
 List1.items.add('IC_Status()ok!');

 If st = 1 Then
      List1.items.add('No card!')
 else
       List1.items.add('Card in Reader!');
                                                                               //写卡
 inbuff:='0011223344556677';
 st := IC_Write24_Hex(icdev, 10,8,pchar(inbuff));
 If st <> 0 Then begin
     List1.Items.add('IC_Write24_Hex error');
     Exit;
 End;
 List1.Items.add('IC_Write24_Hex ok');

 getmem(outbuff,18);
 st := IC_Read_hex(icdev, 10,8,outbuff);                                //读数据
 If st <> 0 Then begin
     List1.Items.add('IC_Read_Hex error!');
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('IC_Read_Hex ok');
 outbuff[16]:=chr(0);
 List1.items.add('Data:'+outbuff);
 if copy(inbuff,1,16)<>copy(outbuff,1,16) then begin
 list1.Items.Add('compa data error');
 FreeMem(outbuff);
 Exit;
 end;
 list1.Items.Add('compa data ok ');
 freemem(outbuff);
 application.ProcessMessages ;

 st:=IC_Encrypt('12345678','这是一个测试方式',16,dest);                //DES加密
if st<>0 then
   begin
    List1.items.add('encrypt error');
    exit;
  end
else
  List1.items.add('encrypt ok');
  List1.items.add('encrypt text:'+dest);

st:=IC_Decrypt('12345678',dest,16,source);                             //DES解密
if st<>0 then
   begin
    List1.items.add('decrypt error');
    exit;
  end
else
  List1.items.add('decrypt ok');
  List1.items.add('decrypt text:'+source);

 List1.Items.add('Test Reader ok!');

end;

procedure TFrm24c01.Button4Click(Sender: TObject);
begin
 st := IC_ExitComm(icdev);
 close
end;

end.
