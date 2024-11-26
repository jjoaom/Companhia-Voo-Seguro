@echo off
REM Compilar o código para Windows usando MinGW (ou outro compilador de sua escolha)
echo "Compilando o código para Windows..."

cd src
g++ -o main main.cpp

echo "Compilação concluída!"
