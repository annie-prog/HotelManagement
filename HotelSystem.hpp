#pragma once
#include "Room.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"
#include "Accommodation.hpp"

const double PRICE_PER_NIGHT_PER_PERSON = 75.0;
class HotelSystem{
private:
    Accommodation* accommodation; // Pointer to the accommodation object
    Room* emergencyRoom; // Pointer to the emergency room
    Room** rooms; // Array of pointers to Room objects
    unsigned int roomCount;
    Reservation** reservations; // Array of pointers to Reservation objects
    unsigned int reservationCount;
    Activity** activities; // Array of pointers to Activity objects
    unsigned int activitiesCount;

    HotelSystem();
    static HotelSystem* instance; // Singleton instance

public:
    static HotelSystem* GetInstance(); // Gets the singleton instance

    ~HotelSystem();
    void AddEmergencyRoom(Room* room); 
    void AddRoom(const Room* room);  
    void AddRoom(int roomNumber, unsigned int numBeds); 
    Room* GetRoom(int roomNumber) const; // Gets a room by its room number
    Room** GetRooms() const; 
    unsigned int GetRoomCount() const; 
    void PrintRooms() const; // Prints information about all the rooms

    void Checkin(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests); // Making reservation to a room 
    bool IsRoomAvailable(const std::string& date) const; // Checks if a room is available on a given date
    void PrintAvailableRooms(const std::string& date) const; // Prints the available rooms on a given date

    void AddActivity(const std::string& name); // Adds an activity to the system
    void PrintActivities() const; // Prints information about all the activities
    void PrintActivityGuests(const std::string& activityName) const; // Prints the guests participating in a specific activity

    void AddGuest(Guest* guest); 
    void AddGuestToRoom(int roomNumber, Guest* guest); // Adds a guest to room
    void AddGuestToActivity(const std::string& activityName, Guest* guest); // Adds a guest to activity
    void PrintGuests() const; // Prints information about all the guests
    Guest** GetGuests() const; 
    unsigned int GetNumGuests() const;

    std::string GetCurrentDate() const; // Gets the current date
    void PrintRoomUsageReport(const std::string& from, const std::string& to) const; // Prints the room usage report within a specified period
    Room* FindAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const; // Finds an available room with the specified number of beds within a period
    bool FindEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to); // Finds an emergency room with the specified number of beds within a period
    void DeclareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note); // Declares a room as unavailable within a period with a note
    void AddGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest); // Adds a guest to a specific activity in a room
    void PrintRoomActivities(int roomNumber) const; // Print information about activities in a specific room
    void Checkout(int roomNumber); // Checkout clients from a room
    Guest* FindGuestByName(const std::string& guestName) const; // Finds a guest by their first name
    void AddRoomActivity(int roomNumber, Activity* activity); // Adds an activity to a specific room
};

#ifdef TEST
TEST_SUITE("HotelSystem") {
    TEST_CASE("Add Room") {
        HotelSystem* hotelSystem = HotelSystem::GetInstance();

        SUBCASE("Add room with room number and number of beds") {
            hotelSystem->AddRoom(101, 2);

            Room** rooms = hotelSystem->GetRooms();
            unsigned int roomCount = hotelSystem->GetRoomCount();

            CHECK_EQ(roomCount, 1);
            CHECK_EQ(rooms[0]->GetNumber(), 101);
            CHECK_EQ(rooms[0]->GetNumberOfBeds(), 2);
        }

        delete hotelSystem;
    }

    TEST_CASE("Add Activity") {
        Room room(101, 2);
        Activity activity1("Swimming");
        Activity activity2("Gym");

        room.AddActivity(activity1);
        room.AddActivity(activity2);

        Activity** activities = room.GetActivities();

        CHECK_EQ(activities[0]->GetName(), "Swimming");
        CHECK_EQ(activities[1]->GetName(), "Gym");
    }

}
#endif