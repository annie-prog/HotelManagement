#include "Reservation.hpp"
#include <sstream>
#include <iomanip>

Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate)
    : Accommodation(), roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate), note("") {
}
Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate, const std::string& note)
    : Accommodation(), roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {
}
Reservation::Reservation(int roomNumber, const std::string& checkInDate, const std::string& checkOutDate, const std::string& note, unsigned int numGuests)
    : Accommodation(), roomNumber(roomNumber), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {
    setNumberOfGuests(numGuests);
}
Reservation::~Reservation() {}

int Reservation::getRoomNumber() const {
    return this->roomNumber;
}
void Reservation::setRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
}
std::string Reservation::getCheckInDate() const {
    return this->checkInDate;
}
void Reservation::setCheckInDate(const std::string& checkIn) {
    this->checkInDate = checkIn;
}
std::string Reservation::getCheckOutDate() const {
    return this->checkOutDate;
}
void Reservation::setCheckOutDate(const std::string& checkOut) {
    checkOutDate = checkOut;
}
std::string Reservation::getNote() const {
    return note;
}
void Reservation::checkNote(const std::string& note) {
    this->note = note;
}
unsigned int Reservation::getNumGuests() const {
    return numGuests;
}
Guest** Reservation::getGuests() const {
    return guests;
}
void Reservation::addGuest(Guest* guest) {
    Accommodation::addGuest(guest);
}
bool Reservation::includesDate(const std::string& currentDate) const {
    return (currentDate >= checkInDate && currentDate <= checkOutDate);
}
void Reservation::setNumberOfGuests(unsigned int numGuests) {
    if (guests != nullptr) {
        deallocate();
    }
    this->numGuests = numGuests;
    guests = new Guest*[numGuests];
}

void Reservation::deallocate() {
    if (guests != nullptr) {
        for (unsigned int i = 0; i < numGuests; ++i) {
            delete guests[i];
        }
        delete[] guests;
        guests = nullptr;
        numGuests = 0;
    }
}

int Reservation::getUsageDays(const std::string& from, const std::string& to) const {
    std::tm tm_from = {};
    std::tm tm_to = {};
    std::istringstream iss_from(from);
    std::istringstream iss_to(to);
    iss_from >> std::get_time(&tm_from, "%Y-%m-%d");
    iss_to >> std::get_time(&tm_to, "%Y-%m-%d");
    std::time_t time_from = std::mktime(&tm_from);
    std::time_t time_to = std::mktime(&tm_to);

    if (time_from == -1 || time_to == -1) {
        return 0; 
    }

    std::time_t reservation_from = std::mktime(&tm_from);
    std::time_t reservation_to = std::mktime(&tm_to);

    double seconds = std::difftime(reservation_to, reservation_from);
    int days = static_cast<int>(seconds / (24 * 60 * 60));

    if (days < 0) {
        return 0;
    }

    if (reservation_to < time_from || reservation_from > time_to) {
        return 0;
    }
    if (reservation_from < time_from) {
        reservation_from = time_from;
    }
    if (reservation_to > time_to) {
        reservation_to = time_to;
    }

    seconds = std::difftime(reservation_to, reservation_from);
    days = static_cast<int>(seconds / (24 * 60 * 60));

    return days;
}





