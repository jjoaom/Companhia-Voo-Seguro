#!/bin/bash

# Descarta quaisquer alterações locais e força o checkout da branch 'linux'
git reset --hard
git checkout linux
git pull origin linux

echo "Branch linux atualizada com sucesso!"
