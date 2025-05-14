// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <iostream>
using namespace std;
//Resource class represents community resources in Merced, includes information like name, type of business, address, description,hours of operation, and contact information.
class Resource {
private:
    string name; //These are very simple examples, but I would also like it to have listings for local events, concerts, pop-ups, etc. 
    string type;        // Example: "Food Bank", "Shelter", "Healthcare"
    string address;     // Example: "3600 M St, Merced, CA" (No Zip Codes for now)
    string description; // Example: For example "Regal Theaters" can have something like "Theater complex with multiple screens featuring new release films, plush seating & concession stand." similar to the current description on Google
    string hoursOfOperation; // Example: "Mon-Sat: 10:00AM to 8:00 PM, Sunday: Closed"
    string contactInfo; // Example: "867-5309"

public:
    // Constructors
    Resource();
    Resource(const string& name, const string& type, 
             const string& address, const string& description,
             const string& hoursOfOperation, const string& contactInfo);
    
    // Getters
    string getName() const;
    string getType() const;
    string getAddress() const;
    string getDescription() const;
    string getHoursOfOperation() const;
    string getContactInfo() const;
    
    // Setters
    void setName(const string& name);
    void setType(const string& type);
    void setAddress(const string& address);
    void setDescription(const string& description);
    void setHoursOfOperation(const string& hoursOfOperation);
    void setContactInfo(const string& contactInfo);
    
    // Display resource details
    void display() const;
};

#endif