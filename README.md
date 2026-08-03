# Library Management System

Um sistema de gerenciamento de biblioteca desenvolvido em **C++ moderno**, com foco em boas práticas de engenharia de software, gerenciamento de memória e conceitos fundamentais da linguagem.

Este projeto foi criado para estudar e aplicar conceitos como **RAII**, **ownership**, **smart pointers**, **move semantics**, **STL**, **CMake** e organização de projetos C++.

---

## Objetivos do projeto

O principal objetivo é construir um sistema organizado que demonstre como o C++ moderno gerencia recursos de forma segura e eficiente.

Conceitos aplicados:

* RAII (Resource Acquisition Is Initialization)
* Ownership e gerenciamento de recursos
* `std::unique_ptr`
* `std::shared_ptr`
* `std::weak_ptr`
* Move semantics (`std::move`)
* Rule of Zero / Rule of Five
* Containers da STL
* CMake
* Testes automatizados
* Debugging e sanitizers

---

# Arquitetura

O sistema representa uma biblioteca onde usuários podem cadastrar livros e realizar empréstimos.

Principais componentes:

## Book

Representa um livro dentro do sistema.

Responsabilidades:

* Armazenar informações do livro.
* Gerenciar seus próprios dados.
* Utilizar o conceito de Rule of Zero quando possível.

---

## Library

Responsável pelo gerenciamento dos livros.

A biblioteca possui ownership dos livros utilizando:

```cpp
std::unique_ptr<Book>
```

Isso significa que a biblioteca é a única responsável pelo ciclo de vida dos objetos `Book`.

Exemplo:

```cpp
library.addBook(
    std::make_unique<Book>("Clean Code")
);
```

Após adicionar o livro, a propriedade do recurso é transferida para a biblioteca.

---

## User

Representa usuários cadastrados no sistema.

Usuários podem acessar informações de empréstimos, mas não são donos dos objetos relacionados.

---

## Loan

Representa um empréstimo realizado.

Utiliza:

```cpp
std::shared_ptr<Loan>
```

quando múltiplas partes do sistema precisam compartilhar acesso ao mesmo recurso.

---

## weak_ptr e prevenção de ciclos

Relacionamentos que não representam ownership utilizam:

```cpp
std::weak_ptr
```

Isso evita ciclos de referência entre objetos e permite que os recursos sejam destruídos corretamente.

---

# RAII

O projeto utiliza RAII para garantir que recursos sejam liberados automaticamente.

Exemplos:

* Arquivos abertos e fechados automaticamente.
* Conexões simuladas com ciclo de vida controlado.
* Objetos destruídos automaticamente ao sair do escopo.

O objetivo é evitar:

* Memory leaks
* Double free
* Uso de objetos inválidos

---

# Estrutura do projeto

```
Library/
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
│
├── CMakeLists.txt
└── README.md
```

---

# Requisitos

* C++17 ou superior
* CMake 3.20+
* Compilador compatível:

  * GCC
  * Clang
  * MSVC

---

# Como compilar

Clone o repositório:

```bash
git clone git@github.com:SEU_USUARIO/Library.git
```

Entre na pasta:

```bash
cd Library
```

Crie a pasta de build:

```bash
mkdir build
cd build
```

Configure o projeto:

```bash
cmake ..
```

Compile:

```bash
cmake --build .
```

Execute:

```bash
./Library
```

---

# Testes

Os testes serão executados utilizando o sistema configurado pelo CMake.

Exemplo:

```bash
ctest
```

---

# Ferramentas utilizadas

* C++
* CMake
* Git
* GoogleTest
* AddressSanitizer
* UndefinedBehaviorSanitizer
* LLDB/GDB

---

# O que este projeto demonstra

Este projeto demonstra:

* Como projetar sistemas usando ownership explícito.
* Como evitar gerenciamento manual de memória.
* Como utilizar smart pointers corretamente.
* Como aplicar princípios modernos de C++.
* Como estruturar um projeto profissional usando CMake.

---

# Próximos passos

Possíveis melhorias:

* Persistência de dados em arquivos.
* Banco de dados.
* Interface gráfica.
* API REST.
* Sistema de autenticação.
* Logs utilizando RAII.
* Benchmark de performance.

---

## Autor

Amil

Projeto desenvolvido como estudo de C++ moderno e gerenciamento seguro de recursos.
