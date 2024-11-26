@echo off

REM Verifica se o sistema é Windows
IF EXIST "%SystemRoot%\System32\bash.exe" (
    echo Sistema detectado: Linux (WSL)
    git checkout linux
) ELSE (
    echo Sistema detectado: Windows
    git checkout windows
)

REM Compilação
echo Compilando o código...
g++ -o src\main src\main.cpp
IF %ERRORLEVEL% EQU 0 (
    echo Compilação bem-sucedida!
) ELSE (
    echo Erro na compilação. Verifique os logs.
)

echo Fim do script.
pause
