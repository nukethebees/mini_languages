find_package(GTest CONFIG REQUIRED)

add_executable(tests
    test_scanner.cpp
    "test_parser.cpp")
target_link_libraries(tests PRIVATE 
    GTest::gtest_main printlang
)

