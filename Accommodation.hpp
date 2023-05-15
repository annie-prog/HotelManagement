#pragma once
#include "Guest.hpp"
#include <vector>

class Accommodation{
protected:
    std::vector<Guest*> guests;
public:
    virtual ~Accommodation();
    virtual void addGuest(Guest *guest);
    virtual std::vector<Guest*> getGuests() const;
};