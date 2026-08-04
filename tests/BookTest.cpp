#include <gtest/gtest.h>
#include "Book.hpp"


TEST(BookTest, StoresTitleAuthorAndID)
{
    Book book(
        "C++ Primer",
        "Stanley Lippman",
        20
    );

    EXPECT_EQ(book.getTitle(), "C++ Primer");
    EXPECT_EQ(book.getAuthor(), "Stanley Lippman");
    EXPECT_EQ(book.getID(), 20);
}
