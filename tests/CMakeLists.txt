cmake_minimum_required(VERSION 3.20)


include(FetchContent)


FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)


FetchContent_MakeAvailable(googletest)


enable_testing()


add_executable(
    LibraryTests

    BookTest.cpp
    OwnershipTest.cpp
    LibraryTest.cpp
)


target_link_libraries(
    LibraryTests

    PRIVATE

    LibraryCore
    GTest::gtest_main
)


include(GoogleTest)

gtest_discover_tests(LibraryTests)
