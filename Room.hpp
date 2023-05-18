#pragma once
#include "Guest.hpp"
#include "Reservation.hpp"
#include "Activity.hpp"
#include "Accommodation.hpp"

class Room : public Accommodation{
protected:
    int number;   
    unsigned int numBeds;
    Guest** guests;
    unsigned int guestsCount;
    Reservation** reservations;
    unsigned int reservationsCount;
    Activity** activities;
    unsigned int activitiesCount;
public:
    Room();
    Room(int number, unsigned int numBeds);
    ~Room();
    int getNumber() const;
    unsigned int getNumberOfBeds() const;
    
    virtual Guest** getGuests() const override;
    unsigned int getGuestsCount() const;

    virtual Reservation** getReservations() const;
    unsigned int getReservationsCount() const;

    virtual Activity** getActivities() const;
    unsigned int getActivitiesCount() const;

    void addGuest(Guest* guest);
    void addReservation(Reservation* reservation);
    void cancelReservation(const std::string& checkIn, const std::string& checkOut);
    void addActivity(Activity* activity);

    bool isReservedInPeriod(const std::string& from, const std::string& to) const;
    void addGuestToActivity(const std::string& activityName, Guest* guest);
    void clearGuests();
    void clearReservation();
    void checkout();

    void printRoomUsageReport(const std::string& from, const std::string& to) const;
    int getUsageDays(const std::string& from, const std::string& to) const;
    void moveGuestsFromRoom(Room* sourceRoom);
};