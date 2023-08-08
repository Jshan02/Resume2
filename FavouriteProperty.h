#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct FavouriteProperty{
    string username;
    string password;
};

struct FavouritePropertyLinkedList
{
    FavouriteProperty data;
    FavouritePropertyLinkedList* prev;
    FavouritePropertyLinkedList* next;

    // Preset Favourite Property Data
    void presetData(FavouritePropertyLinkedList** head, string uName, string pID) {
        FavouritePropertyLinkedList* newFav = new FavouritePropertyLinkedList;
        newFav->data.username = uName;
        newFav->data.password = pID;
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
            cout << "Favourite Property ID\t: " << current->data.password << endl;
            cout << "---------------------------------------\n\n";
            current = current->next;
        }
    }
};
