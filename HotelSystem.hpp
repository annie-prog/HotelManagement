#pragma once
#include "Room.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"
#include "Accommodation.hpp"

const double PRICE_PER_NIGHT_PER_PERSON = 75.0;
class HotelSystem{
private:
    Accommodation* accommodation;
    Room* emergencyRoom;
    Room** rooms;
    unsigned int roomCount;
    Reservation** reservations;
    unsigned int reservationCount;
    Activity** activities;
    unsigned int activitiesCount;

    HotelSystem();
    static HotelSystem* instance;

public:
    static HotelSystem* GetInstance();

    ~HotelSystem();
    void AddEmergencyRoom(Room* room); 
    void AddRoom(const Room* room);  
    void AddRoom(int roomNumber, unsigned int numBeds); 
    Room* GetRoom(int roomNumber) const; 
    Room** GetRooms() const; 
    unsigned int GetRoomCount() const; 
    void PrintRooms() const; 

    void Checkin(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests); 
    bool IsRoomAvailable(const std::string& date) const; 
    void PrintAvailableRooms(const std::string& date) const; 

    void AddActivity(const std::string& name); 
    void PrintActivities() const; 
    void PrintActivityGuests(const std::string& activityName) const; 

    void AddGuest(Guest* guest); 
    void AddGuestToRoom(int roomNumber, Guest* guest); 
    void AddGuestToActivity(const std::string& activityName, Guest* guest); 
    void PrintGuests() const; 
    Guest** GetGuests() const; 
    unsigned int GetNumGuests() const;

    std::string GetCurrentDate() const;
    void PrintRoomUsageReport(const std::string& from, const std::string& to) const;
    Room* FindAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const;
    bool FindEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to);
    void DeclareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note);
    void AddGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest);
    void PrintRoomActivities(int roomNumber) const;
    void Checkout(int roomNumber);
    Guest* FindGuestByName(const std::string& guestName) const;
    void AddRoomActivity(int roomNumber, Activity* activity);
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