#include "Accommodation.hpp"
#include <stdexcept>

Accommodation::Accommodation() : guests(nullptr), numGuests(0) {}

Accommodation::~Accommodation() {
    delete[] this->guests;
}
void Accommodation::addGuest(Guest* guest) {
    if (guest == nullptr) {
        throw std::invalid_argument("Invalid guest provided.");
    }
    try {
        Guest** temp = new Guest*[this->numGuests + 1];
        for (int i = 0; i < numGuests; ++i) {
            temp[i] = this->guests[i];
        }
        temp[this->numGuests] = guest;
        delete[] this->guests;
        this->guests = temp;
        this->numGuests++;
    } 
    catch (std::bad_alloc& e) {
        throw std::runtime_error("Failed to allocate memory for guests.");
    }
}
Guest** Accommodation::getGuests() const {
    return this->guests;
}
unsigned int Accommodation::getNumGuests() const {
    return this->numGuests;
}