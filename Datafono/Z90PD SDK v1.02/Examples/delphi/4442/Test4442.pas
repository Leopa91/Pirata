unit Test4442;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls;

type
  TFrm4442 = class(TForm)
    List1: TListBox;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Edit3: TEdit;
    Button5: TButton;
    Button6: TButton;
    Label4: TLabel;
    Edit4: TEdit;
    Label5: TLabel;
    Edit5: TEdit;
    Label6: TLabel;
    Edit6: TEdit;
    Button7: TButton;
    Label7: TLabel;
    Label8: TLabel;
    Edit7: TEdit;
    Edit8: TEdit;
    Label9: TLabel;
    Label10: TLabel;
    Edit9: TEdit;
    Edit10: TEdit;
    Button8: TButton;
    Label11: TLabel;
    Edit11: TEdit;
    RadioGroup1: TRadioGroup;
    Button9: TButton;
    Button10: TButton;
    Label12: TLabel;
    Edit12: TEdit;
    Label13: TLabel;
    Edit13: TEdit;
    Label14: TLabel;
    Edit14: TEdit;
    Button11: TButton;
    Edit15: TEdit;
    Label15: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button11Click(Sender: TObject);

  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  icdev:longint;
  st:smallint;
  Frm4442:TFrm4442;
  outbuff:pchar; //输出缓冲区
  inbuff:string; //输入缓冲区
implementation

uses drv_unit;

{$R *.DFM}

procedure TFrm4442.Button1Click(Sender: TObject);
var
  m_icdev:longint;
begin
{ m_icdev:=IC_InitComm_Baud(0,115200);
 IC_ExitComm(m_icdev);
 m_icdev:= 0;   }

if RadioGroup1.ItemIndex =2 then
begin
   icdev := IC_InitComm(100);
end
else if RadioGroup1.ItemIndex =0 then
begin
  icdev := IC_InitComm(0) ;
end
else if RadioGroup1.ItemIndex =1 then
begin
    icdev := IC_InitComm(1);
end;

                                         //初始化串口一
  If icdev < 0 Then begin
      List1.items.Add('调用 IC_InitComm()函数出错!');
      list1.Selected [list1.Items.Count -1]:=true;
     exit;
 end;
 List1.Items.add('调用 IC_InitComm()函数成功!');
 list1.Selected [list1.Items.Count -1]:=true;
                                                                    
 st := IC_InitType(icdev, 16);                                        //给卡型号
 If st <> 0 Then begin
     List1.Items.add('调用 IC_InitType函数出错');
     Exit;
 End;
 List1.Items.add('调用 IC_InitType函数成功');

end;

procedure TFrm4442.Button2Click(Sender: TObject);
begin
 st := IC_Status(icdev);
 If st <0 Then begin
      List1.items.add('读写器存在错误!');
      list1.Selected [list1.Items.Count -1]:=true;
      exit;
 end;
 List1.items.add('调用 IC_Status()函数成功!');
 list1.Selected [list1.Items.Count -1]:=true;
 If st = 1 Then  begin
      List1.items.add('没有卡!')    ;
      list1.Selected [list1.Items.Count -1]:=true;
      exit;
 end ;


 st:= IC_Check_4442(icdev);
 If st < 0 Then begin
     List1.Items.add('调用 IC_Check_4442函数出错');
     list1.Selected [list1.Items.Count -1]:=true;
     Exit;
 End;
   List1.Items.add('调用 IC_Check_4442函数ok');
   list1.Selected [list1.Items.Count -1]:=true;


 st := IC_ReadCount_SLE4442(icdev);
 If st < 0 Then begin
     List1.Items.add('调用 IC_ReadCount_SLE4442函数出错');
     list1.Selected [list1.Items.Count -1]:=true;
     Exit;
 End;
 List1.Items.add('调用 IC_ReadCount_SLE4442函数成功');
 list1.Selected [list1.Items.Count -1]:=true;
 List1.Items.add('错误记数器为'+inttostr(st));
 list1.Selected [list1.Items.Count -1]:=true;

 inbuff:=trim(Edit11.text);             //核对密码
 st := IC_CheckPass_4442hex(icdev,pchar(inbuff));
 If st <> 0 Then begin
     List1.Items.add('调用 IC_CheckPass_4442hex函数出错');
     list1.Selected [list1.Items.Count -1]:=true;
     Exit;
 End;
 List1.Items.add('调用 IC_CheckPass_4442hex函数成功');
 list1.Selected [list1.Items.Count -1]:=true;
