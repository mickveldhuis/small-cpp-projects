add_executable(testthreadpool test.cpp threadpool.cpp)
target_link_libraries(testthreadpool PRIVATE GTest::gtest GTest::gtest_main)

# The following two lines are includes such that VS Code intellisense properly picks up GoogleTest!
# get_target_property(GTEST_INCLUDE_DIRS gtest INTERFACE_INCLUDE_DIRECTORIES)
# target_include_directories(testthreadpool PRIVATE ${GTEST_INCLUDE_DIRS})

include(GoogleTest)
gtest_discover_tests(testthreadpool)
