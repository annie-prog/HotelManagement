#pragma once
#include "Guest.hpp"
#include <vector>
#include <string>

class Activity{
    private:
    std::string name;
    std::vector<Guest*> guests;

    public:
    Activity(const std::string &name);
    ~Activity();

    const std::string getName() const;
    void setName(const std::string &name);

    void addGuest(const Guest* guest);
    std::vector<Guest*> getGuests() const;

};