end;

procedure TFrm4442.Button3Click(Sender: TObject);

begin

 inbuff:='001122334455';                                                //写数据
 st := IC_Write_hex(icdev, 40,6,pchar(inbuff));
 If st <> 0 Then begin
     List1.Items.add('调用 IC_Write_Hex函数出错');
     Exit;
 End;
 List1.Items.add('调用 IC_Write_Hex函数成功');

 getmem(outbuff,15);                                                    //读数据
 st := IC_Read_hex(icdev, 40,6,outbuff);
 If st <> 0 Then begin
     List1.Items.add('调用 IC_Read_Hex函数出错');
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('调用 IC_Read_Hex函数成功');
 outbuff[12]:=chr(0);
 List1.items.add('数据为:'+outbuff);
 if copy(inbuff,1,12)<>copy(outbuff,1,12) then begin
 list1.Items.Add('比较读数据与写数据错误');
 freemem(outbuff);
 exit;
 end;
 list1.Items.Add('比较读数据与写数据正确');
 freemem(outbuff);

 inbuff:='B62307';                                                    //修改密码
 st := IC_ChangePass_4442hex(icdev,pchar(inbuff));
 If st <> 0 Then begin
     List1.Items.add('调用 IC_ChangePass_4442hex函数出错');
     Exit;
 End;
 List1.Items.add('调用 IC_ChangePass_4442hex函数成功');
 List1.Items.add('卡密码改为B62307');


 List1.Items.add('读写设备测试通过!');

end;

procedure TFrm4442.Button4Click(Sender: TObject);
begin
 if icdev>0 then begin
 st := IC_ExitComm(icdev);                                            //关闭串口
 icdev:=0 ;
 end;
 close();
end;

procedure TFrm4442.Button5Click(Sender: TObject);
begin
 if (Edit1.Text ='')or (Edit2.Text ='') or (Edit3.Text ='') then
 begin
   list1.Items.Add('请输入写卡数据参数！');
   Edit1.SetFocus ;
   exit;
 end;
 st:=IC_Write(icdev,strtoint(Edit3.Text ),strtoint(Edit2.Text ),pchar(trim(Edit1.Text )));
 if st<>0 then
 begin
    list1.Items.Add('写卡错误！');
    list1.Selected [list1.Items.Count -1]:=true;
    exit;
 end ;
  list1.Items.Add('写卡成功！');
  list1.Selected [list1.Items.Count -1]:=true;
end;

procedure TFrm4442.Button7Click(Sender: TObject);
begin
if  (Edit2.Text ='') or (Edit3.Text ='') then
 begin
   list1.Items.Add('请输入读卡数据参数！');   
   exit;
 end;
 getmem(outbuff,100);                                                    //读数据
 st := IC_Read_hex(icdev,  strtoint(Edit3.Text ),strtoint(Edit2.Text ),outbuff);
 If st <> 0 Then begin
     List1.Items.add('调用 IC_Read_Hex函数出错');
     list1.Selected [list1.Items.Count -1]:=true;
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('调用 IC_Read_Hex函数成功');
 List1.items.add('数据为:'+outbuff);
 list1.Selected [list1.Items.Count -1]:=true;
 Edit7.Text :=copy(outbuff,1,strtoint(Edit2.Text )*2);

 getmem(outbuff,100);                                                    //读数据
 st := IC_Read(icdev, strtoint(Edit3.Text ),strtoint(Edit2.Text ),outbuff);
 If st <> 0 Then begin
     List1.Items.add('调用 IC_Read函数出错');
     list1.Selected [list1.Items.Count -1]:=true;
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('调用 IC_Read函数成功');
 List1.items.add('数据为:'+outbuff);
 list1.Selected [list1.Items.Count -1]:=true;
 Edit8.Text :=copy(outbuff,1,strtoint(Edit2.Text ));

end;

procedure TFrm4442.Button6Click(Sender: TObject);
begin
  if (Edit4.Text ='') or (Edit5.Text ='') or (Edit6.Text ='') then
  begin
    list1.Items.Add('请输入写卡数据!');
    list1.Selected [list1.Items.Count -1]:=true;
    exit;
  end;
  st:=IC_Write_hex(icdev,strtoint(Edit6.Text ),strtoint(Edit5.Text ),pchar(trim(Edit4.Text )));
  if st<>0 then
  begin
    list1.Items.Add('写卡错误！');
    list1.Selected [list1.Items.Count -1]:=true;
    exit;
  end ;
  list1.Items.Add('写卡成功！');
  list1.Selected [list1.Items.Count -1]:=true;

