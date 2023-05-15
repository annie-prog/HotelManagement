#pragma once
#include <string>

class Guest{
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
public:
    Guest(const std::string &firstName, const std::string &lastName, const std::string &phoneNumber);
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;
};