#pragma once
#include "Accommodation.hpp"
#include "Guest.hpp"
#include <string>
#include <ctime>

class Reservation{
private:
    int roomNumber;
    std::string checkInDate;
    std::string checkOutDate;
    std::string note;  
    Accommodation accommodation; 
public:
    Reservation(const std::string& checkInDate, const std::string& checkOutDate);
    Reservation(const std::string& checkInDate, const std::string& checkOutDate, const std::string& note);
    Reservation(int roomNumber, const std::string& checkInDate, const std::string& checkOutDate, const std::string& note);
    ~Reservation();

    int getRoomNumber() const;
    void setRoomNumber(int roomNumber);

    std::string getCheckInDate() const;
    void setCheckInDate(const std::string& checkIn); 

    std::string getCheckOutDate() const;
    void setCheckOutDate(const std::string& checkOut);

    std::string getNote() const;
    void checkNote(const std::string& note);

    Guest** getGuests() const;
    int getNumGuests() const;

    bool includesDate(const std::string& currentDate) const;

    bool isValidDate(const std::string& date);
    bool isValidRoomNumber(int roomNumber) const;

    Accommodation& getAccommodation();
};

#ifdef TEST
#include "doctest.h"
#include "Reservation.hpp"
#include "Guest.hpp"

TEST_SUITE("Reservation") {
    TEST_CASE("Get Room Number") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.getRoomNumber(), 0);

        reservation.setRoomNumber(42);
        CHECK_EQ(reservation.getRoomNumber(), 42);
    }

    TEST_CASE("Get Check-In Date") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.getCheckInDate(), "2023-05-20");

        reservation.setCheckInDate("2023-05-21");
        CHECK_EQ(reservation.getCheckInDate(), "2023-05-21");
    }

    TEST_CASE("Get Check-Out Date") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.getCheckOutDate(), "2023-05-22");

        reservation.setCheckOutDate("2023-05-23");
        CHECK_EQ(reservation.getCheckOutDate(), "2023-05-23");
    }

    TEST_CASE("Get Note") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.getNote(), "Sample Note");

        reservation.checkNote("Updated Note");
        CHECK_EQ(reservation.getNote(), "Updated Note");
    }

    TEST_CASE("Get Accommodation") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        Accommodation& accommodation = reservation.getAccommodation();

        CHECK_EQ(&accommodation, &reservation.getAccommodation());
    }

    TEST_CASE("Includes Date") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK(reservation.includesDate("2023-05-20"));
        CHECK(reservation.includesDate("2023-05-21"));
        CHECK(reservation.includesDate("2023-05-22"));
        CHECK_FALSE(reservation.includesDate("2023-05-19"));
        CHECK_FALSE(reservation.includesDate("2023-05-23"));
    }

    TEST_CASE("isValidDate") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");

        CHECK(reservation.isValidDate("2023-05-20"));
        CHECK(reservation.isValidDate("2023-12-31"));
        CHECK(reservation.isValidDate("2023-01-01"));

        CHECK_FALSE(reservation.isValidDate("2023/05/20"));
        CHECK_FALSE(reservation.isValidDate("2023-5-20"));
        CHECK_FALSE(reservation.isValidDate("05-20-2023"));
        CHECK_FALSE(reservation.isValidDate("2023-05-32"));
    }

    TEST_CASE("isValidRoomNumber") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");

        CHECK(reservation.isValidRoomNumber(-1000));
        CHECK(reservation.isValidRoomNumber(0));
        CHECK(reservation.isValidRoomNumber(1000));

        CHECK_FALSE(reservation.isValidRoomNumber(-1001));
        CHECK_FALSE(reservation.isValidRoomNumber(1001));
        CHECK_FALSE(reservation.isValidRoomNumber(2000));
        CHECK_FALSE(reservation.isValidRoomNumber(-2000));
    }
}
#endif