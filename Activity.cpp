#include "Activity.hpp"

Activity::Activity(const std::string& name) : name(name) {}

Activity::~Activity() {}

const std::string Activity::getName() const {
    return this->name;
}
void Activity::setName(const std::string& name) {
    this->name = name;
}
void Activity::addGuest(Guest* guest) {
    guests.push_back(guest);
}
std::vector<Guest*> Activity::getGuests() const {
    return this->guests;
}