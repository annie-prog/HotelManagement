#include "Guest.hpp"
#include <cctype>
#include <sstream>

std::set<std::string> Guest::phoneNumbersSet; // Initialize the static set for phone numbers

Guest::Guest(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber) : firstName(firstName), lastName(lastName), phoneNumber(phoneNumber) {
    // Some cases for constructor to throw exceptions
    if (!IsValidName(firstName) || !IsValidName(lastName)) {
        throw std::invalid_argument("Invalid name. Name must have only letters.");
        std::exit(0);
    }
    if (!IsValidPhoneNumber(phoneNumber)) {
        throw std::invalid_argument("Invalid phone number. Phone number must have only digits.");
        std::exit(0);
    }
    if (phoneNumber.size() > 13) {
        throw std::invalid_argument("Too lond phone number.");
        std::exit(0);
    }
    if (phoneNumber.size() < 10) {
        throw std::invalid_argument("Too short phone number.");
        std::exit(0);
    }
    if ((firstName.size() > 20) || (lastName.size() > 20)) {
        throw std::invalid_argument("Too long name.");
        std::exit(0);
    }
    if ((firstName.size() < 2) || (lastName.size() < 2)) {
        throw std::invalid_argument("Too short name.");
        std::exit(0);
    }
    if (phoneNumbersSet.find(phoneNumber) != phoneNumbersSet.end()) {
        throw std::invalid_argument("Phone number already exists.");
        std::exit(0);
    }
    phoneNumbersSet.insert(phoneNumber);
}
Guest::~Guest() {
    phoneNumbersSet.erase(phoneNumber); // Remove phone number from the set
}
std::string Guest::GetFirstName() const {
    return this->firstName;
}
std::string Guest::GetLastName() const {
    return this->lastName;
}
std::string Guest::GetPhoneNumber() const {
    return this->phoneNumber;
}
bool Guest::IsValidName(const std::string& name) const {
    for (int i = 0; i < name.size(); i++){
        if (!std::isalpha(name[i])) {
            return false; // Return false if any character is not a letter
        }
    }
    return true; // All characters are letters and the name is valid
}
bool Guest::IsValidPhoneNumber(const std::string& phoneNumber) const {
    for (int i = 0; i < phoneNumber.size(); i++){
        if (!std::isdigit(phoneNumber[i]) && phoneNumber[i] != '-') {
            return false; // Return false if any character is not a digit or a dash
        }
    }
    return true; // All characters are digits or dashes and the phone number is valid
}