@echo off
REM Descarta quaisquer alterações locais e força o checkout da branch 'windows'
git reset --hard
git checkout windows
git pull origin windows

REM Compila o código
g++ -o src/main src/main.cpp

REM Finaliza com uma mensagem para o usuário
echo "Compilação concluída!"
echo "Execute o programa com: src\main.exe"
