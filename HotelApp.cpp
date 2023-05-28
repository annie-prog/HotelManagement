#include "HotelApp.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "CSVUtils.hpp"
#include <algorithm>

HotelApp::HotelApp() {
    hotel = HotelSystem::GetInstance();
}
void HotelApp::Run() {
    PrintWelcomeMessage();
    while (true) {
        std::string input = GetUserInput();
        ProcessCommand(input);
    }
}
void HotelApp::PrintWelcomeMessage() {
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
    std::cout << "Welcome to hotel 'Amelia Resort'! " << std::endl;
    std::cout << "Type 'help' for a list of supported commands." << std::endl;
    std::cout << "°°°°°°°°°°°°°°°°°°°°°°°°" << std::endl;
}
std::string HotelApp::GetUserInput() {
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    return input;
}
void HotelApp::ProcessOpenCommand(const std::vector<std::string>& tokens) {
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
        std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // Reads the content of the file
        file.close();

        isOpen = true;
        currentFile = filePath;
    }
}
void HotelApp::ProcessCloseCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::cout << "Successfully closed " << currentFile << std::endl;
    isOpen = false;
    //currentFile = "";
    CSVUtils::ClearCSVFiles(currentFile);
}
void HotelApp::ProcessSaveCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::cout << "Successfully saved " << currentFile << std::endl;
}
void HotelApp::ProcessSaveAsCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    if (tokens.size() < 2) {
        std::cout << "Please provide a file path to save as." << std::endl;
        return;
    }

    std::string newFilePath = tokens[1];

    std::ifstream current(currentFile); // Reads the content of the current file
    std::string fileContent((std::istreambuf_iterator<char>(current)), std::istreambuf_iterator<char>());
    current.close();

    std::ofstream newFile(newFilePath); // Saves the content to the new file
    if (!newFile) {
        std::cout << "Error creating the new file." << std::endl;
        return;
    }
    newFile << fileContent;
    newFile.close();

    std::cout << "Successfully saved as " << newFilePath << std::endl;
}
void HotelApp::PrintHelp() {
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "open <file>                                                                 opens <file>" << std::endl;
    std::cout << "close                                                                       closes currently opened file" << std::endl;
    std::cout << "save                                                                        saves the currently open file" << std::endl;
    std::cout << "saveas <file>                                                               saves the currently open file in <file>" << std::endl;
    std::cout << "checkin <room number> <start date> <end date> <note> [<numberGuests>]       checks in guests to the room" << std::endl; 
    std::cout << "checkout <room number>                                                      checks out guests from the room" << std::endl;
    std::cout << "availability [<date>]                                                       prints all available rooms for a date" << std::endl;
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
    std::cout << "addRoomActivity <room number> <activity name>                               adds activity to a room" << std::endl;
    std::cout << "getCurrentDate                                                              gets the current date " << std::endl;
    std::cout << "addEmergencyRoom <room number> <beds>                                       adds an emergency room if there are no available rooms for a specified period" << std::endl;
    std::cout << "exit                                                                        exits the program" << std::endl;
}
void HotelApp::ProcessCheckinCommand(const std::vector<std::string>& tokens) {
    try {
        if (!isOpen) {
            std::cout << "No file is currently open." << std::endl;
            return;
        }
        if (tokens.size() < 5) {
            std::cout << "Invalid command. Please provide room number, check-in date, check-out date, note." << std::endl;
            return;
        }
        int roomNumber = std::stoi(tokens[1]);
        std::string checkIn = tokens[2];
        std::string checkOut = tokens[3];
        std::string note = tokens[4];
        unsigned int numGuests = 0;

        if (tokens.size() >= 6) {
            numGuests = std::stoi(tokens[5]);
        } 
        else {
            Room* room = hotel->GetRoom(roomNumber);
            if (room) {
                numGuests = room->GetNumberOfBeds();
            }
        }
        hotel->Checkin(roomNumber, checkIn, checkOut, note, numGuests);
        if (currentFile.empty()) {
            std::cout << "No filename specified. Cannot save the rooms." << std::endl;
            return;
        }
        std::vector<std::vector<std::string>> previousRooms = CSVUtils::ReadReservationsFromCSV(currentFile); // Reads the previous reservations from the file
        previousRooms.push_back({ std::to_string(roomNumber), checkIn, checkOut, note, std::to_string(numGuests) }); // Adds the new reservation to the list

        CSVUtils::SaveReservationsToCSV(previousRooms, currentFile); // Saves the updated reservations to the file
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::ClearCSVFiles(currentFile);
        return;
    }
}
void HotelApp::ProcessCheckoutCommand(const std::vector<std::string>& tokens) {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    if (tokens.size() < 2) {
        std::cout << "Invalid command. Please provide a room number for checkout." << std::endl;
        return;
    }
    int roomNumber = std::stoi(tokens[1]);
    hotel->Checkout(roomNumber);

    std::string filename = currentFile;
    std::vector<std::vector<std::string>> reservationsData = CSVUtils::ReadReservationsFromCSV(filename);
    std::vector<std::vector<std::string>> updatedReservationsData;

    // Removes the checked-out room from the reservations list
    for (const auto& reservation : reservationsData) {
        if (reservation[0] != std::to_string(roomNumber)) {
            updatedReservationsData.push_back(reservation);
        }
    }
    CSVUtils::SaveReservationsToCSV(updatedReservationsData, filename); // Saves the updated reservations to the file
}
void HotelApp::ProcessAvailabilityCommand(const std::vector<std::string>& tokens) {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    if (date.empty()) {
        std::string currentDate = hotel->GetCurrentDate();
        hotel->PrintAvailableRooms(currentDate);
    } 
    else {
        hotel->PrintAvailableRooms(date);
    }
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessReportCommand(const std::vector<std::string>& tokens) {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    hotel->PrintRoomUsageReport(from, to);
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessFindCommand(const std::vector<std::string>& tokens) {
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

    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    Room* availableRoom = hotel->FindAvailableRoom(beds, from, to);
    if (availableRoom != nullptr) {
        std::cout << "Found available room: Room " << availableRoom->GetNumber() << std::endl;
    } 
    else {
        std::cout << "No available room found." << std::endl;
    }
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessFindEmergencyCommand(const std::vector<std::string>& tokens) {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());
    bool success = hotel->FindEmergencyRoom(beds, from, to);
    if (success) {
        std::cout << "Found an available room for emergency: Room with " << beds << " beds" << std::endl;
    } 
    else {
        std::cout << "No available room found for emergency." << std::endl;
    }
    std::cout.rdbuf(coutBuffer); // Restores the standard output

    file.close();
}
void HotelApp::ProcessUnavailableCommand(const std::vector<std::string>& tokens) {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    hotel->DeclareRoomUnavailable(roomNumber, from, to, note);
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessPrintRoomActivitiesCommand(const std::vector<std::string>& tokens) {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    hotel->PrintRoomActivities(roomNumber);
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessPrintActivityGuestsCommand(const std::vector<std::string>& tokens) {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    hotel->PrintActivityGuests(activityName);
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessPrintRoomsCommand() {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    std::string hotelDataFilename = currentFile;
    std::vector<std::vector<std::string>> roomData = CSVUtils::ReadCSVFile(hotelDataFilename);
    if (roomData.empty()) {
        std::cout << "No room data found." << std::endl;
        return;
    }
    hotel->PrintRooms();
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessAddRoomCommand(const std::vector<std::string>& tokens) {
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
        hotel->AddRoom(room);

        std::vector<std::vector<std::string>> roomData;
        roomData.push_back({ std::to_string(roomNumber), std::to_string(numBeds) });

        std::string filename = currentFile;
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cout << "Error opening the file " << filename << std::endl;
            return;
        }
        std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
        std::cout.rdbuf(coutBuffer);

        std::vector<std::vector<std::string>> existingRoomData = CSVUtils::ReadCSVFile(filename);
        existingRoomData.insert(existingRoomData.end(), roomData.begin(), roomData.end());
        CSVUtils::CreateCSVFile(filename, existingRoomData);
        std::cout << "Room " << roomNumber << " with " << numBeds << " beds has been added." << std::endl;

        file.close();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::ClearCSVFiles(currentFile);
    }
}
void HotelApp::ProcessAddActivityCommand(const std::vector<std::string>& tokens) {
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
        hotel->AddActivity(activityName);

        std::string existingFilename = currentFile;
        std::vector<std::string> previousActivities = CSVUtils::ReadActivitiesFromCSV(existingFilename);
        previousActivities.push_back(activityName);

        CSVUtils::SaveActivitiesToCSV(previousActivities, existingFilename);
        std::cout << "Activity " << activityName << " has been added." << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::ClearCSVFiles(currentFile);
    }
}
void HotelApp::ProcessAddGuestToActivityCommand(const std::vector<std::string>& tokens) {
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

    Guest* guest = hotel->FindGuestByName(guestName);
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    hotel->AddGuestToActivity(activityName, guest);
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessAddGuestCommand(const std::vector<std::string>& tokens) {
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
        hotel->AddGuest(guest);

        std::string filename = currentFile;
        std::ofstream file(filename, std::ios::app);

        if (!file.is_open()) {
            std::cout << "Error opening the file " << filename << std::endl;
            return;
        }
        std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
        std::cout.rdbuf(file.rdbuf());

        std::vector<std::vector<std::string>> previousGuests = CSVUtils::ReadGuestsFromCSV(filename);
        previousGuests.push_back({ firstName, lastName, phoneNumber });
        CSVUtils::SaveGuestsToCSV(previousGuests, filename);

        std::cout.rdbuf(coutBuffer); // Restores the standard output
        file.close();
        std::cout << "Guest " << firstName << " " << lastName << " has been added!" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CSVUtils::ClearCSVFiles(currentFile);
        return;
    }
}
void HotelApp::ProcessPrintGuestsCommand() {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    std::string guestsFilename = currentFile;
    std::vector<std::vector<std::string>> guestsData = CSVUtils::ReadGuestsFromCSV(guestsFilename);

    if (guestsData.empty()) {
        std::cout << "No guest data found." << std::endl;
        return;
    }
    hotel->PrintGuests();
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessAddRoomActivityCommand(const std::vector<std::string>& tokens) {
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
    hotel->AddRoomActivity(roomNumber, activity);

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    std::cout << "Room activity added: Room " << roomNumber << " - " << activityName << std::endl;
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessAddEmergencyRoomCommand(const std::vector<std::string>& tokens) {
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

    hotel->AddEmergencyRoom(room);

    std::string filename = currentFile;
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    std::cout << "Emergency room added: Room " << roomNumber << " with " << numBeds << " beds." << std::endl;
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessGetCurrentDateCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::string currentDate = hotel->GetCurrentDate();

    std::string filename = currentDate;
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening the file " << filename << std::endl;
        return;
    }
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    std::cout << "Current date is: " << currentDate << std::endl;
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessPrintActivitiesCommand() {
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
    std::streambuf* coutBuffer = std::cout.rdbuf(); // Redirects the output to the file
    std::cout.rdbuf(file.rdbuf());

    std::vector<std::string> activityData = CSVUtils::ReadActivitiesFromCSV(filename);
    if (activityData.empty()) {
        std::cout << "No activity data found." << std::endl;
        return;
    }
    hotel->PrintActivities();
    std::cout.rdbuf(coutBuffer); // Restores the standard output
    file.close();
}
void HotelApp::ProcessExitCommand() {
    if (!isOpen) {
        std::cout << "No file is currently open." << std::endl;
        CSVUtils::ClearCSVFiles(currentFile);
        std::exit(0);
    }
    
    std::string response;
    std::cout << "Do you want to save changes before exiting? (yes/no): ";
    std::cin >> response;

    if (response == "yes") {
        ProcessSaveCommand();
        std::cout << "Exiting the program. Goodbye!" << std::endl;
        std::exit(0);
    } 
    else if (response == "no") {
        std::cout << "Exiting the program without saving. Goodbye!" << std::endl;
        CSVUtils::ClearCSVFiles(currentFile);
        std::exit(0);
    } 
    else {
        std::cout << "Invalid response. Exiting the program without saving. Goodbye!" << std::endl;
        CSVUtils::ClearCSVFiles(currentFile);
        std::exit(0);
    }
}
void HotelApp::ProcessCommand(const std::string& input) {
    std::istringstream iss(input); // Tokenize the input command
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> std::quoted(token)) {
        tokens.push_back(token);
    }
    if (tokens.empty()) {
        return;
    }
    std::string command = tokens[0];

    // Process the command based on its type
    if (command == "open") {
        ProcessOpenCommand(tokens);
    }
    else if (command == "close") {
        ProcessCloseCommand();
    }
    else if (command == "save") {
        ProcessSaveCommand();
    }
    else if (command == "saveas") {
        ProcessSaveAsCommand(tokens);
    }
    else if (command == "help") {
        PrintHelp();
    }
    else if (command == "checkin") {
        ProcessCheckinCommand(tokens);
    }
    else if (command == "checkout") {
        ProcessCheckoutCommand(tokens);
    }
    else if (command == "availability") {
        ProcessAvailabilityCommand(tokens);
    }
    else if (command == "report") {
        ProcessReportCommand(tokens);
    }
    else if (command == "find") {
        ProcessFindCommand(tokens);
    }
    else if (command == "find!") {
        ProcessFindEmergencyCommand(tokens);
    }
    else if (command == "unavailable") {
        ProcessUnavailableCommand(tokens);
    }
    else if (command == "printRoomActivities") {
        ProcessPrintRoomActivitiesCommand(tokens);
    }
    else if (command == "printActivityGuests") {
        ProcessPrintActivityGuestsCommand(tokens);
    }
    else if (command == "printRooms") {
        ProcessPrintRoomsCommand();
    }
    else if (command == "addRoom") {
        ProcessAddRoomCommand(tokens);
    }
    else if (command == "addActivity") {
        ProcessAddActivityCommand(tokens);
    }
    else if (command == "addGuestToActivity") {
        ProcessAddGuestToActivityCommand(tokens);
    }
    else if (command == "addGuest") {
        ProcessAddGuestCommand(tokens);
    }
    else if (command == "printGuests") {
        ProcessPrintGuestsCommand();
    }
    else if (command == "addRoomActivity") {
        ProcessAddRoomActivityCommand(tokens);
    }
    else if (command == "addEmergencyRoom") {
        ProcessAddEmergencyRoomCommand(tokens);
    }
    else if (command == "getCurrentDate") {
        ProcessGetCurrentDateCommand();
    }
    else if (command == "printActivities") {
        ProcessPrintActivitiesCommand();
    }
    else if (command == "exit") {
        ProcessExitCommand();
    }
    else {
        std::cout << "Invalid command. Type 'help' for a list of supported commands." << std::endl;
    }
}
