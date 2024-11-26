#!/bin/bash

# Verifica se o sistema é Linux
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Sistema detectado: Linux"

    # Faz checkout na branch correta
    git checkout linux

    # Compila o código
    echo "Compilando o código..."
    g++ -o src/main src/main.cpp

    if [ $? -eq 0 ]; then
        echo "Compilação bem-sucedida!"
    else
        echo "Erro na compilação. Verifique os logs."
    fi
else
    echo "Este script é apenas para sistemas Linux."
fi

echo "Fim do script."
