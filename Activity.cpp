#include "Activity.hpp"
#include <iostream>

Activity::Activity(const std::string& name) : name(name){}
Activity::~Activity() = default;
std::string Activity::getName() const {
    return this->name;
}
void Activity::setName(const std::string& name) {
    this->name = name;
}