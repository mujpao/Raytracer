set(PROJECT_SOURCES
        materials/dielectricmaterial.h
        materials/dielectricmaterial.cpp
        materials/diffusematerial.h
        materials/diffusematerial.cpp
        materials/material.h
        materials/metalmaterial.h
        materials/metalmaterial.cpp
        materials/phongmaterial.h
        materials/phongmaterial.cpp

        math/mat3.h
        math/mat3.cpp
        math/mat4.h
        math/mat4.cpp
        math/transform.h
        math/transform.cpp
        math/vec.h
        math/vec.cpp

        shapes/abstractshape.h
        shapes/boundingboxnode.h
        shapes/boundingboxnode.cpp
        shapes/shape.h
        shapes/shape.cpp
        shapes/shapelist.h
        shapes/shapelist.cpp
        shapes/sphere.h
        shapes/sphere.cpp
        shapes/triangle.h
        shapes/triangle.cpp

        textures/checkeredtexture.h
        textures/checkeredtexture.cpp
        textures/flatcolortexture.h
        textures/flatcolortexture.cpp
        textures/imagetexture.h
        textures/imagetexture.cpp
        textures/perlintexture.h
        textures/perlintexture.cpp
        textures/texture.h

        boundingbox.h
        boundingbox.cpp
        camera.h
        camera.cpp
        image.h
        image.cpp
        intersectioninfo.h
        light.h
        light.cpp
        progressindicator.h
        progressindicator.cpp
        ray.h
        ray.cpp
        raytracer.h
        raytracer.cpp
        readfile.h
        readfile.cpp
        scene.h
        scene.cpp
        utils.h
        utils.cpp
)

add_library(RayTracerSrc STATIC ${PROJECT_SOURCES})

target_include_directories(RayTracerSrc
          PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
          )

target_link_libraries(RayTracerSrc PRIVATE CompilerFlags)
