#include "User.hpp"

#include <utility>

User::User(std::string name)
    : name(std::move(name))
{
}

const std::string &User::getName() const
{
    return name;
}

void User::addLoan(
    std::shared_ptr<Loan> loan)
{
    loans.push_back(loan);
}
