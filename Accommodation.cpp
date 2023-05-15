#include "Accommodation.hpp"

Accommodation::~Accommodation() {}

void Accommodation::addGuest(Guest* guest){
    guests.push_back(guest);
}
std::vector<Guest*> Accommodation::getGuests() const{
    return this->guests;
}