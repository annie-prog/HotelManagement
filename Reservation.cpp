#include "Reservation.hpp"
#include <sstream>
#include <iomanip>
#include <regex>
#include <algorithm>

Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate)
    : roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate) {
        if (!isValidDate(checkInDate) || !isValidDate(checkOutDate)) {
            throw std::invalid_argument("Invalid data. Data must consist of digits and dashes only.");
        }
}
Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate, const std::string& note)
    : roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {
        if (!isValidDate(checkInDate) || !isValidDate(checkOutDate)) {
            throw std::invalid_argument("Invalid data. Data must consist of digits and dashes only.");
        }
        if (note.size() < 2) {
            throw std::invalid_argument("Note is shorter than it should.");
        }
        if (note.size() > 20) {
            throw std::invalid_argument("Note is longer than it should.");
        }
}
Reservation::Reservation(int roomNumber, const std::string& checkInDate, const std::string& checkOutDate, const std::string& note)
    : roomNumber(roomNumber), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {
        if (!isValidDate(checkInDate) || !isValidDate(checkOutDate)) {
            throw std::invalid_argument("Invalid data. Data must consist of digits and dashes only.");
        }
        if (note.size() < 2) {
            throw std::invalid_argument("Note is shorter than it should.");
        }
        if (note.size() > 20) {
            throw std::invalid_argument("Note is longer than it should.");
        }
        if (!isValidRoomNumber(roomNumber)) {
            throw std::invalid_argument("Invalid room number. Room number must consist of digits and only.");
        }
}    
Reservation::~Reservation() = default;
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
    if (!isValidDate(checkIn)) {
        throw std::invalid_argument("Invalid data. Data must consist of digits and dashes only.");
    }
    this->checkInDate = checkIn;
}
std::string Reservation::getCheckOutDate() const {
    return this->checkOutDate;
}
void Reservation::setCheckOutDate(const std::string& checkOut) {
    if (!isValidDate(checkOut)) {
        throw std::invalid_argument("Invalid data. Data must consist of digits and dashes only.");
    }
    checkOutDate = checkOut;
}
std::string Reservation::getNote() const {
    return note;
}
void Reservation::checkNote(const std::string& note) {
    this->note = note;
}
Accommodation& Reservation::getAccommodation() {
    return this->accommodation;
}
bool Reservation::includesDate(const std::string& currentDate) const {
    std::tm tm_current = {};
    std::istringstream iss_current(currentDate);
    iss_current >> std::get_time(&tm_current, "%Y-%m-%d");

    std::tm tm_checkIn = {};
    std::istringstream iss_checkIn(checkInDate);
    iss_checkIn >> std::get_time(&tm_checkIn, "%Y-%m-%d");

    std::tm tm_checkOut = {};
    std::istringstream iss_checkOut(checkOutDate);
    iss_checkOut >> std::get_time(&tm_checkOut, "%Y-%m-%d");

    std::time_t time_current = std::mktime(&tm_current);
    std::time_t time_checkIn = std::mktime(&tm_checkIn);
    std::time_t time_checkOut = std::mktime(&tm_checkOut);

    return (time_current >= time_checkIn) && (time_current <= time_checkOut);
}
bool Reservation::isValidDate(const std::string& date) {
    std::regex iso8601Pattern("^\\d{4}-\\d{2}-\\d{2}$");
    if (!std::regex_match(date, iso8601Pattern)) {
        return false;
    }

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    if (month == 2) { 
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeapYear)) {
            return false;
        }
    } 
    else if (month == 4 || month == 6 || month == 9 || month == 11) { 
        if (day > 30) {
            return false;
        }
    }

    return true;
}
bool Reservation::isValidRoomNumber(int roomNumber) const {
    return (roomNumber >= -1000) && (roomNumber <= 1000);
}
Guest** Reservation::getGuests() const {
    return accommodation.getGuests();
}
int Reservation::getNumGuests() const {
    return accommodation.getNumGuests();
}
