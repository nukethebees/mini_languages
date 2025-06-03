find_package(GTest CONFIG REQUIRED)

add_executable(tests
    "test_ast_processor.cpp"
    "test_scanner.cpp"
    "test_parser.cpp" 
    "test_code_generator.cpp"
)
target_link_libraries(tests PRIVATE 
    GTest::gtest_main intlang
)

