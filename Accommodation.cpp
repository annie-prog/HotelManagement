#include "Accommodation.hpp"
#include <stdexcept>

Accommodation::Accommodation() : guests(nullptr), numGuests(0) {}

Accommodation::~Accommodation() {
    delete[] this->guests;
}
void Accommodation::addGuest(const Guest& guest) {
    Guest** newGuests = new Guest*[numGuests + 1];

    for (unsigned int i = 0; i < numGuests; i++) {
        newGuests[i] = guests[i];
    }
    newGuests[numGuests] = new Guest(guest);

    delete[] guests;
    guests = newGuests;
    numGuests++;
}
Guest** Accommodation::getGuests() const {
    return this->guests;
}
unsigned int Accommodation::getNumGuests() const {
    return this->numGuests;
}
void Accommodation::setGuests(Guest** guests) {
    this->guests = guests;
}
void Accommodation::setNumGuests(unsigned int numGuests) {
    this->numGuests = numGuests;
}
void Accommodation::clearGuests() {
    if (guests) {
        delete[] guests;
        guests = nullptr;
        numGuests = 0;
    }
}