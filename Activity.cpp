#include "Activity.hpp"
#include <iostream>

Activity::Activity(const std::string& name) : name(name), accommodation(){
    if (!IsValidName(name)) {
        throw std::invalid_argument("Invalid name. Name must have only letters.");
    }
    if(name.size() > 20){
        throw std::invalid_argument("Too long name.");
    }
    if(name.size() < 2){
        throw std::invalid_argument("Too short name.");
    }
}
Activity::~Activity() = default;
std::string Activity::GetName() const {
    return this->name;
}
void Activity::SetName(const std::string& name) {
    this->name = name;
}
Accommodation& Activity::GetAccommodation() {
    return this->accommodation;
}
void Activity::SetAccommodation(const Accommodation& accommodation) {
    this->accommodation = accommodation;
}
bool Activity::IsValidName(const std::string& name) const {
    for (int i = 0; i < name.size(); i++){
        if (!std::isalpha(name[i])) {
            return false;
        }
    }
    return true;
}
void Activity::AddGuest(const Guest& guest) {
    accommodation.AddGuest(guest);
}