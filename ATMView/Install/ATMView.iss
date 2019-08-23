
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "ATMView"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "北京智慧眼科技股份有限公司"
#define MyAppURL "http://www.a-eye.cn"
#define MyAppExeName "ATMView.exe"
#define MyAppIcoName "ATMView.ico"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2774543F-B8FD-4545-967F-E1DB97362B84}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\AthenaEye\{#MyAppName}
DisableProgramGroupPage=yes
DisableReadyMemo=yes
DisableReadyPage=yes
CloseApplications=no
DefaultGroupName=自助服务一体机系统
OutputDir=.
OutputBaseFilename=SetupATMView
Compression=lzma
PrivilegesRequired=admin
SolidCompression=yes
ChangesEnvironment=yes

[Languages]
Name: "chinesesimplified"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "..\Win32\Release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\config.ini"; DestDir: "{userdocs}\AthenaEye\ATMView"; Flags: onlyifdoesntexist uninsneveruninstall

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#MyAppIcoName}";

[Run]
Filename: "{app}\ATMLauncher.exe"; Parameters:"/verysilent /norestart"; Flags: nowait postinstall unchecked runhidden

[UninstallRun]

[Registry]
Root: HKLM; SubKey: Software\AthenaEye\ATMView; ValueType: string; ValueName: InstalledVersion; ValueData: {#MyAppVersion}; Flags: UninsDeleteValue;
Root: HKLM; SubKey: Software\AthenaEye\ATMView; ValueType: string; ValueName: InstalledPath; ValueData: {app}; Flags: UninsDeleteValue;
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "ATMLauncher"; ValueData: "{app}\ATMLauncher.exe"
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "ATMView"; ValueData: "{app}\ATMView.exe" 
Root: HKCU; Subkey: "Software\Microsoft\Internet Explorer\Main\FeatureControl\FEATURE_SCRIPTURL_MITIGATION"; ValueType:dword;ValueName:"ATMView.exe";ValueData:1
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment";ValueType: expandsz; ValueName: "Path"; ValueData: "{olddata};{app}\";Check:NeedsAddPath('{app}\')

[UninstallDelete]
Type: files; Name: "{app}\ATMLauncher.exe"
Type: files; Name: "{app}\ATMView.exe"

[Code]
type
    SERVICE_STATUS = record
    dwServiceType                : cardinal;
    dwCurrentState                : cardinal;
    dwControlsAccepted            : cardinal;
    dwWin32ExitCode                : cardinal;
    dwServiceSpecificExitCode    : cardinal;
    dwCheckPoint                : cardinal;
    dwWaitHint                    : cardinal;end;
    HANDLE = cardinal;
constSC_MANAGER_ALL_ACCESS        = $f003f;SERVICE_START                = $10;SERVICE_STOP                 = $20;SERVICE_CONTROL_STOP         = $1;
SERVICE_DELETE               = $10000;
function OpenSCManager(lpMachineName, lpDatabaseName: string; dwDesiredAccess :cardinal): HANDLE;
external 'OpenSCManagerA@advapi32.dll stdcall';

function OpenService(hSCManager :HANDLE;lpServiceName: string; dwDesiredAccess :cardinal): HANDLE;
external 'OpenServiceA@advapi32.dll stdcall';

function ControlService(hService :HANDLE; dwControl :cardinal;var ServiceStatus :SERVICE_STATUS) : boolean;
external 'ControlService@advapi32.dll stdcall';

function CloseServiceHandle(hSCObject :HANDLE): boolean;
external 'CloseServiceHandle@advapi32.dll stdcall';

function DeleteService(hService :HANDLE): boolean;
external 'DeleteService@advapi32.dll stdcall';

function OpenServiceManager() : HANDLE;
begin
    if UsingWinNT() = true then begin
        Result := OpenSCManager('','ServicesActive',SC_MANAGER_ALL_ACCESS);
    end
end;

function StopService(ServiceName: string) : boolean;
var
    hSCM    : HANDLE;
    hService: HANDLE;
    Status    : SERVICE_STATUS;
begin
    hSCM := OpenServiceManager();
    Result := false;
    if hSCM <> 0 then begin
        hService := OpenService(hSCM,ServiceName,SERVICE_STOP);
        if hService <> 0 then begin
            Result := ControlService(hService,SERVICE_CONTROL_STOP,Status);
            CloseServiceHandle(hService);
        end;
        CloseServiceHandle(hSCM);
    end;
end;

function RemoveService(ServiceName: string) : boolean;
var
    hSCM    : HANDLE;
    hService: HANDLE;
begin
    hSCM := OpenServiceManager();
    Result := false;
    if hSCM <> 0 then begin
        hService := OpenService(hSCM,ServiceName,SERVICE_DELETE);
        if hService <> 0 then begin
            Result := DeleteService(hService);
            CloseServiceHandle(hService);
        end;
        CloseServiceHandle(hSCM);
    end
end;

function InitializeSetup(): Boolean;
var
  installedPath : string;
  installedVersion : string;
  uninstallerPath : string;
  resultCode : Integer;
  ErrorCode: Integer;
begin
  ShellExec('open', ExpandConstant('{cmd}'), '/c taskkill /f /t /im ATMLauncher.exe', '', SW_HIDE, ewNoWait, ErrorCode);
  ShellExec('open', ExpandConstant('{cmd}'), '/c taskkill /f /t /im ATMView.exe', '', SW_HIDE, ewNoWait, ErrorCode);

  Result := True;
  if RegValueExists(HKEY_LOCAL_MACHINE, 'Software\AthenaEye\ATMView', 'InstalledVersion') and RegValueExists(HKEY_LOCAL_MACHINE, 'Software\AthenaEye\ATMView', 'InstalledPath') then
  begin
    RegQueryStringValue(HKEY_LOCAL_MACHINE, 'Software\AthenaEye\ATMView', 'InstalledVersion', installedVersion);
    RegQueryStringValue(HKEY_LOCAL_MACHINE, 'Software\AthenaEye\ATMView', 'InstalledPath', installedPath);
    uninstallerPath := installedPath + '\unins000.exe';

    if FileExists(uninstallerPath) then
    begin
        Exec(uninstallerPath, '/SILENT', installedPath, SW_SHOW, ewWaitUntilTerminated, resultCode);
    end;
  end;
end;

function NeedsAddPath(Param: string): boolean;
var
  OrigPath: string;
  ParamExpanded: string;
begin
  //expand the setup constants like {app} from Param
  ParamExpanded := ExpandConstant(Param);
  if not RegQueryStringValue(HKEY_LOCAL_MACHINE,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path', OrigPath)
  then begin
    Result := True;
    exit;
  end;
  // look for the path with leading and trailing semicolon and with or without \ ending
  // Pos() returns 0 if not found
  Result := Pos(';' + UpperCase(ParamExpanded) + ';', ';' + UpperCase(OrigPath) + ';') = 0;  
  if Result = True then
     Result := Pos(';' + UpperCase(ParamExpanded) + '\;', ';' + UpperCase(OrigPath) + ';') = 0; 
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  resultCode : Integer;
  ErrorCode: Integer;
begin
  ShellExec('open', ExpandConstant('{cmd}'), '/c taskkill /f /t /im ATMLauncher.exe', '', SW_HIDE, ewNoWait, ErrorCode);
  ShellExec('open', ExpandConstant('{cmd}'), '/c taskkill /f /t /im ATMView.exe', '', SW_HIDE, ewNoWait, ErrorCode);

  case CurUninstallStep of
    usUninstall:
      begin
          RegDeleteValue(HKEY_LOCAL_MACHINE,'SOFTWARE\Microsoft\Windows\CurrentVersion\Run','ATMLauncher');
          RegDeleteValue(HKEY_LOCAL_MACHINE,'SOFTWARE\Microsoft\Windows\CurrentVersion\Run','ATMView');
          DelTree(ExpandConstant('{app}'), True, True, True);
       end;
    usPostUninstall:
      begin
        RemoveDir(ExpandConstant('{app}'));
        StopService('HP LEDM Proxy Service');
        RemoveService('HP LEDM Proxy Service');
      end;
  end;
end;

[CustomMessages]
CheckForUpdates=检查更新 %1
;UserManual=%1操作手册
