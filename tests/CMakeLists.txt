project(Tests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(TEST_LIBRARIES RayTracerSrc CompilerFlags)

enable_testing(true)

function(make_test name file)
    add_executable(${name} ${file})
    add_test(NAME ${name} COMMAND ${name})
    target_link_libraries(${name} PRIVATE ${TEST_LIBRARIES})
endfunction(make_test)

make_test(TestReferenceViewer testreferenceviewer.cpp)
