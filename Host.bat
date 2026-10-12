
@echo off
set "UE=D:\FLIN\UE_5.5\Engine\Binaries\Win64\UnrealEditor.exe"
set "PROJECT=D:\FLIN\UE_Projects\MPPingPong\MPPingPong.uproject"
set "MAP=/Game/MPPingPongContent/DevelopmentContent/Maps/lvl_MainMenu"

start "" "%UE%" "%PROJECT%" "%MAP%" -game -log -windowed -ResX=1280 -ResY=720
