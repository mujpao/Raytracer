project(Tests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

SET(TEST_LIBRARIES RayTracerSrc CompilerFlags Boost::unit_test_framework)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
configure_file(configure.h.in configure.h @ONLY)

enable_testing(true)

function(make_test name file)
    add_executable(${name} ${file})
    add_test(NAME ${name} COMMAND ${name})
    target_link_libraries(${name} PRIVATE ${TEST_LIBRARIES})
endfunction(make_test)

make_test(TestVec testvec.cpp)
# make_test(TestRay testray.cpp)
make_test(TestMat3 testmat3.cpp)
make_test(TestMat4 testmat4.cpp)
make_test(TestTransform testtransform.cpp)
# make_test(TestShapes testshapes.cpp)
# make_test(TestLights testlights.cpp)
# make_test(TestReadFile testreadfile.cpp)
make_test(TestRenderScene testrenderscene.cpp)
