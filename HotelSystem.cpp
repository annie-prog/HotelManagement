#include "HotelSystem.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>

HotelSystem* HotelSystem::instance = nullptr;

HotelSystem* HotelSystem::getInstance(){
    if(instance == nullptr){
        instance = new HotelSystem();
    }
    return instance;
}
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
void HotelSystem::printActivityGuests(const std::string& activityName) const {
    bool activityFound = false;

    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i]->getName() == activityName) {
            activityFound = true;
            Guest** guests = activities[i]->getGuests();
            unsigned int guestsCount = activities[i]->getGuestsCount();

            std::cout << "Guests for activity '" << activityName << "':" << std::endl;
            for (unsigned int j = 0; j < guestsCount; j++) {
                std::cout << "- " << guests[j]->getFirstName() << " " << guests[j]->getLastName() << std::endl;
            }
            break;
        }
    }

    if (!activityFound) {
        std::cout << "Activity '" << activityName << "' not found." << std::endl;
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
std::string HotelSystem::getCurrentDate() const {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d");

    return oss.str();
}
void HotelSystem::printAvailableRooms(const std::string& date) const {
    std::string currentDate = date.empty() ? getCurrentDate() : date;
    std::cout << "Available Rooms on " << currentDate << ":" << std::endl;

    bool isAvailable = false;
    for (unsigned int i = 0; i < roomCount; i++) {
        if (!rooms[i]->isReservedOnDate(currentDate)) {
            std::cout << "Room Number: " << rooms[i]->getNumber() << std::endl;
            std::cout << "Number of Beds: " << rooms[i]->getNumberOfBeds() << std::endl;
            std::cout << "------------------------" << std::endl;
            isAvailable = true;
        }
    }

    if (!isAvailable) {
        std::cout << "No available rooms on " << currentDate << "!" << std::endl;
    }
}
void HotelSystem::makeReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests) {
    Room* room = getRoom(roomNumber);
    if (room) {
        if (numGuests == 0) {
            numGuests = room->getNumberOfBeds();
        }

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
void HotelSystem::addGuestToRoom(int roomNumber, Guest* guest) {
    Room* room = getRoom(roomNumber);
    if (room) {
        room->addGuest(guest);
        std::cout << "Guest added to Room " << roomNumber << " successfully." << std::endl;
    } else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::checkout(int roomNumber) {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        room->checkout();
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
            int usageDays = rooms[i]->getUsageDays(from, to);
            std::cout << "Occupied (" << usageDays << " days)" << std::endl;
        } 
        else {
            std::cout << "Available" << std::endl;
        }
    }
}
Room* HotelSystem::findAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const {
    Room* preferredRoom = nullptr;

    for (unsigned int i = 0; i < roomCount; i++) {
        Room* currentRoom = rooms[i];
        if (currentRoom->getNumberOfBeds() >= beds && !currentRoom->isReservedInPeriod(from, to)) {
            if (preferredRoom == nullptr || currentRoom->getNumberOfBeds() < preferredRoom->getNumberOfBeds()) {
                preferredRoom = currentRoom;
            }
        }
    }

    return preferredRoom;
}
bool HotelSystem::findEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to) {
    Room* preferredRoom = nullptr;

    Room** occupiedRooms = new Room*[roomCount];
    unsigned int occupiedRoomCount = 0;

    for (unsigned int i = 0; i < roomCount; i++) {
        Room* currentRoom = rooms[i];
        if (currentRoom->isReservedInPeriod(from, to)) {
            occupiedRooms[occupiedRoomCount] = currentRoom;
            occupiedRoomCount++;
        }
    }

    std::sort(occupiedRooms, occupiedRooms + occupiedRoomCount, [](Room* a, Room* b) {
        return a->getNumberOfBeds() < b->getNumberOfBeds();
    });

    for (unsigned int i = 0; i < roomCount; i++) {
        Room* currentRoom = rooms[i];
        if (currentRoom->getNumberOfBeds() >= beds && !currentRoom->isReservedInPeriod(from, to)) {
            if (preferredRoom == nullptr || currentRoom->getNumberOfBeds() < preferredRoom->getNumberOfBeds()) {
                preferredRoom = currentRoom;
            }
        }
    }

    if (preferredRoom != nullptr) {
        for (unsigned int i = 0; i < occupiedRoomCount; i++) {
            Room* occupiedRoom = occupiedRooms[i];
            if (preferredRoom->getNumberOfBeds() - occupiedRoom->getNumberOfBeds() <= 2) {
                preferredRoom->moveGuestsFromRoom(occupiedRoom);
                occupiedRoom->clearReservation();
            }
        }

        delete[] occupiedRooms;
        return true;
    }

    delete[] occupiedRooms;
    return false;
}
void HotelSystem::declareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note) {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        room->addReservation(new Reservation(from, to, note));
        std::cout << "Room " << roomNumber << " declared as unavailable because of " << note << std::endl;
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
            std::cout << "- " << roomActivities[i]->getName() << std::endl;
        }
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}