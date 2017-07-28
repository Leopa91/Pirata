unit device;

interface
Function IC_InitComm(port:integer):longint; stdcall;
far; external'Dcic32.dll' name 'IC_InitComm';

function IC_ResetMifare(icdev:longint; wMsec:smallint):integer;stdcall;
far; external'Dcic32.dll' name 'IC_ResetMifare';

function IC_Card(icdev:LongInt; mode:Smallint; snr: pchar):Integer;
stdcall; far; external 'Dcic32.dll' name 'IC_Card';

function IC_Authentication(icdev:LongInt; mode:Byte; secnr:Byte):Integer;
stdcall; far; external 'Dcic32.dll' name 'IC_Authentication';

function IC_ReadMifare_Hex(icdev:LongInt; mode:Byte; snr:pchar):Integer;
stdcall; far; external 'Dcic32.dll' name 'IC_ReadMifare_Hex';

function IC_CpuReset(icdev:LongInt; relen:SmallInt; redata:PChar):Integer;
stdcall; far; external 'Dcic32.dll' name 'IC_CpuReset';

function IC_CpuApdu_Hex(icdev:LongInt; slen:SmallInt; sendata:PChar;
relen:SmallInt; redata:PChar):Integer; stdcall; far; external 'IC_CpuApdu_Hex';

function IC_Load_Keyhex(icdev:LongInt; mode:Byte; secNr:Byte; password:PChar):Integer;
stdcall; far; external 'Dcic32.dll' name 'IC_Load_Keyhex';

function IC_WriteMifare_Hex(icdev:LongInt; addr:Byte; wdata:PChar):Integer;
stdcall; far; external 'Dcic32.dll' name 'IC_WriteMifare_Hex';
implementation

end.
