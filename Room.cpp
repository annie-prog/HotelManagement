#include "Room.hpp"
#include <iostream>
#include <ctime>

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
    delete[] guests;
    guests = nullptr;
    guestsCount = 0;
}

void Room::clearReservation() {
    if (reservationsCount > 0) {
        for (unsigned int i = 0; i < reservationsCount; i++) {
            delete reservations[i];
        }
        delete[] reservations;
        reservations = nullptr;
        reservationsCount = 0;
    }
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
int Room::getUsageDays(const std::string& from, const std::string& to) const {
    int usageDays = 0;
    for (int i = 0; i < this->reservationsCount; i++) {
        Reservation* reservation = this->reservations[i];
        if (reservation->getCheckInDate() <= to && reservation->getCheckOutDate() >= from) {
            std::string reservationStartDate = (reservation->getCheckInDate() > from) ? reservation->getCheckInDate() : from;
            std::string reservationEndDate = (reservation->getCheckOutDate() < to) ? reservation->getCheckOutDate() : to;

            int startYear = std::stoi(reservationStartDate.substr(0, 4));
            int startMonth = std::stoi(reservationStartDate.substr(5, 2));
            int startDay = std::stoi(reservationStartDate.substr(8, 2));

            int endYear = std::stoi(reservationEndDate.substr(0, 4));
            int endMonth = std::stoi(reservationEndDate.substr(5, 2));
            int endDay = std::stoi(reservationEndDate.substr(8, 2));

            std::tm startTm = {0};
            startTm.tm_year = startYear - 1900; 
            startTm.tm_mon = startMonth - 1;    
            startTm.tm_mday = startDay;        

            std::tm endTm = {0};
            endTm.tm_year = endYear - 1900; 
            endTm.tm_mon = endMonth - 1;   
            endTm.tm_mday = endDay;         

            std::time_t startTime = std::mktime(&startTm);
            std::time_t endTime = std::mktime(&endTm);

            std::time_t difference = endTime - startTime;

            int differenceDays = difference / (60 * 60 * 24);

            usageDays += differenceDays;
        }
    }
    return usageDays + 1;
}
void Room::moveGuestsFromRoom(Room* sourceRoom) {
    for (unsigned int i = 0; i < sourceRoom->guestsCount; i++) {
        this->addGuest(sourceRoom->guests[i]);
    }

    sourceRoom->clearGuests();
}
void Room::checkout() {
    if (this->guestsCount == 0) {
        std::cout << "No guests in the room." << std::endl;
        return;
    }

    for (unsigned int i = 0; i < this->guestsCount; i++) {
        delete this->guests[i];
    }
    delete[] this->guests;
    this->guests = nullptr;
    this->guestsCount = 0;

    this->guests = new Guest*[this->guestsCount];

    std::cout << "Room checked out successfully." << std::endl;
}














