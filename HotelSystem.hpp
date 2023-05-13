#pragma once
#include "Room.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"
#include <vector>

class HotelSystem{
private:
    std::vector<Room*> rooms;

public:
    HotelSystem();
    ~HotelSystem();

    void addRoom(const Room* room);
    Room* getRoom(int roomNumber) const;
    std::vector<Room*> getRooms() const;
    std::vector<Reservation*> getReservations() const;
    std::vector<Activity*> getActivities() const;
    void printRooms() const;
    void printAvailableRooms(const std::string &checkIn, const std::string &checkOut) const;
    void makeReservation(int roomNumber, const std::string &checkIn, const std::string &checkOut, const std::string &note, unsigned int numGuests);
    void cancelReservation(int roomNumber, const std::string &checkIn, const std::string &checkOut);
    void addActivity(const std::string &name);
    void addGuestToActivity(const std::string &activityName, const Guest* guest);
    void printActivities() const;
    void printGuests() const;

};