#include "Reservation.hpp"
#include <sstream>
#include <iomanip>
#include <regex>
#include <algorithm>

Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate)
    : roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate) {
        // A case which checks if the dates are valid
        if (!IsValidDate(checkInDate) || !IsValidDate(checkOutDate)) {
            throw std::invalid_argument("Invalid data. Data must have only digits and dashes.");
        }
}
Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate, const std::string& note)
    : roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {
        // Some cases for throwing exceptions in the constructor with check-in date, check-out date and note 
        if (!IsValidDate(checkInDate) || !IsValidDate(checkOutDate)) {
            throw std::invalid_argument("Invalid data. Data must have only digits and dashes.");
        }
        if (note.size() < 2) {
            throw std::invalid_argument("Too short note.");
        }
        if (note.size() > 20) {
            throw std::invalid_argument("Too long note.");
        }
}
Reservation::Reservation(int roomNumber, const std::string& checkInDate, const std::string& checkOutDate, const std::string& note)
    : roomNumber(roomNumber), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {
        // Some cases for throwing exceptions in the constructor with room number, check-in date, check-out date and note 
        if (!IsValidDate(checkInDate) || !IsValidDate(checkOutDate)) {
            throw std::invalid_argument("Invalid data. Data must have only digits and dashes.");
        }
        if (note.size() < 2) {
            throw std::invalid_argument("Too short note.");
        }
        if (note.size() > 20) {
            throw std::invalid_argument("Too long note.");
        }
        if (!IsValidRoomNumber(roomNumber)) {
            throw std::invalid_argument("Invalid room number. Room number must have only digits.");
        }
}    
Reservation::~Reservation() = default;
int Reservation::GetRoomNumber() const {
    return this->roomNumber;
}
void Reservation::SetRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
}
std::string Reservation::GetCheckInDate() const {
    return this->checkInDate;
}
void Reservation::SetCheckInDate(const std::string& checkIn) {
    if (!IsValidDate(checkIn)) {
        throw std::invalid_argument("Invalid data. Data must have only digits and dashes.");
    }
    this->checkInDate = checkIn;
}
std::string Reservation::GetCheckOutDate() const {
    return this->checkOutDate;
}
void Reservation::SetCheckOutDate(const std::string& checkOut) {
    if (!IsValidDate(checkOut)) {
        throw std::invalid_argument("Invalid data. Data must have only digits and dashes.");
    }
    checkOutDate = checkOut;
}
std::string Reservation::GetNote() const {
    return this->note;
}
void Reservation::CheckNote(const std::string& note) {
    this->note = note;
}
Accommodation& Reservation::GetAccommodation() {
    return this->accommodation;
}
bool Reservation::IncludesDate(const std::string& currentDate) const {
    // Convert the currentDate string to a std::tm object
    std::tm tm_current = {};
    std::istringstream iss_current(currentDate);
    iss_current >> std::get_time(&tm_current, "%Y-%m-%d");

    // Convert the check-in date string to a std::tm object
    std::tm tm_checkIn = {};
    std::istringstream iss_checkIn(checkInDate);
    iss_checkIn >> std::get_time(&tm_checkIn, "%Y-%m-%d");

    // Convert the check-out date string to a std::tm object
    std::tm tm_checkOut = {};
    std::istringstream iss_checkOut(checkOutDate);
    iss_checkOut >> std::get_time(&tm_checkOut, "%Y-%m-%d");

    // Convert std::tm objects to std::time_t values
    std::time_t time_current = std::mktime(&tm_current);
    std::time_t time_checkIn = std::mktime(&tm_checkIn);
    std::time_t time_checkOut = std::mktime(&tm_checkOut);

    // Check if the current date is within the reservation period
    return (time_current >= time_checkIn) && (time_current <= time_checkOut);
}
bool Reservation::IsValidDate(const std::string& date) {
    // Regular expression pattern to match date format (YYYY-MM-DD)
    std::regex iso8601Pattern("^\\d{4}-\\d{2}-\\d{2}$");

    // Check if the date matches the expected format
    if (!std::regex_match(date, iso8601Pattern)) {
        return false;
    }

    // Extract year, month, and day components from the date string
    unsigned int year = std::stoi(date.substr(0, 4));
    unsigned int month = std::stoi(date.substr(5, 2));
    unsigned int day = std::stoi(date.substr(8, 2));

    // Checking if the date is valid
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Check for specific constraints based on the month and day
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
    return true; // Date is valid if all checks pass
}
bool Reservation::IsValidRoomNumber(int roomNumber) const {
    return (roomNumber >= -1000) && (roomNumber <= 1000);
}
Guest** Reservation::GetGuests() const {
    return accommodation.GetGuests();
}
int Reservation::GetNumGuests() const {
    return accommodation.GetNumGuests();
}
