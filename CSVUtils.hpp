#include <vector>
#include <string>
#include <fstream>
#include "Accommodation.hpp"

class CSVUtils {
public:
    static void saveGuestsToCSV(const std::vector<std::vector<std::string>>& guests, const std::string& filename);
    static std::vector<std::vector<std::string>> readGuestsFromCSV(const std::string& filename);
    static void printGuests(const std::vector<std::vector<std::string>>& guests);
    static void saveActivitiesToCSV(const std::vector<std::string>& activities, const std::string& filename);
    static std::vector<std::string> readActivitiesFromCSV(const std::string& filename);
    static void saveReservationsToCSV(const std::vector<std::vector<std::string>>& reservations, const std::string& filename);
    static std::vector<std::vector<std::string>> readReservationsFromCSV(const std::string& filename);
    static void printReservations(const std::vector<std::vector<std::string>>& reservations);
    static void createCSVFile(const std::string& filename, const std::vector<std::vector<std::string>>& data);
    static std::vector<std::vector<std::string>> readCSVFile(const std::string& filename);
    static void printCSVData(const std::vector<std::vector<std::string>>& data);
    static void clearCSVFiles(const std::string& filename);
};