// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;
//I used AI to assist with coding my User Interface, as coding all 500+ lines myself would have been way too timeconsuming and tedious
// Copilot, Microsoft, 2 May. 2025, "Filling in Menus", copilot.microsoft.com/.
// Default constructor for UserInterface class
UserInterface::UserInterface() {}

// Initializes and starts the application interface
void UserInterface::start() {
    clearScreen();
    cout << "======================================\n";
    cout << "   Welcome to Merced Connect!\n";
    cout << "   Your local events and resources hub\n";
    cout << "======================================\n\n";
    
    processMainMenu();
}

// Displays the main menu options to the user
void UserInterface::displayMainMenu() const {
    cout << "\n=== MAIN MENU ===\n";
    cout << "1. Events\n";
    cout << "2. Resources\n";
    cout << "3. Exit\n";
    cout << "================\n";
}

// Displays all event-related options
void UserInterface::displayEventMenu() const {
    cout << "\n=== EVENTS MENU ===\n";
    cout << "1. View All Events\n";
    cout << "2. Search for an Event\n";
    cout << "3. Add New Event\n";
    cout << "4. Sort Events\n";
    cout << "5. Filter Events by Category\n";
    cout << "6. Return to Main Menu\n";
    cout << "===================\n";
}

// Displays all resource-related options
void UserInterface::displayResourceMenu() const {
    cout << "\n=== RESOURCES MENU ===\n";
    cout << "1. View All Resources\n";
    cout << "2. Search for a Resource\n";
    cout << "3. Add New Resource\n";
    cout << "4. Filter Resources by Type\n";
    cout << "5. Return to Main Menu\n";
    cout << "======================\n";
}

// Main menu processing loop - handles user input and navigation
void UserInterface::processMainMenu() {
    bool exitProgram = false;
    
    while (!exitProgram) {
        displayMainMenu();
        // Get user choice between 1-3
        int choice = getIntInput("Enter your choice (1-3): ", 1, 3);
        
        switch (choice) {
            case 1: // Events menu
                processEventMenu();
                break;
            case 2: // Resources menu
                processResourceMenu();
                break;
            case 3: // Exit program
                cout << "\nThank you for using Merced Connect!\n";
                cout << "Goodbye!\n";
                exitProgram = true;
                break;
        }
    }
}

// Event menu processing loop - handles all event-related operations
void UserInterface::processEventMenu() {
    bool returnToMain = false;
    
    while (!returnToMain) {
        displayEventMenu();
        // Get user choice between 1-6
        int choice = getIntInput("Enter your choice (1-6): ", 1, 6);
        
        switch (choice) {
            case 1: // Display all events
                viewAllEvents();
                break;
            case 2: // Search for specific event
                searchEvent();
                break;
            case 3: // Add new event
                addNewEvent();
                break;
            case 4: // Sort events
                sortEvents();
                break;
            case 5: // Filter events by category
                filterEvents();
                break;
            case 6: // Return to main menu
                returnToMain = true;
                break;
        }
    }
}

// Resource menu processing loop - handles all resource-related operations
void UserInterface::processResourceMenu() {
    bool returnToMain = false;
    
    while (!returnToMain) {
        displayResourceMenu();
        // Get user choice between 1-5
        int choice = getIntInput("Enter your choice (1-5): ", 1, 5);
        
        switch (choice) {
            case 1: // Display all resources
                viewAllResources();
                break;
            case 2: // Search for specific resource
                searchResource();
                break;
            case 3: // Add new resource
                addNewResource();
                break;
            case 4: // Filter resources by type
                filterResources();
                break;
            case 5: // Return to main menu
                returnToMain = true;
                break;
        }
    }
}

// Displays all events and allows user to view detailed information
void UserInterface::viewAllEvents() const {
    vector<Event> allEvents = dataManager.getAllEvents();
    
    clearScreen();
    cout << "\n=== ALL EVENTS ===\n";
    
    if (allEvents.empty()) {
        cout << "No events found.\n";
    } else {
        // Display list of events with numbers
        for (size_t i = 0; i < allEvents.size(); i++) {
            cout << i + 1 << ". " << allEvents[i].getName() 
                      << " (" << allEvents[i].getDate() << ")\n";
        }
        
        // Allow user to select an event for detailed view
        int eventIndex = getIntInput("Enter event number to see details (0 to go back): ", 
                                    0, static_cast<int>(allEvents.size()));
        
        if (eventIndex > 0) {
            allEvents[eventIndex - 1].display();
        }
    }
    
    pressEnterToContinue();
}

// Searches for an event by name using binary search
void UserInterface::searchEvent() {
    clearScreen();
    cout << "\n=== SEARCH FOR AN EVENT ===\n";
    string name = getInput("Enter event name to search for: ");
    
    // Perform binary search for the event
    Event* event = dataManager.binarySearchEvent(name);
    
    if (event) {
        cout << "Event found!\n";
        event->display();
    } else {
        cout << "Event not found. Please check the spelling and try again.\n";
    }
    
    pressEnterToContinue();
}

