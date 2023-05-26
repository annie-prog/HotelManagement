#pragma once
#include "Accommodation.hpp"
#include <string>

class Activity{
private:
    std::string name;
    Accommodation accommodation;
public:
    Activity(const std::string& name);
    ~Activity();

    std::string getName() const;
    void setName(const std::string& name);
    Accommodation& getAccommodation();
    void setAccommodation(const Accommodation& accommodation);
    bool isValidName(const std::string& name) const;
    void addGuest(const Guest& guest);
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

    TEST_CASE("Valid Name") {
        Activity activity("ValidName");

        CHECK(activity.isValidName("ValidName"));
        CHECK(activity.isValidName("AnotherValidName"));
    }

    TEST_CASE("Invalid Name: Empty") {
        CHECK_THROWS_AS(Activity(""), std::invalid_argument);
    }

    TEST_CASE("Invalid Name: Non-Alphabetic Characters") {
        CHECK_THROWS_AS(Activity("123"), std::invalid_argument);
        CHECK_THROWS_AS(Activity("Name1"), std::invalid_argument);
        CHECK_THROWS_AS(Activity("Invalid-Name"), std::invalid_argument);
    }

    TEST_CASE("Invalid Name: Too Long") {
        CHECK_THROWS_AS(Activity("ThisNameIsTooLongToBeValid"), std::invalid_argument);
    }

    TEST_CASE("Invalid Name: Too Short") {
        CHECK_THROWS_AS(Activity("A"), std::invalid_argument);
    }

    TEST_CASE("Get Accommodation") {
        Activity activity("Swimming");
        Accommodation& accommodation = activity.getAccommodation();

        CHECK_EQ(&accommodation, &activity.getAccommodation());
    }
}
#endif