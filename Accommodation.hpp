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