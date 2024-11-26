@echo off
REM Muda para a branch 'windows' e garante que o repositório esteja atualizado
git reset --hard
git checkout windows
git pull origin windows

echo "Branch windows atualizada com sucesso!"
