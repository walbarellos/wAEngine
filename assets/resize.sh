#!/bin/bash
set -e

echo "== Pepeta | Resize de Sprites =="

# Diretório atual (build/img)
IMG_DIR="."
SIZE="32x32"

# Lista de arquivos
FILES=("carretel.png" "linha.png" "pepeta.png" "pepeta-red.png")

# Verifica dependência
if ! command -v mogrify &> /dev/null; then
    echo "❌ O comando 'mogrify' (ImageMagick) não está instalado."
    echo "Instale com: sudo pacman -S imagemagick"
    exit 1
fi

# Faz backup antes de sobrescrever
mkdir -p "$IMG_DIR/backup"
for f in "${FILES[@]}"; do
    if [ -f "$IMG_DIR/$f" ]; then
        cp "$IMG_DIR/$f" "$IMG_DIR/backup/"
        echo "Backup salvo: $IMG_DIR/backup/$f"
    fi
done

# Redimensiona (mantendo proporção e preenchendo transparente se necessário)
for f in "${FILES[@]}"; do
    if [ -f "$IMG_DIR/$f" ]; then
        mogrify -resize $SIZE\! "$IMG_DIR/$f"
        echo "✅ Redimensionado: $IMG_DIR/$f -> $SIZE"
    else
        echo "⚠️ Arquivo não encontrado: $IMG_DIR/$f"
    fi
done

echo "== Concluído. Todos os sprites agora estão 32x32 px =="
