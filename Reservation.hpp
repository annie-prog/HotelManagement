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

    int GetRoomNumber() const;
    void SetRoomNumber(int roomNumber);

    std::string GetCheckInDate() const;
    void SetCheckInDate(const std::string& checkIn); 

    std::string GetCheckOutDate() const;
    void SetCheckOutDate(const std::string& checkOut);

    std::string GetNote() const;
    void CheckNote(const std::string& note);

    Guest** GetGuests() const;
    int GetNumGuests() const;

    bool IncludesDate(const std::string& currentDate) const;

    bool IsValidDate(const std::string& date);
    bool IsValidRoomNumber(int roomNumber) const;

    Accommodation& GetAccommodation();
};

#ifdef TEST
#include "doctest.h"
#include "Reservation.hpp"
#include "Guest.hpp"

TEST_SUITE("Reservation") {
    TEST_CASE("Get Room Number") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.GetRoomNumber(), 0);

        reservation.SetRoomNumber(42);
        CHECK_EQ(reservation.GetRoomNumber(), 42);
    }

    TEST_CASE("Get Check-In Date") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.GetCheckInDate(), "2023-05-20");

        reservation.SetCheckInDate("2023-05-21");
        CHECK_EQ(reservation.GetCheckInDate(), "2023-05-21");
    }

    TEST_CASE("Get Check-Out Date") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.GetCheckOutDate(), "2023-05-22");

        reservation.SetCheckOutDate("2023-05-23");
        CHECK_EQ(reservation.GetCheckOutDate(), "2023-05-23");
    }

    TEST_CASE("Get Note") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK_EQ(reservation.GetNote(), "Sample Note");

        reservation.CheckNote("Updated Note");
        CHECK_EQ(reservation.GetNote(), "Updated Note");
    }

    TEST_CASE("Get Accommodation") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        Accommodation& accommodation = reservation.GetAccommodation();

        CHECK_EQ(&accommodation, &reservation.GetAccommodation());
    }

    TEST_CASE("Includes Date") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");
        CHECK(reservation.IncludesDate("2023-05-20"));
        CHECK(reservation.IncludesDate("2023-05-21"));
        CHECK(reservation.IncludesDate("2023-05-22"));
        CHECK_FALSE(reservation.IncludesDate("2023-05-19"));
        CHECK_FALSE(reservation.IncludesDate("2023-05-23"));
    }

    TEST_CASE("isValidDate") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");

        CHECK(reservation.IsValidDate("2023-05-20"));
        CHECK(reservation.IsValidDate("2023-12-31"));
        CHECK(reservation.IsValidDate("2023-01-01"));

        CHECK_FALSE(reservation.IsValidDate("2023/05/20"));
        CHECK_FALSE(reservation.IsValidDate("2023-5-20"));
        CHECK_FALSE(reservation.IsValidDate("05-20-2023"));
        CHECK_FALSE(reservation.IsValidDate("2023-05-32"));
    }

    TEST_CASE("isValidRoomNumber") {
        Reservation reservation("2023-05-20", "2023-05-22", "Sample Note");

        CHECK(reservation.IsValidRoomNumber(-1000));
        CHECK(reservation.IsValidRoomNumber(0));
        CHECK(reservation.IsValidRoomNumber(1000));

        CHECK_FALSE(reservation.IsValidRoomNumber(-1001));
        CHECK_FALSE(reservation.IsValidRoomNumber(1001));
        CHECK_FALSE(reservation.IsValidRoomNumber(2000));
        CHECK_FALSE(reservation.IsValidRoomNumber(-2000));
    }
}
#endif