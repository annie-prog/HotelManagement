#define TEST
#include "HotelSystem.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "CSVUtils.hpp"

/*#ifdef DOCTEST_CONFIG_IMPLEMENT
#define test doctest::Context().run()
#else
#define test
#endif*/

int main() {

/*#ifdef TEST
    test;
#else*/

    std::string currentFile;
    bool isOpen = false;
	
    HotelSystem* hotel = HotelSystem::getInstance();

    /*Room* room1 = new Room(101, 2);
    Room* room2 = new Room(102, 2);
    Room* room3 = new Room(201, 3);

    hotel->addRoom(room1);
    hotel->addRoom(room2);
    hotel->addRoom(room3);

    Guest* guest1 = new Guest("Aneliya", "Konarcheva", "0882750588");
    Guest* guest = new Guest("Mirela", "Slavova", "0878695591");
    Guest* guest2 = new Guest("Blagovesta", "Hubanova", "0889654321");
    Guest* guest3 = new Guest("Simona", "Koleva", "0876593846");
    Guest* guest4 = new Guest("Stefania", "Dimitrova", "0897234567");
    Guest* guest5 = new Guest("Chocho", "Vladovski", "0897639574");
    Guest* guest6 = new Guest("Fani", "Manahova", "0876395827");

    hotel->addGuestToRoom(101, guest1);
    hotel->addGuestToRoom(101, guest2);
    hotel->addGuestToRoom(102, guest6);
    hotel->addGuestToRoom(102, guest3);
    hotel->addGuestToRoom(201, guest4);
    hotel->addGuestToRoom(201, guest5);
    std::cout << std::endl;*/
    
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    std::cout << "Welcome to hotel 'Amelia Resort'! " << std::endl;
    std::cout << "Type 'help' for a list of supported commands." << std::endl;
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;

    while (true) {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> std::quoted(token)) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }

        std::string command = tokens[0];

        if (command == "open") {
            if (isOpen) {
                std::cout << "A file is already open. Close it before opening another file." << std::endl;
                continue;
            }
            
            if (tokens.size() < 2) {
                std::cout << "Please provide a file path to open." << std::endl;
                continue;
            }

            std::string filePath = tokens[1];
            std::ifstream file(filePath);
            if (!file) {
                std::cout << "File not found. Creating a new file." << std::endl;
            } 
            else {
                std::cout << "Successfully opened " << filePath << std::endl;
                std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                file.close();

                isOpen = true;
                currentFile = filePath;
            }
        } 
        else if (command == "close") {
            if (!isOpen) {
                std::cout << "No file is currently open." << std::endl;
                continue;
            }
            std::cout << "Successfully closed " << currentFile << std::endl;
            isOpen = false;
            currentFile = "";
        } 
        else if (command == "save") {
            if (!isOpen) {
                std::cout << "No file is currently open." << std::endl;
                continue;
            }
            std::cout << "Successfully saved " << currentFile << std::endl;
        } 
        else if (command == "saveas") {
            if (!isOpen) {
                std::cout << "No file is currently open." << std::endl;
                continue;
            }
            if (tokens.size() < 2) {
                std::cout << "Please provide a file path to save as." << std::endl;
                continue;
            }
            std::string newFilePath = tokens[1];
            std::cout << "Successfully saved as " << newFilePath << std::endl;
        } 
        else if (command == "help") {
            std::cout << "The following commands are supported:" << std::endl;
            std::cout << "open <file>                                                                 opens <file>" << std::endl;
            std::cout << "close                                                                       closes currently opened file" << std::endl;
            std::cout << "save                                                                        saves the currently open file" << std::endl;
            std::cout << "saveas <file>                                                               saves the currently open file in <file>" << std::endl;
            std::cout << "checkin <room number> <start date> <end date> <note> <numberGuests>         checks in guests to the room" << std::endl;
            std::cout << "checkout <room number>                                                      checks out guests from the room" << std::endl;
            std::cout << "availability <date>                                                              prints all available rooms for a date" << std::endl;
            std::cout << "report <from> <to>                                                          prints room usage report for the specified period" << std::endl;
            std::cout << "find <beds> <from> <to>                                                     finds an available room" << std::endl;
            std::cout << "find! <beds> <from> <to>                                                    finds an emergency available room" << std::endl;
            std::cout << "unavailable <room> <from> <to> <note>                                       declares a room as unavailable" << std::endl;
            std::cout << "printRoomActivities <room number>                                           prints activities for the specified room" << std::endl;
            std::cout << "printActivityGuests <activity name>                                         prints guests for the specified activity" << std::endl;
            std::cout << "printrooms                                                                  prints all rooms and their details" << std::endl;
            std::cout << "addroom <room number> <num beds>                                            adds a room with the specified number of beds" << std::endl;
            std::cout << "addactivity <activity name>                                                 adds a new activity" << std::endl;
            std::cout << "addguesttoactivity <activity name> <first name> <last name> <phone number>  adds a guest to the specified activity" << std::endl;
            std::cout << "addguest <first name> <last name> <phone number>                            adds a guest to the hotel" << std::endl;
            std::cout << "printActivities                                                             prints all activities" << std::endl;
            std::cout << "printguests                                                                 prints all guests in the hotel" << std::endl;
            std::cout << "exit                                                                        exits the program" << std::endl;
        }
        else if (command == "checkin") {
            if (tokens.size() < 4) {
                std::cout << "Invalid command. Please provide room number, check-in date, check-out date, and note." << std::endl;
                continue;
            }
            int roomNumber = std::stoi(tokens[1]);
            std::string checkIn = tokens[2];
            std::string checkOut = tokens[3];
            std::string note;
            if (tokens.size() > 4) {
                note = tokens[4];
            }

            unsigned int numGuests = 0;
            if (tokens.size() > 5) {
                numGuests = std::stoi(tokens[5]);
            }
            hotel->checkin(roomNumber, checkIn, checkOut, note, numGuests);

            std::string filename = "reservations.csv";
            std::vector<std::vector<std::string>> previousReservations = CSVUtils::readReservationsFromCSV(filename);
            previousReservations.push_back({ std::to_string(roomNumber), checkIn, checkOut, note, std::to_string(numGuests) });
            
            CSVUtils::saveReservationsToCSV(previousReservations, filename);
            std::cout << "Reservations have been saved to " << filename << std::endl;
        }
        else if (command == "availability") {
            std::string date = tokens.size() > 1 ? tokens[1] : "";
            hotel->printAvailableRooms(date);
        }
        else if (command == "checkout") {
            if (tokens.size() < 2) {
                std::cout << "Invalid command. Please provide a room number for checkout." << std::endl;
                continue;
            }
            int roomNumber = std::stoi(tokens[1]);
            hotel->checkout(roomNumber);

            std::vector<std::vector<std::string>> reservationsData = CSVUtils::readReservationsFromCSV("reservations.csv");

            for (auto it = reservationsData.begin(); it != reservationsData.end(); ++it) {
                if ((*it)[0] == std::to_string(roomNumber)) {
                    reservationsData.erase(it);
                    break;
                }
            }

            std::string filename = "reservations.csv";
            CSVUtils::saveReservationsToCSV(reservationsData, filename);
            std::cout << "Reservation for room " << roomNumber << " has been removed from " << filename << std::endl;
        }
        else if (command == "addroomactivity") {
            if (tokens.size() < 2) {
                std::cout << "Invalid command. Please provide a room number and an activity." << std::endl;
                continue;
            }
            int roomNumber = std::stoi(tokens[1]);
            std::string activityName = tokens[2];

            Activity* activity = new Activity(activityName);

            hotel->addRoomActivity(roomNumber, activity);
        }
        else if (command == "report") {
            if (tokens.size() < 3) {
                std::cout << "Invalid command. Please provide 'from' and 'to' dates." << std::endl;
                continue;
            }
            std::string from = tokens[1];
            std::string to = tokens[2];
            hotel->printRoomUsageReport(from, to);
        }
        else if (command == "find") {
            if (tokens.size() < 4) {
                std::cout << "Invalid command. Please provide the number of beds, start date, and end date." << std::endl;
                continue;
            }
            unsigned int beds = std::stoi(tokens[1]);
            std::string from = tokens[2];
            std::string to = tokens[3];

            Room* availableRoom = hotel->findAvailableRoom(beds, from, to);
            if (availableRoom != nullptr) {
                std::cout << "Found available room: Room " << availableRoom->getNumber() << std::endl;
            } 
            else {
                std::cout << "No available room found." << std::endl;
            }
        }
        else if (command == "find!") {
            if (tokens.size() < 4) {
                std::cout << "Invalid command. Please provide the number of beds, start date, and end date." << std::endl;
                continue;
            }
            unsigned int beds = std::stoi(tokens[1]);
            std::string from = tokens[2];
            std::string to = tokens[3];

            bool success = hotel->findEmergencyRoom(beds, from, to);
            if (success) {
                std::cout << "Found an available room for emergency: Room " << beds << " beds" << std::endl;
            } 
            else {
                std::cout << "No available room found for emergency." << std::endl;
            }
        }
        else if (command == "unavailable") {
            if (tokens.size() < 4) {
                std::cout << "Invalid command. Please provide room number, from date, to date, and note." << std::endl;
                continue;
            }
            int roomNumber = std::stoi(tokens[1]);
            std::string from = tokens[2];
            std::string to = tokens[3];
            std::string note;
            if (tokens.size() > 4) {
                note = tokens[4];
            }
            hotel->declareRoomUnavailable(roomNumber, from, to, note);
        }
        else if (command == "printRoomActivities") {
            if (tokens.size() < 2) {
                std::cout << "Invalid command. Please provide a room number." << std::endl;
                continue;
            }
            int roomNumber = std::stoi(tokens[1]);
            hotel->printRoomActivities(roomNumber);
        }
        else if (command == "printActivityGuests") {
            if (tokens.size() < 2) {
                std::cout << "Invalid command. Please provide an activity name." << std::endl;
                continue;
            }
            std::string activityName = tokens[1];
            hotel->printActivityGuests(activityName);
        }
        else if (command == "addroom") {
            if (tokens.size() < 3) {
                std::cout << "Invalid command. Please provide room number and number of beds." << std::endl;
                continue;
            }
            int roomNumber = std::stoi(tokens[1]);
            int numBeds = std::stoi(tokens[2]);
            Room* room = new Room(roomNumber, numBeds);
            hotel->addRoom(room);

            std::vector<std::vector<std::string>> roomData;
            roomData.push_back({std::to_string(roomNumber), std::to_string(numBeds)});

            std::string filename = "rooms.csv";

            std::vector<std::vector<std::string>> existingRoomData = CSVUtils::readCSVFile(filename);

            existingRoomData.insert(existingRoomData.end(), roomData.begin(), roomData.end());
            CSVUtils::createCSVFile(filename, existingRoomData);
            std::cout << "Room " << roomNumber << " with " << numBeds << " beds has been added." << std::endl;
        }
        else if (command == "addemergencyroom") {
            if (tokens.size() < 3) {
                std::cout << "Invalid command. Please provide room number and number of beds." << std::endl;
                continue;
            }
            int roomNumber = std::stoi(tokens[1]);
            int numBeds = std::stoi(tokens[2]);
            Room* room = new Room(roomNumber, numBeds);
            hotel->addEmergencyRoom(room);
        }
        else if (command == "getcurrentdate") {
            std::string currentDate = hotel->getCurrentDate();
            std::cout << "Current date is: " << currentDate << std::endl;
        }
        else if (command == "addactivity") {
            if (tokens.size() < 2) {
                std::cout << "Invalid command. Please provide an activity name." << std::endl;
                continue;
            }
            std::string activityName = tokens[1];
            hotel->addActivity(activityName);

            std::string filename = "activities.csv";
            std::vector<std::string> previousActivities = CSVUtils::readActivitiesFromCSV(filename);
            previousActivities.push_back({ activityName });

            CSVUtils::saveActivitiesToCSV(previousActivities, filename);
            std::cout << "Activity " << activityName << " has been added." << std::endl;
        }
        else if (command == "addguesttoactivity") {
            if (tokens.size() < 3) {
                std::cout << "Invalid command. Please provide an activity name and guest details." << std::endl;
                continue;
            }
            std::string activityName = tokens[1];
            std::string guestName = tokens[2]; 
            
            Guest* guest = hotel->findGuestByName(guestName);

            if (guest == nullptr) {
                std::cout << "Guest not found. Please make sure the guest is registered in the hotel." << std::endl;
                continue;
            }
            
            hotel->addGuestToActivity(activityName, guest);
        }
        else if (command == "addguest") {
            try {
                if (tokens.size() < 4) {
                    std::cout << "Invalid command. Please provide guest's first name, last name, and phone number." << std::endl;
                    continue;
                }
                std::string firstName = tokens[1];
                std::string lastName = tokens[2];
                std::string phoneNumber = tokens[3];
                Guest* guest = new Guest(firstName, lastName, phoneNumber);
                hotel->addGuest(guest);

                std::string filename = "guests.csv";

                std::vector<std::vector<std::string>> previousGuests = CSVUtils::readGuestsFromCSV(filename);
                previousGuests.push_back({ firstName, lastName, phoneNumber });

                CSVUtils::saveGuestsToCSV(previousGuests, filename);

                std::cout << "Guest " << firstName << " " << lastName << " has been added and saved to " << filename << std::endl;
            } 
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                CSVUtils::clearCSVFiles();
                return 0;
            }         
        }
        else if (command == "printguests") {
            if (!isOpen) {
                std::cout << "No file is currently open." << std::endl;
                continue;
            }
            std::string filename = "guests.csv";
            std::vector<std::vector<std::string>> guestsData = CSVUtils::readGuestsFromCSV(filename);
            if (guestsData.empty()) {
                std::cout << "No guest data found." << std::endl;
                continue;
            }

            //std::cout << "Guests:" << std::endl;
            //CSVUtils::printGuests(guestsData);
            hotel->printGuests();
        }
        else if (command == "printrooms") {
            if (!isOpen) {
                std::cout << "Error: No hotel is currently open." << std::endl;
                continue;
            }

            std::string filename = "rooms.csv";
            std::vector<std::vector<std::string>> roomData = CSVUtils::readCSVFile(filename);

            if (roomData.empty()) {
                std::cout << "No room data found." << std::endl;
                continue;
            }
            std::cout << "Rooms in the hotel:" << std::endl;

            //CSVUtils::printCSVData(roomData);
            hotel->printRooms();
        }
        else if (command == "printActivityGuests") {
            if (tokens.size() < 2) {
                std::cout << "Invalid command. Please provide an activity name." << std::endl;
                continue;
            }

            std::string activityName = tokens[1];
            hotel->printActivityGuests(activityName);
        }
        else if (command == "printActivities") {
            if (!isOpen) {
                std::cout << "No file is currently open." << std::endl;
                continue;
            }
            std::string filename = "activities.csv";
            std::vector<std::string> activityData = CSVUtils::readActivitiesFromCSV(filename);

            if (activityData.empty()) {
                std::cout << "No room data found." << std::endl;
                continue;
            }

            hotel->printActivities();
        }
        else if (command == "exit") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            CSVUtils::clearCSVFiles();
            break;
        } 
        else {
            std::cout << "Invalid command. Type 'help' for a list of supported commands." << std::endl;
        }
    }

    /*delete[] guest1;
    delete[] guest2;
    delete[] guest3;
    delete[] guest4;
    delete[] guest5;
    delete[] guest6;
    delete[] room1;
    delete[] room2;
    delete[] room3;*/
    delete[] hotel;

    std::cout << "Exiting the program..." << std::endl;

    return 0;

    /*std::vector<std::vector<std::string>> guests = {
        {"Antonio", "Petrov", "0882748573"},
        {"Ekaterina", "Dimova", "0987264758"},
        {"Katerina", "Vassileva", "0876384756"}
    };

    std::string filename = "test.csv";

    saveGuestsToCSV(guests, filename);*/

    /*std::string filename = "test.csv";
    std::vector<std::vector<std::string>> guests = readGuestsFromCSV(filename);

    printGuests(guests);

    return 0;*/
    /*Accommodation accommodation;

    accommodation.addGuest(Guest("Aneliya", "Konarcheva", "0882750588"));
    accommodation.addGuest(Guest("Mirela", "Slavova", "0878695591"));
    accommodation.addGuest(Guest("Blagovesta", "Hubanova", "0889654321"));
    accommodation.addGuest(Guest("Simona", "Koleva", "0876593846"));
    accommodation.addGuest(Guest("Stefania", "Dimitrova", "0897234567"));
    accommodation.addGuest(Guest("Chocho", "Vladovski", "0897639574"));
    accommodation.addGuest(Guest("Fani", "Manahova", "0876395827"));

    std::string filename = "accommodations.csv";
    saveGuestsToCSV(accommodation, filename);
    std::cout << accommodation.getNumGuests() << std::endl;

    return 0;*/

    /*std::string filename = "accommodations.csv";
    std::vector<std::vector<std::string>> guests = readGuestsFromCSV(filename);

    printGuests(guests);

    return 0;*/

    /*std::vector<std::string> activities = {
        "Swimming",
        "Gym",
        "Jaccuzzi",
        "Tennis",
        "Football",
        "Volleyball",
        "Massage"
    };

    std::string filename = "activities.csv";

    saveActivitiesToCSV(activities, filename);

    return 0;*/

    /*std::string filename = "activities.csv";

    std::vector<std::string> activities = readActivitiesFromCSV(filename);

    if (activities.empty()) {
        std::cout << "Error wth opening the file " << filename << std::endl;
        return 0;
    }
    for (const auto& activity : activities) {
        std::cout << activity << " ";
    }

    return 0;*/

    /*std::vector<std::vector<std::string>> reservations = {
        {"101", "2023-06-13", "2023-06-15", "Reservation 1", "2"},
        {"102", "2023-06-14", "2023-06-16", "Reservation 2", "2"},
        {"201", "2023-06-15", "2023-06-19", "Reservation 3", "3"}
    };

    std::string filename = "reservations.csv";

    saveReservationsToCSV(reservations, filename);

    return 0;*/

    /*std::string filename = "reservations.csv";
    std::vector<std::vector<std::string>> reservations = readReservationsFromCSV(filename);

    if (!reservations.empty()) {
        printReservations(reservations);
    }

    return 0;*/

    /*std::string filename = "rooms.csv";
    std::vector<std::vector<std::string>> data = {
        {"101", "2"},
        {"102", "2"},
        {"201", "3"},
        {"202", "3"}
    };

    createCSVFile(filename, data);

    return 0;*/

    /*std::string filename = "rooms.csv";

    std::vector<std::vector<std::string>> data = readCSVFile(filename);

    if (data.empty()) {
        return 1;
    }

    printCSVData(data);

    return 0;*/

//#endif
}