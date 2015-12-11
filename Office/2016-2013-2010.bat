@echo off
::本批处理仅适用于Office 2010/13/16 批量授权版(即大客户或Vl版)
::如果你的Office并非批量授权版，那么本批处理将自动把Office转为Vl版


set KMS_Sev=kms.landian.news
::set KMS_Sev=kms.landiannews.com:1688
::set KMS_Sev=kms.landiannews.xyz:1688

::======================= 以下内容无需更改 ======================
setlocal EnableDelayedExpansion&color 3e & cd /d "%~dp0"
title KMS_Activation_for_Office2010_2013_2016 - [hnfeng]
%1 %2
mshta vbscript:createobject("shell.application").shellexecute("%~s0","goto :runas","","runas",1)(window.close)&goto :eof
:runas
call :strset
cls
if not defined str1 goto en
echo %bar%%bar%%bar%
echo               %str0%
echo.&echo %str1%
echo.&echo %str2%
echo    Office_KMS_Activation.bat
echo.&echo %str3%
echo    Office_KMS_Activation+GVLK.bat
echo.&echo %str4%
echo.&echo %str5%
echo.&echo %str6%
echo.&echo %str7%
echo.&echo %str8%
echo.&echo %str9%
set space=                         
echo.&echo %space%%space%2015.12 hnfeng
echo %bar%%bar%%bar%
timeout /t 30
:en

call :GetOfficePath 14 Office2010
call :ActOffice 14 Office2010
echo %bar%%bar%

call :GetOfficePath 15 Office2013
call :ActOffice 15 Office2013
echo %bar%%bar%

if exist "%ProgramFiles%\Microsoft Office\Office16\ospp.vbs" set _Office16Path=%ProgramFiles%\Microsoft Office\Office16
if exist "%ProgramFiles(x86)%\Microsoft Office\Office16\ospp.vbs" set _Office16Path=%ProgramFiles(x86)%\Microsoft Office\Office16
if DEFINED _Office16Path (echo.&echo %str18% Office2016 %str13%
    call :ActOffice 16 Office2016
  ) else (echo.&echo %str19% Office2016 %str13%)

echo %bar%%bar%

echo.&pause
exit

:ActOffice
if DEFINED _Office%1Path (
    cd /d "!_Office%1Path!"
    if %1 EQU 16 call :Licens16
    echo.&echo %str12% %2 %str13%...&echo.
    cscript //nologo ospp.vbs /sethst:%KMS_Sev% >nul
    cscript //nologo ospp.vbs /act | find /i "successful" && (
        echo.&echo ***** %2 %str14% ***** & echo.) || (echo.&echo ***** %2 %str15% ***** & echo.)
)    
cd /d "%~dp0"
goto :EOF

:GetOfficePath
echo.&echo %str16% %2 %str17%...
set _Office%1Path=
set _Reg32=HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Office\%1.0\Common\InstallRoot
set _Reg64=HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Office\%1.0\Common\InstallRoot
reg query "%_Reg32%" /v "Path" > nul 2>&1 && FOR /F "tokens=2*" %%a IN ('reg query "%_Reg32%" /v "Path"') do SET "_OfficePath1=%%b"
reg query "%_Reg64%" /v "Path" > nul 2>&1 && FOR /F "tokens=2*" %%a IN ('reg query "%_Reg64%" /v "Path"') do SET "_OfficePath2=%%b"
if DEFINED _OfficePath1 (if exist "%_OfficePath1%ospp.vbs" set _Office%1Path=!_OfficePath1!)
if DEFINED _OfficePath2 (if exist "%_OfficePath2%ospp.vbs" set _Office%1Path=!_OfficePath2!)
set _OfficePath1=
set _OfficePath2=
if DEFINED _Office%1Path (echo.&echo %str18% %2 %str13%) else (echo.&echo %str19% %2 %str13%)
goto :EOF

