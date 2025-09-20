#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Screenshot.hpp"

#include <GL/gl.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>   // para std::memcpy
#include <iostream>

void Screenshot::save(int width, int height) {
    std::vector<unsigned char> pixels(width * height * 3);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // gera timestamp no nome do arquivo
    auto t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << "screenshot_"
        << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S")
        << ".png";

    // inverte verticalmente (OpenGL coord Y é invertido)
    std::vector<unsigned char> flipped(width * height * 3);
    for (int y = 0; y < height; y++) {
        std::memcpy(
            &flipped[y * width * 3],
            &pixels[(height - 1 - y) * width * 3],
            width * 3
        );
    }

    if (stbi_write_png(oss.str().c_str(), width, height, 3, flipped.data(), width * 3)) {
        std::cout << "📸 Screenshot salva: " << oss.str() << "\n";
    } else {
        std::cerr << "❌ Falha ao salvar screenshot!\n";
    }
}
