# Library Management System

A modern **C++ Library Management System** designed to study and apply professional software engineering practices, memory management, and modern C++ architecture.

This project focuses on understanding and implementing core C++ concepts such as:

* RAII (Resource Acquisition Is Initialization)
* Ownership and resource management
* Smart pointers (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`)
* Move semantics
* Rule of Zero / Rule of Five
* STL containers
* CMake project organization
* Automated testing
* Debugging and sanitizers

---

# Project Goal

The goal of this project is to build a library management system while applying modern C++ resource management techniques.

The main focus is not only creating a functional application, but designing the system with:

* Clear ownership rules
* Automatic resource management
* Safe object lifetime control
* Maintainable project structure

---

# Concepts Applied

## RAII (Resource Acquisition Is Initialization)

RAII is used throughout the project to guarantee that resources are properly acquired and released automatically through object lifetime.

Examples:

* Automatic resource cleanup.
* Objects managing their own lifetime.
* Scoped resources.

The goal is to prevent:

* Memory leaks
* Double deletion
* Invalid resource access

---

# Ownership Model

The project demonstrates different ownership relationships between objects.

## unique_ptr

Used when a resource has a single owner.

Example:

```cpp
std::unique_ptr<Book>
```

The `Library` class owns the books and is responsible for their lifetime.

Example:

```cpp
library.addBook(
    std::make_unique<Book>("Clean Code")
);
```

Ownership is transferred to the library.

---

## shared_ptr

Used when multiple parts of the system need shared access to the same object.

Example:

```cpp
std::shared_ptr<Loan>
```

A loan can be referenced by multiple components while keeping the object alive as long as references exist.

---

## weak_ptr

Used when an object only needs to observe another object without owning it.

Example:

```cpp
std::weak_ptr<Loan>
```

This prevents circular references and allows objects to be destroyed correctly.

---

# System Architecture

The system is divided into the following components:

## Book

Represents a book in the library.

Responsibilities:

* Store book information.
* Maintain book data.
* Follow modern C++ object lifetime practices.

---

## Library

Responsible for managing books.

The library owns `Book` objects using `std::unique_ptr`.

This means the library controls the lifetime of the books.

---

## User

Represents users registered in the system.

Users can access loan information but do not own the related resources.

---

## Loan

Represents a book loan.

Uses smart pointers where shared ownership or non-owning references are required.

---

# Project Structure

```text
Library/
│
├── README.md
├── CMakeLists.txt
│
├── include/
│   ├── Book.hpp
│   ├── User.hpp
│   ├── Loan.hpp
│   └── Library.hpp
│
├── src/
│   ├── Book.cpp
│   ├── User.cpp
│   ├── Loan.cpp
│   ├── Library.cpp
│   └── main.cpp
│
├── tests/
│   ├── CMakeLists.txt
│   ├── BookTest.cpp
│   ├── OwnershipTest.cpp
│   └── LibraryTest.cpp
│
└── build/
```

---

# Build System

The project uses a modular CMake structure.

The root:

```text
CMakeLists.txt
```

handles the main project configuration.

The tests directory contains its own:

```text
tests/CMakeLists.txt
```

to keep test configuration separated from the main application.

---

# Testing

Tests are used to validate:

* Object creation and destruction.
* RAII behavior.
* Ownership transfer.
* Smart pointer usage.
* Library operations.

Run tests:

```bash
ctest
```

---

# Requirements

* C++17 or newer
* CMake 3.20+
* Compatible compiler:

  * Clang
  * GCC
  * MSVC

---

# Building the Project

Clone the repository:

```bash
git clone git@github.com:YOUR_USERNAME/Library.git
```

Navigate into the project:

```bash
cd Library
```

Create a build directory:

```bash
mkdir build
cd build
```

Configure the project:

```bash
cmake ..
```

Build:

```bash
cmake --build .
```

Run:

```bash
./Library
```

---

# Tools Used

* C++
* CMake
* Git
* GoogleTest
* AddressSanitizer
* UndefinedBehaviorSanitizer
* LLDB/GDB

---

# Future Improvements

Possible improvements:

* Data persistence.
* Database integration.
* User authentication.
* Graphical interface.
* REST API.
* RAII-based logging system.
* Performance benchmarks.

---
