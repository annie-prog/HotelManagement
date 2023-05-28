#pragma once
#include <string>
#include <stdexcept>
#include <set>

class Guest{
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    static std::set<std::string> phoneNumbersSet;
private:
    bool IsValidName(const std::string& name) const;
    bool IsValidPhoneNumber(const std::string& phoneNumber) const;
public:
    Guest(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber);
    ~Guest();
    std::string GetFirstName() const;
    std::string GetLastName() const;
    std::string GetPhoneNumber() const;
};

#ifdef TEST
#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

TEST_SUITE("Guest") {
    TEST_CASE("Get Guest Information") {
        Guest guest("Aneliya", "Konarcheva", "0836475867");

        REQUIRE_EQ(guest.GetFirstName(), "Aneliya");
        REQUIRE_EQ(guest.GetLastName(), "Konarcheva");
        REQUIRE_EQ(guest.GetPhoneNumber(), "0836475867");
    }

    TEST_CASE("Invalid First Name") {
        SUBCASE("Empty First Name") {
            CHECK_THROWS_AS(Guest("", "Konarcheva", "0836475867"), std::invalid_argument);
        }

        SUBCASE("Whitespace First Name") {
            CHECK_THROWS_AS(Guest("   ", "Konarcheva", "0836475867"), std::invalid_argument);
        }
    }

    TEST_CASE("Invalid Last Name") {
        SUBCASE("Empty Last Name") {
            CHECK_THROWS_AS(Guest("Aneliya", "", "0836475867"), std::invalid_argument);
        }

        SUBCASE("Whitespace Last Name") {
            CHECK_THROWS_AS(Guest("Aneliya", "   ", "0836475867"), std::invalid_argument);
        }
    }

    TEST_CASE("Invalid Phone Number") {
        SUBCASE("Empty Phone Number") {
            CHECK_THROWS_AS(Guest("Aneliya", "Konarcheva", ""), std::invalid_argument);
        }

        SUBCASE("Whitespace Phone Number") {
            CHECK_THROWS_AS(Guest("Aneliya", "Konarcheva", "   "), std::invalid_argument);
        }

        SUBCASE("Invalid Format") {
            CHECK_THROWS_AS(Guest("Aneliya", "Konarcheva", "1234"), std::invalid_argument);
        }
    }
}

#endif