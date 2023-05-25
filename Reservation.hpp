#pragma once
#include "Accommodation.hpp"
#include "Guest.hpp"
#include <string>
#include <ctime>

class Reservation : public Accommodation {
private:
    int roomNumber;
    std::string checkInDate;
    std::string checkOutDate;
    std::string note;   
public:
    Reservation(const std::string& checkInDate, const std::string& checkOutDate);
    Reservation(const std::string& checkInDate, const std::string& checkOutDate, const std::string& note);
    Reservation(int roomNumber, const std::string& checkInDate, const std::string& checkOutDate, const std::string& note);
    virtual ~Reservation();

    int getRoomNumber() const;
    void setRoomNumber(int roomNumber);

    std::string getCheckInDate() const;
    void setCheckInDate(const std::string& checkIn); 

    std::string getCheckOutDate() const;
    void setCheckOutDate(const std::string& checkOut);

    std::string getNote() const;
    void checkNote(const std::string& note);

    bool includesDate(const std::string& currentDate) const;
    int getUsageDays(const std::string& from, const std::string& to) const;
};

#ifdef TEST
#include "doctest.h"
#include "Reservation.hpp"
#include "Guest.hpp"

TEST_SUITE("Reservation") {
    TEST_CASE("Getters and Setters") {
        Reservation reservation("2023-05-20", "2023-05-22");
        CHECK_EQ(reservation.getCheckInDate(), "2023-05-20");
        CHECK_EQ(reservation.getCheckOutDate(), "2023-05-22");

        reservation.setCheckInDate("2023-05-25");
        reservation.setCheckOutDate("2023-05-27");
        CHECK_EQ(reservation.getCheckInDate(), "2023-05-25");
        CHECK_EQ(reservation.getCheckOutDate(), "2023-05-27");

        reservation.setRoomNumber(101);
        CHECK_EQ(reservation.getRoomNumber(), 101);

        reservation.checkNote("Important note");
        CHECK_EQ(reservation.getNote(), "Important note");
    }

    TEST_CASE("Add and Get Guests") {
        Reservation reservation("2023-05-20", "2023-05-22");
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");

        reservation.addGuest(&guest1);
        reservation.addGuest(&guest2);

        Guest** guests = reservation.getGuests();

        CHECK_EQ(reservation.getNumGuests(), 2);
        CHECK_EQ(guests[0]->getFirstName(), "John");
        CHECK_EQ(guests[0]->getLastName(), "Doe");
        CHECK_EQ(guests[0]->getPhoneNumber(), "123456789");
        CHECK_EQ(guests[1]->getFirstName(), "Jane");
        CHECK_EQ(guests[1]->getLastName(), "Smith");
        CHECK_EQ(guests[1]->getPhoneNumber(), "987654321");
    }

    TEST_CASE("Includes Date") {
        Reservation reservation("2023-05-20", "2023-05-22");
        CHECK(reservation.includesDate("2023-05-20"));
        CHECK(reservation.includesDate("2023-05-21"));
        CHECK(reservation.includesDate("2023-05-22"));
        CHECK_FALSE(reservation.includesDate("2023-05-19"));
        CHECK_FALSE(reservation.includesDate("2023-05-23"));
    }
}
#endif