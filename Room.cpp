#include "Room.hpp"
#include <iostream>

Room::Room() : number(0), numBeds(0), guests(nullptr), 
    guestsCount(0), reservations(nullptr), reservationsCount(0), activities(nullptr), activitiesCount(0) {}

Room::Room(int number, unsigned int numBeds) : number(number), numBeds(numBeds), guestsCount(0), reservationsCount(0), activitiesCount(0) {
    this->guests = new Guest*[numBeds];
    reservations = new Reservation*[numBeds];
    activities = new Activity*[numBeds];
}
Room::~Room() {
    if (this->guests != nullptr) {
        for (unsigned int i = 0; i < this->guestsCount; i++) {
            delete this->guests[i];
        }
        delete[] this->guests;
    }
    if (this->reservations != nullptr) {
        for (unsigned int i = 0; i < this->reservationsCount; i++) {
            delete this->reservations[i];
        }
        delete[] this->reservations;
    }
    if (this->activities != nullptr) {
        for (unsigned int i = 0; i < this->activitiesCount; i++) {
            delete this->activities[i];
        }
        delete[] this->activities;
    }
}
int Room::getNumber() const {
    return this->number;
}
unsigned int Room::getNumberOfBeds() const {
    return this->numBeds;
}
Guest** Room::getGuests() const {
    return this->guests;
}
unsigned int Room::getGuestsCount() const{
    return this->guestsCount;
}
Reservation** Room::getReservations() const {
    return this->reservations;
}
unsigned int Room::getReservationsCount() const{
    return this->reservationsCount;
}
Activity** Room::getActivities() const {
    return this->activities;
}
unsigned int Room::getActivitiesCount() const{
    return this->activitiesCount;
}
void Room::addGuest(Guest* guest) {
    this->guests[guestsCount++] = guest;
}
void Room::addReservation(Reservation* reservation) {
    this->reservations[reservationsCount++] = reservation;
}
void Room::cancelReservation(const std::string& checkIn, const std::string& checkOut) {
    for (unsigned int i = 0; i < this->reservationsCount; i++) {
        if (this->reservations[i]->getCheckInDate() == checkIn && this->reservations[i]->getCheckOutDate() == checkOut) {
            delete this->reservations[i];

            this->reservations[i] = this->reservations[reservationsCount - 1];
            this->reservations[reservationsCount - 1] = nullptr;
            this->reservationsCount--;
            std::cout << "Reservation canceled successfully." << std::endl;
            return;
        }
    }
    std::cout << "Reservation not found." << std::endl;
}
void Room::addActivity(Activity* activity) {
    this->activities[activitiesCount++] = activity;
}
bool Room::isReservedInPeriod(const std::string& from, const std::string& to) const {
    for (unsigned int i = 0; i < this->reservationsCount; i++) {
        Reservation* reservation = this->reservations[i];
        if (reservation->getCheckInDate() <= to && reservation->getCheckOutDate() >= from) {
            return true;
        }
    }
    return false;
}
void Room::addGuestToActivity(const std::string& activityName, Guest* guest) {
    for (unsigned int i = 0; i < this->activitiesCount; i++) {
        Activity* activity = activities[i];
        if (activity->getName() == activityName) {
            activity->addGuest(guest);
            std::cout << "Guest " << guest->getFirstName() << " " << guest->getLastName()
                      << " added to activity " << activityName << " in room " << number << "." << std::endl;
            return;
        }
    }
    std::cout << "Activity not found." << std::endl;
}
void Room::clearGuests() {
    for (unsigned int i = 0; i < guestsCount; i++) {
        delete guests[i];
    }
    guestsCount = 0;
}
void Room::printRoomUsageReport(const std::string& from, const std::string& to) const {
    std::cout << "Room " << number << " usage report:" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    for (unsigned int i = 0; i < reservationsCount; i++) {
        Reservation* reservation = reservations[i];
        const std::string& startDate = reservation->getCheckInDate();
        const std::string& endDate = reservation->getCheckOutDate();

        if (startDate <= to && endDate >= from) {
            std::string reservationFrom = (startDate >= from) ? startDate : from;
            std::string reservationTo = (endDate <= to) ? endDate : to;

            std::cout << "Reservation: " << reservationFrom << " - " << reservationTo << std::endl;
        }
    }
    std::cout << "-------------------------------------" << std::endl;
}