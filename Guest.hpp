#pragma once
#include <string>
#include <stdexcept>

class Guest {
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
};

#ifdef TEST
#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

TEST_SUITE("Guest") {
    TEST_CASE("Get Guest Information") {
        Guest guest("John", "Doe", "123456789");

        REQUIRE_EQ(guest.getFirstName(), "John");
        REQUIRE_EQ(guest.getLastName(), "Doe");
        REQUIRE_EQ(guest.getPhoneNumber(), "123456789");
    }
}

#endif