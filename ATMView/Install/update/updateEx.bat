%~d0
cd %~dp0

set devicecode=%1
set version=%2
set installdir=%3

::去掉首尾的双引号
%installdir:*"=set "installdir=%

set appPath="%installdir%ATMView.exe"
set starterpath="%installdir%ATMLauncher.exe"

tasklist|find /i "ATMView.exe" ||exit

taskkill /f /FI "IMAGENAME eq ATMLauncher.exe"  
taskkill /f /FI "IMAGENAME eq ATMView.exe"  
taskkill /f /FI "IMAGENAME eq ATMStarter.exe"  

::等待3秒，确保exe不再占用（主要是在Win8下）
ping -n 3 127.0.0.1>nul

SetupATMView.exe  /verysilent  /suppressmsgboxes

taskkill /f /FI "IMAGENAME eq ATMLauncher.exe"  
taskkill /f /FI "IMAGENAME eq ATMView.exe"

ping -n 2 127.0.0.1>nul 

start "" %appPath% %version%
start "" %starterpath%

