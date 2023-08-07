#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct TenancyHistory
{
    string tenancyID;
    string username;
    string tenant_name;
    string property_name;
    string start_date;
    string duration;
    string end_date;
    string rental;
    string status;
};

struct TenancyLinkedList
{
    TenancyHistory data;
    TenancyLinkedList* prev;
    TenancyLinkedList* next;

    // Preset Tenancy History Data
    void presetData(TenancyLinkedList** head, string tID, string tUName, string tName, string pName, string sDate, string duration, string eDate, string rental, string status){
        TenancyLinkedList* newTenancy = new TenancyLinkedList;
        newTenancy->data.tenancyID = tID;
        newTenancy->data.username = tUName;
        newTenancy->data.tenant_name = tName;
        newTenancy->data.property_name = pName;
        newTenancy->data.start_date = sDate;
        newTenancy->data.duration = duration;
        newTenancy->data.end_date = eDate;
        newTenancy->data.rental = rental;
        newTenancy->data.status = status;
        newTenancy->prev = nullptr;
        newTenancy->next = nullptr;

        if (*head == nullptr) {
            *head = newTenancy;
        } else {
            TenancyLinkedList* current = *head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newTenancy;
            newTenancy->prev = current;
        }
    }

    // Diplay All Tenancy History
    void displayTenancyHistory(TenancyLinkedList* head) {
        TenancyLinkedList* current = head;
        cout << "All Tenancy History\n";
        cout << "===================\n";
        while (current != nullptr) {
            cout << "Tenancy ID\t\t: " << current->data.tenancyID << endl;
			cout << "Tenant Username\t: " << current->data.username << endl;
			cout << "Tenant Name\t\t: " << current->data.tenant_name << endl;
			cout << "Property Name\t: " << current->data.property_name << endl;
			cout << "Start Date\t\t: " << current->data.start_date << endl;
			cout << "Duration\t\t: " << current->data.duration << endl;
			cout << "End Date\t\t: " << current->data.end_date << endl;
			cout << "Rental\t\t\t: " << current->data.rental << endl;
			cout << "Tenancy Status\t: " << current->data.status << endl;
			cout << "----------------------------------------\n\n";
			current = current->next;
        }
    }
};
