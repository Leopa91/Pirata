unit Test102;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFrm102 = class(TForm)
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
  Frm102:TFrm102;
  outbuff:pchar; //输出缓冲区
  inbuff:string; //输入缓冲区
  startadd:smallint;
  length:smallint;
  Password:string;
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm102.Button1Click(Sender: TObject);
begin
 icdev := IC_InitComm(0);                                         //初始化串口一
  If icdev < 0 Then
  begin
      List1.items.Add('IC_InitComm() error!');
     exit;
 end;
 List1.Items.add('IC_InitComm() ok!');
                                                                     //给卡型号
 st := IC_InitType(icdev, 32);
 If st <> 0 Then
 begin
     List1.Items.add('IC_InitType error!');
     Exit;
 End;
 List1.Items.add('IC_InitType ok!');

end;


procedure TFrm102.Button3Click(Sender: TObject);

begin
st := IC_Status(icdev);
 If st <0 Then
 begin
      List1.items.add('Communication error!');
      exit;
 end;
 List1.items.add('IC_Status() ok!');

 If st = 1
 Then
      List1.items.add('No card!')
 else
       List1.items.add('Card in Reader!');

    st := IC_ReadCount_102(icdev);                                //读错误计数器
    If st < 0 Then begin
       List1.Items.add ('Read Card Count Error!');
       Exit;
    end;
    List1.Items.add ('Read Card Count OK! The Count is ' + inttostr(st));


    Password := 'F0F0';
    st := IC_CheckPass_102hex(icdev, pchar(Password));                //核对密码
    If st < 0 Then begin
       List1.Items.add ('Check Card Password Error!');
       Exit;
    end;
    List1.Items.add ('Check Card Password OK!');


                                                                //校验应用区密码
    Password := 'FFFFFFFFFFFF';
    st := IC_CheckAZPass_102hex(icdev, 1, pchar(Password));
    If st < 0 Then begin
        List1.Items.add ('Check Card AZ 1 Password Error!');
        Exit;
    end;
    List1.Items.add ('Check Card AZ 1 Password OK!');

    startadd:= 23;
    length := 63;
    inbuff:=StringOfChar('F',126);

     //写数据，只有擦除后才能写卡
    st:= IC_Write_Hex(icdev, startadd, length, pchar(inbuff));
    If st < 0 Then begin
        List1.Items.add ('Write Card Error!');
        Exit;
    end;
    List1.Items.add ('Write Card OK!');

    application.ProcessMessages;

    startadd := 23;
    length := 63;
    inbuff:=StringOfChar('A',126);
    st:= IC_Write_Hex(icdev, startadd, length, pchar(inbuff));
    If st < 0 Then begin
        List1.Items.add ('Write Card Error!');
        Exit;
    end;
    List1.Items.add ('Write Card OK!');
    application.ProcessMessages;

    getmem(outbuff,200);
    st:= IC_Read_Hex(icdev, startadd, length,outbuff);
    If st < 0 Then begin
        List1.Items.add ('Read Card Error!');
        freemem(outbuff);
        Exit;
    end;
    List1.Items.add ('Read Card OK!');
    application.ProcessMessages;

    If copy(inbuff,1,length * 2) = copy(outbuff, 1, length * 2) Then
       List1.Items.add ('Comp Read Data and Write Data OK!')
    Else
       List1.Items.add ('Comp Read Data and Write Data Error!');
        freemem(outbuff);

    application.ProcessMessages;

    startadd:= 93;
    length:= 63;

    Password:='FFFFFFFF';
    st:= IC_CheckAZPass_102hex(icdev, 2,pchar(Password));
    If st < 0 Then begin
        List1.Items.add ('Check Card AZ 2 Password Error!"');
        Exit;
    end;
    List1.Items.add ('Check Card AZ 2 Password OK!');
    application.ProcessMessages;

    inbuff:=StringOfChar('F',126);
    st:= IC_Write_Hex(icdev, startadd, length, pchar(inbuff));
    If st < 0 Then begin
        List1.Items.add ('Write Card Error!');
        Exit;
    end;

    List1.Items.add ('Write Card OK!');
    application.ProcessMessages;

    inbuff:=StringOfChar('A',126);
    st:= IC_Write_Hex(icdev, startadd, length, pchar(inbuff));
    If st < 0 Then begin
        List1.Items.add ('Write Card Error!');
        Exit;
    end;
    List1.Items.add ('Write Card OK!');
    application.ProcessMessages;

    getmem(outbuff,200);                                                //read
    st:= IC_Read_Hex(icdev, startadd, length,outbuff);
    If st < 0 Then begin
        List1.Items.add ('Read Card Error!');
        freemem(outbuff);
        Exit;
    end;
    List1.Items.add ('Read Card OK!');
    application.ProcessMessages;

    If copy(inbuff,1,length * 2) = copy(outbuff, 1, length * 2) Then
       List1.Items.add ('Comp Read Data and Write Data OK!')
    Else
       List1.Items.add ('Comp Read Data and Write Data Error!');
    freemem(outbuff);
    application.ProcessMessages;

                                                                      //change password
    Password:='F0F0';
    st:= IC_ChangePass_102hex(icdev,pchar(Password));
    If st < 0 Then begin
        List1.Items.add ('Change Card Password Error!');
        Exit;
    end;
    List1.Items.add ('Change Card Password Ok!');


    st:=IC_Down(icdev);                                               //power down
    If st < 0 Then begin
        List1.Items.add ('IC_Down Error!');
        Exit;
    end;
    List1.Items.add ('IC_Down Ok!');
    List1.Items.add ('Test Ok!');

end;

procedure TFrm102.Button4Click(Sender: TObject);
begin
if icdev>0 then begin
 st := IC_ExitComm(icdev);                                            //exit
 end;
 close
end;

end.
