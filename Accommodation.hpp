#pragma once
#include "Guest.hpp"

class Accommodation {
private:
    Guest** guests;
    unsigned int numGuests;
public:
    Accommodation();
    ~Accommodation();
    void addGuest(const Guest& guest);
    Guest** getGuests() const;
    unsigned int getNumGuests() const;
    
    void setGuests(Guest** guests);
    void setNumGuests(unsigned int numGuests);
    void clearGuests();
};

#ifdef TEST
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_SUITE("Accommodation") {
    TEST_CASE("Add Guest") {
        Accommodation accommodation;
        Guest guest("John", "Doe", "12345678932");

        accommodation.addGuest(guest);

        CHECK_EQ(accommodation.getNumGuests(), 1);
        CHECK_EQ(accommodation.getGuests()[0]->getFirstName(), "John");
        CHECK_EQ(accommodation.getGuests()[0]->getLastName(), "Doe");
        CHECK_EQ(accommodation.getGuests()[0]->getPhoneNumber(), "12345678932");
    }

    TEST_CASE("Get Guests") {
        Accommodation accommodation;
        Guest guest1("John", "Doe", "12345678932");
        Guest guest2("Jane", "Smith", "98765432143");

        accommodation.addGuest(guest1);
        accommodation.addGuest(guest2);

        Guest** guests = accommodation.getGuests();

        CHECK_EQ(accommodation.getNumGuests(), 2);
        CHECK_EQ(guests[0]->getFirstName(), "John");
        CHECK_EQ(guests[0]->getLastName(), "Doe");
        CHECK_EQ(guests[0]->getPhoneNumber(), "12345678932");
        CHECK_EQ(guests[1]->getFirstName(), "Jane");
        CHECK_EQ(guests[1]->getLastName(), "Smith");
        CHECK_EQ(guests[1]->getPhoneNumber(), "98765432143");
    }
}
#endif