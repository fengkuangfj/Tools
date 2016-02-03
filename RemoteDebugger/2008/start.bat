@echo off

:SelectAppType
echo 请选择被调试程序类型：
echo x64
echo x86
set /p APP_TYPE=
echo 被调试程序类型：%APP_TYPE%
goto CheckAppType

:CheckAppType
if x64 == %APP_TYPE% (
goto start
) else (
if x86 == %APP_TYPE% (
goto start
) else (
goto SelectAppType
)
)

:start
taskkill /im msvsmon.exe /t /f
call %APP_TYPE%\msvsmon.exe /noauth /anyuser /nowowwarn /nosecuritywarn

pause