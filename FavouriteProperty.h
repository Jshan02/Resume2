#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct FavouritePropertyLinkedList
{
    string username;
    string propertyID;

    FavouritePropertyLinkedList* prev;
    FavouritePropertyLinkedList* next;

    // Preset Favourite Property Data
    void presetData(FavouritePropertyLinkedList** head, string uName, string pID) {
        FavouritePropertyLinkedList* newFav = new FavouritePropertyLinkedList;
        newFav->username = uName;
        newFav->propertyID = pID;
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
            cout << "Username\t\t\t\t: " << current->username << endl;
            cout << "Favourite Property ID\t: " << current->propertyID << endl;
            cout << "---------------------------------------\n\n";
            current = current->next;
        }
    }
};
