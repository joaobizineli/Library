#include "Loan.hpp"

Loan::Loan(
    int book_id,
    std::shared_ptr<User> user)
    : book_id(book_id),
      user(user)
{
}

int Loan::getBookID() const
{
    return book_id;
}
