@echo off

echo 请输入需要查询的文件的全路径(支持拖拽) :
set /p IMAGE_PATH=

set IMAGE_PATH=%IMAGE_PATH:"=%

if exist "%VS90COMNTOOLS%vsvars32.bat" (
call "%VS90COMNTOOLS%vsvars32.bat"
) else (
if exist "%VS100COMNTOOLS%vsvars32.bat" (
call "%VS100COMNTOOLS%vsvars32.bat"
) else (
if exist "%VS110COMNTOOLS%vsvars32.bat" (
call "%VS110COMNTOOLS%vsvars32.bat"
) else (
if exist "%VS120COMNTOOLS%vsvars32.bat" (
call "%VS120COMNTOOLS%vsvars32.bat"
) else (
if exist "%VS140COMNTOOLS%vsvars32.bat" (
call "%VS140COMNTOOLS%vsvars32.bat"
)
)
)
)
)

del /f /q /a "DependenciesList.log"

rem dumpbin /dependents "%IMAGE_PATH%" >"DependenciesList.log"
dumpbin /imports "%IMAGE_PATH%" >"DependenciesList.log"
call "DependenciesList.log"