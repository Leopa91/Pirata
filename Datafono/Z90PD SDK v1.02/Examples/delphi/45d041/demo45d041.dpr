program demo45d041;

uses
  Forms,
  Test45d041 in 'Test45d041.pas' {Frm45d041},
  drv_unit in 'drv_unit.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TFrm45d041, Frm45d041);
  Application.Run;
end.
