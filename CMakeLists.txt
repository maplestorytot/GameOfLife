cmake_minimum_required(VERSION 3.14)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG "v3.1.0"
        )

FetchContent_MakeAvailable(GSL)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        life_test
        tests/life_test.cpp
        src/Board.cpp
)
target_link_libraries(
        life_test
        gtest_main
        GSL
)
include(GoogleTest)
gtest_discover_tests(life_test)