project(Examples LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(EXAMPLE_LIBRARIES RayTracerSrc CompilerFlags)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

function(make_example name file)
    add_executable(${name} ${file})
    target_link_libraries(${name} PRIVATE ${EXAMPLE_LIBRARIES})
endfunction(make_example)

make_example(diffuseexample diffuseexample.cpp)
make_example(metalexample1 metalexample1.cpp)
make_example(dielectricexample1 dielectricexample1.cpp)
make_example(dielectricexample2 dielectricexample2.cpp)
make_example(randomspherescene randomspherescene.cpp)
