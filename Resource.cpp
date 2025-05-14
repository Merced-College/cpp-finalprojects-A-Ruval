// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#include "Resource.h"
#include <iostream>
#include <iomanip>
using namespace std;

Resource::Resource() : 
    name(""), type(""), address(""), description(""),
    hoursOfOperation(""), contactInfo("") {}

Resource::Resource(const string& name, const string& type, 
                  const string& address, const string& description,
                  const string& hoursOfOperation, const string& contactInfo) :
    name(name), type(type), address(address), description(description),
    hoursOfOperation(hoursOfOperation), contactInfo(contactInfo) {}

// Getters
string Resource::getName() const { return name; }
string Resource::getType() const { return type; }
string Resource::getAddress() const { return address; }
string Resource::getDescription() const { return description; }
string Resource::getHoursOfOperation() const { return hoursOfOperation; }
string Resource::getContactInfo() const { return contactInfo; }

// Setters
void Resource::setName(const string& name) { this->name = name; }
void Resource::setType(const string& type) { this->type = type; }
void Resource::setAddress(const string& address) { this->address = address; }
void Resource::setDescription(const string& description) { this->description = description; }
void Resource::setHoursOfOperation(const string& hoursOfOperation) { this->hoursOfOperation = hoursOfOperation; }
void Resource::setContactInfo(const string& contactInfo) { this->contactInfo = contactInfo; }

// Display resource details. Using a basic text interface 
void Resource::display() const {
    cout << "\n===== RESOURCE DETAILS =====\n";
    cout << "Name: " << name << "\n";
    cout << "Type: " << type << "\n";
    cout << "Address: " << address << "\n";
    cout << "Hours: " << hoursOfOperation << "\n";
    cout << "Contact: " << contactInfo << "\n";
    cout << "\nDescription:\n" << description << "\n";
    cout << "============================\n";
}