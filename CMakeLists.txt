cmake_minimum_required(VERSION 3.16.0)

project(RayTracer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(RT_BUILD_TESTS "Build tests for Raytracer" ON)

if(MSVC)
  set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
      /permissive-
      /W4
      /w14640
    )
else()
  enable_language(C)
  set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
      -g
      -Wall
      -Wextra
      -Wshadow
      -Wnon-virtual-dtor
      -pedantic
    )
endif()

add_subdirectory(src)
add_subdirectory(examples)

if(RT_BUILD_TESTS)
  enable_testing(true)
  add_subdirectory(tests)
endif()
