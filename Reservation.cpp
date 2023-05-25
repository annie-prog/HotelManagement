#include "Reservation.hpp"
#include <sstream>
#include <iomanip>

Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate)
    : roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate) {}
Reservation::Reservation(const std::string& checkInDate, const std::string& checkOutDate, const std::string& note)
    : roomNumber(0), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {}
Reservation::Reservation(int roomNumber, const std::string& checkInDate, const std::string& checkOutDate, const std::string& note)
    : roomNumber(roomNumber), checkInDate(checkInDate), checkOutDate(checkOutDate), note(note) {}    
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

    std::tm tm_checkIn = {};
    std::istringstream iss_checkIn(checkInDate);
    iss_checkIn >> std::get_time(&tm_checkIn, "%Y-%m-%d");

    std::tm tm_checkOut = {};
    std::istringstream iss_checkOut(checkOutDate);
    iss_checkOut >> std::get_time(&tm_checkOut, "%Y-%m-%d");

    std::time_t time_checkIn = std::mktime(&tm_checkIn);
    std::time_t time_checkOut = std::mktime(&tm_checkOut);

    if (time_checkIn == -1 || time_checkOut == -1) {
        return 0;
    }

    if (time_checkOut < time_from || time_checkIn > time_to) {
        return 0;
    }

    std::time_t start_date = std::max(time_checkIn, time_from);
    std::time_t end_date = std::min(time_checkOut, time_to);

    double seconds = std::difftime(end_date, start_date);
    int days = static_cast<int>(seconds / (24 * 60 * 60));

    return days + 1;
}