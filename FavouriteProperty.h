#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

struct FavouriteProperty{
    string username;
    string propId;
};

struct FavouritePropertyLinkedList
{
    FavouriteProperty data;
    FavouritePropertyLinkedList* prev;
    FavouritePropertyLinkedList* next;

    PropertyTree property;

    // Preset Favourite Property Data
    void presetData(FavouritePropertyLinkedList** head, string uName, string pID) {
        FavouritePropertyLinkedList* newFav = new FavouritePropertyLinkedList;
        newFav->data.username = uName;
        newFav->data.propId = pID;
        newFav->prev = nullptr;
        newFav->next = nullptr;

        if (*head == nullptr) {
            *head = newFav;
        } else {
            FavouritePropertyLinkedList* current = *head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newFav;
            newFav->prev = current;
        }
    }

    // Display All Users Favourite Property
    void displayAllFavourite(FavouritePropertyLinkedList* head) {
        FavouritePropertyLinkedList* current = head;
        cout << "All Favourite Properties\n";
        cout << "========================\n";
        while (current != nullptr) {
            cout << "Username\t\t\t\t: " << current->data.username << endl;
            cout << "Favourite Property ID\t: " << current->data.propId << endl;
            cout << "---------------------------------------\n\n";
            current = current->next;
        }
    }

    // Display facourite specific user's favourite property
    void displayUserFavourite(FavouritePropertyLinkedList* head, string username, PropertyTree* root) {
    FavouritePropertyLinkedList* current = head;
    cout << "\nFavourite Properties for " << username << "\n";
    cout << "============================================\n\n";
    bool found = false;
    
    while (current != nullptr) {
        if (current->data.username == username) {
            string propertyID = current->data.propId;
            // Search for the property in the binary search tree
            PropertyTree* propertyNode = property.getPropertyInfo(root, propertyID);
            if (propertyNode != nullptr) {
                // Display the property information
                Property property = propertyNode->data;
                cout << "Property ID: " << property.propertyID << endl
                    << "Property Name: " << property.propertyName << endl
                    << "Completion Year: " << property.completion_year << endl
                    << "Monthly Rental: " << property.monthly_rental << endl
                    << "Location: " << property.location << endl
                    << "Property Type: " << property.propertyType << endl
                    << "Rooms: " << property.rooms << endl
                    << "Parking: " << property.parking << endl
                    << "Bathroom: " << property.bathroom << endl
                    << "Size: " << property.size << endl
                    << "Furnished: " << property.furnished << endl
                    << "Facilities: " << property.facilities << endl
                    << "Additional Facilities: " << property.additional_facilities << endl
                    << "Region: " << property.region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                found = true;
            }
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "No favourite properties found for " << username << ".\n";
    }

    // FavouritePropertyLinkedList favourite;
    // favourite.displayUserFavourite(fav_root, "Suyinsss", prop_root);
}

    void displayTop10Favourite(FavouritePropertyLinkedList* head, PropertyTree* root) {
        map<string, int> propertyCounts;
        PropertyTree property;
        // Counting the favorites for each property ID
        FavouritePropertyLinkedList* current = head;
        int maxIDLength = 0, maxNameLength = 0;
        while (current != nullptr) {
            propertyCounts[current->data.propId]++; // Increment count for this property ID
            maxIDLength = max(maxIDLength, (int)current->data.propId.length());
            string propertyID = current->data.propId;
            PropertyTree* propertyNode = property.getPropertyInfo(root, propertyID);
            maxNameLength = max(maxNameLength, (int)propertyNode->data.propertyName.length());
            current = current->next;
        }

        // Sorting the property counts
        vector<pair<string, int>> sortedCounts(propertyCounts.begin(), propertyCounts.end());
        sort(sortedCounts.begin(), sortedCounts.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return b.second < a.second;
            });

        // Displaying the top 10 favorite properties
        cout << "Top 10 Favourite Properties\n";
        cout << "==========================================================\n";
        cout << left << setw(maxIDLength + 5) << "Property ID" << setw(maxNameLength + 5) << "Name" << setw(12) << "Total Favorites\n";
        cout << string(maxIDLength + maxNameLength + 25, '=') << '\n';
        for (int i = 0; i < 10 && i < sortedCounts.size(); i++) {
            string propertyID = sortedCounts[i].first;
            PropertyTree* propertyNode = property.getPropertyInfo(root, propertyID);
            string propertyName = propertyNode->data.propertyName;
            cout << left << setw(maxIDLength + 5) << propertyID << setw(maxNameLength + 5) << propertyName << setw(12) << sortedCounts[i].second << endl;
        }
    }

    bool isInFavouriteList(FavouritePropertyLinkedList* fav_root, string username, string propertyID) {
        FavouritePropertyLinkedList* current = fav_root;

        while (current != nullptr) {
            if (current->data.username == username && current->data.propId == propertyID) {
                return true;
            }
            current = current -> next;
        }

        return false;
    }
};
