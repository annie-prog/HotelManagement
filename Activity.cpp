#include "Activity.hpp"
#include <iostream>

Activity::Activity(const std::string& name) : name(name), guests(nullptr), guestsCount(0) {}

Activity::~Activity() {
    if (this->guests != nullptr) {
        for (unsigned int i = 0; i < this->guestsCount; i++) {
            delete this->guests[i];
        }
        delete[] this->guests;
    }
}
const std::string Activity::getName() const {
    return this->name;
}
void Activity::setName(const std::string& name) {
    this->name = name;
}
void Activity::addGuest(Guest* guest) {
    Guest** newGuests = new Guest*[this->guestsCount + 1];
    for (unsigned int i = 0; i < this->guestsCount; i++) {
        newGuests[i] = this->guests[i];
    }
    newGuests[this->guestsCount] = guest;

    delete[] this->guests;
    this->guests = newGuests;
    this->guestsCount++;
}
Guest** Activity::getGuests() const {
    return this->guests;
}
unsigned int Activity::getGuestsCount() const{
    return this->guestsCount;
}
void Activity::printGuests() const {
    if (guestsCount != 0) {
        for (unsigned int i = 0; i < guestsCount; i++) {
            std::cout << "Guest Name: " << guests[i]->getFirstName() << " " << guests[i]->getLastName() << std::endl;
            std::cout << "Guest Phone: " << guests[i]->getPhoneNumber() << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    } 
    else {
        std::cout << "No guests for this activity." << std::endl;
    }
}