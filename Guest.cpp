#include "Guest.hpp"

Guest::Guest(const std::string &firstName, const std::string &lastName, const std::string &phoneNumber)
    :firstName(firstName), lastName(lastName), phoneNumber(phoneNumber) {}

std::string Guest::getFirstName() const{
    return this->firstName;
}    
std::string Guest::getLastName() const{
    return this->lastName;
}
std::string Guest::getPhoneNumber() const{
    return this->phoneNumber;
}