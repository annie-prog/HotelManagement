#include <vector>
#include <string>
#include <fstream>
#include "Accommodation.hpp"

class CSVUtils {
public:
    static void SaveGuestsToCSV(const std::vector<std::vector<std::string>>& guests, const std::string& filename);
    static std::vector<std::vector<std::string>> ReadGuestsFromCSV(const std::string& filename);
    static void PrintGuests(const std::vector<std::vector<std::string>>& guests);
    static void SaveActivitiesToCSV(const std::vector<std::string>& activities, const std::string& filename);
    static std::vector<std::string> ReadActivitiesFromCSV(const std::string& filename);
    static void SaveReservationsToCSV(const std::vector<std::vector<std::string>>& reservations, const std::string& filename);
    static std::vector<std::vector<std::string>> ReadReservationsFromCSV(const std::string& filename);
    static void PrintReservations(const std::vector<std::vector<std::string>>& reservations);
    static void CreateCSVFile(const std::string& filename, const std::vector<std::vector<std::string>>& data);
    static std::vector<std::vector<std::string>> ReadCSVFile(const std::string& filename);
    static void PrintCSVData(const std::vector<std::vector<std::string>>& data);
    static void ClearCSVFiles(const std::string& filename);
};