:Licens16
for /f %%x in ('dir /b ..\root\Licenses16\project???vl_kms*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
for /f %%x in ('dir /b ..\root\Licenses16\proplusvl_kms*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
for /f %%x in ('dir /b ..\root\Licenses16\standardvl_kms*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
for /f %%x in ('dir /b ..\root\Licenses16\visio???vl_kms*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
for /f %%x in ('dir /b ..\root\Licenses16\project???vl_mak*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
for /f %%x in ('dir /b ..\root\Licenses16\proplusvl_mak*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
for /f %%x in ('dir /b ..\root\Licenses16\standardvl_mak*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
for /f %%x in ('dir /b ..\root\Licenses16\visio???vl_mak*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul
cscript ospp.vbs /inpkey:NYH39-6GMXT-T39D4-WVXY2-D69YY >nul
cscript ospp.vbs /inpkey:7WHWN-4T7MP-G96JF-G33KR-W8GF4 >nul
cscript ospp.vbs /inpkey:RBWW7-NTJD4-FFK2C-TDJ7V-4C2QP >nul
cscript ospp.vbs /inpkey:XQNVK-8JYDB-WJ9W3-YJ8YR-WFG99 >nul
cscript ospp.vbs /inpkey:YG9NW-3K39V-2T3HJ-93F3Q-G83KT >nul
cscript ospp.vbs /inpkey:PD3PC-RHNGV-FXJ29-8JK7D-RJRJK >nul
goto :EOF

:strset
chcp | find "936" > nul && (
	set bar=*************************
	set str0=用于 纯批处理 KMS 方式激活 Office 系列产品
	set str1=1、该批处理仅用于激活 VL版（VOL,大客户版）Office2010、2013、2016（已含零售转KMS）
	set str2=2、如果你默认安装的Office VL版（例如未输入过其他的MAK），建议使用：
	set str3=3、如果你安装的Office VL版曾经输入过其他的MAK，建议使用：
	set str4=4、如果你安装的是零售版的Office，请先使用转换工具转换为VL版，或重新安装VL版
	set str5=5、支持系统中同时安装有不同版本的Office（例如2010+2013）
	set str6=6、支持32位系统安装32位Office，64位系统安装32位或64位Office
	set str7=7、支持自定义的Office安装路径（例如把Office安装到其他磁盘）
	set str8=8、本人不对该批处理作任何保证，请自己斟酌风险，并决定是否使用
	set str9=9、按任意键继续（超时后自动继续），按 Ctrl+C 退出
	set str10=正在安装
	set str11=系列产品密钥，请稍等...
	set str12=尝试激活
	set str13=系列产品
	set str14=激活成功
	set str15=激活失败
	set str16=正在检测
	set str17=系列产品的安装路径
	set str18=已发现
	set str19=未发现
)
chcp | find "950" > nul && (
	set bar=*************************
	set str0=ノ у矪瞶 KMS よΑ币ノ Office ╰玻珇
	set str1=1赣у矪瞶度ノ币ノ VLVOL,めOffice201020132016
	set str2=2狦纐粄杆Office VLㄒゼ块筁ㄤMAK某ㄏノ
	set str3=3狦杆Office VL纯竒块筁ㄤMAK某ㄏノ
	set str4=4狦杆琌箂扳Office叫ㄏノ锣传ㄣ锣传VL┪穝杆VL
	set str5=5や╰参い杆ΤぃセOfficeㄒ2010+2013
	set str6=6や32╰参杆32Office64╰参杆32┪64Office
	set str7=7や﹚竡Office杆隔畖ㄒрOffice杆ㄤ合絃
	set str8=8セぃ癸赣у矪瞶ヴ玂谍叫穜皍繧∕﹚琌ㄏノ
	set str9=9ヴ種龄膥尿禬笆膥尿 Ctrl+C 癶
	set str10=タ杆
	set str11=╰玻珇盞芲叫祔单...
	set str12=沽刚币ノ
	set str13=╰玻珇
	set str14=币ノΘ
	set str15=币ノア毖
	set str16=タ浪代
	set str17=╰玻珇杆竚
	set str18=祇瞷
	set str19=ゼ祇瞷
)
if not defined str1 (
	set bar=*************************
	set str1=
	set str10=Installing
	set str11=GVLK, Just a moment, please...
	set str12=Trying to activate
	set str13=series products
	set str14=activation success
	set str15=activation failure
	set str16=Identifying install_path of
	set str17=series products
	set str18=Have been found
	set str19=Not found
)
goto :EOF