end;

procedure TFrm4442.Button8Click(Sender: TObject);
begin
  if  (Edit5.Text ='') or (Edit6.Text ='') then
  begin
    list1.Items.Add('请输入写卡数据!');
    list1.Selected [list1.Items.Count -1]:=true;
    exit;
  end;

 getmem(outbuff,100);                                                    //读数据
 st := IC_Read_hex(icdev,  strtoint(Edit6.Text ),strtoint(Edit5.Text ),outbuff);
 If st <> 0 Then begin
     List1.Items.add('调用 IC_Read_Hex函数出错');
     list1.Selected [list1.Items.Count -1]:=true;
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('调用 IC_Read_Hex函数成功');
 List1.items.add('数据为:'+outbuff);
 list1.Selected [list1.Items.Count -1]:=true;
 Edit9.Text :=copy(outbuff,1,strtoint(Edit5.Text )*2) ;

 getmem(outbuff,100);                                                    //读数据
 st := IC_Read(icdev, strtoint(Edit6.Text ),strtoint(Edit5.Text ),outbuff);
 If st <> 0 Then begin
     List1.Items.add('调用 IC_Read函数出错');
     list1.Selected [list1.Items.Count -1]:=true;
     freemem(outbuff);
     Exit;
 End;
 List1.Items.add('调用 IC_Read函数成功');
 List1.items.add('数据为:'+outbuff);
 list1.Selected [list1.Items.Count -1]:=true;
 Edit10.Text :=copy(outbuff,1,strtoint(Edit5.Text ));
end;

procedure TFrm4442.FormCreate(Sender: TObject);
begin
  Radiogroup1.ItemIndex :=2;
  
end;

procedure TFrm4442.Button9Click(Sender: TObject);
var
 // Devbuffer:array [0..1024] of char;
 // Devbufferhex:array [0..1024] of char;
  Devbuffer,Devbufferhex:pchar;

begin
// fillchar(Devbuffer, sizeof(Devbuffer), 0) ;
// fillchar(Devbufferhex, sizeof(Devbufferhex), 0) ;

 if (edit12.Text ='') or (edit14.Text ='' ) then
 begin
    showmessage('请输入读E2信息参数！');
    Edit12.SetFocus ;
    exit;
 end;
 getmem(Devbuffer,100);
  st:=IC_ReadDevice(icdev,strtoint(edit12.Text),strtoint(edit14.Text),Devbuffer);
  if st<> 0 then
  begin
      showmessage('读存储区信息错误！');
      freemem(Devbuffer);
      exit;
  end;
  Devbuffer[strtoint(Edit14.Text ) * 2]:=chr(0);
  Edit15.Text :=Devbuffer;
   freemem(Devbuffer);

  getmem(Devbufferhex,100);
   st:=IC_ReadDevice_hex(icdev,strtoint(edit12.Text),strtoint(edit14.Text),Devbufferhex);
  if st<> 0 then
  begin
      showmessage('读存储区信息错误！');
        freemem(Devbufferhex);
      exit;
  end;
  Devbufferhex[strtoint(Edit14.Text ) * 2]:=chr(0);
  Edit13.Text :=Devbufferhex;
   freemem(Devbufferhex);

end;

procedure TFrm4442.Button10Click(Sender: TObject);
begin
 if (edit12.Text='') or (edit14.Text='') or (edit13.Text='') then
 begin
    showmessage('请输入写E2信息参数！');
    Edit13.SetFocus ;
    exit;
 end;
  st:=IC_WriteDevice_Hex(icdev,strtoint(Edit12.Text ),strtoint(Edit14.Text ),pchar(Edit13.Text ));
  if st<> 0 then
  begin
      showmessage('写E2（hex）错误！');
      exit;
  end;
   showmessage('写E2（hex）成功！');
end;

procedure TFrm4442.Button11Click(Sender: TObject);
begin
 if (edit12.Text='') or (edit14.Text='') or (edit15.Text='') then
 begin
    showmessage('请输入写E2信息参数！');
    Edit15.SetFocus ;
    exit;
 end;
  st:=IC_WriteDevice(icdev,strtoint(Edit12.Text ),strtoint(Edit14.Text ),pchar(Edit15.Text ));
  if st<> 0 then
  begin
      showmessage('写E2（ASC）错误！');
      exit;
  end;
    showmessage('写E2（ASC）成功！');
end;

end.
