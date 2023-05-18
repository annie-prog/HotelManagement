#include "HotelSystem.hpp"
#include <iostream>

int main() {
    Room* room1 = new Room(101, 2);
    Room* room2 = new Room(102, 2);
    Room* room3 = new Room(201, 3);

    Guest* guest1 = new Guest("Aneliya", "Konarcheva", "0882750588");
    Guest* guest2 = new Guest("Blagovesta", "Hubanova", "0889654321");
    Guest* guest3 = new Guest("Simona", "Koleva", "0876593846");
    Guest* guest4 = new Guest("Stefania", "Dimitrova", "0897234567");
    Guest* guest5 = new Guest("Chocho", "Vladovski", "0897639574");
    Guest* guest6 = new Guest("Fani", "Manahova", "0876395827");

    HotelSystem* hotel = HotelSystem::getInstance();

    hotel->addRoom(room1);
    hotel->addRoom(room2);
    hotel->addRoom(room3);

    std::cout << "Making reservations..." << std::endl;
    hotel->makeReservation(101, "2023-05-20", "2023-05-25", "Reservation 1", 0);
    hotel->makeReservation(102, "2023-05-22", "2023-05-24", "Reservation 2", 2);
    hotel->makeReservation(201, "2023-05-23", "2023-05-26", "Reservation 3", 3);
    std::cout << std::endl;

    hotel->addGuestToRoom(101, guest1);
    hotel->addGuestToRoom(101, guest2);
    hotel->addGuestToRoom(102, guest6);
    hotel->addGuestToRoom(102, guest3);
    hotel->addGuestToRoom(201, guest4);
    hotel->addGuestToRoom(201, guest5);
    std::cout << std::endl;
    
    std::cout << "All Rooms:" << std::endl;
    hotel->printRooms();
    std::cout << std::endl;

    hotel->declareRoomUnavailable(101, "2023-05-17", "2023-05-19", "Under Construction");

    std::cout << "Available Rooms:" << std::endl;
    hotel->printAvailableRooms("2023-05-17", "2023-05-19");
    std::cout << std::endl;

    std::cout << "Room Activities:" << std::endl;
    hotel->printRoomActivities(101);
    std::cout << std::endl;

    std::cout << "Adding activity and guest to activity..." << std::endl;
    hotel->addActivity("Swimming");
    Guest* guest = new Guest("John", "Doe", "0882750588");
    hotel->addGuestToActivity("Swimming", guest);
    std::cout << std::endl;

    hotel->addActivity("Jaccuzzi");
    hotel->addGuestToActivity("Jaccuzzi", guest3);
    std::cout << std::endl;

    std::cout << "Activity Guests:" << std::endl;
    hotel->printActivityGuests("Swimming");
    hotel->printActivityGuests("Jaccuzzi");
    hotel->printActivities();
    std::cout << std::endl;

    std::cout << "Room Activities:" << std::endl;
    hotel->printRoomActivities(102);
    std::cout << std::endl;

    std::cout << "Checking out room..." << std::endl;
    hotel->checkout(102);
    std::cout << std::endl;

    std::cout << "Available Rooms:" << std::endl;
    hotel->printAvailableRooms("2023-05-22", "2023-05-24");
    std::cout << std::endl;

    std::cout << "Room Activities:" << std::endl;
    hotel->printRoomActivities(101);
    std::cout << std::endl;

    hotel->printRoomUsageReport("2023-05-22", "2023-05-24");
    std::cout << std::endl;

    Room* availableRoom = hotel->findAvailableRoom(2, "2023-05-19", "2023-05-21");
    if (availableRoom != nullptr) {
        std::cout << "Available room found: " << availableRoom->getNumber() << std::endl;
    } 
    else {
        std::cout << "No available room found." << std::endl;
    }

    std::cout << std::boolalpha << hotel->findEmergencyRoom(2, "2023-05-20", "2023-05-24") << std::endl;

    delete guest;
    delete guest1;
    delete guest2;
    delete guest3;
    delete guest4;
    delete guest5;
    delete guest6;
    delete room1;
    delete room2;
    delete room3;

    return 0;
}