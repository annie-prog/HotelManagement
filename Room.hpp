#pragma once
#include "Reservation.hpp"
#include "Activity.hpp"
#include "Accommodation.hpp"
#include <vector>

class Room : public Accommodation {
private:
    int number;
    unsigned int numBeds;
    Reservation** reservations;
    unsigned int reservationsCount;
    Activity** activities;
    unsigned int activitiesCount;

public:
    Room();
    Room(int number, unsigned int numBeds);
    virtual ~Room();

    int getNumber() const;
    unsigned int getNumberOfBeds() const;

    Reservation** getReservations() const;
    unsigned int getReservationsCount() const;

    Activity** getActivities() const;
    unsigned int getActivitiesCount() const;

    void addReservation(Reservation* reservation);
    void cancelReservation(const std::string& checkIn, const std::string& checkOut);
    void addActivity(Activity* activity);

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

    TEST_CASE("Add Guest") {
        Room room(101, 2);
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");

        room.addGuest(&guest1);
        room.addGuest(&guest2);

        Guest** guests = room.getGuests();

        CHECK_EQ(guests[0]->getFirstName(), "John");
        CHECK_EQ(guests[0]->getLastName(), "Doe");
        CHECK_EQ(guests[0]->getPhoneNumber(), "123456789");
        CHECK_EQ(guests[1]->getFirstName(), "Jane");
        CHECK_EQ(guests[1]->getLastName(), "Smith");
        CHECK_EQ(guests[1]->getPhoneNumber(), "987654321");
    }

    TEST_CASE("Add Reservation") {
        Room room(101, 2);
        Reservation reservation1("2023-05-20", "2023-05-22");
        Reservation reservation2("2023-05-25", "2023-05-27");

        room.addReservation(&reservation1);

        CHECK_EQ(room.getReservationsCount(), 1);
        CHECK_EQ(room.getReservations()[0], &reservation1);

        room.addReservation(&reservation2);

        CHECK_EQ(room.getReservationsCount(), 2);
        CHECK_EQ(room.getReservations()[0], &reservation1);
        CHECK_EQ(room.getReservations()[1], &reservation2);
    }

    /*TEST_CASE("Cancel Reservation") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.addReservation(&reservation1);
        room.addReservation(&reservation2);

        room.cancelReservation("2023-06-01", "2023-06-05");

        Reservation** reservations = room.getReservations();

        CHECK_EQ(reservations[0]->getCheckInDate(), "2023-06-10");
        CHECK_EQ(reservations[0]->getCheckOutDate(), "2023-06-15");
    }*/
    
    TEST_CASE("Add Activity") {
        Room room(101, 2);
        Activity activity1("Swimming");
        Activity activity2("Gym");

        room.addActivity(&activity1);
        room.addActivity(&activity2);

        Activity** activities = room.getActivities();

        CHECK_EQ(activities[0]->getName(), "Swimming");
        CHECK_EQ(activities[1]->getName(), "Gym");
    }

    TEST_CASE("Is Reserved in Period") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.addReservation(&reservation1);
        room.addReservation(&reservation2);

        CHECK_EQ(room.isReservedInPeriod("2023-06-02", "2023-06-04"), true);
        CHECK_EQ(room.isReservedInPeriod("2023-06-06", "2023-06-09"), false);
    }

    TEST_CASE("Add Guest to Activity") {
        Room room(101, 2);
        Guest guest("John", "Doe", "123456789");
        Activity activity("Swimming");

        room.addGuest(&guest);
        room.addActivity(&activity);
        room.addGuestToActivity("Swimming", &guest);

        CHECK_EQ(activity.getGuests()[0]->getFirstName(), "John");
        CHECK_EQ(activity.getGuests()[0]->getLastName(), "Doe");
        CHECK_EQ(activity.getGuests()[0]->getPhoneNumber(), "123456789");
    }

    TEST_CASE("Clear Guests") {
        Room room(101, 2);
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");

        room.addGuest(&guest1);
        room.addGuest(&guest2);
        room.clearGuests();

        Guest** guests = room.getGuests();

        CHECK(guests == nullptr);
    }

    TEST_CASE("Clear Reservations") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.addReservation(&reservation1);
        room.addReservation(&reservation2);
        room.clearReservations();

        Reservation** reservations = room.getReservations();

        CHECK(reservations == nullptr);
    }

    TEST_CASE("Checkout") {
        Room room(101, 2);
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");
        Reservation reservation("2023-06-01", "2023-06-05");

        room.addGuest(&guest1);
        room.addGuest(&guest2);
        room.addReservation(&reservation);
        room.checkout();

        Guest** guests = room.getGuests();
        Reservation** reservations = room.getReservations();

        CHECK(guests == nullptr);
        CHECK(reservations == nullptr);
    }

    TEST_CASE("Get Usage Days") {
        Room room(101, 2);
        Reservation reservation1("2023-06-01", "2023-06-05");
        Reservation reservation2("2023-06-10", "2023-06-15");

        room.addReservation(&reservation1);
        room.addReservation(&reservation2);

        CHECK_EQ(room.getUsageDays("2023-06-01", "2023-06-05"), 5);
    }
}
#endif
