#pragma once
#include <string>
#include <stdexcept>

class Guest{
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
private:
    bool isValidName(const std::string& name) const;
    bool isValidPhoneNumber(const std::string& phoneNumber) const;
public:
    Guest(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber);
    ~Guest();
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;

    /*std::string serialize() const override;
    void deserialize(const std::string& data) override;*/
};

#ifdef TEST
#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

TEST_SUITE("Guest") {
    TEST_CASE("Get Guest Information") {
        Guest guest("John", "Doe", "12345678932");

        REQUIRE_EQ(guest.getFirstName(), "John");
        REQUIRE_EQ(guest.getLastName(), "Doe");
        REQUIRE_EQ(guest.getPhoneNumber(), "12345678932");
    }

    TEST_CASE("Invalid First Name") {
        SUBCASE("Empty First Name") {
            CHECK_THROWS_AS(Guest("", "Doe", "123456789"), std::invalid_argument);
        }

        SUBCASE("Whitespace First Name") {
            CHECK_THROWS_AS(Guest("   ", "Doe", "123456789"), std::invalid_argument);
        }
    }

    TEST_CASE("Invalid Last Name") {
        SUBCASE("Empty Last Name") {
            CHECK_THROWS_AS(Guest("John", "", "123456789"), std::invalid_argument);
        }

        SUBCASE("Whitespace Last Name") {
            CHECK_THROWS_AS(Guest("John", "   ", "123456789"), std::invalid_argument);
        }
    }

    TEST_CASE("Invalid Phone Number") {
        SUBCASE("Empty Phone Number") {
            CHECK_THROWS_AS(Guest("John", "Doe", ""), std::invalid_argument);
        }

        SUBCASE("Whitespace Phone Number") {
            CHECK_THROWS_AS(Guest("John", "Doe", "   "), std::invalid_argument);
        }

        SUBCASE("Invalid Format") {
            CHECK_THROWS_AS(Guest("John", "Doe", "1234"), std::invalid_argument);
        }
    }
}

#endif