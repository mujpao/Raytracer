cmake_minimum_required(VERSION 3.16.0)

project(RayTracer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CompilerFlags INTERFACE)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(CompilerFlags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wnon-virtual-dtor;-pedantic>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:/permissive-;/W4;/w14640>>"
)

add_subdirectory(src)

add_subdirectory(examples)

add_subdirectory(tests)

add_executable(RayTracer
    src/main.cpp
)

target_link_libraries(RayTracer PRIVATE CompilerFlags RayTracerSrc)
