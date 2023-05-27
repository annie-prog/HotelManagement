#include "Guest.hpp"
#include <cctype>
#include <sstream>

Guest::Guest(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber) : firstName(firstName), lastName(lastName), phoneNumber(phoneNumber) {
    if (!isValidName(firstName) || !isValidName(lastName)) {
        throw std::invalid_argument("Invalid name. Name must consist of letters only.");
    }
    if (!isValidPhoneNumber(phoneNumber)) {
        throw std::invalid_argument("Invalid phone number. Phone number must consist of digits only.");
    }
    if(phoneNumber.size() > 13){
        throw std::invalid_argument("Phone number is longer than it should.");
    }
    if(phoneNumber.size() < 10){
        throw std::invalid_argument("Phone number is shorter than it should.");
    }
    if((firstName.size() > 20) || lastName.size() > 20){
        throw std::invalid_argument("Name is longer than it should.");
    }
    if((firstName.size() < 2) || lastName.size() < 2){
        throw std::invalid_argument("Name is shorter than it should.");
    }
}
Guest::~Guest() = default;
std::string Guest::getFirstName() const {
    return this->firstName;
}
std::string Guest::getLastName() const {
    return this->lastName;
}
std::string Guest::getPhoneNumber() const {
    return this->phoneNumber;
}
bool Guest::isValidName(const std::string& name) const {
    for (char c : name) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}
bool Guest::isValidPhoneNumber(const std::string& phoneNumber) const {
    for (char c : phoneNumber) {
        if (!std::isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}
/*std::string Guest::serialize() const{
    std::stringstream ss;
    ss << firstName << "," << lastName << "," << phoneNumber;
    return ss.str();
}

void Guest::deserialize(const std::string& data){
    std::stringstream ss(data);
    std::getline(ss, firstName, ',');
    std::getline(ss, lastName, ',');
    std::getline(ss, phoneNumber, ',');
}*/