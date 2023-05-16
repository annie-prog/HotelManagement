#include "HotelSystem.hpp"
#include <iostream>

int main() {
    Room* room1 = new Room(101, 2);
    Room* room2 = new Room(102, 1);
    Room* room3 = new Room(201, 3);

    HotelSystem hotel;

    hotel.addRoom(room1);
    hotel.addRoom(room2);
    hotel.addRoom(room3);

    std::cout << "All Rooms:" << std::endl;
    hotel.printRooms();
    std::cout << std::endl;

    std::cout << "Making reservations..." << std::endl;
    hotel.makeReservation(101, "2023-05-20", "2023-05-25", "Reservation 1", 2);
    hotel.makeReservation(102, "2023-05-22", "2023-05-24", "Reservation 2", 1);
    hotel.makeReservation(201, "2023-05-23", "2023-05-26", "Reservation 3", 3);
    std::cout << std::endl;

    std::cout << "Available Rooms:" << std::endl;
    hotel.printAvailableRooms("2023-05-20", "2023-05-22");
    std::cout << std::endl;

    std::cout << "Room Activities:" << std::endl;
    hotel.printRoomActivities(101);
    std::cout << std::endl;

    std::cout << "Adding activity and guest to room activity..." << std::endl;
    hotel.addActivity("Swimming");
    Guest* guest = new Guest("John", "Doe", "0882750588");
    hotel.addGuestToRoomActivity(101, "Swimming", guest);
    std::cout << std::endl;

    std::cout << "Room Activities:" << std::endl;
    hotel.printRoomActivities(101);
    std::cout << std::endl;

    std::cout << "Checking out room..." << std::endl;
    hotel.checkout(101);
    std::cout << std::endl;

    std::cout << "Room Activities:" << std::endl;
    hotel.printRoomActivities(101);
    std::cout << std::endl;

    delete[] guest;
    delete[] room1;
    delete[] room2;
    delete[] room3;

    return 0;
}

