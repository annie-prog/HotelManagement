#pragma once
#include "Room.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"
#include "Accommodation.hpp"

class HotelSystem{
private:
    Accommodation* accommodation;
    Room* emergencyRoom;
    Room** rooms;
    unsigned int roomCount;
    Reservation** reservations;
    unsigned int reservationCount;
    Activity** activities;
    unsigned int activitiesCount;

    HotelSystem();
    static HotelSystem* instance;

public:
    static HotelSystem* getInstance();

    ~HotelSystem();
    void addEmergencyRoom(Room* room);
    void addRoom(const Room* room); 
    void addRoom(int roomNumber, unsigned int numBeds);
    Room* getRoom(int roomNumber) const;
    Room** getRooms() const;
    unsigned int getRoomCount() const;
    void printRooms() const;

    void makeReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests);
    bool isRoomAvailable(const std::string& date) const;
    void printAvailableRooms(const std::string& date) const;

    void addActivity(const std::string& name);
    void printActivities() const;
    void printActivityGuests(const std::string& activityName) const;

    void addGuest(Guest* guest);
    void addGuestToRoom(int roomNumber, Guest* guest);
    void addGuestToActivity(const std::string& activityName, Guest* guest);
    void printGuests() const;
    Guest** getGuests() const;
    unsigned int getNumGuests() const;

    std::string getCurrentDate() const;
    void printRoomUsageReport(const std::string& from, const std::string& to) const;
    Room* findAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const;
    bool findEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to);
    void declareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note);
    void addGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest);
    void printRoomActivities(int roomNumber) const;
    void checkout(int roomNumber);
    Guest* findGuestByName(const std::string& guestName) const;
    void addRoomActivity(int roomNumber, Activity* activity);
};

#ifdef TEST
TEST_SUITE("HotelSystem") {
    TEST_CASE("Add Room") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();

        SUBCASE("Add room with room number and number of beds") {
            hotelSystem->addRoom(101, 2);

            Room** rooms = hotelSystem->getRooms();
            unsigned int roomCount = hotelSystem->getRoomCount();

            CHECK_EQ(roomCount, 1);
            CHECK_EQ(rooms[0]->getNumber(), 101);
            CHECK_EQ(rooms[0]->getNumberOfBeds(), 2);
        }

        delete hotelSystem;
    }

    TEST_CASE("Add Activity") {
        Room room(101, 2);
        Activity activity1("Swimming");
        Activity activity2("Gym");

        room.addActivity(activity1);
        room.addActivity(activity2);

        Activity** activities = room.getActivities();

        CHECK_EQ(activities[0]->getName(), "Swimming");
        CHECK_EQ(activities[1]->getName(), "Gym");
    }

    /*TEST_CASE("Add Reservation") {
        Room room(101, 2);
        Reservation reservation1("2023-05-20", "2023-05-22");
        Reservation reservation2("2023-05-25", "2023-05-27");

        room.addReservation(reservation1);

        CHECK_EQ(room.getReservationsCount(), 1);
        CHECK_EQ(room.getReservations()[0], &reservation1);

        room.addReservation(reservation2);

        CHECK_EQ(room.getReservationsCount(), 2);
        CHECK_EQ(room.getReservations()[0], &reservation1);
        CHECK_EQ(room.getReservations()[1], &reservation2);
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
    }*/
}
#endif