#include "HotelSystem.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

int main() {
    std::string currentFile;
    bool isOpen = false;

    HotelSystem* hotel = HotelSystem::getInstance();
    
    std::cout << "Hotel System - Command Line Interface" << std::endl;
    std::cout << "Type 'help' for a list of supported commands." << std::endl;

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
            std::cout << "open <file>                          opens <file>" << std::endl;
            std::cout << "close                                closes currently opened file" << std::endl;
            std::cout << "save                                 saves the currently open file" << std::endl;
            std::cout << "saveas <file>                        saves the currently open file in <file>" << std::endl;
            std::cout << "checkin <room number> <start date> <end date>     checks in guests to the room" << std::endl;
            std::cout << "checkout <room number>               checks out guests from the room" << std::endl;
            std::cout << "availability                         prints all available rooms for a date" << std::endl;
            std::cout << "report <from> <to>                   prints room usage report for the specified period" << std::endl;
            std::cout << "find <beds> <from> <to>              finds an available room" << std::endl;
            std::cout << "find! <beds> <from> <to>             finds an emergency available room" << std::endl;
            std::cout << "unavailable <room> <from> <to> <note>      declares a room as unavailable" << std::endl;
            std::cout << "printRoomActivities <room number>    prints activities for the specified room" << std::endl;
            std::cout << "printActivityGuests <activity name>  prints guests for the specified activity" << std::endl;
            std::cout << "help                                 prints this information" << std::endl;
            std::cout << "exit                                 exits the program" << std::endl;
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

            hotel->makeReservation(roomNumber, checkIn, checkOut, note, numGuests);
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
            } else {
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
        else if (command == "exit") {
            break;
        } 
        else {
            std::cout << "Invalid command. Type 'help' for a list of supported commands." << std::endl;
        }
    }

    std::cout << "Exiting the program..." << std::endl;

    return 0;
}