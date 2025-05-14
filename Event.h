// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
// Event covers community events in Merced. Stores information about the event including name, date, location, description, category, and organizer.
class Event {
private:
    string name;
    string date;        // Date is formatted in YEAR - MONTH - DAY
    string location;
    string description;
    string category;
    string organizer;
    string contactInfo;

public:
    // Constructors
    Event();
    Event(const string& name, const string& date, 
          const string& location, const string& description,
          const string& category, const string& organizer,
          const string& contactInfo);
    
    // Getters
    string getName() const;
    string getDate() const;
    string getLocation() const;
    string getDescription() const;
    string getCategory() const;
    string getOrganizer() const;
    string getContactInfo() const;
    
    // Setters
    void setName(const string& name);
    void setDate(const string& date);
    void setLocation(const string& location);
    void setDescription(const string& description);
    void setCategory(const string& category);
    void setOrganizer(const string& organizer);
    void setContactInfo(const string& contactInfo);
    
    // Display event details
    void display() const;
    
    // Static validation methods
    static bool isValidDate(const string& date);
};

#endif // EVENT_H