// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#include "DataManager.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

DataManager::DataManager() {
    // Initialize with sample data
    initializeSampleData();
}

void DataManager::initializeSampleData() {
    // Add some initial events
    Event event1("Merced Farmers Market", "2025-5-15", "16th St. and, Canal St", 
                "Local farmers selling fresh produce and handmade goods.", 
                "Community", "Merced City", "info@mercedmarket.org");
    
    Event event2("Art Hop", "2025-5-22", "Main Street", 
                "Evening of art, music, and culture in downtown Merced.", 
                "Arts", "Merced Arts Council", "arts@merced.org");
    
    Event event3("Merced County Fair", "2025-6-4", "900 Martin Luther King Jr Way", 
                "Fairground providing rides, food, and entertainment, including bands and events.", 
                "Fun", "Merced City", "fair@mercedcounty.org");
    
    // Add some initial resources
    Resource resource1("Merced Food Bank", "Food Assistance", 
                      "2000 W Olive Ave, Merced", 
                      "Provides food assistance to those in need.", 
                      "Mon-Fri: 9AM-3PM", "209-726-3663");
    
    Resource resource2("Golden Valley Health Center", "Healthcare", 
                      "3940 Sandpiper Ave, Merced", 
                      "Low-cost healthcare services for residents.", 
                      "Mon-Sat: 8AM-8PM", "209-722-4842");
    
    Resource resource3("D Street Homeless Shelter", "Shelter", 
                      "317 E 15th St, Merced", 
                      "The D St. Homeless Shelter is open all year to homeless single men and women over the age of 18. Individuals are allowed to stay for 160 days per calendar year. On-site health clinic and mental health services are available.", 
                      "24/7", "209-725-8188");
    
    // Add events and resources to vectors
    addEvent(event1);
    addEvent(event2);
    addEvent(event3);
    
    addResource(resource1);
    addResource(resource2);
    addResource(resource3);
}

void DataManager::addEvent(const Event& event) {
    events.push_back(event);
    
    // Also add to the category map
    string category = event.getCategory();
    eventsByCategory[category].push_back(event);
    
    // Sort the events vector by name to maintain order for binary search
    sort(events.begin(), events.end(), 
              [](const Event& a, const Event& b) { 
                  return a.getName() < b.getName(); 
              });
}

bool DataManager::removeEvent(const string& name) {
    int index = findEventIndexByName(name);
    if (index == -1) return false;
    
    // Remove from category map
    string category = events[index].getCategory();
    auto& categoryEvents = eventsByCategory[category];
    categoryEvents.erase(
        remove_if(categoryEvents.begin(), categoryEvents.end(),
                      [&name](const Event& e) { return e.getName() == name; }),
        categoryEvents.end());
    
    // Remove from main vector
    events.erase(events.begin() + index);
    return true;
}

Event* DataManager::findEventByName(const string& name) {
    int index = findEventIndexByName(name);
    if (index == -1) return nullptr;
    return &events[index];
}

vector<Event> DataManager::getAllEvents() const {
    return events;
}

void DataManager::addResource(const Resource& resource) {
    resources.push_back(resource);
    
    // Also add to the type map
    string type = resource.getType();
    resourcesByType[type].push_back(resource);
    
    // Sort the resources vector by name to maintain order for binary search
    sort(resources.begin(), resources.end(), 
              [](const Resource& a, const Resource& b) { 
                  return a.getName() < b.getName(); 
              });
}

bool DataManager::removeResource(const string& name) {
    int index = findResourceIndexByName(name);
    if (index == -1) return false;
    
    // Remove from type map
    string type = resources[index].getType();
    auto& typeResources = resourcesByType[type];
    typeResources.erase(
        remove_if(typeResources.begin(), typeResources.end(),
                      [&name](const Resource& r) { return r.getName() == name; }),
        typeResources.end());
    
    // Remove from main vector
    resources.erase(resources.begin() + index);
    return true;
}

Resource* DataManager::findResourceByName(const string& name) {
    int index = findResourceIndexByName(name);
    if (index == -1) return nullptr;
    return &resources[index];
}

vector<Resource> DataManager::getAllResources() const {
    return resources;
}

// Algorithm 1: Binary Search (O(log n))
int DataManager::findEventIndexByName(const string& name) {
    int left = 0;
    int right = events.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (events[mid].getName() == name) {
            return mid;
        }
        
        if (events[mid].getName() < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // Not found
}

Event* DataManager::binarySearchEvent(const string& name) {
    int index = findEventIndexByName(name);
    if (index == -1) return nullptr;
    return &events[index];
}

int DataManager::findResourceIndexByName(const string& name) {
    int left = 0;
    int right = resources.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (resources[mid].getName() == name) {
            return mid;
        }
        
        if (resources[mid].getName() < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // Not found
}

Resource* DataManager::binarySearchResource(const string& name) {
    int index = findResourceIndexByName(name);
    if (index == -1) return nullptr;
    return &resources[index];
}

// Algorithm 2: Quick Sort (O(n log n))
vector<Event> DataManager::sortEventsByDate() {
    vector<Event> sortedEvents = events;
    
    // Using lambda for comparison in sort function
    sort(sortedEvents.begin(), sortedEvents.end(), 
              [](const Event& a, const Event& b) { 
                  return a.getDate() < b.getDate(); 
              });
    
    return sortedEvents;
}

vector<Event> DataManager::sortEventsByName() {
    vector<Event> sortedEvents = events;
    
    sort(sortedEvents.begin(), sortedEvents.end(), 
              [](const Event& a, const Event& b) { 
                  return a.getName() < b.getName(); 
              });
    
    return sortedEvents;
}

vector<Event> DataManager::sortEventsByLocation() {
    vector<Event> sortedEvents = events;
    
    sort(sortedEvents.begin(), sortedEvents.end(), 
              [](const Event& a, const Event& b) { 
                  return a.getLocation() < b.getLocation(); 
              });
    
    return sortedEvents;
}

// Algorithm 3: Linear Filtering (O(n))
vector<Event> DataManager::filterEventsByCategory(const string& category) {
    // Use the map for O(1) access to category
    if (eventsByCategory.find(category) != eventsByCategory.end()) {
        return eventsByCategory[category];
    }
    
    // If category not found in map, return empty vector
    return vector<Event>();
}

vector<Resource> DataManager::filterResourcesByType(const string& type) {
    // Use the map for O(1) access to type
    if (resourcesByType.find(type) != resourcesByType.end()) {
        return resourcesByType[type];
    }
    
    // If type not found in map, return empty vector
    return vector<Resource>();
}

vector<string> DataManager::getAllEventCategories() const {
    vector<string> categories;
    for (const auto& pair : eventsByCategory) {
        categories.push_back(pair.first);
    }
    return categories;
}

vector<string> DataManager::getAllResourceTypes() const {
    vector<string> types;
    for (const auto& pair : resourcesByType) {
        types.push_back(pair.first);
    }
    return types;
}