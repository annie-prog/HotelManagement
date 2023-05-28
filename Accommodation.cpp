#include "Accommodation.hpp"
#include <stdexcept>

Accommodation::Accommodation() : guests(nullptr), numGuests(0) {}

Accommodation::~Accommodation() {
    delete[] this->guests; // Deallocate memory for guests array
}
void Accommodation::AddGuest(const Guest& guest) {
    Guest** newGuests = new Guest*[numGuests + 1]; // Create a new array with one additional element

    for (unsigned int i = 0; i < numGuests; i++) {
        newGuests[i] = guests[i]; // Copy existing guests to the new array
    }
    newGuests[numGuests] = new Guest(guest); // Add the new guest to the last element of the new array

    delete[] guests; // Deallocate memory for the old guests array
    guests = newGuests; // Update guests to the new array
    numGuests++; // Increment the number of guests
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
        delete[] guests; // Deallocate memory for guests array
        guests = nullptr; // Set guests to null pointer
        numGuests = 0; // Reset the number of guests to 0
    }
}