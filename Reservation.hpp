#pragma once
#include "Guest.hpp"
#include <string>

class Reservation{
private:
    int roomNumber;
    std::string checkInDate;
    std::string checkOutDate;
    std::string note;
    unsigned int numGuests;
    std::vector<Guest*> guests;

public:
    Reservation(int roomNumber, const std::string &checkInDate, const std::string &checkOutDate, const std::string &note, unsigned int numGuests);
    ~Reservation();

    int getRoomNumber() const;
    void setRoomNumber(int roomNumber);

    std::string getCheckInDate() const;
    void setCheckInDate(const std::string &checkIn); 

    std::string getCheckOutDate() const;
    void setCheckOutDate(const std::string &checkOut);

    std::string getNote() const;
    void checkNote(const std::string &note);

    unsigned int getNumberOfGuests() const;
    void setNumberOfGuests(unsigned int roomNumber);

    std::vector<Guest*> getGuests() const;
    void addGuest(const Guest* guest);

};