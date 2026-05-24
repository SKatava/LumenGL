include(GoogleTest)

add_executable(lumengl_tests
    test_result.cpp
    test_mesh.cpp
    test_camera.cpp
)

target_link_libraries(lumengl_tests
    PRIVATE
        lumengl
        GTest::gtest_main
)

gtest_discover_tests(lumengl_tests)
