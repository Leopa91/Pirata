program demo1608;

uses
  Forms,
  Test1608 in 'Test1608.pas' {Frm1608},
  drv_unit in 'drv_unit.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TFrm1608, Frm1608);
  Application.Run;
  if icdev>0 then begin
        st := IC_ExitComm(icdev);      //关闭串口，这是整个程序结束后执行的操作
        if st=0 then icdev:=0;
  end;
end.
