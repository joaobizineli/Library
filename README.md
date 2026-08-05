# Library Management System

A modern **C++ Library Management System** designed to study and apply professional software engineering practices, memory management, and modern C++ architecture.

This project focuses on understanding and implementing core C++ concepts such as:

* RAII (Resource Acquisition Is Initialization)
* Ownership and resource management
* Smart pointers (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`)
* Move semantics
* Rule of Zero
* STL containers
* CMake project organization
* Automated testing

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
std::weak_ptr<User>
```

A `Loan` observes the `User` it belongs to without owning it. Since `User` also holds a `shared_ptr<Loan>`, using `shared_ptr` on both sides would create a reference cycle that leaks memory (neither object's refcount would ever reach zero). The `weak_ptr` on the `Loan` side breaks that cycle.

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

Responsible for managing books and loans.

The library owns `Book` objects using `std::unique_ptr` and controls their lifetime. It also holds `std::shared_ptr<Loan>`, sharing ownership of active loans with the `User` that borrowed the book.

Responsibilities:

* `addBook` — registers a new book (transfers ownership to the library).
* `findBook(id)` — looks up a book by ID, returning a non-owning `Book*` (or `nullptr` if not found).
* `getBooks()` — read-only access to the full catalog.
* `borrowBook(id, user)` — validates that the book exists and isn't already on loan, then creates the `Loan` and registers it with both the library and the user. Returns `nullptr` if the borrow is invalid.

A `Loan` refers to its book by **ID (`int`)**, not by pointer. Since the `Library` is the sole owner of each `Book` (via `unique_ptr`), no other object is allowed to hold a pointer to it — that would either fight the `unique_ptr` for ownership or risk becoming a dangling pointer if the book were ever removed. An ID is looked up through `Library::findBook` on demand instead.

---

## User

Represents users registered in the system.

A `User` shares ownership of the `Loan`s associated with it (`std::shared_ptr<Loan>`), alongside the `Library`.

---

## Loan

Represents a book loan.

Holds the borrowed book's ID (`int`, not a pointer — see above) and a `std::weak_ptr<User>` observing the borrower without owning them, which avoids a reference cycle with `User`'s `shared_ptr<Loan>`.

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

This launches an interactive terminal menu, pre-loaded with a few example books and a user, where you can list/search books, register books and users, and borrow a book:

```text
1. Listar livros
2. Consultar livro por ID
3. Adicionar livro
4. Listar usuarios
5. Adicionar usuario
6. Emprestar livro
0. Sair
```

---

# Tools Used

* C++
* CMake
* Git
* GoogleTest

---
