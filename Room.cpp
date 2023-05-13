#include "Room.hpp"

Room::Room(int number, unsigned int numBeds) 
    :number(number), numBeds(numBeds) {}

int Room::getNumber() const{
    return this->number;
}    
unsigned int Room::getNumberOfBeds() const{
    return this->numBeds;
}
std::vector<Guest> Room::getGuests() const{
    return this->guests;
}
std::vector<Reservation> Room::getReservations() const{
    return this->reservations;
}
std::vector<Activity> Room::getActivities() const{
    return this->activities;
}
void Room::addGuest(const Guest& guest){
    guests.push_back(guest);
}
void Room::addReservation(const Reservation& reservation){
    reservations.push_back(reservation);
}
void Room::addActivity(const Activity& activity){
    activities.push_back(activity);
}