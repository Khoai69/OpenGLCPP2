@echo off

Set RegQry=HKLM\Hardware\Description\System\CentralProcessor\0
REG.exe Query %RegQry%  | Find /i "x86" 
If %ERRORLEVEL% == 0 (
    set SVN="..\tools\bin\SVN17_win32\svn.exe"
    set SVN_VERSION="..\tools\bin\SVN17_win32\svnversion.exe"    
) ELSE (
	set SVN="..\tools\bin\SVN17\svn.exe"
	set SVN_VERSION="..\tools\bin\SVN17\svnversion.exe"
)

%SVN_VERSION% 2>NUL

If %ERRORLEVEL% == 0 (
	rem 1.7 vers 
) ELSE (
	rem assume 1.8 ?
	set SVN="..\tools\bin\SVN18\svn.exe"
)	

SET SVN_PATH=https://svn02/vc

SET FILE=svn.externals

echo premake %SVN_PATH%/libs/trunk/tools/bin/premake5 >> %FILE%

%SVN% pset svn:externals tools -F %FILE%

del %FILE%

