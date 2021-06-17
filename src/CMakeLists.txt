set(PROJECT_SOURCES
        camera.h
        camera.cpp
        image.h
        image.cpp
        light.h
        light.cpp
        mat3.h
        mat3.cpp
        mat4.h
        mat4.cpp
        ray.h
        ray.cpp
        raytracer.h
        raytracer.cpp
        readfile.h
        readfile.cpp
        scene.h
        scene.cpp
        shape.h
        shape.cpp
        transform.h
        transform.cpp
        utils.h
        utils.cpp
        vec.h
        vec.cpp
)

add_library(RayTracerSrc STATIC ${PROJECT_SOURCES})

target_include_directories(RayTracerSrc
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(RayTracerSrc PRIVATE CompilerFlags)
