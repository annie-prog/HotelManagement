#pragma once
#include "Guest.hpp"
#include "Accommodation.hpp"
#include <vector>
#include <string>

class Activity : public Accommodation{
private:
    std::string name;
    std::vector<Guest*> guests;
public:
    Activity(const std::string &name);
    ~Activity();

    const std::string getName() const;
    void setName(const std::string &name);

    virtual void addGuest(Guest* guest) override;
    virtual std::vector<Guest*> getGuests() const override;
};