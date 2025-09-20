cmake_minimum_required(VERSION 3.16)
project(pepeta_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ================================
# Dependências
# ================================
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# ================================
# Biblioteca da Engine
# ================================
set(ENGINE_SOURCES
    src/ecs/MovementSystem.cpp
    src/ecs/systems/KiteSystem.cpp
    src/ecs/systems/WindSystem.cpp
    src/ecs/systems/RenderSystem.cpp
    src/ecs/systems/DestroySystem.cpp
    src/ecs/systems/HudSystem.cpp
    src/ecs/debug/DebugSystem.cpp
    src/engine/Screenshot.cpp
    src/engine/TextureManager.cpp
    src/engine/Renderer.cpp        # <-- ADICIONADO
    src/engine/TextureLoader.cpp   # <-- ADICIONADO
)

add_library(pepeta_engine STATIC ${ENGINE_SOURCES})

target_include_directories(pepeta_engine PUBLIC
    src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/third_party/stb
)

target_link_libraries(pepeta_engine PUBLIC
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
    SDL2_image::SDL2_image
    OpenGL::GL
    SFML::Graphics
    SFML::Window
    SFML::System
)

# ================================
# Copiar assets (fonte para debug)
# ================================
file(COPY ${CMAKE_SOURCE_DIR}/assets/DejaVuSans.ttf
     DESTINATION ${CMAKE_BINARY_DIR}/assets)

# ================================
# Executável do jogo de teste (pipa via engine)
# ================================
set(GAME_SOURCES
    src/main.cpp
    src/game/Game.cpp
)

add_executable(pepeta_kite ${GAME_SOURCES})
target_link_libraries(pepeta_kite PRIVATE pepeta_engine)

# ================================
# Executável de teste (ECS unitário)
# ================================
set(ECS_SOURCES
    src/ecs_test.cpp
)

add_executable(ecs_test ${ECS_SOURCES})
target_link_libraries(ecs_test PRIVATE pepeta_engine)

# ================================
# Exemplo independente: pipas vetorizadas (SFML 3)
# ================================
set(KITES_SOURCES
    src/examples/kites/main_kites.cpp
    src/examples/kites/KiteEntity.cpp
    src/examples/kites/ReelEntity.cpp
    src/examples/kites/LineEntity.cpp
)

add_executable(wa_kites ${KITES_SOURCES})

target_include_directories(wa_kites PRIVATE src/examples/kites)

target_link_libraries(wa_kites PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
