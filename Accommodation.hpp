#pragma once
#include "Guest.hpp"

class Accommodation {
protected:
    Guest** guests;
    unsigned int numGuests;
public:
    Accommodation();
    virtual ~Accommodation();
    virtual void addGuest(Guest* guest);
    virtual Guest** getGuests() const;
    virtual unsigned int getNumGuests() const;
};

#ifdef TEST
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
TEST_SUITE("Accommodation") {
    TEST_CASE("Add Guest") {
        Accommodation accommodation;
        Guest guest("John", "Doe", "123456789");

        accommodation.addGuest(&guest);

        CHECK_EQ(accommodation.getNumGuests(), 1);
        CHECK_EQ(accommodation.getGuests()[0]->getFirstName(), "John");
        CHECK_EQ(accommodation.getGuests()[0]->getLastName(), "Doe");
        CHECK_EQ(accommodation.getGuests()[0]->getPhoneNumber(), "123456789");
    }

    TEST_CASE("Get Guests") {
        Accommodation accommodation;
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");

        accommodation.addGuest(&guest1);
        accommodation.addGuest(&guest2);

        Guest** guests = accommodation.getGuests();

        CHECK_EQ(accommodation.getNumGuests(), 2);
        CHECK_EQ(guests[0]->getFirstName(), "John");
        CHECK_EQ(guests[0]->getLastName(), "Doe");
        CHECK_EQ(guests[0]->getPhoneNumber(), "123456789");
        CHECK_EQ(guests[1]->getFirstName(), "Jane");
        CHECK_EQ(guests[1]->getLastName(), "Smith");
        CHECK_EQ(guests[1]->getPhoneNumber(), "987654321");
    }
}
#endif