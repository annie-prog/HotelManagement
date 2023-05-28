#include "Guest.hpp"
#include <cctype>
#include <sstream>

std::set<std::string> Guest::phoneNumbersSet;

Guest::Guest(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber) : firstName(firstName), lastName(lastName), phoneNumber(phoneNumber) {
    if (!IsValidName(firstName) || !IsValidName(lastName)) {
        throw std::invalid_argument("Invalid name. Name must have only letters.");
    }
    if (!IsValidPhoneNumber(phoneNumber)) {
        throw std::invalid_argument("Invalid phone number. Phone number must have only digits.");
    }
    if (phoneNumber.size() > 13) {
        throw std::invalid_argument("Too lond phone number.");
    }
    if (phoneNumber.size() < 10) {
        throw std::invalid_argument("Too short phone number.");
    }
    if ((firstName.size() > 20) || (lastName.size() > 20)) {
        throw std::invalid_argument("Too long name.");
    }
    if ((firstName.size() < 2) || (lastName.size() < 2)) {
        throw std::invalid_argument("Too short name.");
    }
    if (phoneNumbersSet.find(phoneNumber) != phoneNumbersSet.end()) {
        throw std::invalid_argument("Phone number already exists.");
    }
    phoneNumbersSet.insert(phoneNumber);
}
Guest::~Guest() {
    phoneNumbersSet.erase(phoneNumber);
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
            return false;
        }
    }
    return true;
}
bool Guest::IsValidPhoneNumber(const std::string& phoneNumber) const {
    for (int i = 0; i < phoneNumber.size(); i++){
        if (!std::isdigit(phoneNumber[i]) && phoneNumber[i] != '-') {
            return false;
        }
    }
    return true;
}