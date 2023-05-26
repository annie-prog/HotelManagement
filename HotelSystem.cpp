#include "HotelSystem.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>

HotelSystem* HotelSystem::instance = nullptr;

HotelSystem* HotelSystem::getInstance(){
    if(!instance){
        instance = new HotelSystem();
    }
    return instance;
}
HotelSystem::HotelSystem() : rooms(nullptr), roomCount(0), reservations(nullptr), reservationCount(0), activities(nullptr), activitiesCount(0), emergencyRoom(nullptr) {
    accommodation = new Accommodation();
}
HotelSystem::~HotelSystem() {
    delete accommodation;
    delete[] rooms;
    delete[] reservations;
    delete[] activities;
}
Room* HotelSystem::getRoom(int roomNumber) const {
    for (unsigned int i = 0; i < roomCount; i++) {
        if (rooms[i]->getNumber() == roomNumber) {
            return rooms[i];
        }
    }
    return nullptr;
}
void HotelSystem::addRoom(int roomNumber, unsigned int numBeds) {
    Room* room = new Room(roomNumber, numBeds);
    Room** newRooms = new Room*[roomCount + 1];
    for (unsigned int i = 0; i < roomCount; i++) {
        newRooms[i] = rooms[i];
    }
    newRooms[roomCount] = room;

    delete[] rooms;
    rooms = newRooms;
    roomCount++;
}
void HotelSystem::addRoom(const Room* room) {
    Room* newRoom = new Room(*room);
    Room** newRooms = new Room*[roomCount + 1];
    for (unsigned int i = 0; i < roomCount; i++) {
        newRooms[i] = rooms[i];
    }
    newRooms[roomCount] = newRoom;

    delete[] rooms;
    rooms = newRooms;
    roomCount++;

    std::cout << "Room added successfully." << std::endl;
}
Room** HotelSystem::getRooms() const {
    return this->rooms;
}
unsigned int HotelSystem::getRoomCount() const {
    return this->roomCount;
}
Guest** HotelSystem::getGuests() const {
    return accommodation->getGuests();
}
unsigned int HotelSystem::getNumGuests() const {
    return accommodation->getNumGuests();
}
void HotelSystem::printRooms() const {
    std::cout << "Rooms:" << std::endl;
    for (unsigned int i = 0; i < roomCount; i++) {
        std::cout << "Room " << rooms[i]->getNumber() << ", Beds: " << rooms[i]->getNumberOfBeds() << std::endl;
    }
}
void HotelSystem::printActivityGuests(const std::string& activityName) const {
    Activity* activity = nullptr;
    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i]->getName() == activityName) {
            activity = activities[i];
            break;
        }
    }
    if (activity) {
        Accommodation& accommodation = activity->getAccommodation();
        Guest** guests = accommodation.getGuests();
        unsigned int guestCount = accommodation.getNumGuests();

        std::cout << "Guests for Activity " << activityName << ":" << std::endl;
        for (unsigned int i = 0; i < guestCount; i++) {
            std::cout << guests[i]->getFirstName() << " " << guests[i]->getLastName() << std::endl;
        }
    } 
    else {
        std::cout << "Activity not found." << std::endl;
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
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
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

        Reservation* reservation = new Reservation(roomNumber, checkIn, checkOut, note);
        room->addReservation(*reservation);
        std::cout << "Reservation made successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::addGuestToRoom(int roomNumber, Guest* guest) {
    Room room(roomNumber, 4); //max number of beds is 4

    if (room.getNumber() == roomNumber) {
        room.addGuest(*guest);
        std::cout << "Guest added to Room " << roomNumber << " successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::checkout(int roomNumber) {
    Room* room = getRoom(roomNumber);
    if (room) {
        room->checkout();
        std::cout << "Room " << roomNumber << " checked out successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::addActivity(const std::string& name) {
    Activity* activity = new Activity(name);
    Activity** newActivities = new Activity*[activitiesCount + 1];
    for (unsigned int i = 0; i < activitiesCount; i++) {
        newActivities[i] = activities[i];
    }
    newActivities[activitiesCount] = activity;

    delete[] activities;
    activities = newActivities;
    activitiesCount++;

    std::cout << "Activity added successfully." << std::endl;
}
void HotelSystem::addGuest(Guest* guest) {
    accommodation->addGuest(*guest);
    std::cout << "Guest added successfully." << std::endl;
}
void HotelSystem::addGuestToActivity(const std::string& activityName, Guest* guest) {
    Activity* activity = nullptr;
    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i]->getName() == activityName) {
            activity = activities[i];
            break;
        }
    }
    if (activity) {
        activity->addGuest(*guest);
        std::cout << "Guest added to Activity " << activityName << " successfully." << std::endl;
    } 
    else {
        std::cout << "Activity not found." << std::endl;
    }
}
void HotelSystem::printActivities() const {
    std::cout << "Activities:" << std::endl;
    for (unsigned int i = 0; i < activitiesCount; i++) {
        std::cout << activities[i]->getName() << std::endl;
    }
}
void HotelSystem::printGuests() const {
    Guest** guests = accommodation->getGuests();
    unsigned int numGuests = accommodation->getNumGuests();

    std::cout << "Guests:" << std::endl;
    for (unsigned int i = 0; i < numGuests; i++) {
        std::cout << guests[i]->getFirstName() << " " << guests[i]->getLastName() << std::endl;
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
    for (unsigned int i = 0; i < roomCount; i++) {
        Room* room = rooms[i];
        if (!room->isReservedInPeriod(from, to) && room->getNumberOfBeds() >= beds) {
            return room;
        }
    }
    return nullptr;
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
                occupiedRoom->clearReservations();
            }
        }

        delete[] occupiedRooms;
        return true;
    } 
    else {
        if (emergencyRoom != nullptr && emergencyRoom->getNumberOfBeds() >= beds && !emergencyRoom->isReservedInPeriod(from, to)) {
            for (unsigned int i = 0; i < occupiedRoomCount; i++) {
                Room* occupiedRoom = occupiedRooms[i];
                if (emergencyRoom->getNumberOfBeds() - occupiedRoom->getNumberOfBeds() <= 2) {
                    emergencyRoom->moveGuestsFromRoom(occupiedRoom);
                    occupiedRoom->clearReservations();
                }
            }
            delete[] occupiedRooms;
            return true;
        }
    }

    delete[] occupiedRooms;
    return false;
}
void HotelSystem::declareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note) {
    Room* room = getRoom(roomNumber);
    if (room) {
        room->addReservation(Reservation(roomNumber, from, to, note));
        std::cout << "Room " << roomNumber << " declared unavailable because of " << note << std::endl;
    }
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::addGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest) {
    for (unsigned int i = 0; i < this->activitiesCount; i++) {
        Activity* activity = activities[i];
        if (activity->getName() == activityName) {
            activity->addGuest(*guest);
            std::cout << "Guest " << guest->getFirstName() << " " << guest->getLastName()
                      << " added to activity " << activityName << " in room " << roomNumber << "." << std::endl;
            return;
        }
    }
    std::cout << "Activity not found." << std::endl;
}
void HotelSystem::printRoomActivities(int roomNumber) const {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        std::cout << "Activities for Room " << roomNumber << ":" << std::endl;
        if (room->getActivitiesCount() == 0) {
            std::cout << "No activities found." << std::endl;
        } 
        else {
            Activity** roomActivities = room->getActivities();
            unsigned int activityCount = room->getActivitiesCount();
            for (unsigned int i = 0; i < activityCount; i++) {
                std::cout << "- " << roomActivities[i]->getName() << std::endl;
            }
        }
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
Guest* HotelSystem::findGuestByName(const std::string& guestName) const {
    Guest** guests = accommodation->getGuests();
    unsigned int numGuests = accommodation->getNumGuests();

    for (unsigned int i = 0; i < numGuests; i++) {
        Guest* guest = guests[i];
        if (guest->getFirstName() == guestName) {
            return guest;
        }
    }
    return nullptr;
}
void HotelSystem::addRoomActivity(int roomNumber, Activity* activity) {
    Room* room = getRoom(roomNumber);
    if (room != nullptr) {
        room->addActivity(*activity);
        std::cout << "Activity added to Room " << roomNumber << " successfully." << std::endl;
    }
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::addEmergencyRoom(Room* room) {
    emergencyRoom = room;
    if(emergencyRoom != nullptr){
        std::cout << "Energency room added!" << std::endl;
    }
}