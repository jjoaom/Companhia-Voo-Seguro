@echo off
REM Muda para a branch 'windows' e garante que o repositório esteja atualizado
git reset --hard
git checkout windows
git pull origin windows

<<<<<<< HEAD
echo "Branch windows atualizada com sucesso!"
=======
REM Compila o código
g++ -o src/main src/main.cpp

REM Finaliza com uma mensagem para o usuário
echo "Compilação concluída!"
echo "Execute o programa com: src\main.exe"
>>>>>>> 4ddfda1e5a6abcfaf8e39735641acf0a0445dd14
