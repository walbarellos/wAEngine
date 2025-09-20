#pragma once
#include <vector>
#include <cmath>
#include <utility>

class LineShape {
public:
    enum class CurveType {
        Parabola,
        Catenary
    };

    // Gera pontos de linha curvada (parábola ou catenária)
    static std::vector<std::pair<float,float>> generate(
        float x1, float y1,
        float x2, float y2,
        float tension,              // [0..1]
        int segments = 25,
        CurveType type = CurveType::Parabola
    ) {
        if (segments < 2) segments = 2;
        std::vector<std::pair<float,float>> pts;
        pts.reserve(segments+1);

        switch (type) {
            case CurveType::Parabola:
                pts = parabola(x1, y1, x2, y2, tension, segments);
                break;
            case CurveType::Catenary:
                pts = catenary(x1, y1, x2, y2, tension, segments);
                break;
        }
        return pts;
    }

private:
    // ===========================
    // Curva parabólica simples
    // ===========================
    static std::vector<std::pair<float,float>> parabola(
        float x1, float y1,
        float x2, float y2,
        float tension,
        int segments
    ) {
        std::vector<std::pair<float,float>> pts;
        pts.reserve(segments+1);

        float midx = (x1 + x2) * 0.5f;
        float k = (1.0f - tension) * 0.002f; // fator de curvatura

        for (int i=0; i<=segments; i++) {
            float t = (float)i / segments;
            float x = x1 + (x2 - x1) * t;
            float ylin = y1 + (y2 - y1) * t;
            float curve = k * (x - midx) * (x - midx);
            float y = ylin - curve;
            pts.push_back({x,y});
        }
        return pts;
    }

    // ===========================
    // Curva catenária realista
    // ===========================
    static std::vector<std::pair<float,float>> catenary(
        float x1, float y1,
        float x2, float y2,
        float tension,
        int segments
    ) {
        std::vector<std::pair<float,float>> pts;
        pts.reserve(segments+1);

        // Parâmetros simplificados
        float L = std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)); // distância
        float a = (1.0f - tension) * 0.2f + 0.01f;              // fator de "soltura"

        for (int i=0; i<=segments; i++) {
            float t = (float)i / segments;
            float x = x1 + (x2 - x1) * t;

            // Normalizamos para -0.5..0.5 e aplicamos cosh
            float xn = (t - 0.5f) * L;
            float y = (y1 + (y2 - y1) * t) - a * (std::cosh(xn/a) - 1.0f);

            pts.push_back({x,y});
        }
        return pts;
    }
};
