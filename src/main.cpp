#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Library.hpp"
#include "Book.hpp"
#include "User.hpp"
#include "Loan.hpp"

namespace
{
    std::optional<int> readInt()
    {
        int value;

        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return std::nullopt;
        }

        return value;
    }

    std::string readLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string line;
        std::getline(std::cin, line);

        return line;
    }

    void printMenu()
    {
        std::cout
            << "\n=============================\n"
            << "   Library Management System\n"
            << "=============================\n"
            << "1. Listar livros\n"
            << "2. Consultar livro por ID\n"
            << "3. Adicionar livro\n"
            << "4. Listar usuarios\n"
            << "5. Adicionar usuario\n"
            << "6. Emprestar livro\n"
            << "0. Sair\n"
            << "Escolha uma opcao: ";
    }

    void printBook(const Book &book)
    {
        std::cout
            << "[" << book.getID() << "] "
            << book.getTitle()
            << " - " << book.getAuthor()
            << "\n";
    }

    void listBooks(const Library &library)
    {
        const auto &books = library.getBooks();

        if (books.empty())
        {
            std::cout << "Nenhum livro cadastrado.\n";
            return;
        }

        for (const auto &book : books)
        {
            printBook(*book);
        }
    }

    void findBookByID(const Library &library)
    {
        std::cout << "ID do livro: ";

        auto id = readInt();

        if (!id)
        {
            std::cout << "ID invalido.\n";
            return;
        }

        const Book *book = library.findBook(*id);

        if (book == nullptr)
        {
            std::cout << "Livro nao encontrado.\n";
            return;
        }

        printBook(*book);
    }

    void addBookInteractive(Library &library)
    {
        std::cout << "Titulo: ";
        std::string title = readLine();

        std::cout << "Autor: ";
        std::string author = readLine();

        std::cout << "ID: ";
        auto id = readInt();

        if (!id)
        {
            std::cout << "ID invalido.\n";
            return;
        }

        if (library.findBook(*id) != nullptr)
        {
            std::cout << "Ja existe um livro com esse ID.\n";
            return;
        }

        library.addBook(
            std::make_unique<Book>(title, author, *id));

        std::cout << "Livro adicionado com sucesso!\n";
    }

    void listUsers(const std::vector<std::shared_ptr<User>> &users)
    {
        if (users.empty())
        {
            std::cout << "Nenhum usuario cadastrado.\n";
            return;
        }

        for (std::size_t i = 0; i < users.size(); ++i)
        {
            std::cout << "[" << i << "] " << users[i]->getName() << "\n";
        }
    }

    void addUserInteractive(std::vector<std::shared_ptr<User>> &users)
    {
        std::cout << "Nome: ";
        std::string name = readLine();

        users.push_back(
            std::make_shared<User>(name));

        std::cout << "Usuario adicionado com sucesso!\n";
    }

    void borrowBookInteractive(
        Library &library,
        const std::vector<std::shared_ptr<User>> &users)
    {
        if (users.empty())
        {
            std::cout << "Cadastre um usuario primeiro.\n";
            return;
        }

        listUsers(users);

        std::cout << "Indice do usuario: ";
        auto userIndex = readInt();

        if (!userIndex ||
            *userIndex < 0 ||
            static_cast<std::size_t>(*userIndex) >= users.size())
        {
            std::cout << "Usuario invalido.\n";
            return;
        }

        std::cout << "ID do livro: ";
        auto bookId = readInt();

        if (!bookId)
        {
            std::cout << "ID invalido.\n";
            return;
        }

        const auto &user = users[*userIndex];

        auto loan = library.borrowBook(*bookId, user);

        if (loan == nullptr)
        {
            std::cout << "Nao foi possivel emprestar (livro inexistente ou ja emprestado).\n";
            return;
        }

        std::cout
            << "Emprestimo realizado: "
            << user->getName()
            << " pegou o livro ID " << loan->getBookID()
            << "\n";
    }
}

int main()
{
    Library library;
    std::vector<std::shared_ptr<User>> users;

    library.addBook(
        std::make_unique<Book>("Clean Code", "Robert C. Martin", 1));

    library.addBook(
        std::make_unique<Book>("Effective Modern C++", "Scott Meyers", 2));

    library.addBook(
        std::make_unique<Book>("The Pragmatic Programmer", "Andrew Hunt", 3));

    users.push_back(
        std::make_shared<User>("Jaypas"));

    while (true)
    {
        printMenu();

        auto option = readInt();

        if (!option)
        {
            std::cout << "Opcao invalida.\n";
            continue;
        }

        switch (*option)
        {
        case 1:
            listBooks(library);
            break;
        case 2:
            findBookByID(library);
            break;
        case 3:
            addBookInteractive(library);
            break;
        case 4:
            listUsers(users);
            break;
        case 5:
            addUserInteractive(users);
            break;
        case 6:
            borrowBookInteractive(library, users);
            break;
        case 0:
            std::cout << "Encerrando...\n";
            return 0;
        default:
            std::cout << "Opcao invalida.\n";
        }
    }
}
