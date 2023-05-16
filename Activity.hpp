#pragma once
#include "Guest.hpp"
#include "Accommodation.hpp"
#include <vector>
#include <string>

class Activity : public Accommodation{
private:
    std::string name;
    Guest** guests;
    unsigned int guestsCount;
public:
    Activity(const std::string &name);
    ~Activity();

    const std::string getName() const;
    void setName(const std::string &name);

    virtual void addGuest(Guest* guest) override;
    virtual Guest** getGuests() const override;
};