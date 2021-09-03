find_package(Boost REQUIRED COMPONENTS unit_test_framework)

SET(TEST_LIBRARIES RayTracerSrc Boost::unit_test_framework)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
configure_file(configure.h.in configure.h @ONLY)

function(make_test name file)
  add_executable(${name} ${file})
  add_test(NAME ${name} COMMAND ${name})
  target_include_directories(${name}
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${CMAKE_CURRENT_BINARY_DIR}
  )
  target_link_libraries(${name} PRIVATE ${TEST_LIBRARIES})
  target_compile_options(${name} PRIVATE ${DEFAULT_COMPILE_OPTIONS})
endfunction(make_test)

set(TEST_SOURCES
  runtests.cpp
  testvec.cpp
  testmat3.cpp
  testmat4.cpp
  testtransform.cpp
  testimage.cpp
  testboundingbox.cpp
  testshapes.cpp
)

add_executable(RTUnitTests ${TEST_SOURCES})
add_test(NAME RTUnitTests COMMAND RTUnitTests)
target_link_libraries(RTUnitTests PRIVATE ${TEST_LIBRARIES})

make_test(TestRenderScene testrenderscene.cpp)