// Adds a new event with user-provided details
void UserInterface::addNewEvent() {
    clearScreen();
    cout << "\n=== ADD NEW EVENT ===\n";
    
    string name = getInput("Enter event name: ");
    
    // Check for duplicate events
    if (dataManager.findEventByName(name)) {
        cout << "An event with this name already exists.\n";
        pressEnterToContinue();
        return;
    }
    
    // Validate date format
    string date;
    bool validDate = false;
    while (!validDate) {
        date = getInput("Enter event date (YYYY-MM-DD): ");
        validDate = Event::isValidDate(date);
        if (!validDate) {
            cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
        }
    }
    
    // Collect remaining event details
    string location = getInput("Enter event location: ");
    string description = getInput("Enter event description: ");
    string category = getInput("Enter event category: ");
    string organizer = getInput("Enter event organizer: ");
    string contactInfo = getInput("Enter contact information: ");
    
    // Create and add the new event
    Event newEvent(name, date, location, description, category, organizer, contactInfo);
    dataManager.addEvent(newEvent);
    
    cout << "Event added successfully!\n";
    pressEnterToContinue();
}

// Handles event sorting by different criteria
void UserInterface::sortEvents() {
    clearScreen();
    cout << "\n=== SORT EVENTS ===\n";
    cout << "1. Sort by Date\n";
    cout << "2. Sort by Name\n";
    cout << "3. Sort by Location\n";
    cout << "4. Go Back\n";
    
    int choice = getIntInput("Enter your choice (1-4): ", 1, 4);
    
    std::vector<Event> sortedEvents;
    std::string sortType;
    
    // Sort events based on user choice
    switch (choice) {
        case 1:
            sortedEvents = dataManager.sortEventsByDate();
            sortType = "Date";
            break;
        case 2:
            sortedEvents = dataManager.sortEventsByName();
            sortType = "Name";
            break;
        case 3:
            sortedEvents = dataManager.sortEventsByLocation();
            sortType = "Location";
            break;
        case 4:
            return;
    }
    
    // Display sorted events
    clearScreen();
    std::cout << "\n=== EVENTS SORTED BY " << sortType << " ===\n";
    
    if (sortedEvents.empty()) {
        std::cout << "No events found.\n";
    } else {
        // Show sorted list with relevant information
        for (size_t i = 0; i < sortedEvents.size(); i++) {
            std::cout << i + 1 << ". " << sortedEvents[i].getName() << " - ";
            
            if (sortType == "Date") {
                std::cout << sortedEvents[i].getDate();
            } else if (sortType == "Location") {
                std::cout << sortedEvents[i].getLocation();
            }
            
            std::cout << "\n";
        }
        
        // Allow viewing detailed information for a specific event
        int eventIndex = getIntInput("Enter event number to see details (0 to go back): ", 
                                    0, static_cast<int>(sortedEvents.size()));
        
        if (eventIndex > 0) {
            sortedEvents[eventIndex - 1].display();
        }
    }
    
    pressEnterToContinue();
}

// Filters and displays events by category
void UserInterface::filterEvents() {
    clearScreen();
    std::cout << "\n=== FILTER EVENTS BY CATEGORY ===\n";
    
    // Get all available categories
    std::vector<std::string> categories = dataManager.getAllEventCategories();
    
    if (categories.empty()) {
        std::cout << "No event categories found.\n";
        pressEnterToContinue();
        return;
    }
    
    // Display available categories
    std::cout << "Available categories:\n";
    for (size_t i = 0; i < categories.size(); i++) {
        std::cout << i + 1 << ". " << categories[i] << "\n";
    }
    
    // Let user select a category
    int categoryIndex = getIntInput("Select a category (0 to go back): ", 
                                  0, static_cast<int>(categories.size()));
    
    if (categoryIndex == 0) {
        return;
    }
    
    // Filter and display events in selected category
    std::string selectedCategory = categories[categoryIndex - 1];
    std::vector<Event> filteredEvents = dataManager.filterEventsByCategory(selectedCategory);
    
    clearScreen();
    std::cout << "\n=== EVENTS IN CATEGORY: " << selectedCategory << " ===\n";
    
    if (filteredEvents.empty()) {
        std::cout << "No events found in this category.\n";
    } else {
        // Display filtered events
        for (size_t i = 0; i < filteredEvents.size(); i++) {
            std::cout << i + 1 << ". " << filteredEvents[i].getName() 
                      << " (" << filteredEvents[i].getDate() << ")\n";
        }
        
        // Allow viewing detailed information
        int eventIndex = getIntInput("Enter event number to see details (0 to go back): ", 
                                    0, static_cast<int>(filteredEvents.size()));
        
        if (eventIndex > 0) {
            filteredEvents[eventIndex - 1].display();
        }
    }
    
    pressEnterToContinue();
}

