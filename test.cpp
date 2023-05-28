#define TEST
#include "HotelSystem.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "CSVUtils.hpp"
#include "HotelApp.hpp"

/*#ifdef DOCTEST_CONFIG_IMPLEMENT
#define test doctest::Context().run()
#else
#define test
#endif*/

int main() {

/*#ifdef TEST
    test;
#else*/
    HotelApp hotelApp;
    hotelApp.run();

    return 0;

//#endif
}