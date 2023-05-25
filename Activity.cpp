#include "Activity.hpp"
#include <iostream>

Activity::Activity(const std::string& name) : name(name){
    if (!isValidName(name)) {
        throw std::invalid_argument("Invalid name. Name must consist of letters only.");
    }
    if(name.size() > 20){
        throw std::invalid_argument("Name is longer than it should.");
    }
    if(name.size() < 2){
        throw std::invalid_argument("Name is shorter than it should.");
    }
}
Activity::~Activity() = default;
std::string Activity::getName() const {
    return this->name;
}
void Activity::setName(const std::string& name) {
    this->name = name;
}
bool Activity::isValidName(const std::string& name) const {
    for (char c : name) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}