# Raytracer

A basic raytracer supporting diffuse, metal, and dielectric materials, textures, and Phong shading.

## Features

- Materials
    - Diffuse
    - Metal
    - Dielectric
    - Phong
- Textures
    - Image textures
    - Perlin noise textures
    - Normal maps
- Import camera and objects from file using Assimp (works best with .gltf files)
- Bounding volume hierarchy

# Example Renders

# Demo

# Build Instructions

## Requires
- CMake 3.16.0
- C++17

## Install Assimp
- Download [Assimp](https://github.com/assimp/assimp/releases/tag/v5.0.1)
- Build/install Assimp
    ```cd assimp
    cmake CMakeLists.txt
    cmake --build .
    cmake --install .
    ```

## Build
```
git clone https://github.com/mujpao/Raytracer.git
cd Raytracer
mkdir build
cd build
cmake ..
cmake --build .
```

# TODO
- [ ] Physically-based materials/lights
- [ ] Read lights from file
- [ ] Environment maps

# Resources
- [Ray Tracing in One Weekend Series](https://raytracing.github.io/)
- [edX Computer Graphics Course](https://www.edx.org/course/computer-graphics-2)
- [stb image libraries](https://github.com/nothings/stb)
- [Scratchapixel](https://www.scratchapixel.com/)
- [Assimp](https://github.com/assimp/assimp)