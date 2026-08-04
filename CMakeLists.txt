cmake_minimum_required(VERSION 3.20)

project(Library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    LibraryCore

    src/Book.cpp
    src/User.cpp
    src/Loan.cpp
    src/Library.cpp
)

target_include_directories(
    LibraryCore
    PUBLIC
    include
)

add_executable(
    Library

    src/main.cpp
)

target_link_libraries(
    Library
    PRIVATE
    LibraryCore
)

enable_testing()

add_subdirectory(tests)
