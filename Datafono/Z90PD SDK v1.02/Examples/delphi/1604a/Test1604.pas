unit Test1604;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TFrm1604 = class(TForm)
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
  Frm1604:TFrm1604;
  outbuff:pchar; //���������     ��ע�����ﶼ���� pchar����
  inbuff:pchar; //���뻺����      ��ע�����ﶼ���� pchar����
  startadd:smallint;
  length:smallint;
  Password:string;
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm1604.Button1Click(Sender: TObject);
begin
 icdev := IC_InitComm(0);                                         //��ʼ������һ
  If icdev < 0 Then begin
      List1.items.Add('IC_InitComm() error!');
     exit;
 end;
 List1.Items.add('IC_InitComm() ok!');

 st := IC_InitType(icdev, 160);   //���ÿ�����Ϊ1604���ͣ���ע��˺��������������⿨
 If st <> 0 Then begin
     List1.Items.add('IC_InitType error');
     Exit;
 End;
 List1.Items.add('IC_InitType ok');

end;


procedure TFrm1604.Button3Click(Sender: TObject);

begin
 st := IC_Status(icdev);                          //�ж϶�д����״̬�Ϳ��Ƿ����
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
       
    st:= IC_ReadCount_1604(icdev,0);       //�������������1604��������������8
    If st < 0 Then begin
       List1.Items.add ('Read Card Count Error!');
       Exit;
    end;
    List1.Items.add ('Read Card Count OK! The Count is ' + inttostr(st));


    Password := 'F0F0';
    st := IC_CheckPass_1604hex(icdev,0, pchar(Password));   //�˶Կ������룬��HEX��ʽ
    If st < 0 Then begin
       List1.Items.add ('Check Card Password Error!');
       Exit;
    end;
    List1.Items.add ('Check Card Password OK!');


    getmem(inbuff,200);                 //����һ��Ҫ����ռ䣬��СҪ���ݾ������
    edit1.text:=Trim(edit1.text);

    startadd:= 33;
    length:=edit1.GetTextLen;
    strcopy(inbuff,pchar(edit1.text));

     st:=IC_Erase(icdev,startadd,length);       //��ע�⣬д��ǰҪ�����߳��Ĺ���
    If st <> 0 Then begin
       List1.Items.add ('IC_Erase Error!');
       Exit;
    end;
    List1.Items.add ('IC_Erase OK!');

    st:= IC_Write(icdev, startadd, length, inbuff);    //����ʹ����ͨ��д��ʽ������д�뺺��
    If st < 0 Then begin
        List1.Items.add ('Write Card Error!');
        freemem(inbuff);                        //��ע���κγ�����ڶ�Ҫ�ͷſռ�
        Exit;
    end;
    List1.Items.add ('Write Card OK!');



    getmem(outbuff,200);
    st:= IC_Read(icdev, startadd, length,outbuff);    //����ʹ����ͨ�Ķ���ʽ�����Զ�������ʾ����
    If st < 0 Then begin
        List1.Items.add ('Read Card Error!');
        freemem(outbuff);                             //��ע���κγ�����ڶ�Ҫ�ͷſռ�
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

    Password:='F0F0';
    st:= IC_ChangePass_1604hex(icdev,0,pchar(Password));     //�Ŀ������룬��HEX��ʽ��
    If st < 0 Then begin
        List1.Items.add ('Change Card Password Error!');
        Exit;
    end;
    List1.Items.add ('Change Card Password Ok!');


    st:=IC_Down(icdev);            //�µ����Ҫ���º˶�����ſ��Բ������޸ĺ������Ҳ��Ч��
                                   //������µ磬����һֱ�����ں˶Թ������״̬����ʱ��˶��κ�����
                                   //���᷵����ȷ���������Ҫ�øĺ�������Ч����ע���µ������
    If st < 0 Then begin
        List1.Items.add ('IC_Down Error!');
        Exit;
    end;
    List1.Items.add ('IC_Down Ok!');
    List1.Items.add ('Test Ok!');

end;

procedure TFrm1604.Button4Click(Sender: TObject);
begin
if icdev>0 then begin
 st := IC_ExitComm(icdev);              //�رմ��ڣ������������������ִ�еĲ���
 icdev:=0;
 end;
 close
end;

end.
