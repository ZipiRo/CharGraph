@echo off
setlocal

set PATH_TO_MAIN=%1
set NAME=%2
set OUT_DIRECTORY=%3

mingw32-make -f makefile PATH_TO_MAIN="%PATH_TO_MAIN%" NAME="%NAME%" OUT_DIRECTORY="%OUT_DIRECTORY%"
start %OUT_DIRECTORY%/%NAME%.exe