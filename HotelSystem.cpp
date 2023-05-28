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
    // Deallocated memory for all members in the system
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
    // Create a new Room object with the given room number and number of beds
    Room* room = new Room(roomNumber, numBeds);

    // Create a new array of Room pointers with increased size
    Room** newRooms = new Room*[roomCount + 1];
    for (unsigned int i = 0; i < roomCount; i++) {
        newRooms[i] = rooms[i]; // Copy the existing Room objects to the new array
    }
    newRooms[roomCount] = room; // Add the new Room object to the end of the new array

    delete[] rooms; // Delete the old array of Room pointers
    rooms = newRooms; // Update the rooms pointer to point to the new array
    roomCount++; // Increment the room count
}
void HotelSystem::AddRoom(const Room* room) {
    Room* newRoom = new Room(*room); // Create a new Room object by copying the provided room
    Room** newRooms = new Room*[roomCount + 1]; // Create a new array of Room pointers with increased size
    for (unsigned int i = 0; i < roomCount; i++) {
        newRooms[i] = rooms[i]; // Copy the existing Room objects to the new array
    }
    newRooms[roomCount] = newRoom; // Add the new Room object to the end of the new array

    delete[] rooms; // Delete the old array of Room pointers
    rooms = newRooms; // Update the rooms pointer to point to the new array
    roomCount++; // Increment the room count
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
    Activity* activity = nullptr; // Initialize a pointer to an Activity object as null pointer
    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i]->GetName() == activityName) {
            activity = activities[i]; // Assign the pointer to the matching activity
            break;
        }
    }
    if (activity) { // Check if the activity pointer is not null pointer
        Accommodation& accommodation = activity->GetAccommodation();
        Guest** guests = accommodation.GetGuests();
        unsigned int guestCount = accommodation.GetNumGuests();

        std::cout << "Guests for Activity " << activityName << ":" << std::endl;

        // Iterate through the guests and print their first and last names
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
            return false; // If the room is reserved, return false
        }
    }
    return true; // If none of the rooms are reserved for the given date, return true
}
std::string HotelSystem::GetCurrentDate() const {
    time_t now = time(nullptr); // Get the current system time in seconds
    struct tm* timeinfo = localtime(&now); // Convert the time to the local time
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo); // Format the date and store it in the buffer according to the specified format ("%Y-%m-%d")
    return std::string(buffer); // Convert the formatted date to a std::string and return it
}
void HotelSystem::PrintAvailableRooms(const std::string& date) const {
    std::string currentDate = date.empty() ? GetCurrentDate() : date; // Checks if parameter date is passed
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

        if (checkOut < checkIn) { // Checks if checkIn date is later than checkOut
            throw std::invalid_argument("Invalid reservation dates. Check-out date cannot be earlier than check-in date.");
            std::exit(0);
        }

        Reservation* reservation = new Reservation(roomNumber, checkIn, checkOut, note);
        room->AddReservation(*reservation); // Adds reservation to a room
        unsigned int usageDays = room->GetUsageDays(checkIn, checkOut); // Gets usage days in a specific period of time
        std::cout << "Reservation made successfully. You have to pay " << ((usageDays - 1) * PRICE_PER_NIGHT_PER_PERSON * numGuests) << "lv." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::AddGuestToRoom(int roomNumber, Guest* guest) {
    Room room(roomNumber, 4); // Max number of beds is 4 (look at class HotelApp.cpp in the command ProcessAddGuestToRoom)

    if (room.GetNumber() == roomNumber) {
        room.AddGuest(*guest); // Adds guest to room
        std::cout << "Guest added to Room " << roomNumber << " successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::Checkout(int roomNumber) {
    Room* room = GetRoom(roomNumber);
    if (room) {
        room->Checkout(); // Checks out of the room
        std::cout << "Room " << roomNumber << " checked out successfully." << std::endl;
    } 
    else {
        std::cout << "Room not found." << std::endl;
    }
}
void HotelSystem::AddActivity(const std::string& name) {
    Activity* activity = new Activity(name); // Create a new Activity object with the provided name
    Activity** newActivities = new Activity*[activitiesCount + 1]; // Create a new array to hold the updated list of activities with increased size
    for (unsigned int i = 0; i < activitiesCount; i++) {
        newActivities[i] = activities[i];
    }
    newActivities[activitiesCount] = activity; // Add the new activity to the end of the new array

    delete[] activities; // Delete the old activities array to free up memory
    activities = newActivities; // Update the activities pointer to point to the new array
    activitiesCount++; // Increment the count of activities
}
void HotelSystem::AddGuest(Guest* guest) {
    accommodation->AddGuest(*guest); // Add the guest to the accommodation
}
void HotelSystem::AddGuestToActivity(const std::string& activityName, Guest* guest) {
    Activity* activity = nullptr; // Initialize a pointer to an Activity object as null pointer
    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i]->GetName() == activityName) { // Checks if the name of the current activity matches the provided activity name
            activity = activities[i]; // Assign the pointer to the matching activity
            break;
        }
    }
    if (activity) {
        activity->AddGuest(*guest); // Add the guest to the activity
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
    Guest** guests = accommodation->GetGuests(); // Retrieve the array of guests from the accommodation
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
            int usageDays = rooms[i]->GetUsageDays(from, to); // Calculate the number of days the room is occupied
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

            // Find the room with the minimum number of beds among the available rooms
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

    // Find the rooms that are occupied during the specified period 
    for (unsigned int i = 0; i < roomCount; i++) {
        Room* currentRoom = rooms[i];
        if (currentRoom->IsReservedInPeriod(from, to)) {
            occupiedRooms[occupiedRoomCount] = currentRoom;
            occupiedRoomCount++;
        }
    }

    // Sort the occupied rooms in ascending order based on the number of beds
    std::sort(occupiedRooms, occupiedRooms + occupiedRoomCount, [](Room* a, Room* b) {
        return a->GetNumberOfBeds() < b->GetNumberOfBeds();
    });

    // Find the preferred room that is available and has the required number of beds
    for (unsigned int i = 0; i < roomCount; i++) {
        Room* currentRoom = rooms[i];
        if (currentRoom->GetNumberOfBeds() >= beds && !currentRoom->IsReservedInPeriod(from, to)) {
            if (preferredRoom == nullptr || currentRoom->GetNumberOfBeds() < preferredRoom->GetNumberOfBeds()) {
                preferredRoom = currentRoom; // Update the preferred room if it is null or the current room has fewer beds
            }
        }
    }

    // If a preferred room is found, check if guests can be moved from occupied rooms to the preferred room
    if (preferredRoom != nullptr) {
        for (unsigned int i = 0; i < occupiedRoomCount; i++) {
            Room* occupiedRoom = occupiedRooms[i];

            // Check if the difference in the number of beds between the preferred room and occupied room is within the limit
            if (preferredRoom->GetNumberOfBeds() - occupiedRoom->GetNumberOfBeds() <= 2) {
                preferredRoom->MoveGuestsFromRoom(occupiedRoom);
                occupiedRoom->ClearReservations();
            }
        }

        delete[] occupiedRooms;
        return true;
    } 
    else {
        // If no preferred room is found, check if the emergency room can accommodate the guests
        if (emergencyRoom != nullptr && emergencyRoom->GetNumberOfBeds() >= beds && !emergencyRoom->IsReservedInPeriod(from, to)) {
            for (unsigned int i = 0; i < occupiedRoomCount; i++) {
                Room* occupiedRoom = occupiedRooms[i];

                // Check if the difference in the number of beds between the emergency room and occupied room is within the limit
                if (emergencyRoom->GetNumberOfBeds() - occupiedRoom->GetNumberOfBeds() <= 2) {
                    emergencyRoom->MoveGuestsFromRoom(occupiedRoom);
                    occupiedRoom->ClearReservations();
                }
            }
            delete[] occupiedRooms;
            return true;
        }
    }

    delete[] occupiedRooms; // Deallocation memory from occupied rooms
    return false;
}
void HotelSystem::DeclareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note) {
    Room* room = GetRoom(roomNumber);
    if (room) {
        room->AddReservation(Reservation(roomNumber, from, to, note)); // Adding a reservation to a room
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
            activity->AddGuest(*guest); // Adding guest to activity
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
            Activity** roomActivities = room->GetActivities(); // Getting all activities from a room
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
Guest* HotelSystem::FindGuestByName(const std::string& guestName) const { // Here name is the first name
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
        room->AddActivity(*activity); // Adding activity to a room
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