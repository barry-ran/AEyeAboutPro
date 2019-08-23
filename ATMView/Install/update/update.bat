%~d0
cd %~dp0

set devicecode=%1
set version=%2
set installdir=%3

call cmdReg.bat
call updateEx.bat %devicecode% %version% %installdir%


