#include "HotelSystem.hpp"
#include <string>

class HotelApp{
private:
    std::string currentFile;
    bool isOpen = false;
    HotelSystem* hotel;

public:
    HotelApp();
    void Run();
    void PrintWelcomeMessage();
    std::string GetUserInput();
    void ProcessCommand(const std::string& input);

    void ProcessOpenCommand(const std::vector<std::string>& tokens);
    void ProcessCloseCommand();
    void ProcessSaveCommand();
    void ProcessSaveAsCommand(const std::vector<std::string>& tokens);
    void PrintHelp();
    void ProcessCheckinCommand(const std::vector<std::string>& tokens);
    void ProcessCheckoutCommand(const std::vector<std::string>& tokens);
    void ProcessAvailabilityCommand(const std::vector<std::string>& tokens);
    void ProcessReportCommand(const std::vector<std::string>& tokens);
    void ProcessFindCommand(const std::vector<std::string>& tokens);
    void ProcessFindEmergencyCommand(const std::vector<std::string>& tokens);
    void ProcessUnavailableCommand(const std::vector<std::string>& tokens);
    void ProcessPrintRoomActivitiesCommand(const std::vector<std::string>& tokens); 
    void ProcessPrintActivityGuestsCommand(const std::vector<std::string>& tokens); 
    void ProcessPrintRoomsCommand();
    void ProcessAddRoomCommand(const std::vector<std::string>& tokens); 
    void ProcessAddActivityCommand(const std::vector<std::string>& tokens); 
    void ProcessAddGuestToActivityCommand(const std::vector<std::string>& tokens); 
    void ProcessAddGuestCommand(const std::vector<std::string>& tokens);
    void ProcessPrintGuestsCommand(); 
    void ProcessAddRoomActivityCommand(const std::vector<std::string>& tokens); 
    void ProcessAddEmergencyRoomCommand(const std::vector<std::string>& tokens); 
    void ProcessGetCurrentDateCommand(); 
    void ProcessPrintActivitiesCommand(); 
    void ProcessExitCommand(); 
};