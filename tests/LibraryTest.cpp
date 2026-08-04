#include <gtest/gtest.h>

#include <memory>

#include "Library.hpp"
#include "Book.hpp"
#include "Loan.hpp"
#include "User.hpp"


TEST(LibraryTest, AddsBookAndFindsItByID)
{
    Library library;

    library.addBook(
        std::make_unique<Book>(
            "C++ Primer",
            "Stanley Lippman",
            20
        )
    );

    Book *found = library.findBook(20);

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getTitle(), "C++ Primer");
}


TEST(LibraryTest, FindBookReturnsNullptrWhenNotFound)
{
    Library library;

    EXPECT_EQ(library.findBook(999), nullptr);
}


TEST(LibraryTest, BorrowBookCreatesLoanForExistingBook)
{
    Library library;

    library.addBook(
        std::make_unique<Book>(
            "Clean Code",
            "Robert C. Martin",
            1
        )
    );

    auto user = std::make_shared<User>("Jaypas");

    auto loan = library.borrowBook(1, user);

    ASSERT_NE(loan, nullptr);
    EXPECT_EQ(loan->getBookID(), 1);
}


TEST(LibraryTest, BorrowBookFailsWhenBookDoesNotExist)
{
    Library library;

    auto user = std::make_shared<User>("Jaypas");

    auto loan = library.borrowBook(999, user);

    EXPECT_EQ(loan, nullptr);
}


TEST(LibraryTest, BorrowBookFailsWhenAlreadyBorrowed)
{
    Library library;

    library.addBook(
        std::make_unique<Book>(
            "Clean Code",
            "Robert C. Martin",
            1
        )
    );

    auto firstUser = std::make_shared<User>("Jaypas");
    auto secondUser = std::make_shared<User>("Amil");

    auto firstLoan = library.borrowBook(1, firstUser);
    auto secondLoan = library.borrowBook(1, secondUser);

    ASSERT_NE(firstLoan, nullptr);
    EXPECT_EQ(secondLoan, nullptr);
}


TEST(LibraryTest, BorrowBookRegistersLoanInBothLibraryAndUser)
{
    Library library;

    library.addBook(
        std::make_unique<Book>(
            "Clean Code",
            "Robert C. Martin",
            1
        )
    );

    auto user = std::make_shared<User>("Jaypas");

    auto loan = library.borrowBook(1, user);

    ASSERT_NE(loan, nullptr);

    // held by: this local variable, library.loans and user.loans
    EXPECT_EQ(loan.use_count(), 3);
}
