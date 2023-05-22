#pragma once
#include "Accommodation.hpp"
#include <string>

class Activity : public Accommodation {
private:
    std::string name;
public:
    Activity(const std::string& name);
    virtual ~Activity();

    std::string getName() const;
    void setName(const std::string& name);
};

#ifdef TEST
#include "doctest.h"

TEST_SUITE("Activity") {
    TEST_CASE("Get Name") {
        Activity activity("Swimming");

        CHECK_EQ(activity.getName(), "Swimming");
    }

    TEST_CASE("Set Name") {
        Activity activity("Swimming");
        activity.setName("Hiking");

        CHECK_EQ(activity.getName(), "Hiking");
    }

    TEST_CASE("Add Guest") {
        Activity activity("Swimming");
        Guest guest("John", "Doe", "123456789");

        activity.addGuest(&guest);

        CHECK_EQ(activity.getNumGuests(), 1);
        CHECK_EQ(activity.getGuests()[0]->getFirstName(), "John");
        CHECK_EQ(activity.getGuests()[0]->getLastName(), "Doe");
        CHECK_EQ(activity.getGuests()[0]->getPhoneNumber(), "123456789");
    }

    TEST_CASE("Get Guests") {
        Activity activity("Swimming");
        Guest guest1("John", "Doe", "123456789");
        Guest guest2("Jane", "Smith", "987654321");

        activity.addGuest(&guest1);
        activity.addGuest(&guest2);

        Guest** guests = activity.getGuests();

        CHECK_EQ(activity.getNumGuests(), 2);
        CHECK_EQ(guests[0]->getFirstName(), "John");
        CHECK_EQ(guests[0]->getLastName(), "Doe");
        CHECK_EQ(guests[0]->getPhoneNumber(), "123456789");
        CHECK_EQ(guests[1]->getFirstName(), "Jane");
        CHECK_EQ(guests[1]->getLastName(), "Smith");
        CHECK_EQ(guests[1]->getPhoneNumber(), "987654321");
    }
}
#endif