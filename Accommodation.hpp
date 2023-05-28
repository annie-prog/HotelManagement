#pragma once
#include "Guest.hpp"

class Accommodation {
private:
    Guest** guests;
    unsigned int numGuests;
public:
    Accommodation();
    ~Accommodation();
    void AddGuest(const Guest& guest);
    Guest** GetGuests() const;
    unsigned int GetNumGuests() const;
    
    void SetGuests(Guest** guests);
    void SetNumGuests(unsigned int numGuests);
    void ClearGuests();
};

#ifdef TEST
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_SUITE("Accommodation") {
    TEST_CASE("Add Guest") {
        Accommodation accommodation;
        Guest guest("Aneliya", "Konarcheva", "0746375867");

        accommodation.AddGuest(guest);

        CHECK_EQ(accommodation.GetNumGuests(), 1);
        CHECK_EQ(accommodation.GetGuests()[0]->GetFirstName(), "Aneliya");
        CHECK_EQ(accommodation.GetGuests()[0]->GetLastName(), "Konarcheva");
        CHECK_EQ(accommodation.GetGuests()[0]->GetPhoneNumber(), "0746375867");
    }

    TEST_CASE("Get Guests") {
        Accommodation accommodation;
        Guest guest1("Aneliya", "Konarcheva", "0746375867");
        Guest guest2("Blagovesta", "Hubanova", "0837485768");

        accommodation.AddGuest(guest1);
        accommodation.AddGuest(guest2);

        Guest** guests = accommodation.GetGuests();

        CHECK_EQ(accommodation.GetNumGuests(), 2);
        CHECK_EQ(guests[0]->GetFirstName(), "Aneliya");
        CHECK_EQ(guests[0]->GetLastName(), "Konarcheva");
        CHECK_EQ(guests[0]->GetPhoneNumber(), "0746375867");
        CHECK_EQ(guests[1]->GetFirstName(), "Blagovesta");
        CHECK_EQ(guests[1]->GetLastName(), "Hubanova");
        CHECK_EQ(guests[1]->GetPhoneNumber(), "0837485768");
    }
}
#endif