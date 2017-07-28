unit Test1608;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFrm1608 = class(TForm)
    List1: TListBox;
    Button1: TButton;
    Button3: TButton;
    Button4: TButton;
    Edit1: TEdit;
    Label1: TLabel;
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
  Frm1608:TFrm1608;
  outbuff:pchar; //输出缓冲区     请注意这里都用了 pchar类型
  inbuff:pchar; //输入缓冲区      请注意这里都用了 pchar类型
  startadd:smallint;
  length:smallint;
  Password:string;
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm1608.Button1Click(Sender: TObject);
begin
 icdev := IC_InitComm(0);                                         //初始化串口一
  If icdev < 0 Then begin
      List1.items.Add('IC_InitComm() error!');
     exit;
 end;
 List1.Items.add('IC_InitComm() ok!');

   st := IC_InitType(icdev, 208);   //设置卡类型为1608卡型，请注意此函数并不是用来测卡
 If st <> 0 Then begin
     List1.Items.add('IC_InitType error');
     Exit;
 End;
 List1.Items.add('IC_InitType ok');

end;


procedure TFrm1608.Button3Click(Sender: TObject);

begin

  st := IC_Status(icdev);                          //判断读写器的状态和卡是否存在
 If st <0 Then begin
      List1.items.add('Communication error!');
      exit;
 end;
 List1.items.add('IC_Status() ok!');

 If st = 1 Then  begin
      List1.items.add('No card!') ;

 end;
       List1.items.add('Card in Reader!');
       exit;

    st:= IC_ReadWPasswordCount(icdev,7);       //读错误记数器，1608卡如果正常情况是8
    If st < 0 Then begin
       List1.Items.add ('Read Card Count Error!');
       Exit;
    end;
    List1.Items.add ('Read Card Count OK! The Count is ' + inttostr(st));


    Password := '343434';
    st := IC_CheckWPassword_Hex(icdev,7, pchar(Password));   //核对卡总密码，用HEX方式
    If st < 0 Then begin
       List1.Items.add ('Check Card Password Error!');
       Exit;
    end;
    List1.Items.add ('Check Card Password OK!');


    getmem(inbuff,200);                 //这里一定要申请空间，大小要根据具体情况
    edit1.text:=Trim(edit1.text);

    startadd:= 33;
    length:=edit1.GetTextLen;
    strcopy(inbuff,pchar(edit1.text));

    st:=IC_SetUserZone(icdev,0);  //设置要操作的用户区
    if st<0 then begin
        list1.items.Add('IC_SetUserZone Error');
        freemem(inbuff);
        Exit;
    end;
    list1.Items.Add('IC_SetUserZone Ok');

    st:= IC_WriteUserZone(icdev, startadd, length, inbuff);    //这里使用普通的写方式，可以写入汉字
    If st < 0 Then begin
        List1.Items.add ('Write Card Error!');
        freemem(inbuff);                        //请注意任何程序出口都要释放空间
        Exit;
    end;
    List1.Items.add ('Write Card OK!');




    getmem(outbuff,200);
    st:= IC_ReadUserZone(icdev, startadd, length,outbuff);    //这里使用普通的读方式，可以读出并显示汉字
    If st < 0 Then begin
        List1.Items.add ('Read Card Error!');
        freemem(outbuff);                             //请注意任何程序出口都要释放空间
        freemem(inbuff);
        Exit;
    end;
    List1.Items.add ('Read Card OK!');
    outbuff[length]:=chr(0);
    List1.Items.add(outbuff);

    If copy(inbuff,1,length ) = copy(outbuff, 1, length ) Then
       List1.Items.add ('Comp Read Data and Write Data OK!')
    Else
       List1.Items.add ('Comp Read Data and Write Data Error!');
    freemem(outbuff);
     freemem(inbuff);



    st:=IC_Down(icdev);            //下电后卡需要重新核对密码才可以操作，修改后的密码也生效了
                                   //如果不下电，卡会一直保持在核对过密码的状态，这时候核对任何密码
                                   //都会返回正确，所以如果要让改后密码生效，请注意下电操作。
    If st < 0 Then begin
        List1.Items.add ('IC_Down Error!');
        Exit;
    end;
    List1.Items.add ('IC_Down Ok!');
    List1.Items.add ('Test Ok!');

end;

procedure TFrm1608.Button4Click(Sender: TObject);
begin
if icdev>0 then begin
 st := IC_ExitComm(icdev);              //关闭串口，这是整个程序结束后执行的操作
 icdev:=0;
 end;
 close
end;

end.
