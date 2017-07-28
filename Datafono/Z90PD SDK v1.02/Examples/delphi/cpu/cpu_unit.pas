unit cpu_unit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    GroupBox1: TGroupBox;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    List1: TListBox;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure RadioButton3Click(Sender: TObject);
    procedure RadioButton4Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
    icdev:longint;
    st:smallint;
    Ic_type:smallint;
    
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation
uses
declare_unit;

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
 icdev:=IC_InitComm(0);
 if icdev<0 then
 begin
 list1.Items.Add('IC_InitComm Error');
 exit;
 end;
 list1.Items.Add('IC_InitComm OK');

 st:=IC_InitType(icdev,Ic_type);
if st<>0 then
 begin
 list1.Items.Add('IC_InitType Error');
 exit;
 end;
 list1.Items.Add('IC_InitType OK');
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
     Ic_type:=12;
end;

procedure TForm1.RadioButton1Click(Sender: TObject);
begin
Ic_type:=12;
end;

procedure TForm1.RadioButton2Click(Sender: TObject);
begin
Ic_type:=13;

end;

procedure TForm1.RadioButton3Click(Sender: TObject);
begin  
Ic_type:=14;

end;

procedure TForm1.RadioButton4Click(Sender: TObject);
begin   
Ic_type:=15;

end;

procedure TForm1.Button2Click(Sender: TObject);
var
rele:smallint;
redata:pchar;
begin

 getmem(redata,64);
 st:=IC_CpuReset_Hex(icdev,rele,redata);
if st<>0 then
 begin
 list1.Items.Add('IC_CpuReset Error');
 freemem(redata);
 exit;
 end;
 list1.Items.Add('IC_CpuReset OK');
 list1.Items.Add(redata);
 st:=IC_CpuApdu_Hex(icdev,5,'0084000008',rele,redata);
if st<>0 then
 begin
 list1.Items.Add('IC_CpuApdu_Hex Error');
 freemem(redata);
 exit;
 end;
 list1.Items.Add('IC_CpuApdu_Hex OK');  
 list1.Items.Add(redata);
 freemem(redata);

end;

procedure TForm1.Button3Click(Sender: TObject);
begin
if icdev>0 then begin
IC_ExitComm(icdev);
icdev:=0;
end;
close;
end;


procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
if icdev>0 then
IC_ExitComm(icdev);

end;

end.
