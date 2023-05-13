#pragma once
#include "Guest.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"
#include <vector>

class Room{
private:
    int number;   
    unsigned int numBeds;
    std::vector<Guest> guests;
    std::vector<Reservation> reservations;
    std::vector<Activity> activities;

public:
    Room(int number, unsigned int numBeds);
    int getNumber() const;
    unsigned int getNumberOfBeds() const;
    std::vector<Guest> getGuests() const;
    std::vector<Reservation> getReservations() const;
    std::vector<Activity> getActivities() const;
    void addGuest(const Guest& guest);
    void addReservation(const Reservation& reservation);
    void addActivity(const Activity& activity);
    
};