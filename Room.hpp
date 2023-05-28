#pragma once
#include "Reservation.hpp"
#include "Activity.hpp"
#include "Accommodation.hpp"
#include <vector>

class Room{
private:
    int number;
    unsigned int numBeds;
    Reservation** reservations;
    unsigned int reservationsCount;
    Activity** activities;
    unsigned int activitiesCount;
    Accommodation** accommodations;
    unsigned int accommodationsCount;
    Guest** guests;
    unsigned int guestsCount;
public:
    Room();
    Room(int number, unsigned int numBeds);
    ~Room();

    int GetNumber() const;
    unsigned int GetNumberOfBeds() const;

    Reservation** GetReservations() const;
    unsigned int GetReservationsCount() const;

    Guest** GetGuests() const;
    unsigned int GetGuestsCount() const;

    Activity** GetActivities() const;
    unsigned int GetActivitiesCount() const;

    Accommodation** GetAccommodations() const;
    unsigned int GetAccommodationsCount() const;

    void AddReservation(const Reservation& reservation);
    void AddActivity(const Activity& activity);
    void AddGuest(const Guest& guest);

    bool IsReservedInPeriod(const std::string& from, const std::string& to) const;
    void AddGuestToActivity(const std::string& activityName, Guest* guest);
    void ClearGuests();
    void ClearReservations();
    void Checkout();

    void PrintRoomUsageReport(const std::string& from, const std::string& to) const;
    int GetUsageDays(const std::string& from, const std::string& to) const;
    void MoveGuestsFromRoom(Room* sourceRoom);

    bool IsReservedOnDate(const std::string& currentDate) const;

    Guest* FindGuestByName(const std::string& guestName) const;
    void PrintActivities() const;
};

#ifdef TEST
TEST_SUITE("Room") {
    TEST_CASE("Get Room Number") {
        Room room(101, 2);
        CHECK_EQ(room.GetNumber(), 101);
    }

    TEST_CASE("Get Number of Beds") {
        Room room(101, 2);
        CHECK_EQ(room.GetNumberOfBeds(), 2);
    }

    TEST_CASE("Add Reservation") {
        Room room(101, 2);
        Reservation reservation("2023-05-20", "2023-05-22");
        room.AddReservation(reservation);
        CHECK_EQ(room.GetReservationsCount(), 1);
        CHECK_EQ(room.GetReservations()[0]->GetCheckInDate(), "2023-05-20");
        CHECK_EQ(room.GetReservations()[0]->GetCheckOutDate(), "2023-05-22");
    }

    TEST_CASE("Add Guest") {
        Room room(101, 2);
        Guest guest("Aneliya", "Konarcheva", "0882750588");
        room.AddGuest(guest);

        CHECK_EQ(room.GetGuestsCount(), 1);

        CHECK_EQ(room.GetGuests()[0]->GetFirstName(), "Aneliya");
        CHECK_EQ(room.GetGuests()[0]->GetLastName(), "Konarcheva");
    }

    TEST_CASE("Add Activity") {
        Room room(101, 2);
        Activity activity("Swimming");
        room.AddActivity(activity);
        CHECK_EQ(room.GetActivitiesCount(), 1);
        CHECK_EQ(room.GetActivities()[0]->GetName(), "Swimming");
    }

    TEST_CASE("Is Reserved in Period") {
        Room room(101, 2);
        Reservation reservation("2023-05-20", "2023-05-22");
        room.AddReservation(reservation);
        CHECK_EQ(room.IsReservedInPeriod("2023-05-19", "2023-05-21"), true);
        CHECK_EQ(room.IsReservedInPeriod("2023-05-21", "2023-05-23"), true);
        CHECK_EQ(room.IsReservedInPeriod("2023-05-23", "2023-05-25"), false);
    }

    TEST_CASE("Is Reserved on Date") {
        Room room(101, 2);
        Reservation reservation("2023-05-20", "2023-05-22");
        room.AddReservation(reservation);
        CHECK_EQ(room.IsReservedOnDate("2023-05-20"), true);
        CHECK_EQ(room.IsReservedOnDate("2023-05-23"), false);
    }

    TEST_CASE("Clear Guests") {
        Room room(101, 2);
        Guest guest1("Aneliya", "Konarcheva", "0837485764");
        Guest guest2("Blagovesta", "Hubanova", "0837485968");

        room.AddGuest(guest1);
        room.AddGuest(guest2);
        room.ClearGuests();

        REQUIRE(room.GetGuestsCount() == 0);
    }

    TEST_CASE("Clear Reservations") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.AddReservation(reservation1);
        room.AddReservation(reservation2);
        room.ClearReservations();

        REQUIRE(room.GetReservationsCount() == 0);
    }

    TEST_CASE("Room Checkout") {
        Room room(101, 2);

        Guest guest1("Aneliya", "Konarcheva", "0837485764");
        Guest guest2("Blagovesta", "Hubanova", "0837485968");

        room.AddGuest(guest1);
        room.AddGuest(guest2);

        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.AddReservation(reservation1);
        room.AddReservation(reservation2);

        room.Checkout();

        REQUIRE(room.GetGuestsCount() == 0);
        REQUIRE(room.GetReservationsCount() == 0);
    }

    TEST_CASE("Get Usage Days") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.AddReservation(reservation1);
        room.AddReservation(reservation2);

        CHECK_EQ(room.GetUsageDays("2023-06-01", "2023-06-05"), 5);
    }
}
#endif
