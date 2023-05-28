#include "Room.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

Room::Room() : number(0), numBeds(0), reservations(new Reservation*[100]), reservationsCount(0), activities(new Activity*[100]), activitiesCount(0), accommodations(new Accommodation*[100]), accommodationsCount(0), guests(new Guest*[100]), guestsCount(0) {}

Room::Room(int number, unsigned int numBeds) : number(number), numBeds(numBeds), reservations(new Reservation*[100]), reservationsCount(0), activities(new Activity*[100]), activitiesCount(0), accommodations(new Accommodation*[100]), accommodationsCount(0), guests(new Guest*[100]), guestsCount(0) {
    if (number < -1000 || number > 1000) {
        throw std::invalid_argument("Room number is out of range. Room number must be between -1000 and 1000.");
    }
    if (numBeds > 4) {
        throw std::invalid_argument("Number of beds exceeds the maximum limit of 4.");
    }
}
Room::~Room() {
    ClearReservations();
    ClearGuests();
}
int Room::GetNumber() const {
    return this->number;
}
unsigned int Room::GetNumberOfBeds() const {
    return this->numBeds;
}
Reservation** Room::GetReservations() const {
    return this->reservations;
}
unsigned int Room::GetReservationsCount() const{
    return this->reservationsCount;
}
Guest** Room::GetGuests() const {
    return this->guests;
}
unsigned int Room::GetGuestsCount() const{
    return this->guestsCount;
}
Activity** Room::GetActivities() const {
    return this->activities;
}
unsigned int Room::GetActivitiesCount() const{
    return this->activitiesCount;
}
Accommodation** Room::GetAccommodations() const {
    return this->accommodations;
}
unsigned int Room::GetAccommodationsCount() const {
    return this->accommodationsCount;
}
void Room::AddReservation(const Reservation& reservation) {
    if (reservationsCount < 100) {
        reservations[reservationsCount] = new Reservation(reservation);
        reservationsCount++;
    } 
    else {
        std::cout << "Cannot add reservation. Maximum number of reservations reached." << std::endl;
    }
}
void Room::AddActivity(const Activity& activity) {
    if (activitiesCount < 100) {
        activities[activitiesCount] = new Activity(activity);
        activitiesCount++;
    } 
    else {
        std::cout << "Cannot add activity. Maximum number of activities reached." << std::endl;
    }
}
void Room::AddGuest(const Guest& guest) {
    if (guestsCount < this->numBeds) {
        guests[guestsCount] = new Guest(guest);
        guestsCount++;
    } 
    else {
        std::cout << "Cannot add guest. Maximum number of guests in a room reached." << std::endl;
    }
}
bool Room::IsReservedInPeriod(const std::string& from, const std::string& to) const {
    for (unsigned int i = 0; i < reservationsCount; i++) {
        Reservation* reservation = reservations[i];
        if (reservation->IncludesDate(from) || reservation->IncludesDate(to)) {
            return true;
        }
    }
    return false;
}
void Room::AddGuestToActivity(const std::string& activityName, Guest* guest) {
    for (unsigned int i = 0; i < this->activitiesCount; i++) {
        Activity* activity = activities[i];
        if (activity->GetName() == activityName) {
            activity->AddGuest(*guest);
            std::cout << "Guest " << guest->GetFirstName() << " " << guest->GetLastName()
                      << " added to activity " << activityName << " in room " << number << "." << std::endl;
            return;
        }
    }
    std::cout << "Activity not found." << std::endl;
}
void Room::ClearGuests() {
    for (unsigned int i = 0; i < activitiesCount; i++) {
        Activity* activity = activities[i];
        Accommodation& accommodation = activity->GetAccommodation();
        accommodation.ClearGuests();
    }
    guestsCount = 0;
}
void Room::ClearReservations() {
    for (unsigned int i = 0; i < reservationsCount; i++) {
        delete reservations[i];
    }
    reservationsCount = 0;
}
void Room::Checkout() {
    ClearGuests();
    ClearReservations();
}
void Room::PrintRoomUsageReport(const std::string& from, const std::string& to) const {
    std::cout << "Room " << number << " usage report:" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    int usageDays = GetUsageDays(from, to);

    std::cout << "Usage days: " << usageDays << std::endl;

    if (usageDays > 0) {
        std::cout << "Reservations within the specified period:" << std::endl;
        for (unsigned int i = 0; i < reservationsCount; i++) {
            Reservation* reservation = reservations[i];
            const std::string& startDate = reservation->GetCheckInDate();
            const std::string& endDate = reservation->GetCheckOutDate();

            if (startDate <= to && endDate >= from) {
                std::string reservationFrom = (startDate >= from) ? startDate : from;
                std::string reservationTo = (endDate <= to) ? endDate : to;

                std::cout << "Reservation: " << reservationFrom << " - " << reservationTo << std::endl;
            }
        }
    }

    std::cout << "-------------------------------------" << std::endl;
}
int Room::GetUsageDays(const std::string& from, const std::string& to) const {
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
        std::istringstream res_iss_from(reservations[i]->GetCheckInDate());
        std::istringstream res_iss_to(reservations[i]->GetCheckOutDate());
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
void Room::MoveGuestsFromRoom(Room* sourceRoom) {
    if (sourceRoom->GetActivitiesCount() == 0) {
        std::cout << "Source room has no activities." << std::endl;
        return;
    }

    Activity** sourceActivities = sourceRoom->GetActivities();
    unsigned int sourceActivitiesCount = sourceRoom->GetActivitiesCount();

    for (unsigned int i = 0; i < sourceActivitiesCount; i++) {
        Activity* activity = sourceActivities[i];
        Guest** guests = activity->GetAccommodation().GetGuests();
        unsigned int numGuests = activity->GetAccommodation().GetNumGuests();

        for (unsigned int j = 0; j < numGuests; j++) {
            AddGuestToActivity(activity->GetName(), guests[j]);
        }
    }

    sourceRoom->ClearGuests();
    std::cout << "Guests moved successfully." << std::endl;
}
bool Room::IsReservedOnDate(const std::string& currentDate) const {
    for (unsigned int i = 0; i < reservationsCount; i++) {
        if (reservations[i]->IncludesDate(currentDate)) {
            return true;
        }
    }
    return false;
}
Guest* Room::FindGuestByName(const std::string& guestName) const {
    for (unsigned int i = 0; i < guestsCount; i++) {
        Guest* guest = guests[i];
        if (guest->GetFirstName() == guestName) {
            return guest;
        }
    }
    return nullptr;
}
void Room::PrintActivities() const {
    std::cout << "Activities for Room " << number << ":" << std::endl;
    if (activitiesCount == 0) {
        std::cout << "No activities found." << std::endl;
    } 
    else {
        for (unsigned int i = 0; i < activitiesCount; ++i) {
            std::cout << "- " << activities[i]->GetName() << std::endl;
        }
    }
}