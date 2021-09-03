SET(EXAMPLE_LIBRARIES RayTracerSrc)

function(make_example name file)
  add_executable(${name} ${file})
  target_include_directories(${name}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(${name} PRIVATE ${EXAMPLE_LIBRARIES})
  target_compile_options(${name} PRIVATE ${DEFAULT_COMPILE_OPTIONS})
endfunction(make_example)

make_example(diffuseexample diffuseexample.cpp)
make_example(metalexample1 metalexample1.cpp)
make_example(dielectricexample1 dielectricexample1.cpp)
make_example(dielectricexample2 dielectricexample2.cpp)
make_example(randomspherescene randomspherescene.cpp)
make_example(textureexample1 textureexample1.cpp)
make_example(textureexample2 textureexample2.cpp)
make_example(perlintextureexample perlintextureexample.cpp)
make_example(boxexample boxexample.cpp)
make_example(importexample importexample.cpp)
