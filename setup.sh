#!/bin/bash

# Descarta quaisquer alterações locais e força o checkout da branch 'linux'
git reset --hard
git checkout linux
git pull origin linux

# Compila o código
cd src
g++ -o main main.cpp

# Mensagem de sucesso
echo "Compilação concluída!"
echo "Execute o programa com: ./main"
