@echo off

Xcopy ..\Release\Launcher.exe . /c /v /q /y
Xcopy ..\Release\Launcher.map . /c /v /q /y

Xcopy ..\Release\Client.dll . /c /v /q /y
Xcopy ..\Release\Client.map . /c /v /q /y

Xcopy ..\Release\Setup.exe . /c /v /q /y
Xcopy ..\Release\Setup.map . /c /v /q /y

Xcopy ..\Release\CSGOX.dll . /c /v /q /y
Xcopy ..\Release\CSGOX.map . /c /v /q /y
