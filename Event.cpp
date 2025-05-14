// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#include "Event.h"
#include <iostream>
#include <iomanip>
#include <regex>
using namespace std;

// Default constructor
Event::Event() : 
    name(""), date(""), location(""), description(""),
    category(""), organizer(""), contactInfo("") {}

// Full constructor
Event::Event(const string& name, const string& date, 
             const string& location, const string& description,
             const string& category, const string& organizer,
             const string& contactInfo) :
    name(name), date(date), location(location), description(description),
    category(category), organizer(organizer), contactInfo(contactInfo) {}

// Get event details
string Event::getName() const { return name; }
string Event::getDate() const { return date; }
string Event::getLocation() const { return location; }
string Event::getDescription() const { return description; }
string Event::getCategory() const { return category; }
string Event::getOrganizer() const { return organizer; }
string Event::getContactInfo() const { return contactInfo; }

// Set event details
void Event::setName(const string& name) { this->name = name; }
void Event::setDate(const string& date) { this->date = date; }
void Event::setLocation(const string& location) { this->location = location; }
void Event::setDescription(const string& description) { this->description = description; }
void Event::setCategory(const string& category) { this->category = category; }
void Event::setOrganizer(const string& organizer) { this->organizer = organizer; }
void Event::setContactInfo(const string& contactInfo) { this->contactInfo = contactInfo; }

// Show event info
void Event::display() const {
    cout << "\n===== EVENT DETAILS =====\n";
    cout << "Name: " << name << "\n";
    cout << "Date: " << date << "\n";
    cout << "Location: " << location << "\n";
    cout << "Category: " << category << "\n";
    cout << "Organizer: " << organizer << "\n";
    cout << "Contact: " << contactInfo << "\n";
    cout << "\nDescription:\n" << description << "\n";
    cout << "=========================\n";
}

// Check date format
bool Event::isValidDate(const string& date) {
    regex datePattern("\\d{4}-\\d{2}-\\d{2}");
    
    if (!regex_match(date, datePattern)) {
        return false;
    }
    
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    
    // Basic date checks
    if (year < 2023 || year > 2030) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // Month length check
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            return false;
        }
    }
    
    return true;
}