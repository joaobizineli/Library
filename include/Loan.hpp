#pragma once

#include <memory>
#include <string>

class User;

class Loan
{
private:
    int book_id;

    std::weak_ptr<User> user;

public:
    Loan(
        int book_id,
        std::shared_ptr<User> user);

    int getBookID() const;

    std::string getBorrowerName() const;
};
