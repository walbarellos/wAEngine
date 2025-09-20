#!/bin/bash
set -e

echo "== Pepeta Engine | Build & Run =="

# 1. Garante que estamos na pasta do projeto
ROOT_DIR="$(dirname "$0")"
cd "$ROOT_DIR"

# 2. Garante que a pasta assets existe
mkdir -p assets

# 3. Gera cloud.png placeholder se não existir
if [ ! -f assets/cloud.png ]; then
    echo "[INFO] Gerando cloud.png placeholder..."
    if command -v magick &> /dev/null; then
        magick -size 64x32 xc:none -fill white -draw "roundrectangle 0,0 63,31 15,15" assets/cloud.png
    else
        echo "⚠️ ImageMagick (magick) não encontrado, criando um PNG vazio como fallback."
        convert -size 64x32 xc:white assets/cloud.png || true
    fi
fi

# 4. Garante que a pasta build existe
mkdir -p build

# 5. Garante que os assets estão acessíveis dentro de build/
if [ ! -L build/assets ]; then
    ln -s ../assets build/assets
    echo "[INFO] Link simbólico para assets criado em build/"
fi

# 6. Entra em build e recompila
cd build
cmake ..
make -j"$(nproc)"

echo ""
echo "== Etapa 1: Rodando ECS Test =="
./ecs_test || { echo "❌ ecs_test falhou"; exit 1; }

echo ""
echo "== Etapa 2: Rodando Pepeta Kite =="
./pepeta_kite &

# 7. Espera o jogo abrir
GAME_PID=$!
sleep 3

# 8. Tira screenshot automática (usando SDL interno)
echo "📸 Salvando screenshot..."
xdotool key F12 || echo "⚠️ Precisa mapear F12 no jogo para salvar screenshot"

# 9. Espera mais um pouco e encerra o jogo
sleep 5
kill $GAME_PID || true

echo ""
echo "== Tudo finalizado com sucesso ✅ =="
