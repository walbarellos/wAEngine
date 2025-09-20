# Corrigir/otimizar cloud.png automaticamente
if [ -f assets/cloud.png ]; then
    echo "[INFO] Otimizando cloud.png..."
    if command -v magick &> /dev/null; then
        magick assets/cloud.png -resize 256x256 -trim +repage assets/cloud.png
    else
        echo "⚠️ ImageMagick não encontrado, não foi possível otimizar cloud.png"
    fi
else
    echo "[WARN] Nenhum cloud.png encontrado em assets/"
fi
