program demo1604;

uses
  Forms,
  Test1604 in 'Test1604.pas' {Frm1604},
  drv_unit in 'drv_unit.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TFrm1604, Frm1604);
  Application.Run;
  if icdev>0 then begin
        st := IC_ExitComm(icdev);      //关闭串口，这是整个程序结束后执行的操作
        if st=0 then icdev:=0;
  end;
end.
