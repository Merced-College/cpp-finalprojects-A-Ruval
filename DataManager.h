// Alexander Ruvalcaba -- 5-13-25 -- CPSC-25 -- Final Project: Merced Connect
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "Event.h"
#include "Resource.h"
using namespace std;
// DataManager is responsible for managing all data operations. It implements algorithms for searching, sorting, and filtering data.
class DataManager {
private:
    vector<Event> events;
    vector<Resource> resources;
    map<string, vector<Event>> eventsByCategory;
    map<string, vector<Resource>> resourcesByType;
    
    // Initialize with some sample data
    void initializeSampleData();
    
    // Helper method for binary search
    int findEventIndexByName(const string& name);
    int findResourceIndexByName(const string& name);
    

    
public:
    DataManager();
    
    // Event management
    void addEvent(const Event& event);
    bool removeEvent(const string& name);
    Event* findEventByName(const string& name);
    vector<Event> getAllEvents() const;
    
    // Resource management
    void addResource(const Resource& resource);
    bool removeResource(const string& name);
    Resource* findResourceByName(const string& name);
    vector<Resource> getAllResources() const;
    
    // Algorithm 1: Binary Search (O(log n))
    // Finds an event or resource by name using binary search
    Event* binarySearchEvent(const string& name);
    Resource* binarySearchResource(const string& name);
    
    // Algorithm 2: Quick Sort (O(n log n))
    // Sorts events by date, name, or location
    vector<Event> sortEventsByDate();
    vector<Event> sortEventsByName();
    vector<Event> sortEventsByLocation();
    
    // Algorithm 3: Linear Filtering (O(n))
    // Filters events or resources by category/type
    vector<Event> filterEventsByCategory(const string& category);
    vector<Resource> filterResourcesByType(const string& type);
    
    // Get all available categories and types
    vector<string> getAllEventCategories() const;
    vector<string> getAllResourceTypes() const;
};

#endif // DATA_MANAGER_H