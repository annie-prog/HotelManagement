#include "Accommodation.hpp"
#include <stdexcept>

Accommodation::Accommodation() : guests(nullptr), numGuests(0) {}

Accommodation::~Accommodation() {
    delete[] this->guests;
}
void Accommodation::AddGuest(const Guest& guest) {
    Guest** newGuests = new Guest*[numGuests + 1];

    for (unsigned int i = 0; i < numGuests; i++) {
        newGuests[i] = guests[i];
    }
    newGuests[numGuests] = new Guest(guest);

    delete[] guests;
    guests = newGuests;
    numGuests++;
}
Guest** Accommodation::GetGuests() const {
    return this->guests;
}
unsigned int Accommodation::GetNumGuests() const {
    return this->numGuests;
}
void Accommodation::SetGuests(Guest** guests) {
    this->guests = guests;
}
void Accommodation::SetNumGuests(unsigned int numGuests) {
    this->numGuests = numGuests;
}
void Accommodation::ClearGuests() {
    if (guests) {
        delete[] guests;
        guests = nullptr;
        numGuests = 0;
    }
}