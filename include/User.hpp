#pragma once

#include <string>
#include <vector>
#include <memory>

class Loan;

class User
{
private:
    std::string name;

    std::vector<std::shared_ptr<Loan>> loans;

public:
    User(std::string name);

    const std::string &getName() const;

    void addLoan(
        std::shared_ptr<Loan> loan);
};
