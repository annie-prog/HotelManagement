#include <vector>
#include <string>
#include <fstream>
#include "Accommodation.hpp"

class CSVUtils {
public: 
    static void SaveGuestsToCSV(const std::vector<std::vector<std::string>>& guests, const std::string& filename); // Saves a vector of guests to a CSV file
    static std::vector<std::vector<std::string>> ReadGuestsFromCSV(const std::string& filename); // Reads guests from a CSV file and return them as a vector
    static void PrintGuests(const std::vector<std::vector<std::string>>& guests); // Prints a vector of guests to the console
    static void SaveActivitiesToCSV(const std::vector<std::string>& activities, const std::string& filename); // Saves a vector of activities to a CSV file
    static std::vector<std::string> ReadActivitiesFromCSV(const std::string& filename); // Reads activities from a CSV file and return them as a vector
    static void SaveReservationsToCSV(const std::vector<std::vector<std::string>>& reservations, const std::string& filename); // Saves a vector of reservations to a CSV file
    static std::vector<std::vector<std::string>> ReadReservationsFromCSV(const std::string& filename); // Reads reservations from a CSV file and return them as a vector
    static void PrintReservations(const std::vector<std::vector<std::string>>& reservations); // Prints a vector of reservations to the console
    static void CreateCSVFile(const std::string& filename, const std::vector<std::vector<std::string>>& data); // Creates a new CSV file with the given filename and data
    static std::vector<std::vector<std::string>> ReadCSVFile(const std::string& filename); // Reads data from a CSV file and return it as a vector
    static void PrintCSVData(const std::vector<std::vector<std::string>>& data); // Prints CSV data to the console  
    static void ClearCSVFiles(const std::string& filename); // Clears the contents of a CSV file with the given filename
};