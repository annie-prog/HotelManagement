#include "Room.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

Room::Room() : number(0), numBeds(0), reservations(nullptr), reservationsCount(0), activities(nullptr), activitiesCount(0) {}

Room::Room(int number, unsigned int numBeds) : number(number), numBeds(numBeds), reservations(nullptr), reservationsCount(0), activities(nullptr), activitiesCount(0) {}
Room::~Room() {
    clearGuests();
    clearReservations();
}
int Room::getNumber() const {
    return this->number;
}
unsigned int Room::getNumberOfBeds() const {
    return this->numBeds;
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
void Room::addReservation(Reservation* reservation) {
    if (reservation == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < reservationsCount; i++) {
        if (reservations[i] == reservation) {
            return;
        }
    }
    Reservation** newReservations = new Reservation*[reservationsCount + 1];

    for (unsigned int i = 0; i < reservationsCount; ++i) {
        newReservations[i] = reservations[i];
    }
    newReservations[reservationsCount] = reservation;

    delete[] reservations;

    reservations = newReservations;
    ++reservationsCount;

    Guest** guests = reservation->getGuests();
    unsigned int numGuests = reservation->getNumGuests();
    for (unsigned int i = 0; i < numGuests; ++i) {
        addGuest(guests[i]);
    }
}
void Room::cancelReservation(const std::string& checkIn, const std::string& checkOut) {
    for (unsigned int i = 0; i < reservationsCount; ++i) {
        if (reservations[i] != nullptr && reservations[i]->getCheckInDate() == checkIn && reservations[i]->getCheckOutDate() == checkOut) {
            Guest** guests = reservations[i]->getGuests();
            unsigned int numGuests = reservations[i]->getNumGuests();

            for (unsigned int j = 0; j < numGuests; ++j) {
                removeGuest(guests[j]);
            }

            delete reservations[i];
            reservations[i] = nullptr;

            for (unsigned int k = i; k < reservationsCount - 1; ++k) {
                reservations[k] = reservations[k + 1];
            }

            reservations[reservationsCount - 1] = nullptr;

            reservationsCount--;

            break;
        }
    }
}
void Room::addActivity(Activity* activity) {
    if (activity == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < activitiesCount; i++) {
        if (activities[i] == activity) {
            return;
        }
    }
    Activity** newActivities = new Activity*[activitiesCount + 1];

    for (unsigned int i = 0; i < activitiesCount; ++i) {
        newActivities[i] = activities[i];
    }

    newActivities[activitiesCount] = activity;

    delete[] activities;

    activities = newActivities;
    ++activitiesCount;
}
bool Room::isReservedInPeriod(const std::string& from, const std::string& to) const {
    for (unsigned int i = 0; i < reservationsCount; i++) {
        if (reservations[i]->includesDate(from) || reservations[i]->includesDate(to)) {
            return true;
        }
    }
    return false;
}
void Room::addGuestToActivity(const std::string& activityName, Guest* guest) {
    if (guest == nullptr) {
        return;
    }

    for (unsigned int i = 0; i < activitiesCount; ++i) {
        if (activities[i]->getName() == activityName) {
            activities[i]->addGuest(guest);
            return;
        }
    }
}
void Room::clearGuests() {
    delete[] guests;
    guests = nullptr;
    numGuests = 0;
}
void Room::clearReservations() {
    for (unsigned int i = 0; i < reservationsCount; ++i) {
        Reservation* reservation = reservations[i];
        if (reservation != nullptr) {
            Guest** guests = reservation->getGuests();
            unsigned int numGuests = reservation->getNumGuests();

            for (unsigned int j = 0; j < numGuests; ++j) {
                removeGuest(guests[j]);
                delete guests[j];
            }

            delete[] guests;
            delete reservation;
            reservations[i] = nullptr;
        }
    }

    delete[] reservations;
    reservations = nullptr;
    reservationsCount = 0;
}
void Room::checkout() {
    clearGuests();
    clearReservations();
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
    std::tm tm_from = {};
    std::tm tm_to = {};
    std::istringstream iss_from(from);
    std::istringstream iss_to(to);
    iss_from >> std::get_time(&tm_from, "%Y-%m-%d");
    iss_to >> std::get_time(&tm_to, "%Y-%m-%d");
    std::time_t time_from = std::mktime(&tm_from);
    std::time_t time_to = std::mktime(&tm_to);

    if (time_from == -1 || time_to == -1) {
        return 0;
    }

    int usageDays = 0;
    for (unsigned int i = 0; i < reservationsCount; ++i) {
        std::tm reservation_tm_from = {};
        std::tm reservation_tm_to = {};
        std::istringstream res_iss_from(reservations[i]->getCheckInDate());
        std::istringstream res_iss_to(reservations[i]->getCheckOutDate());
        res_iss_from >> std::get_time(&reservation_tm_from, "%Y-%m-%d");
        res_iss_to >> std::get_time(&reservation_tm_to, "%Y-%m-%d");
        std::time_t reservation_from = std::mktime(&reservation_tm_from);
        std::time_t reservation_to = std::mktime(&reservation_tm_to);

        if (reservation_from == -1 || reservation_to == -1) {
            continue;
        }

        if (reservation_to < time_from || reservation_from > time_to) {
            continue;
        }

        std::time_t start_date = std::max(reservation_from, time_from);
        std::time_t end_date = std::min(reservation_to, time_to);

        double seconds = std::difftime(end_date, start_date);
        int days = static_cast<int>(seconds / (24 * 60 * 60));

        if (days > 0) {
            usageDays += days;
        }
    }

    return usageDays + 1;
}
void Room::moveGuestsFromRoom(Room* sourceRoom) {
    if (sourceRoom == nullptr) {
        return;
    }
    unsigned int sourceGuestsCount = sourceRoom->getNumGuests();
    Guest** sourceGuests = sourceRoom->getGuests();

    for (unsigned int i = 0; i < sourceGuestsCount; ++i) {
        addGuest(sourceGuests[i]);
    }

    sourceRoom->clearGuests();
}
bool Room::isReservedOnDate(const std::string& currentDate) const {
    for (unsigned int i = 0; i < reservationsCount; i++) {
        if (reservations[i]->includesDate(currentDate)) {
            return true;
        }
    }
    return false;
}
Guest* Room::findGuestByName(const std::string& guestFirstName) const {
    for (unsigned int i = 0; i < numGuests; ++i) {
        if (guests[i]->getFirstName() == guestFirstName) {
            return guests[i];
        }
    }
    return nullptr;
}
void Room::printActivities() const {
    std::cout << "Activities for Room " << number << ":" << std::endl;
    for (unsigned int i = 0; i < activitiesCount; ++i) {
        std::cout << "- " << activities[i]->getName() << std::endl;
    }
}
void Room::removeGuest(Guest* guest) {
    if (guests == nullptr || numGuests == 0)
        return;

    for (unsigned int i = 0; i < numGuests; i++) {
        if (guests[i] == guest) {
            delete guests[i];
            for (unsigned int j = i; j < numGuests - 1; j++) {
                guests[j] = guests[j + 1];
            }
            guests[numGuests - 1] = nullptr;
            numGuests--;
            return;
        }
    }
}
