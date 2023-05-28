#include "CSVUtils.hpp"
#include <iostream>
#include <sstream>

void CSVUtils::SaveGuestsToCSV(const std::vector<std::vector<std::string>>& guests, const std::string& filename) {
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
}
std::vector<std::vector<std::string>> CSVUtils::ReadGuestsFromCSV(const std::string& filename) {
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
void CSVUtils::PrintGuests(const std::vector<std::vector<std::string>>& guests) {
    for (const auto& guest : guests) {
        for (const auto& data : guest) {
            std::cout << data << " ";
        }
        std::cout << std::endl;
    }
}
void CSVUtils::SaveActivitiesToCSV(const std::vector<std::string>& activities, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return;
    }

    for (const auto& activity : activities) {
        file << activity << ",\n";
    }

    file.close();
}
std::vector<std::string> CSVUtils::ReadActivitiesFromCSV(const std::string& filename) {
    std::vector<std::string> activities;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error with opening the file " << filename << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == ',') {
            line.pop_back();
        }
        activities.push_back(line);
    }

    file.close();
    return activities;
}
void CSVUtils::SaveReservationsToCSV(const std::vector<std::vector<std::string>>& reservations, const std::string& filename) {
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
}
std::vector<std::vector<std::string>> CSVUtils::ReadReservationsFromCSV(const std::string& filename) {
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
void CSVUtils::PrintReservations(const std::vector<std::vector<std::string>>& reservations) {
    for (const auto& reservation : reservations) {
        for (const auto& field : reservation) {
            std::cout << field << ",";
        }
        std::cout << "\n";
    }
}
void CSVUtils::CreateCSVFile(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
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
}
std::vector<std::vector<std::string>> CSVUtils::ReadCSVFile(const std::string& filename) {
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
void CSVUtils::PrintCSVData(const std::vector<std::vector<std::string>>& data) {
    for (const auto& row : data) {
        for (const auto& field : row) {
            std::cout << field << ",";
        }
        std::cout << "\n";
    }
}
void CSVUtils::ClearCSVFiles(const std::string& filename) {
    std::ofstream file(filename);
    file.close();
}