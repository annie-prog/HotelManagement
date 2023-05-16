#include "Accommodation.hpp"

Accommodation::Accommodation() : guests(nullptr), numGuests(0) {}

Accommodation::~Accommodation() {
    delete[] this->guests;
}
void Accommodation::addGuest(Guest* guest) {
    Guest** temp = new Guest*[this->numGuests + 1];
    for (int i = 0; i < numGuests; ++i) {
        temp[i] = this->guests[i];
    }
    temp[this->numGuests] = guest;
    delete[] this->guests;
    this->guests = temp;
    this->numGuests++;
}
Guest** Accommodation::getGuests() const {
    return this->guests;
}
unsigned int Accommodation::getNumGuests() const {
    return this->numGuests;
}