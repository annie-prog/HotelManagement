#define TEST
#include "HotelSystem.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
//#include "doctest.h"


/*#ifdef DOCTEST_CONFIG_IMPLEMENT
#define test doctest::Context().run()
#else
#define test
#endif*/

int main() {

/*#ifdef TEST
    test;
#else*/
    HotelSystem* hotelSystem = HotelSystem::getInstance();

    Room* room1 = new Room(101, 2);
    Room* room2 = new Room(102, 2);
    Room* room3 = new Room(201, 3);
    Room* emergencyRoom = new Room(202, 2);

    hotelSystem->addRoom(room1);
    hotelSystem->addRoom(room2);
    hotelSystem->addRoom(room3);
    hotelSystem->addEmergencyRoom(emergencyRoom);

    Activity activity("Gym");

    hotelSystem->printRooms();

    hotelSystem->declareRoomUnavailable(102, "2023-05-17", "2023-05-19", "Under Construction");

    hotelSystem->makeReservation(101, "2023-06-13", "2023-06-15", "Reservation 1", 2);
    hotelSystem->makeReservation(102, "2023-06-14", "2023-06-16", "Reservation 2", 2);
    hotelSystem->makeReservation(201, "2023-06-15", "2023-06-19", "Reservation 3", 3);

    hotelSystem->printAvailableRooms("2023-05-20");

    hotelSystem->addActivity("Swimming");

    Guest* guest1 = new Guest("John", "Doe", "1234567897");
    hotelSystem->addGuest(guest1);

    hotelSystem->addGuestToRoom(101, guest1);
    hotelSystem->addGuestToRoomActivity(101, "Swimming", guest1);

    hotelSystem->addRoomActivity(101, &activity);
    hotelSystem->printRoomActivities(101);

    hotelSystem->printActivityGuests("Swimming");

    Guest* foundGuest = hotelSystem->findGuestByName("John");
    if (foundGuest) {
        std::cout << "Found guest: " << foundGuest->getFirstName() << std::endl;
    } 
    else {
        std::cout << "Guest not found." << std::endl;
    }

    Room* availableRoom = hotelSystem->findAvailableRoom(2, "2023-06-01", "2023-06-03");
    if (availableRoom != nullptr) {
        std::cout << "Available room found: " << availableRoom->getNumber() << std::endl;
    } 
    else {
        std::cout << "No available room found." << std::endl;
    }

    bool emergencyRoomFound = hotelSystem->findEmergencyRoom(2, "2023-06-15", "2023-06-19");
    if (emergencyRoomFound) {
        std::cout << "Emergency room found and guests moved." << std::endl;
    } 
    else {
        std::cout << "No emergency room found or guests not moved." << std::endl;
    }

    hotelSystem->checkout(101);
    hotelSystem->printRoomUsageReport("2023-06-14", "2023-06-17");
    hotelSystem->printActivities();

    std::cout << hotelSystem->getCurrentDate() << std::endl;

    delete hotelSystem;
    delete guest1;

    return 0;
//#endif
}