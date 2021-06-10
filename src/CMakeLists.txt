set(PROJECT_SOURCES
        geometry.h
        geometry.cpp
        readfile.h
        readfile.cpp
        transform.h
        transform.cpp
)

add_library(RayTracerSrc STATIC ${PROJECT_SOURCES})

target_include_directories(RayTracerSrc
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(RayTracerSrc PRIVATE CompilerFlags)
