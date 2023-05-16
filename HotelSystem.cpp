#include "HotelSystem.hpp"
#include <iostream>
#include <iomanip>

HotelSystem::HotelSystem(Room** rooms, unsigned int roomCount): rooms(rooms), roomCount(0) {}
HotelSystem::HotelSystem() : rooms(nullptr), roomCount(0) {}
HotelSystem::~HotelSystem() {
    if (this->rooms != nullptr) {
        for (unsigned int i = 0; i < this->roomCount; i++) {
            delete this->rooms[i];
        }
        delete[] this->rooms;
    }
}
void HotelSystem::addRoom(const Room* room) {
    Room** newRooms = new Room*[this->roomCount + 1];
    for (unsigned int i = 0; i < this->roomCount; i++) {
        newRooms[i] = this->rooms[i];
    }
    newRooms[this->roomCount] = const_cast<Room*>(room);

    delete[] this->rooms;
    this->rooms = newRooms;
    this->roomCount++;
}
Room* HotelSystem::getRoom(int roomNumber) const {
    for (unsigned int i = 0; i < this->roomCount; i++) {
        if (this->rooms[i]->getNumber() == roomNumber) {
            return this->rooms[i];
        }
    }
    return nullptr;
}
Room** HotelSystem::getRooms() const {
    return this->rooms;
}
Reservation** HotelSystem::getReservations() const {
    unsigned int totalReservations = 0;
    for (unsigned int i = 0; i < roomCount; i++) {
        totalReservations += rooms[i]->getReservationsCount();
    }

    Reservation** allReservations = new Reservation*[totalReservations];
    unsigned int currentIndex = 0;
    for (unsigned int i = 0; i < roomCount; i++) {
        Reservation** roomReservations = rooms[i]->getReservations();
        for (unsigned int j = 0; j < rooms[i]->getReservationsCount(); j++) {
            allReservations[currentIndex++] = roomReservations[j];
        }
    }

    return allReservations;
}
Activity** HotelSystem::getActivities() const {
    unsigned int totalActivities = 0;
    for (unsigned int i = 0; i < roomCount; i++) {
        totalActivities += rooms[i]->getActivitiesCount();
    }

    Activity** allActivities = new Activity*[totalActivities];
    unsigned int currentIndex = 0;
    for (unsigned int i = 0; i < roomCount; i++) {
        Activity** roomActivities = rooms[i]->getActivities();
        for (unsigned int j = 0; j < rooms[i]->getActivitiesCount(); j++) {
            allActivities[currentIndex++] = roomActivities[j];
        }
    }

    return allActivities;
}
void HotelSystem::printRooms() const {
    for (unsigned int i = 0; i < this->roomCount; i++) {
        std::cout << "Room Number: " << this->rooms[i]->getNumber() << std::endl;
        std::cout << "Number of Beds: " << this->rooms[i]->getNumberOfBeds() << std::endl;
        std::cout << "Guests: ";
        Guest** roomGuests = rooms[i]->getGuests();
        for (unsigned int j = 0; j < this->rooms[i]->getGuestsCount(); j++) {
            std::cout << roomGuests[j]->getFirstName() << " " << roomGuests[j]->getLastName() << ", ";
        }
        std::cout << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}
bool HotelSystem::isRoomAvailable(const std::string& date) const {
    for (unsigned int i = 0; i < this->roomCount; i++) {
        if (this->rooms[i]->isReservedInPeriod(date, date)) {
            return false;
        }
    }
    return true;
}
void HotelSystem::printAvailableRooms(const std::string& checkIn, const std::string& checkOut) const {
    std::cout << "Available Rooms from " << checkIn << " to " << checkOut << ":" << std::endl;
    bool availableRoomsExist = false;
    if (this->roomCount != 0) {
        for (unsigned int i = 0; i < this->roomCount; i++) {
            if (!rooms[i]->isReservedInPeriod(checkIn, checkOut)) {
                std::cout << "Room Number: " << rooms[i]->getNumber() << std::endl;
                std::cout << "Number of Beds: " << rooms[i]->getNumberOfBeds() << std::endl;
                std::cout << "------------------------" << std::endl;
                availableRoomsExist = true;
            }
        }
    }
    if (!availableRoomsExist) {
        std::cout << "No available rooms for this period of time!" << std::endl;
    }
}
void HotelSystem::makeReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests) {
    Room* room = getRoom(roomNumber);
    if (room) {
        Reservation* reservation = new Reservation(roomNumber, checkIn, checkOut, note, numGuests);
        room->addReservation(reservation);
        std::cout << "Reservation made successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::cancelReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut) {
    Room* room = getRoom(roomNumber);
    if (room) {
        room->cancelReservation(checkIn, checkOut);
        std::cout << "Reservation canceled successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::addActivity(const std::string& name) {
    Activity* activity = new Activity(name);
    Activity** newActivities = new Activity*[this->activitiesCount + 1];
    for (unsigned int i = 0; i < this->activitiesCount; i++) {
        newActivities[i] = this->activities[i];
    }
    newActivities[activitiesCount] = activity;

    delete[] this->activities;
    this->activities = newActivities;
    this->activitiesCount++;

    std::cout << "Activity added successfully." << std::endl;
}

void HotelSystem::addGuestToActivity(const std::string& activityName, Guest* guest) {
    for (unsigned int i = 0; i < this->activitiesCount; i++) {
        if (this->activities[i]->getName() == activityName) {
            this->activities[i]->addGuest(guest);
            std::cout << "Guest added to activity successfully." << std::endl;
            return;
        }
    }
    std::cout << "Activity not found." << std::endl;
}
void HotelSystem::printActivities() const {
    std::cout << "Activities:" << std::endl;
    for (unsigned int i = 0; i < activitiesCount; i++) {
        std::cout << activities[i]->getName() << std::endl;
    }
}

void HotelSystem::printGuests() const {
    std::cout << "Guests:" << std::endl;
    for (unsigned int i = 0; i < roomCount; i++) {
        Guest** guests = rooms[i]->getGuests();
        unsigned int guestCount = rooms[i]->getGuestsCount();
        for (unsigned int j = 0; j < guestCount; j++) {
            std::cout << guests[j]->getFirstName() << " " << guests[j]->getLastName() << std::endl;
        }
    }
}
void HotelSystem::printRoomUsageReport(const std::string& from, const std::string& to) const {
    std::cout << "Room Usage Report:" << std::endl;
    for (unsigned int i = 0; i < roomCount; i++) {
        std::cout << "Room " << rooms[i]->getNumber() << ": ";
        if (rooms[i]->isReservedInPeriod(from, to)) {
            std::cout << "Occupied" << std::endl;
        } 
        else {
            std::cout << "Available" << std::endl;
        }
    }
}
Room* HotelSystem::findAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const {
    for (unsigned int i = 0; i < roomCount; i++) {
        if (rooms[i]->getNumberOfBeds() >= beds && !rooms[i]->isReservedInPeriod(from, to)) {
            return rooms[i];
        }
    }
    return nullptr;
}
void HotelSystem::findEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to, Room*& availableRoom, Room*& roomToSwap1, Room*& roomToSwap2) const {
    availableRoom = nullptr;
    roomToSwap1 = nullptr;
    roomToSwap2 = nullptr;

    for (unsigned int i = 0; i < roomCount; i++) {
        if (rooms[i]->getNumberOfBeds() >= beds && !rooms[i]->isReservedInPeriod(from, to)) {
            if (availableRoom == nullptr) {
                availableRoom = rooms[i];
            } 
            else if (roomToSwap1 == nullptr) {
                roomToSwap1 = rooms[i];
            } 
            else if (roomToSwap2 == nullptr) {
                roomToSwap2 = rooms[i];
                return;
            }
        }
    }
}
void HotelSystem::declareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note) {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        room->addReservation(new Reservation(from, to));
        std::cout << "Room " << roomNumber << " declared as unavailable." << note << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::addGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest) {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        Activity* activity = nullptr;
        for (unsigned int i = 0; i < activitiesCount; i++) {
            if (activities[i]->getName() == activityName) {
                activity = activities[i];
                break;
            }
        }
        if (activity != nullptr) {
            room->addGuestToActivity(activityName, guest);
            std::cout << "Guest added to activity successfully." << std::endl;
        } 
        else {
            std::cout << "Activity not found." << std::endl;
        }
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::printRoomActivities(int roomNumber) const {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        std::cout << "Activities for Room " << roomNumber << ":" << std::endl;
        Activity** roomActivities = room->getActivities();
        unsigned int activityCount = room->getActivitiesCount();
        for (unsigned int i = 0; i < activityCount; i++) {
            std::cout << roomActivities[i]->getName() << std::endl;
        }
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::checkout(int roomNumber) {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        room->clearGuests();
        std::cout << "Room " << roomNumber << " checked out successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}