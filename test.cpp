#include "HotelSystem.hpp"
#include <iostream>

int main() {
    Room* room1 = new Room(101, 2);
    Room* room2 = new Room(102, 1);
    Room* room3 = new Room(201, 3);

    HotelSystem hotelSystem({ room1, room2, room3 });

    std::cout << "Initial rooms:" << std::endl;
    hotelSystem.printRooms();

    Guest* guest1 = new Guest("John", "Doe", "0882750588");
    Guest* guest2 = new Guest("Jane", "Smith", "0889345678");
    room1->addGuest(guest1);
    room2->addGuest(guest2);

    

    hotelSystem.addActivity("Swimming");
    hotelSystem.addActivity("Gym");

    hotelSystem.addGuestToActivity("Swimming", guest1);
    hotelSystem.addGuestToActivity("Gym", guest2);

    std::cout << "Updated rooms:" << std::endl;
    hotelSystem.printRooms();

    hotelSystem.printActivities();

    // Print guests
    hotelSystem.printGuests();

    hotelSystem.makeReservation(201, "2023-06-01", "2023-06-05", "Vacation", 2);

    hotelSystem.printAvailableRooms("2023-06-01", "2023-06-05");

    hotelSystem.cancelReservation(201, "2023-06-01", "2023-06-05");

    std::cout << "Updated rooms:" << std::endl;
    hotelSystem.printRooms();

    hotelSystem.checkout(101);
    hotelSystem.checkout(102);

    // Print updated rooms
    std::cout << "Updated rooms:" << std::endl;
    hotelSystem.printRooms();

    delete guest1;
    delete guest2;
    delete room1;
    delete room2;
    delete room3;

    return 0;
}

