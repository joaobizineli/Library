#include "Book.hpp"

#include <utility>

Book::Book(
    std::string title,
    std::string author,
    int id)
    : title(std::move(title)),
      author(std::move(author)),
      id(id)
{
}

const std::string &Book::getTitle() const
{
    return title;
}

const std::string &Book::getAuthor() const
{
    return author;
}

int Book::getID() const
{
    return id;
}
