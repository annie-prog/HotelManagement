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

    std::string GetName() const;
    void SetName(const std::string& name);
    Accommodation& GetAccommodation();
    void SetAccommodation(const Accommodation& accommodation);
    bool IsValidName(const std::string& name) const;
    void AddGuest(const Guest& guest);
};

#ifdef TEST
#include "doctest.h"

TEST_SUITE("Activity") {
    TEST_CASE("Get Name") {
        Activity activity("Swimming");

        CHECK_EQ(activity.GetName(), "Swimming");
    }

    TEST_CASE("Set Name") {
        Activity activity("Swimming");
        activity.SetName("Hiking");

        CHECK_EQ(activity.GetName(), "Hiking");
    }

    TEST_CASE("Valid Name") {
        Activity activity("ValidName");

        CHECK(activity.IsValidName("ValidName"));
        CHECK(activity.IsValidName("AnotherValidName"));
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
        Accommodation& accommodation = activity.GetAccommodation();

        CHECK_EQ(&accommodation, &activity.GetAccommodation());
    }
}
#endif