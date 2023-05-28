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

    int getNumber() const;
    unsigned int getNumberOfBeds() const;

    Reservation** getReservations() const;
    unsigned int getReservationsCount() const;

    Guest** getGuests() const;
    unsigned int getGuestsCount() const;

    Activity** getActivities() const;
    unsigned int getActivitiesCount() const;

    Accommodation** getAccommodations() const;
    unsigned int getAccommodationsCount() const;

    void addReservation(const Reservation& reservation);
    void addActivity(const Activity& activity);
    void addGuest(const Guest& guest);

    bool isReservedInPeriod(const std::string& from, const std::string& to) const;
    void addGuestToActivity(const std::string& activityName, Guest* guest);
    void clearGuests();
    void clearReservations();
    void checkout();

    void printRoomUsageReport(const std::string& from, const std::string& to) const;
    int getUsageDays(const std::string& from, const std::string& to) const;
    void moveGuestsFromRoom(Room* sourceRoom);

    bool isReservedOnDate(const std::string& currentDate) const;

    Guest* findGuestByName(const std::string& guestName) const;
    void printActivities() const;
};

#ifdef TEST
TEST_SUITE("Room") {
    TEST_CASE("Get Room Number") {
        Room room(101, 2);
        CHECK_EQ(room.getNumber(), 101);
    }

    TEST_CASE("Get Number of Beds") {
        Room room(101, 2);
        CHECK_EQ(room.getNumberOfBeds(), 2);
    }

    TEST_CASE("Add Reservation") {
        Room room(101, 2);
        Reservation reservation("2023-05-20", "2023-05-22");
        room.addReservation(reservation);
        CHECK_EQ(room.getReservationsCount(), 1);
        CHECK_EQ(room.getReservations()[0]->getCheckInDate(), "2023-05-20");
        CHECK_EQ(room.getReservations()[0]->getCheckOutDate(), "2023-05-22");
    }

    TEST_CASE("Add Guest") {
        Room room(101, 2);
        Guest guest("John", "Doe", "0882750588");
        room.addGuest(guest);

        CHECK_EQ(room.getGuestsCount(), 1);

        CHECK_EQ(room.getGuests()[0]->getFirstName(), "John");
        CHECK_EQ(room.getGuests()[0]->getLastName(), "Doe");
    }

    TEST_CASE("Add Activity") {
        Room room(101, 2);
        Activity activity("Swimming");
        room.addActivity(activity);
        CHECK_EQ(room.getActivitiesCount(), 1);
        CHECK_EQ(room.getActivities()[0]->getName(), "Swimming");
    }

    TEST_CASE("Is Reserved in Period") {
        Room room(101, 2);
        Reservation reservation("2023-05-20", "2023-05-22");
        room.addReservation(reservation);
        CHECK_EQ(room.isReservedInPeriod("2023-05-19", "2023-05-21"), true);
        CHECK_EQ(room.isReservedInPeriod("2023-05-21", "2023-05-23"), true);
        CHECK_EQ(room.isReservedInPeriod("2023-05-23", "2023-05-25"), false);
    }

    TEST_CASE("Is Reserved on Date") {
        Room room(101, 2);
        Reservation reservation("2023-05-20", "2023-05-22");
        room.addReservation(reservation);
        CHECK_EQ(room.isReservedOnDate("2023-05-20"), true);
        CHECK_EQ(room.isReservedOnDate("2023-05-23"), false);
    }

    TEST_CASE("Clear Guests") {
        Room room(101, 2);
        Guest guest1("John", "Doe", "12345678943");
        Guest guest2("Jane", "Smith", "98765432145");

        room.addGuest(guest1);
        room.addGuest(guest2);
        room.clearGuests();

        REQUIRE(room.getGuestsCount() == 0);
    }

    TEST_CASE("Clear Reservations") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.addReservation(reservation1);
        room.addReservation(reservation2);
        room.clearReservations();

        REQUIRE(room.getReservationsCount() == 0);
    }

    TEST_CASE("Room Checkout") {
        Room room(101, 2);

        Guest guest1("John", "Doe", "12345678943");
        Guest guest2("Jane", "Smith", "98765432145");

        room.addGuest(guest1);
        room.addGuest(guest2);

        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.addReservation(reservation1);
        room.addReservation(reservation2);

        room.checkout();

        REQUIRE(room.getGuestsCount() == 0);
        REQUIRE(room.getReservationsCount() == 0);
    }

    TEST_CASE("Get Usage Days") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.addReservation(reservation1);
        room.addReservation(reservation2);

        CHECK_EQ(room.getUsageDays("2023-06-01", "2023-06-05"), 5);
    }
}
#endif
