unit declare_unit;

interface

Function IC_InitComm(port:integer):longint; stdcall;
 far; external'Dcic32.dll' name'IC_InitComm';
Function IC_ExitComm(icdev:longint):integer;stdcall;
far; external 'dcic32.dll' name 'IC_ExitComm';
Function IC_CpuReset_Hex(icdev:longint;relen:smallint;data:pchar):integer;
stdcall;far; external 'dcic32.dll' name 'IC_CpuReset_Hex';
Function IC_CpuApdu_Hex(icdev:longint;selen:smallint;sdata:pchar;relen:smallint;data:pchar):integer;
stdcall;far; external 'dcic32.dll' name 'IC_CpuApdu_Hex';
Function IC_InitType(icdev:longint;ictype:smallint):integer;
stdcall;far; external 'dcic32.dll' name 'IC_InitType';



implementation

end.
 