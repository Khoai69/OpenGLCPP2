@echo off 
SET MAKETOOL=..\tools\premake\release\premake5.exe

%MAKETOOL% --to=vs2012 vs2012
%MAKETOOL% --to=vs2013 vs2013
%MAKETOOL% --to=vs2015 vs2015

%MAKETOOL% --arch=macosx --to=xcode4\macosx xcode4
%MAKETOOL% --arch=ios --to=xcode4\ios xcode4

%MAKETOOL% --os=linux --to=gmake\x64 gmake
