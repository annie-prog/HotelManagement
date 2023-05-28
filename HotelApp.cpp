#include "HotelApp.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "CSVUtils.hpp"
#include <algorithm>

HotelApp::HotelApp() {
    hotel = HotelSystem::getInstance();
}
void HotelApp::run() {
    printWelcomeMessage();

    while (true) {
        std::string input = getUserInput();
        processCommand(input);
    }
}
void HotelApp::printWelcomeMessage() {
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    std::cout << "Welcome to hotel 'Amelia Resort'! " << std::endl;
    std::cout << "Type 'help' for a list of supported commands." << std::endl;
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
}
std::string HotelApp::getUserInput() {
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    return input;
}
void HotelApp::processOpenCommand(const std::vector<std::string>& tokens) {
    if (isOpen) {
        std::cout << "A file is already open. Close it before opening another file." << std::endl;
        return;
    } 
    if (tokens.size() < 2) {
        std::cout << "Please provide a file path to open." << std::endl;
        return;
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
void HotelApp::processCloseCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::cout << "Successfully closed " << currentFile << std::endl;
    isOpen = false;
    currentFile = "";
}
void HotelApp::processSaveCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::cout << "Successfully saved " << currentFile << std::endl;
}
void HotelApp::processSaveAsCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    if (tokens.size() < 2) {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string newFilePath = tokens[1];

    std::ifstream current(currentFile);
    std::string fileContent((std::istreambuf_iterator<char>(current)), std::istreambuf_iterator<char>());
    current.close();

    std::ofstream newFile(newFilePath);
    if (!newFile) {
        std::cout << "Error creating the new file." << std::endl;
        return;
    }
    newFile << fileContent;
    newFile.close();

    std::cout << "Successfully saved as " << newFilePath << std::endl;
}
void HotelApp::printHelp() {
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "open <file>                                                                 opens <file>" << std::endl;
    std::cout << "close                                                                       closes currently opened file" << std::endl;
    std::cout << "save                                                                        saves the currently open file" << std::endl;
    std::cout << "saveas <file>                                                               saves the currently open file in <file>" << std::endl;
    std::cout << "checkin <room number> <start date> <end date> <note> <numberGuests>         checks in guests to the room" << std::endl; 
    std::cout << "checkout <room number>                                                      checks out guests from the room" << std::endl;
    std::cout << "availability <date>                                                         prints all available rooms for a date" << std::endl;
    std::cout << "report <from> <to>                                                          prints room usage report for the specified period" << std::endl;
    std::cout << "find <beds> <from> <to>                                                     finds an available room" << std::endl;
    std::cout << "find! <beds> <from> <to>                                                    finds an emergency available room" << std::endl;
    std::cout << "unavailable <room> <from> <to> <note>                                       declares a room as unavailable" << std::endl;
    std::cout << "printRoomActivities <room number>                                           prints activities for the specified room" << std::endl;
    std::cout << "printActivityGuests <activity name>                                         prints guests for the specified activity" << std::endl;
    std::cout << "printRooms                                                                  prints all rooms and their details" << std::endl;
    std::cout << "addRoom <room number> <num beds>                                            adds a room with the specified number of beds" << std::endl;
    std::cout << "addActivity <activity name>                                                 adds a new activity" << std::endl;
    std::cout << "addGuestToActivity <activity name> <first name> <last name> <phone number>  adds a guest to the specified activity" << std::endl;
    std::cout << "addGuest <first name> <last name> <phone number>                            adds a guest to the hotel" << std::endl;
    std::cout << "printActivities                                                             prints all activities" << std::endl;
    std::cout << "printGuests                                                                 prints all guests in the hotel" << std::endl;
    std::cout << "addRoomActivity                                                             adds activity to a room" << std::endl;
    std::cout << "getCurrentDate                                                              gets the current date " << std::endl;
    std::cout << "addEmergencyRoom <room> <beds>                                              adds an emergency room if there are no available rooms for a specified period" << std::endl;
    std::cout << "exit                                                                        exits the program" << std::endl;
}
void HotelApp::processCheckinCommand(const std::vector<std::string>& tokens) {
    try {
        if (!isOpen) {
            std::cout << "No file is currently open." << std::endl;
            return;
        }
        if (tokens.size() < 6) {
            std::cout << "Invalid command. Please provide room number, check-in date, check-out date, note, and number of guests." << std::endl;
            return;
        }
        int roomNumber = std::stoi(tokens[1]);
        std::string checkIn = tokens[2];
        std::string checkOut = tokens[3];
        std::string note = tokens[4];
        unsigned int numGuests = std::stoi(tokens[5]);

        hotel->checkin(roomNumber, checkIn, checkOut, note, numGuests);

        if (currentFile.empty()) {
            std::cout << "No filename specified. Cannot save the rooms." << std::endl;
            return;
        }

        std::vector<std::vector<std::string>> previousRooms = CSVUtils::readReservationsFromCSV(currentFile);
        previousRooms.push_back({ std::to_string(roomNumber), checkIn, checkOut, note, std::to_string(numGuests) });

        CSVUtils::saveReservationsToCSV(previousRooms, currentFile);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::clearCSVFiles(currentFile);
        return;
    }
}
void HotelApp::processCheckoutCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 2) {
        std::cout << "Invalid command. Please provide a room number for checkout." << std::endl;
        return;
    }
    int roomNumber = std::stoi(tokens[1]);
    hotel->checkout(roomNumber);

    std::string filename = currentFile;
    std::vector<std::vector<std::string>> reservationsData = CSVUtils::readReservationsFromCSV(filename);

    std::vector<std::vector<std::string>> updatedReservationsData;

    for (const auto& reservation : reservationsData) {
        if (reservation[0] != std::to_string(roomNumber)) {
            updatedReservationsData.push_back(reservation);
        }
    }

    CSVUtils::saveReservationsToCSV(updatedReservationsData, filename);
}
void HotelApp::processAvailabilityCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::string date = tokens.size() > 1 ? tokens[1] : "";
    if (currentFile.empty()) {
        std::cout << "No filename specified. Cannot save the availability." << std::endl;
        return;
    }
    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    if (date.empty()) {
        std::string currentDate = hotel->getCurrentDate();
        hotel->printAvailableRooms(currentDate);
    } 
    else {
        hotel->printAvailableRooms(date);
    }

    std::cout.rdbuf(coutBuffer);
    file.close();
}
void HotelApp::processReportCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 3) {
        std::cout << "Invalid command. Please provide 'from' and 'to' dates." << std::endl;
        return;
    }
    std::string from = tokens[1];
    std::string to = tokens[2];

    if (currentFile.empty()) {
        std::cout << "No filename specified. Cannot save the report." << std::endl;
        return;
    }

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    hotel->printRoomUsageReport(from, to);

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processFindCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 4) {
        std::cout << "Invalid command. Please provide the number of beds, start date, and end date." << std::endl;
        return;
    }
    unsigned int beds = std::stoi(tokens[1]);
    std::string from = tokens[2];
    std::string to = tokens[3];

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    Room* availableRoom = hotel->findAvailableRoom(beds, from, to);
    if (availableRoom != nullptr) {
        std::cout << "Found available room: Room " << availableRoom->getNumber() << std::endl;
    } 
    else {
        std::cout << "No available room found." << std::endl;
    }

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processFindEmergencyCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 4) {
        std::cout << "Invalid command. Please provide the number of beds, start date, and end date." << std::endl;
        return;
    }
    unsigned int beds = std::stoi(tokens[1]);
    std::string from = tokens[2];
    std::string to = tokens[3];

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    bool success = hotel->findEmergencyRoom(beds, from, to);
    if (success) {
        std::cout << "Found an available room for emergency: Room with " << beds << " beds" << std::endl;
    } 
    else {
        std::cout << "No available room found for emergency." << std::endl;
    }

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processUnavailableCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 4) {
        std::cout << "Invalid command. Please provide room number, from date, to date, and note." << std::endl;
        return;
    }
    int roomNumber = std::stoi(tokens[1]);
    std::string from = tokens[2];
    std::string to = tokens[3];
    std::string note;
    if (tokens.size() > 4) {
        note = tokens[4];
    }

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    hotel->declareRoomUnavailable(roomNumber, from, to, note);

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processPrintRoomActivitiesCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 2) {
        std::cout << "Invalid command. Please provide a room number." << std::endl;
        return;
    }
    int roomNumber = std::stoi(tokens[1]);

    std::string filename = currentFile;

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    hotel->printRoomActivities(roomNumber);

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processPrintActivityGuestsCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 2) {
        std::cout << "Invalid command. Please provide an activity name." << std::endl;
        return;
    }
    std::string activityName = tokens[1];

    std::string filename = currentFile;

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    hotel->printActivityGuests(activityName);

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processPrintRoomsCommand() {
    if (!isOpen) {
        std::cout << "Error: No hotel is currently open." << std::endl;
        return;
    }

    std::string filename = currentFile;

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    std::string hotelDataFilename = currentFile;
    std::vector<std::vector<std::string>> roomData = CSVUtils::readCSVFile(hotelDataFilename);

    if (roomData.empty()) {
        std::cout << "No room data found." << std::endl;
        return;
    }
    hotel->printRooms();

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processAddRoomCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    try {
        if (tokens.size() < 3) {
            std::cout << "Invalid command. Please provide room number and number of beds." << std::endl;
            return;
        }
        int roomNumber = std::stoi(tokens[1]);
        int numBeds = std::stoi(tokens[2]);
        Room* room = new Room(roomNumber, numBeds);
        hotel->addRoom(room);

        std::vector<std::vector<std::string>> roomData;
        roomData.push_back({ std::to_string(roomNumber), std::to_string(numBeds) });

        std::string filename = currentFile;

        std::ofstream file(filename, std::ios::app);

        if (!file.is_open()) {
            std::cout << "Error opening the file " << filename << std::endl;
            return;
        }

        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(coutBuffer);

        std::vector<std::vector<std::string>> existingRoomData = CSVUtils::readCSVFile(filename);

        existingRoomData.insert(existingRoomData.end(), roomData.begin(), roomData.end());
        CSVUtils::createCSVFile(filename, existingRoomData);
        std::cout << "Room " << roomNumber << " with " << numBeds << " beds has been added." << std::endl;

        file.close();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::clearCSVFiles(currentFile);
    }
}
void HotelApp::processAddActivityCommand(const std::vector<std::string>& tokens) {
    try {
        if (!isOpen) {
            std::cout << "No file is currently open." << std::endl;
            return;
        }
        if (tokens.size() < 2) {
            std::cout << "Invalid command. Please provide an activity name." << std::endl;
            return;
        }
        std::string activityName = tokens[1];
        hotel->addActivity(activityName);

        std::string existingFilename = currentFile;
        std::vector<std::string> previousActivities = CSVUtils::readActivitiesFromCSV(existingFilename);
        previousActivities.push_back(activityName);

        CSVUtils::saveActivitiesToCSV(previousActivities, existingFilename);
        std::cout << "Activity " << activityName << " has been added." << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::clearCSVFiles(currentFile);
    }
}
void HotelApp::processAddGuestToActivityCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 3) {
        std::cout << "Invalid command. Please provide an activity name and guest details." << std::endl;
        return;
    }
    std::string activityName = tokens[1];
    std::string guestName = tokens[2];

    Guest* guest = hotel->findGuestByName(guestName);

    if (guest == nullptr) {
        std::cout << "Guest not found. Please make sure the guest is registered in the hotel." << std::endl;
        return;
    }

    std::string filename = currentFile;

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    hotel->addGuestToActivity(activityName, guest);

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processAddGuestCommand(const std::vector<std::string>& tokens) {
    try {
        if (!isOpen) {
            std::cout << "No file is currently open." << std::endl;
            return;
        }
        if (tokens.size() < 4) {
            std::cout << "Invalid command. Please provide guest's first name, last name, and phone number." << std::endl;
            return;
        }
        std::string firstName = tokens[1];
        std::string lastName = tokens[2];
        std::string phoneNumber = tokens[3];
        Guest* guest = new Guest(firstName, lastName, phoneNumber);
        hotel->addGuest(guest);

        std::string filename = currentFile;

        std::ofstream file(filename, std::ios::app);

        if (!file.is_open()) {
            std::cout << "Error opening the file " << filename << std::endl;
            return;
        }

        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(file.rdbuf());

        std::vector<std::vector<std::string>> previousGuests = CSVUtils::readGuestsFromCSV(filename);
        previousGuests.push_back({ firstName, lastName, phoneNumber });

        CSVUtils::saveGuestsToCSV(previousGuests, filename);

        std::cout.rdbuf(coutBuffer);

        file.close();

        std::cout << "Guest " << firstName << " " << lastName << " has been added!" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::clearCSVFiles(currentFile);
        return;
    }
}
void HotelApp::processPrintGuestsCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    std::string guestsFilename = currentFile;
    std::vector<std::vector<std::string>> guestsData = CSVUtils::readGuestsFromCSV(guestsFilename);

    if (guestsData.empty()) {
        std::cout << "No guest data found." << std::endl;
        return;
    }
    hotel->printGuests();

    std::cout.rdbuf(coutBuffer);
    file.close();
}
void HotelApp::processAddRoomActivityCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    if (tokens.size() < 3) {
        std::cout << "Invalid command. Please provide a room number and an activity." << std::endl;
        return;
    }

    int roomNumber = std::stoi(tokens[1]);
    std::string activityName = tokens[2];

    Activity* activity = new Activity(activityName);

    hotel->addRoomActivity(roomNumber, activity);

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    std::cout << "Room activity added: Room " << roomNumber << " - " << activityName << std::endl;

    std::cout.rdbuf(coutBuffer);
    file.close();
}
void HotelApp::processAddEmergencyRoomCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    if (tokens.size() < 3) {
        std::cout << "Invalid command. Please provide room number and number of beds." << std::endl;
        return;
    }

    int roomNumber = std::stoi(tokens[1]);
    int numBeds = std::stoi(tokens[2]);
    Room* room = new Room(roomNumber, numBeds);

    hotel->addEmergencyRoom(room);

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    std::cout << "Emergency room added: Room " << roomNumber << " with " << numBeds << " beds." << std::endl;

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processGetCurrentDateCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    std::string currentDate = hotel->getCurrentDate();

    std::string filename = currentDate;
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    std::cout << "Current date is: " << currentDate << std::endl;

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processPrintActivitiesCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    std::string filename = currentFile;

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }

    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    std::vector<std::string> activityData = CSVUtils::readActivitiesFromCSV(filename);

    if (activityData.empty()) {
        std::cout << "No activity data found." << std::endl;
        return;
    }

    hotel->printActivities();

    std::cout.rdbuf(coutBuffer);

    file.close();
}
void HotelApp::processExitCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        CSVUtils::clearCSVFiles(currentFile);
        std::exit(0);
    }
    
    std::string response;
    std::cout << "Do you want to save changes before exiting? (yes/no): ";
    std::cin >> response;

    if (response == "yes") {
        processSaveCommand();
        std::cout << "Exiting the program. Goodbye!" << std::endl;
        std::exit(0);
    } 
    else if (response == "no") {
        std::cout << "Exiting the program without saving. Goodbye!" << std::endl;
        CSVUtils::clearCSVFiles(currentFile);
        std::exit(0);
    } 
    else {
        std::cout << "Invalid response. Exiting the program without saving. Goodbye!" << std::endl;
        CSVUtils::clearCSVFiles(currentFile);
        std::exit(0);
    }
}
void HotelApp::processCommand(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> std::quoted(token)) {
        tokens.push_back(token);
    }
    if (tokens.empty()) {
        return;
    }
    std::string command = tokens[0];

    if (command == "open") {
        processOpenCommand(tokens);
    }
    else if (command == "close") {
        processCloseCommand();
    }
    else if (command == "save") {
        processSaveCommand();
    }
    else if (command == "saveas") {
        processSaveAsCommand(tokens);
    }
    else if (command == "help") {
        printHelp();
    }
    else if (command == "checkin") {
        processCheckinCommand(tokens);
    }
    else if (command == "checkout") {
        processCheckoutCommand(tokens);
    }
    else if (command == "availability") {
        processAvailabilityCommand(tokens);
    }
    else if (command == "report") {
        processReportCommand(tokens);
    }
    else if (command == "find") {
        processFindCommand(tokens);
    }
    else if (command == "find!") {
        processFindEmergencyCommand(tokens);
    }
    else if (command == "unavailable") {
        processUnavailableCommand(tokens);
    }
    else if (command == "printRoomActivities") {
        processPrintRoomActivitiesCommand(tokens);
    }
    else if (command == "printActivityGuests") {
        processPrintActivityGuestsCommand(tokens);
    }
    else if (command == "printRooms") {
        processPrintRoomsCommand();
    }
    else if (command == "addRoom") {
        processAddRoomCommand(tokens);
    }
    else if (command == "addActivity") {
        processAddActivityCommand(tokens);
    }
    else if (command == "addGuestToActivity") {
        processAddGuestToActivityCommand(tokens);
    }
    else if (command == "addGuest") {
        processAddGuestCommand(tokens);
    }
    else if (command == "printGuests") {
        processPrintGuestsCommand();
    }
    else if (command == "addRoomActivity") {
        processAddRoomActivityCommand(tokens);
    }
    else if (command == "addEmergencyRoom") {
        processAddEmergencyRoomCommand(tokens);
    }
    else if (command == "getCurrentDate") {
        processGetCurrentDateCommand();
    }
    else if (command == "printActivities") {
        processPrintActivitiesCommand();
    }
    else if (command == "exit") {
        processExitCommand();
    }
    else {
        std::cout << "Invalid command. Type 'help' for a list of supported commands." << std::endl;
    }
}
