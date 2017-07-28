program demo102;

uses
  Forms,
  Test102 in 'Test102.pas' {Frm102},
  drv_unit in 'drv_unit.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TFrm102, Frm102);
  Application.Run;
  if icdev>0 then begin
  st:=ic_exitcomm(icdev);
  end;
end.
