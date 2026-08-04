#include "Library.hpp"
#include "Book.hpp"
#include "Loan.hpp"
#include "User.hpp"

void Library::addBook(
    std::unique_ptr<Book> book)
{
    books.push_back(std::move(book));
}

void Library::addLoan(
    std::shared_ptr<Loan> loan)
{
    loans.push_back(loan);
}

Book *Library::findBook(int id) const
{
    for (const auto &book : books)
    {
        if (book->getID() == id)
        {
            return book.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<Book>> &Library::getBooks() const
{
    return books;
}

std::shared_ptr<Loan> Library::borrowBook(
    int book_id,
    std::shared_ptr<User> user)
{
    Book *book = findBook(book_id);

    if (book == nullptr)
    {
        return nullptr;
    }

    for (const auto &loan : loans)
    {
        if (loan->getBookID() == book_id)
        {
            return nullptr;
        }
    }

    auto loan = std::make_shared<Loan>(
        book_id,
        user);

    addLoan(loan);
    user->addLoan(loan);

    return loan;
}
