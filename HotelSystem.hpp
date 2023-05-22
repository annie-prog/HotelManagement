#pragma once
#include "Room.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"

class HotelSystem : public Room {
private:
    Room** rooms;
    unsigned int roomCount;

    HotelSystem();
    static HotelSystem* instance;
public:
    static HotelSystem* getInstance();
    HotelSystem(Room** rooms, unsigned int roomCount);
    ~HotelSystem();

    void addRoom(const Room* room);//

    Room* getRoom(int roomNumber) const;
    Room** getRooms() const;
    Reservation** getReservations() const;
    Activity** getActivities() const;

    void printRooms() const;
    bool isRoomAvailable(const std::string& date) const;
    void printAvailableRooms(const std::string& date) const;
    std::string getCurrentDate() const;

    void makeReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests);//
    void cancelReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut);

    virtual void addActivity(const std::string& name);
    void addGuestToRoom(int roomNumber, Guest* guest);
    void addGuestToActivity(const std::string& activityName, Guest* guest);
    void printActivities() const;
    void printActivityGuests(const std::string& activityName) const;

    void printGuests() const;
    void printRoomUsageReport(const std::string& from, const std::string& to) const;

    Room* findAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const;
    bool findEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to); //does not work properly
    
    void declareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note);
    void addGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest);

    void printRoomActivities(int roomNumber) const; // does not work properly
    void checkout(int roomNumber);// does not work properly

    Guest* findGuestByName(const std::string& guestName) const;
};

#ifdef TEST
TEST_SUITE("HotelSystem") {
    /*TEST_CASE("Add Room") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);

        hotelSystem->addRoom(&room);

        CHECK_EQ(hotelSystem->getRoom(101), &room);
        CHECK_EQ(hotelSystem->getRooms()[0], &room);

        delete hotelSystem;
    }

    TEST_CASE("Get Room") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);

        hotelSystem->addRoom(&room);

        Room* retrievedRoom = hotelSystem->getRoom(101);

        CHECK_EQ(retrievedRoom, &room);

        delete hotelSystem;
    }

    TEST_CASE("Get Reservations") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        Reservation reservation("2023-01-01", "2023-01-07");
        room.addReservation(&reservation);
        hotelSystem->addRoom(&room);

        Reservation** reservations = hotelSystem->getReservations();

        CHECK_EQ(reservations[0], &reservation);

        delete hotelSystem;
    }

    TEST_CASE("Get Activities") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        Activity activity("Swimming", 101);
        room.addActivity(&activity);
        hotelSystem->addRoom(&room);

        Activity** activities = hotelSystem->getActivities();

        CHECK_EQ(activities[0], &activity);

        delete hotelSystem;
    }

    TEST_CASE("Make Reservation") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        hotelSystem->addRoom(&room);

        hotelSystem->makeReservation(101, "2023-01-01", "2023-01-07", "", 2);

        Reservation** reservations = hotelSystem->getReservations();

        CHECK_EQ(room.getReservationsCount(), 1);
        CHECK_EQ(reservations[0]->getRoomNumber(), 101);

        delete hotelSystem;
    }

    TEST_CASE("Cancel Reservation") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        Reservation reservation("2023-01-01", "2023-01-07");
        room.addReservation(&reservation);
        hotelSystem->addRoom(&room);

        hotelSystem->cancelReservation(101, "2023-01-01", "2023-01-07");

        CHECK_EQ(room.getReservationsCount(), 0);

        delete hotelSystem;
    }

    TEST_CASE("Add Activity") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Activity activity("Swimming", 101);

        hotelSystem->addActivity("Swimming");

        Activity** activities = hotelSystem->getActivities();

        CHECK_EQ(activities[0]->getName(), "Swimming");

        delete hotelSystem;
    }

    TEST_CASE("Add Guest to Room") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        Guest guest("John", "Doe", "123456789");
        hotelSystem->addRoom(&room);

        hotelSystem->addGuestToRoom(101, &guest);

        CHECK_EQ(room.getGuestsCount(), 1);
        CHECK_EQ(room.getGuests()[0]->getFirstName(), "John");

        delete hotelSystem;
    }

    TEST_CASE("Add Guest to Activity") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Activity activity("Swimming", 101);
        Guest guest("John", "Doe", "123456789");
        hotelSystem->addActivity("Swimming");

        hotelSystem->addGuestToActivity("Swimming", &guest);

        CHECK_EQ(activity.getGuestsCount(), 1);
        CHECK_EQ(activity.getGuests()[0]->getFirstName(), "John");

        delete hotelSystem;
    }

    TEST_CASE("Print Activities") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Activity activity1("Swimming", 101);
        Activity activity2("Gym", 102);
        hotelSystem->addActivity("Swimming");
        hotelSystem->addActivity("Gym");

        std::ostringstream oss;
        hotelSystem->printActivities();
        std::string activities = oss.str();

        CHECK_EQ(activities, "Activities:\n"
                             "1. Swimming\n"
                             "2. Gym\n");
        delete hotelSystem;
    }

    TEST_CASE("Print Activity Guests") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Activity activity("Swimming", 101);
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");
        hotelSystem->addActivity("Swimming");
        activity.addGuest(&guest1);
        activity.addGuest(&guest2);

        std::ostringstream oss;
        hotelSystem->printActivityGuests("Swimming");
        std::string guests = oss.str();

        CHECK_EQ(guests, "Guests in Activity 'Swimming' (Room 101):\n"
                         "1. John Doe\n"
                         "2. Jane Smith\n");

        delete hotelSystem;
    }

    TEST_CASE("Print Guests") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");
        hotelSystem->addRoom(&room);
        room.addGuest(&guest1);
        room.addGuest(&guest2);

        std::ostringstream oss;
        hotelSystem->printGuests();
        std::string guests = oss.str();

        CHECK_EQ(guests, "Guests in Room 101:\n"
                         "1. John Doe\n"
                         "2. Jane Smith\n");

        delete hotelSystem;
    }

    TEST_CASE("Print Room Usage Report") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        Reservation reservation1("2023-01-01", "2023-01-07");
        Reservation reservation2("2023-02-01", "2023-02-07");
        room.addReservation(&reservation1);
        room.addReservation(&reservation2);
        hotelSystem->addRoom(&room);

        std::ostringstream oss;
        hotelSystem->printRoomUsageReport("2023-01-01", "2023-02-28");
        std::string report = oss.str();

        CHECK_EQ(report, "Room Usage Report for Room 101:\n"
                         "Total reservations: 2\n"
                         "Total usage days: 13\n");

        delete hotelSystem;
    }

    TEST_CASE("Find Available Room") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room1(101, 2);
        Room room2(102, 3);
        hotelSystem->addRoom(&room1);
        hotelSystem->addRoom(&room2);

        Room* availableRoom = hotelSystem->findAvailableRoom(2, "2023-01-01", "2023-01-07");

        CHECK_EQ(availableRoom->getNumber(), 101);

        delete hotelSystem;
    }

    TEST_CASE("Find Guest by Name") {
        HotelSystem* hotelSystem = HotelSystem::getInstance();
        Room room(101, 2);
        Guest guest("John", "Doe", "123456789");
        hotelSystem->addRoom(&room);
        room.addGuest(&guest);

        Guest* foundGuest = hotelSystem->findGuestByName("John Doe");

        CHECK_EQ(foundGuest, &guest);

        delete hotelSystem;
    }*/
}
#endif