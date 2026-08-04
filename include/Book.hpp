#pragma once

#include <string>

class Book
{
private:
    std::string title;
    std::string author;
    const int id;

public:
    Book(
        std::string title,
        std::string author,
        int id);

    const std::string &getTitle() const;

    const std::string &getAuthor() const;

    int getID() const;
};
