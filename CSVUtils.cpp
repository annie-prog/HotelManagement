#include "CSVUtils.hpp"
#include <iostream>
#include <sstream>

bool CSVUtils::CheckExtension(const std::string& name) {
    int size = name.size();
    if (name[size - 1] != 'v' && name[size - 1] != 'V')
        return false;
    if (name[size - 2] != 's' && name[size - 2] != 'S')
        return false;
    if (name[size - 3] != 'c' && name[size - 3] != 'C')
        return false;
    if (name[size - 4] != '.')
        return false;
    return true;
}
bool CSVUtils::CheckForbiddenLetters(const std::string& name) {
    const char forbidden[] = "/\\?%*\";:|<>.,=";
    int size = name.size();
    for (int i = 0; i < size - 4; i++) {
        for (int j = 0; j < 15; j++) {
            if (name[i] == forbidden[j])
                return false;
        }
    }
    return true;
}
bool CSVUtils::FileNameCheck(const std::string& name) {
    int size = name.size();
    if (size <= 4) {
        std::cout << "Filename is wrong." << std::endl;
        return false;
    }
    if (CheckForbiddenLetters(name) == false) {
        std::cout << "Forbidden symbols in the file name." << std::endl;
        return false;
    }
    if (CheckExtension(name) == false) {
        std::cout << "Extension is wrong." << std::endl;
        return false;
    }

    return true;
}
int CSVUtils::LinesCounter(std::ifstream& file) {
    int count = 0;
    char a;
    while (file.get(a)) {
        if (a == '\n') {
            count++;
        }
    }
    if (file.eof() && count != 0) {
        count++;
    }
    file.clear();
    file.seekg(0, std::ios::beg);
    return count;
}
void CSVUtils::saveGuestsToCSV(const std::vector<std::vector<std::string>>& guests, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file" << std::endl;
        return;
    }

    for (const auto& guest : guests) {
        for (size_t i = 0; i < guest.size(); i++) {
            file << guest[i];
            if (i < guest.size() - 1) {
                file << ",";
            }
        }
        file << std::endl;
    }

    file.close();
    std::cout << "Allocated correctly" << std::endl;
}
std::vector<std::vector<std::string>> CSVUtils::readGuestsFromCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> guests;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file!" << filename << std::endl;
        return guests;
    }

    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> guest;
        size_t start = 0;
        size_t end = line.find(',');

        while (end != std::string::npos) {
            guest.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(',', start);
        }

        guest.push_back(line.substr(start));
        guests.push_back(guest);
    }

    file.close();

    return guests;
}
void CSVUtils::printGuests(const std::vector<std::vector<std::string>>& guests) {
    for (const auto& guest : guests) {
        for (const auto& data : guest) {
            std::cout << data << " ";
        }
        std::cout << std::endl;
    }
}
void CSVUtils::saveGuestsToCSV(const Accommodation& accommodation, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return;
    }

    Guest** guests = accommodation.getGuests();
    unsigned int numGuests = accommodation.getNumGuests();

    for (unsigned int i = 0; i < numGuests; i++) {
        file << guests[i]->getFirstName() << ","
             << guests[i]->getLastName() << ","
             << guests[i]->getPhoneNumber() << ",\n";
    }

    file.close();
    std::cout << "Allocated successfully" << std::endl;
}
void CSVUtils::printGuestsFromCSV(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(',')) != std::string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        if (tokens.size() == 3) {
            std::cout << "First Name: " << tokens[0] << std::endl;
            std::cout << "Last Name: " << tokens[1] << std::endl;
            std::cout << "Phone Number: " << tokens[2] << std::endl;
            std::cout << std::endl;
        }
    }

    file.close();
}
void CSVUtils::saveActivitiesToCSV(const std::vector<std::string>& activities, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return;
    }

    for (const auto& activity : activities) {
        file << activity << ",\n";
    }

    file.close();
    std::cout << "Allocated successfully " << filename << std::endl;
}
std::vector<std::string> CSVUtils::readActivitiesFromCSV(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return {};
    }

    std::vector<std::string> activities;
    std::string activity;

    while (std::getline(file, activity, ',')) {
        if (!activity.empty() && activity.back() == '\n') {
            activity.pop_back();
        }
        activities.push_back(activity);
    }

    file.close();
    return activities;
}
void CSVUtils::saveReservationsToCSV(const std::vector<std::vector<std::string>>& reservations, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return;
    }

    for (const auto& reservation : reservations) {
        for (const auto& field : reservation) {
            file << field << ",";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Allocated successfully " << filename << std::endl;
}
std::vector<std::vector<std::string>> CSVUtils::readReservationsFromCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> reservations;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return reservations;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> reservation;
        std::istringstream iss(line);
        std::string field;

        while (std::getline(iss, field, ',')) {
            reservation.push_back(field);
        }

        reservations.push_back(reservation);
    }

    file.close();
    return reservations;
}
void CSVUtils::printReservations(const std::vector<std::vector<std::string>>& reservations) {
    for (const auto& reservation : reservations) {
        for (const auto& field : reservation) {
            std::cout << field << ",";
        }
        std::cout << "\n";
    }
}
void CSVUtils::createCSVFile(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (const auto& field : row) {
            file << field << ",";
        }
        file << "\n";
    }

    file.close();
    //std::cout << "CSV file created: " << filename << std::endl;
}
std::vector<std::vector<std::string>> CSVUtils::readCSVFile(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::istringstream iss(line);
        std::string field;

        while (std::getline(iss, field, ',')) {
            row.push_back(field);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}
void CSVUtils::printCSVData(const std::vector<std::vector<std::string>>& data) {
    for (const auto& row : data) {
        for (const auto& field : row) {
            std::cout << field << ",";
        }
        std::cout << "\n";
    }
}
void CSVUtils::clearCSVFiles() {
    std::vector<std::string> filenames = { "guests.csv", "activities.csv", "reservations.csv", "rooms.csv", "accommodations.csv" };

    for (const auto& filename : filenames) {
        std::ofstream file(filename);
        file.close();
    }
}