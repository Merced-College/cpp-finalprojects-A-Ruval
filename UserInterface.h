// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <string>
#include "DataManager.h"
using namespace std;

class UserInterface {
    private:
        DataManager dataManager;
        
        // Menu display methods
        void displayMainMenu() const;
        void displayEventMenu() const;
        void displayResourceMenu() const;
        
        // Menu processing methods
        void processMainMenu();
        void processEventMenu();
        void processResourceMenu();
        
        // Event-related methods
        void viewAllEvents() const;
        void searchEvent();
        void addNewEvent();
        void sortEvents();
        void filterEvents();
        
        // Resource-related methods
        void viewAllResources() const;
        void searchResource();
        void addNewResource();
        void filterResources();
        
        // Helper methods
        string getInput(const string& prompt) const;
        int getIntInput(const string& prompt, int min, int max) const;
        void pressEnterToContinue() const;
        void clearScreen() const;
        
    public:
        UserInterface();
        void start();
    };
    
    #endif // USER_INTERFACE_H