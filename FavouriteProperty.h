#include <iostream>
#include <string>
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
    cout << "Favourite Properties for " << username << "\n";
    cout << "========================\n";
    bool found = false;
    
    while (current != nullptr) {
        if (current->data.username == username) {
            string propertyID = current->data.propertyID;
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
};
