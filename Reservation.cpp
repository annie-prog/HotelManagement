#include "Reservation.hpp"

Reservation::Reservation(const std::string &checkInDate, const std::string &checkOutDate)
    : checkInDate(checkInDate), checkOutDate(checkOutDate){}

Reservation::Reservation(int roomNumber, const std::string &checkInDate, const std::string &checkOutDate, const std::string &note, unsigned int numGuests)
    : roomNumber(roomNumber), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note), numGuests(numGuests) {}

Reservation::~Reservation() {}

int Reservation::getRoomNumber() const {
    return roomNumber;
}
void Reservation::setRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
}
std::string Reservation::getCheckInDate() const {
    return checkInDate;
}
void Reservation::setCheckInDate(const std::string &checkIn) {
    this->checkInDate = checkIn;
}
std::string Reservation::getCheckOutDate() const {
    return checkOutDate;
}
void Reservation::setCheckOutDate(const std::string &checkOut) {
    this->checkOutDate = checkOut;
}
std::string Reservation::getNote() const {
    return note;
}
void Reservation::checkNote(const std::string &note) {
    this->note = note;
}
unsigned int Reservation::getNumberOfGuests() const {
    return numGuests;
}
void Reservation::setNumberOfGuests(unsigned int numGuests) {
    this->numGuests = numGuests;
}
std::vector<Guest*> Reservation::getGuests() const {
    return guests;
}
void Reservation::addGuest(Guest* guest) {
    guests.push_back(guest);
}