// Displays all resources and allows viewing detailed information
void UserInterface::viewAllResources() const {
    std::vector<Resource> allResources = dataManager.getAllResources();
    
    clearScreen();
    std::cout << "\n=== ALL RESOURCES ===\n";
    
    if (allResources.empty()) {
        std::cout << "No resources found.\n";
    } else {
        // Display list of resources
        for (size_t i = 0; i < allResources.size(); i++) {
            std::cout << i + 1 << ". " << allResources[i].getName() 
                      << " (" << allResources[i].getType() << ")\n";
        }
        
        // Allow viewing detailed information
        int resourceIndex = getIntInput("Enter resource number to see details (0 to go back): ", 
                                      0, static_cast<int>(allResources.size()));
        
        if (resourceIndex > 0) {
            allResources[resourceIndex - 1].display();
        }
    }
    
    pressEnterToContinue();
}

// Searches for a resource by name using binary search
void UserInterface::searchResource() {
    clearScreen();
    std::cout << "\n=== SEARCH FOR A RESOURCE ===\n";
    std::string name = getInput("Enter resource name to search for: ");
    
    // Perform binary search
    Resource* resource = dataManager.binarySearchResource(name);
    
    if (resource) {
        std::cout << "Resource found!\n";
        resource->display();
    } else {
        std::cout << "Resource not found. Please check the spelling and try again.\n";
    }
    
    pressEnterToContinue();
}

// Adds a new resource with user-provided details
void UserInterface::addNewResource() {
    clearScreen();
    std::cout << "\n=== ADD NEW RESOURCE ===\n";
    
    std::string name = getInput("Enter resource name: ");
    
    // Check for duplicate resources
    if (dataManager.findResourceByName(name)) {
        std::cout << "A resource with this name already exists.\n";
        pressEnterToContinue();
        return;
    }
    
    // Collect resource details
    std::string type = getInput("Enter resource type (e.g., Food Bank, Shelter, Healthcare): ");
    std::string address = getInput("Enter resource address: ");
    std::string description = getInput("Enter resource description: ");
    std::string hours = getInput("Enter hours of operation: ");
    std::string contact = getInput("Enter contact information: ");
    
    // Create and add the new resource
    Resource newResource(name, type, address, description, hours, contact);
    dataManager.addResource(newResource);
    
    std::cout << "Resource added successfully!\n";
    pressEnterToContinue();
}

// Filters and displays resources by type
void UserInterface::filterResources() {
    clearScreen();
    std::cout << "\n=== FILTER RESOURCES BY TYPE ===\n";
    
    // Get all available resource types
    std::vector<std::string> types = dataManager.getAllResourceTypes();
    
    if (types.empty()) {
        std::cout << "No resource types found.\n";
        pressEnterToContinue();
        return;
    }
    
    // Display available types
    std::cout << "Available types:\n";
    for (size_t i = 0; i < types.size(); i++) {
        std::cout << i + 1 << ". " << types[i] << "\n";
    }
    
    // Let user select a type
    int typeIndex = getIntInput("Select a type (0 to go back): ", 
                              0, static_cast<int>(types.size()));
    
    if (typeIndex == 0) {
        return;
    }
    
    // Filter and display resources of selected type
    std::string selectedType = types[typeIndex - 1];
    std::vector<Resource> filteredResources = dataManager.filterResourcesByType(selectedType);
    
    clearScreen();
    std::cout << "\n=== RESOURCES OF TYPE: " << selectedType << " ===\n";
    
    if (filteredResources.empty()) {
        std::cout << "No resources found of this type.\n";
    } else {
        // Display filtered resources
        for (size_t i = 0; i < filteredResources.size(); i++) {
            std::cout << i + 1 << ". " << filteredResources[i].getName() << "\n";
        }
        
        // Allow viewing detailed information
        int resourceIndex = getIntInput("Enter resource number to see details (0 to go back): ", 
                                      0, static_cast<int>(filteredResources.size()));
        
        if (resourceIndex > 0) {
            filteredResources[resourceIndex - 1].display();
        }
    }
    
    pressEnterToContinue();
}

// Gets string input from user with a prompt
string UserInterface::getInput(const string& prompt) const {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// Gets validated integer input within a specified range
int UserInterface::getIntInput(const std::string& prompt, int min, int max) const {
    int input;
    bool validInput = false;
    
    do {
        std::cout << prompt;
        
        if (std::cin >> input) {
            if (input >= min && input <= max) {
                validInput = true;
            } else {
                std::cout << "Please enter a number between " << min << " and " << max << ".\n";
            }
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!validInput);
    
    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return input;
}

// Pauses program execution until user presses Enter
void UserInterface::pressEnterToContinue() const {
    cout << "\nPress Enter to continue...";
    cin.get();
}

// Clears the console screen
void UserInterface::clearScreen() const {
    // Uses multiple newlines for better portability
    std::cout << std::string(50, '\n');
}