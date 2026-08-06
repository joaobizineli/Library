#include <gtest/gtest.h>

#include <memory>

#include "Library.hpp"
#include "Book.hpp"
#include "Loan.hpp"
#include "User.hpp"



TEST(OwnershipTest, UniquePtrTransfersOwnership)
{
    auto book =
        std::make_unique<Book>(
            "Effective Modern C++",
            "Scott Meyers",
            10
        );


    EXPECT_NE(
        book,
        nullptr
    );


    Library library;


    library.addBook(
        std::move(book)
    );


    // Ownership was transferred
    EXPECT_EQ(
        book,
        nullptr
    );
}



TEST(OwnershipTest, SharedPtrKeepsObjectAlive)
{
    auto user =
        std::make_shared<User>(
            "Amil"
        );


    auto loan =
        std::make_shared<Loan>(
            10,
            user
        );


    EXPECT_EQ(
        loan.use_count(),
        1
    );


    {
        auto another_reference = loan;


        EXPECT_EQ(
            loan.use_count(),
            2
        );
    }


    EXPECT_EQ(
        loan.use_count(),
        1
    );
}



TEST(OwnershipTest, WeakPtrDoesNotIncreaseReferenceCount)
{
    auto user =
        std::make_shared<User>(
            "Jaypas"
        );


    auto loan =
        std::make_shared<Loan>(
            10,
            user
        );


    EXPECT_EQ(
        loan.use_count(),
        1
    );


    std::weak_ptr<Loan> observer = loan;


    // weak_ptr is only an observer
    EXPECT_EQ(
        loan.use_count(),
        1
    );


    EXPECT_FALSE(
        observer.expired()
    );
}



TEST(OwnershipTest, WeakPtrExpiresWhenOwnerDies)
{
    std::weak_ptr<Loan> observer;


    {
        auto user =
            std::make_shared<User>(
                "Jaypas"
            );


        auto loan =
            std::make_shared<Loan>(
                10,
                user
            );


        observer = loan;


        EXPECT_FALSE(
            observer.expired()
        );
    }


    EXPECT_TRUE(
        observer.expired()
    );
}



TEST(OwnershipTest, LoanObservesUserWithoutOwningIt)
{
    std::shared_ptr<Loan> loan;


    {
        auto user =
            std::make_shared<User>(
                "Jaypas"
            );


        loan =
            std::make_shared<Loan>(
                10,
                user
            );


        EXPECT_EQ(
            loan->getBorrowerName(),
            "Jaypas"
        );
    }


    // user died at the end of the block; Loan only held a weak_ptr
    EXPECT_EQ(
        loan->getBorrowerName(),
        "<unknown>"
    );
}
