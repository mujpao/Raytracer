set(PROJECT_SOURCES
        vec.h
        vec.cpp
        mat3.h
        mat3.cpp
        mat4.h
        mat4.cpp
        transform.h
        transform.cpp
        geometry.h
        geometry.cpp
        readfile.h
        readfile.cpp
        utils.h
        utils.cpp
)

add_library(RayTracerSrc STATIC ${PROJECT_SOURCES})

target_include_directories(RayTracerSrc
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(RayTracerSrc PRIVATE CompilerFlags)
