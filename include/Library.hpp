#pragma once

#include <vector>
#include <memory>

class Book;
class Loan;
class User;

class Library
{
private:
    std::vector<std::unique_ptr<Book>> books;

    std::vector<std::shared_ptr<Loan>> loans;

public:
    void addBook(
        std::unique_ptr<Book> book);

    void addLoan(
        std::shared_ptr<Loan> loan);

    Book *findBook(int id) const;

    const std::vector<std::unique_ptr<Book>> &getBooks() const;

    std::shared_ptr<Loan> borrowBook(
        int book_id,
        std::shared_ptr<User> user);
};
