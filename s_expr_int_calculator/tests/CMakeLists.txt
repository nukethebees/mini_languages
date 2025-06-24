find_package(GTest CONFIG REQUIRED)

add_executable(tests
    "test_scripts.cpp"
)
target_link_libraries(tests PRIVATE 
    GTest::gtest_main s_expr_int_calculator
)

