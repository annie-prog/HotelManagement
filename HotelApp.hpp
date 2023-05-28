#include "HotelSystem.hpp"
#include <string>

class HotelApp{
private:
    std::string currentFile;
    bool isOpen = false;
    HotelSystem* hotel;

public:
    HotelApp();
    void run();
    void printWelcomeMessage();
    std::string getUserInput();
    void processCommand(const std::string& input);

    void processOpenCommand(const std::vector<std::string>& tokens);
    void processCloseCommand();
    void processSaveCommand();
    void processSaveAsCommand(const std::vector<std::string>& tokens);
    void printHelp();
    void processCheckinCommand(const std::vector<std::string>& tokens);
    void processCheckoutCommand(const std::vector<std::string>& tokens);
    void processAvailabilityCommand(const std::vector<std::string>& tokens);
    void processReportCommand(const std::vector<std::string>& tokens);
    void processFindCommand(const std::vector<std::string>& tokens);
    void processFindEmergencyCommand(const std::vector<std::string>& tokens);
    void processUnavailableCommand(const std::vector<std::string>& tokens);
    void processPrintRoomActivitiesCommand(const std::vector<std::string>& tokens); 
    void processPrintActivityGuestsCommand(const std::vector<std::string>& tokens); 
    void processPrintRoomsCommand();
    void processAddRoomCommand(const std::vector<std::string>& tokens); 
    void processAddActivityCommand(const std::vector<std::string>& tokens); 
    void processAddGuestToActivityCommand(const std::vector<std::string>& tokens); 
    void processAddGuestCommand(const std::vector<std::string>& tokens);
    void processPrintGuestsCommand(); 
    void processAddRoomActivityCommand(const std::vector<std::string>& tokens); 
    void processAddEmergencyRoomCommand(const std::vector<std::string>& tokens); 
    void processGetCurrentDateCommand(); 
    void processPrintActivitiesCommand(); 
    void processExitCommand(); 
};