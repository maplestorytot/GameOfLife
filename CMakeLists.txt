cmake_minimum_required(VERSION 3.14)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

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
        src/BoardFactory.cpp
        src/SimpleBoard.cpp
        src/hash_life/hash_life_board.cpp
        src/hash_life/NextNodeGenerationTransformer.cpp
        src/hash_life/Node.cpp
        src/hash_life/NodeFactory.cpp
        src/hash_life/NodeStorage.cpp
        src/hash_life/NodePrinter.cpp
        tests/RandomBoardCreator.cpp
)
target_link_libraries(
        life_test
        gtest_main
        GSL
        OpenMP::OpenMP_CXX
)
find_package(OpenMP REQUIRED)
find_package(benchmark REQUIRED)
add_executable(
        perf_test
        tests/performance_test.cpp
        src/BoardFactory.cpp
        src/SimpleBoard.cpp
        tests/RandomBoardCreator.cpp
        src/hash_life/hash_life_board.cpp
        src/hash_life/NextNodeGenerationTransformer.cpp
        src/hash_life/Node.cpp
        src/hash_life/NodeFactory.cpp
        src/hash_life/NodeStorage.cpp
        src/hash_life/NodePrinter.cpp
)

target_link_libraries(
        perf_test
        GSL
        benchmark::benchmark
        benchmark::benchmark_main
        OpenMP::OpenMP_CXX
)

include(GoogleTest)
gtest_discover_tests(life_test)