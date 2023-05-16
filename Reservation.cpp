#include "Reservation.hpp"

#include "Reservation.hpp"

Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate) : roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate), note(""), numGuests(0), guests(nullptr) {}

Reservation::Reservation(int roomNumber, const std::string& checkInDate, const std::string& checkOutDate, const std::string& note, unsigned int numGuests) : roomNumber(roomNumber), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note), numGuests(numGuests) {
    this->guests = new Guest*[numGuests];
}
void Reservation::deallocate(){
    if (this->guests != nullptr) {
        for (unsigned int i = 0; i < numGuests; i++) {
            delete this->guests[i];
        }
        delete[] this->guests;
    }
}
Reservation::~Reservation() {
    this->deallocate();
}
int Reservation::getRoomNumber() const {
    return this->roomNumber;
}
void Reservation::setRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
}
std::string Reservation::getCheckInDate() const {
    return this->checkInDate;
}
void Reservation::setCheckInDate(const std::string& checkInDate) {
    this->checkInDate = checkInDate;
}
std::string Reservation::getCheckOutDate() const {
    return this->checkOutDate;
}
void Reservation::setCheckOutDate(const std::string& checkOutDate) {
    this->checkOutDate = checkOutDate;
}
std::string Reservation::getNote() const {
    return this->note;
}
void Reservation::checkNote(const std::string& note) {
    this->note = note;
}
unsigned int Reservation::getNumberOfGuests() const {
    return this->numGuests;
}
void Reservation::setNumberOfGuests(unsigned int numGuests) {
    this->deallocate();

    this->numGuests = numGuests;
    this->guests = new Guest*[numGuests];
}
Guest** Reservation::getGuests() const {
    return this->guests;
}
void Reservation::addGuest(Guest* guest) {
    for (unsigned int i = 0; i < numGuests; i++) {
        if (this->guests[i] == nullptr) {
            this->guests[i] = guest;
            return;
        }
    }
}
