#pragma once
#include "Room.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"

class HotelSystem : public Room {
private:
    Room** rooms;
    unsigned int roomCount;

    HotelSystem();
    static HotelSystem* instance;
public:
    static HotelSystem* getInstance();
    HotelSystem(Room** rooms, unsigned int roomCount);
    ~HotelSystem();

    void addRoom(const Room* room);

    Room* getRoom(int roomNumber) const;
    Room** getRooms() const;
    virtual Reservation** getReservations() const override;
    virtual Activity** getActivities() const override;

    void printRooms() const;
    bool isRoomAvailable(const std::string& date) const;
    void printAvailableRooms(const std::string& date) const;
    std::string getCurrentDate() const;

    void makeReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut, const std::string& note, unsigned int numGuests);
    void cancelReservation(int roomNumber, const std::string& checkIn, const std::string& checkOut);

    void addActivity(const std::string& name);
    void addGuestToRoom(int roomNumber, Guest* guest);
    void addGuestToActivity(const std::string& activityName, Guest* guest);
    void printActivities() const;
    void printActivityGuests(const std::string& activityName) const;

    void printGuests() const;
    void printRoomUsageReport(const std::string& from, const std::string& to) const;

    Room* findAvailableRoom(unsigned int beds, const std::string& from, const std::string& to) const;
    bool findEmergencyRoom(unsigned int beds, const std::string& from, const std::string& to); //does not work properly
    
    void declareRoomUnavailable(int roomNumber, const std::string& from, const std::string& to, const std::string& note);
    void addGuestToRoomActivity(int roomNumber, const std::string& activityName, Guest* guest);

    void printRoomActivities(int roomNumber) const;
    void checkout(int roomNumber);// does not work properly

};