#include "HotelSystem.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>

HotelSystem* HotelSystem::instance = nullptr;

HotelSystem* HotelSystem::GetInstance(){
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
Room* HotelSystem::GetRoom(int roomNumber) const {
    for (unsigned int i = 0; i < roomCount; i++) {
        if (rooms[i]->GetNumber() == roomNumber) {
            return rooms[i];
        }
    }
    return nullptr;
}
void HotelSystem::AddRoom(int roomNumber, unsigned int numBeds) {
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
void HotelSystem::AddRoom(const Room* room) {
    Room* newRoom = new Room(*room);
    Room** newRooms = new Room*[roomCount + 1];
    for (unsigned int i = 0; i < roomCount; i++) {
        newRooms[i] = rooms[i];
    }
    newRooms[roomCount] = newRoom;

    delete[] rooms;
    rooms = newRooms;
    roomCount++;
}
Room** HotelSystem::GetRooms() const {
    return this->rooms;
}
unsigned int HotelSystem::GetRoomCount() const {
    return this->roomCount;
}
Guest** HotelSystem::GetGuests() const {
    return accommodation->GetGuests();
}
unsigned int HotelSystem::GetNumGuests() const {
    return accommodation->GetNumGuests();
}
void HotelSystem::PrintRooms() const {
    std::cout << "Rooms in the hotel:" << std::endl;
    for (unsigned int i = 0; i < roomCount; i++) {
        std::cout << "Room " << rooms[i]->GetNumber() << ", Beds: " << rooms[i]->GetNumberOfBeds() << std::endl;
    }
}
void HotelSystem::PrintActivityGuests(const std::string& activityName) const {
    Activity* activity = nullptr;
    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i]->GetName() == activityName) {
            activity = activities[i];
            break;
        }
    }
    if (activity) {
        Accommodation& accommodation = activity->GetAccommodation();
        Guest** guests = accommodation.GetGuests();
        unsigned int guestCount = accommodation.GetNumGuests();

        std::cout << "Guests for Activity " << activityName << ":" << std::endl;
        for (unsigned int i = 0; i < guestCount; i++) {
            std::cout << guests[i]->GetFirstName() << " " << guests[i]->GetLastName() << std::endl;
        }
    } 
    else {
        std::cout << "Activity not found." << std::endl;
    }
}
bool HotelSystem::IsRoomAvailable(const std::string& date) const {
    for (unsigned int i = 0; i < this->roomCount; i++) {
        if (this->rooms[i]->IsReservedInPeriod(date, date)) {
            return false;
        }
    }
    return true;
}
std::string HotelSystem::GetCurrentDate() const {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}
void HotelSystem::PrintAvailableRooms(const std::string& date) const {
    std::string currentDate = date.empty() ? GetCurrentDate() : date;
    std::cout << "Available Rooms on " << currentDate << ":" << std::endl;

    bool isAvailable = false;
    for (unsigned int i = 0; i < roomCount; i++) {
        if (!rooms[i]->IsReservedOnDate(currentDate)) {
            std::cout << "Room Number: " << rooms[i]->GetNumber() << std::endl;
            std::cout << "Number of Beds: " << rooms[i]->GetNumberOfBeds() << std::endl;
            std::cout << "------------------------" << std::endl;
            isAvailable = true;
        }
    }

    if (!isAvailable) {
        std::cout << "No available rooms on " << currentDate << "!" << std::endl;
    }
}
void HotelSystem::Checkin(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests) {
    Room* room = GetRoom(roomNumber);
    if (room) {
        if (numGuests == 0) {
            numGuests = room->GetNumberOfBeds();
        }

        if (checkOut < checkIn) {
            throw std::invalid_argument("Invalid reservation dates. Check-out date cannot be earlier than check-in date.");
            std::exit(0);
        }

        Reservation* reservation = new Reservation(roomNumber, checkIn, checkOut, note);
        room->AddReservation(*reservation);
        unsigned int usageDays = room->GetUsageDays(checkIn, checkOut);
        std::cout << "Reservation made successfully. You have to pay " << ((usageDays - 1) * PRICE_PER_NIGHT_PER_PERSON * numGuests) << "lv." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::AddGuestToRoom(int roomNumber, Guest* guest) {
    Room room(roomNumber, 4); //max number of beds is 4

    if (room.GetNumber() == roomNumber) {
        room.AddGuest(*guest);
        std::cout << "Guest added to Room " << roomNumber << " successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::Checkout(int roomNumber) {
    Room* room = GetRoom(roomNumber);
    if (room) {
        room->Checkout();
        std::cout << "Room " << roomNumber << " checked out successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::AddActivity(const std::string& name) {
    Activity* activity = new Activity(name);
    Activity** newActivities = new Activity*[activitiesCount + 1];
    for (unsigned int i = 0; i < activitiesCount; i++) {
        newActivities[i] = activities[i];
    }
    newActivities[activitiesCount] = activity;

    delete[] activities;
    activities = newActivities;
    activitiesCount++;
}
void HotelSystem::AddGuest(Guest* guest) {
    accommodation->AddGuest(*guest);
}
void HotelSystem::AddGuestToActivity(const std::string& activityName, Guest* guest) {
    Activity* activity = nullptr;
    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i]->GetName() == activityName) {
            activity = activities[i];
            break;
        }
    }
    if (activity) {
        activity->AddGuest(*guest);
        std::cout << "Guest added to Activity " << activityName << " successfully." << std::endl;
    } 
    else {
        std::cout << "Activity not found." << std::endl;
    }
}
void HotelSystem::PrintActivities() const {
    std::cout << "Activities:" << std::endl;
    for (unsigned int i = 0; i < activitiesCount; i++) {
        std::cout << activities[i]->GetName() << std::endl;
    }
}
void HotelSystem::PrintGuests() const {
    Guest** guests = accommodation->GetGuests();
    unsigned int numGuests = accommodation->GetNumGuests();

    std::cout << "Guests:" << std::endl;
    for (unsigned int i = 0; i < numGuests; i++) {
        std::cout << guests[i]->GetFirstName() << " " << guests[i]->GetLastName() << " " << guests[i]->GetPhoneNumber() << std::endl;
    }
}
void HotelSystem::PrintRoomUsageReport(const std::string& from, const std::string& to) const {
    std::cout << "Room Usage Report:" << std::endl;
    for (unsigned int i = 0; i < roomCount; i++) {
        std::cout << "Room " << rooms[i]->GetNumber() << ": ";
        if (rooms[i]->IsReservedInPeriod(from, to)) {
            int usageDays = rooms[i]->GetUsageDays(from, to);
            std::cout << "Occupied (" << usageDays << " days)" << std::endl;
        } 
        else {
            std::cout << "Available" << std::endl;
        }
    }
}
Room* HotelSystem::FindAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const {
    Room* bestRoom = nullptr;
    unsigned int minBeds = std::numeric_limits<unsigned int>::max();

    for (unsigned int i = 0; i < roomCount; i++) {
        Room* room = rooms[i];
        if (!room->IsReservedInPeriod(from, to) && room->GetNumberOfBeds() >= beds) {
            if (room->GetNumberOfBeds() < minBeds) {
                minBeds = room->GetNumberOfBeds();
                bestRoom = room;
            }
        }
    }
    return bestRoom;
}
bool HotelSystem::FindEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to) {
    Room* preferredRoom = nullptr;

    Room** occupiedRooms = new Room*[roomCount];
    unsigned int occupiedRoomCount = 0;

    for (unsigned int i = 0; i < roomCount; i++) {
        Room* currentRoom = rooms[i];
        if (currentRoom->IsReservedInPeriod(from, to)) {
            occupiedRooms[occupiedRoomCount] = currentRoom;
            occupiedRoomCount++;
        }
    }

    std::sort(occupiedRooms, occupiedRooms + occupiedRoomCount, [](Room* a, Room* b) {
        return a->GetNumberOfBeds() < b->GetNumberOfBeds();
    });

    for (unsigned int i = 0; i < roomCount; i++) {
        Room* currentRoom = rooms[i];
        if (currentRoom->GetNumberOfBeds() >= beds && !currentRoom->IsReservedInPeriod(from, to)) {
            if (preferredRoom == nullptr || currentRoom->GetNumberOfBeds() < preferredRoom->GetNumberOfBeds()) {
                preferredRoom = currentRoom;
            }
        }
    }

    if (preferredRoom != nullptr) {
        for (unsigned int i = 0; i < occupiedRoomCount; i++) {
            Room* occupiedRoom = occupiedRooms[i];
            if (preferredRoom->GetNumberOfBeds() - occupiedRoom->GetNumberOfBeds() <= 2) {
                preferredRoom->MoveGuestsFromRoom(occupiedRoom);
                occupiedRoom->ClearReservations();
            }
        }

        delete[] occupiedRooms;
        return true;
    } 
    else {
        if (emergencyRoom != nullptr && emergencyRoom->GetNumberOfBeds() >= beds && !emergencyRoom->IsReservedInPeriod(from, to)) {
            for (unsigned int i = 0; i < occupiedRoomCount; i++) {
                Room* occupiedRoom = occupiedRooms[i];
                if (emergencyRoom->GetNumberOfBeds() - occupiedRoom->GetNumberOfBeds() <= 2) {
                    emergencyRoom->MoveGuestsFromRoom(occupiedRoom);
                    occupiedRoom->ClearReservations();
                }
            }
            delete[] occupiedRooms;
            return true;
        }
    }

    delete[] occupiedRooms;
    return false;
}
void HotelSystem::DeclareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note) {
    Room* room = GetRoom(roomNumber);
    if (room) {
        room->AddReservation(Reservation(roomNumber, from, to, note));
        std::cout << "Room " << roomNumber << " declared unavailable because of " << note << std::endl;
    }
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::AddGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest) {
    for (unsigned int i = 0; i < this->activitiesCount; i++) {
        Activity* activity = activities[i];
        if (activity->GetName() == activityName) {
            activity->AddGuest(*guest);
            std::cout << "Guest " << guest->GetFirstName() << " " << guest->GetLastName()
                      << " added to activity " << activityName << " in room " << roomNumber << "." << std::endl;
            return;
        }
    }
    std::cout << "Activity not found." << std::endl;
}
void HotelSystem::PrintRoomActivities(int roomNumber) const {
    Room* room = GetRoom(roomNumber);
    if (room != nullptr) {
        std::cout << "Activities for Room " << roomNumber << ":" << std::endl;
        if (room->GetActivitiesCount() == 0) {
            std::cout << "No activities found." << std::endl;
        } 
        else {
            Activity** roomActivities = room->GetActivities();
            unsigned int activityCount = room->GetActivitiesCount();
            for (unsigned int i = 0; i < activityCount; i++) {
                std::cout << "- " << roomActivities[i]->GetName() << std::endl;
            }
        }
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
Guest* HotelSystem::FindGuestByName(const std::string& guestName) const {
    Guest** guests = accommodation->GetGuests();
    unsigned int numGuests = accommodation->GetNumGuests();

    for (unsigned int i = 0; i < numGuests; i++) {
        Guest* guest = guests[i];
        if (guest->GetFirstName() == guestName) {
            return guest;
        }
    }
    return nullptr;
}
void HotelSystem::AddRoomActivity(int roomNumber, Activity* activity) {
    Room* room = GetRoom(roomNumber);
    if (room != nullptr) {
        room->AddActivity(*activity);
        std::cout << "Activity added to Room " << roomNumber << " successfully." << std::endl;
    }
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::AddEmergencyRoom(Room* room) {
    emergencyRoom = room;
    if(emergencyRoom != nullptr){
        std::cout << "Energency room added!" << std::endl;
    }
}