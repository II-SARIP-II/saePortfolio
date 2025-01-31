# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet et langage
project(MySDL3Project C)

# Indiquer où trouver SDL3Config.cmake
set(SDL3_DIR "C:/SDL/install/lib/cmake/SDL3")

# Chercher SDL3
find_package(SDL3 REQUIRED)

# Créer l'exécutable
add_executable(MySDL3Project main.c
        action.c)

# Lier SDL3 à ton projet
target_link_libraries(MySDL3Project SDL3::SDL3)
