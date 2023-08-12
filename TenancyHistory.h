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
    string property_id;
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
    void presetData(TenancyLinkedList** head, string tID, string tUName, string tName,  string pName, string sDate, string duration, string eDate, string rental, string status){
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
            cout << "Tenant Username\t\t: " << current->data.username << endl;
            cout << "Tenant Name\t\t: " << current->data.tenant_name << endl;
            cout << "Property ID\t\t: " << current->data.property_id << endl;
            cout << "Property Name\t\t: " << current->data.property_name << endl;
            cout << "Start Date\t\t: " << current->data.start_date << endl;
            cout << "Duration\t\t: " << current->data.duration << endl;
            cout << "End Date\t\t: " << current->data.end_date << endl;
            cout << "Rental\t\t\t: " << current->data.rental << endl;
            cout << "Tenancy Status\t\t: " << current->data.status << endl;
            cout << "----------------------------------------\n\n";
			current = current->next;
        }
    }

    // Display specific tenant's renting history with "To Be Approve" status
    void displayUserToBeApproveTenancy(TenancyLinkedList* head, string username) {
        TenancyLinkedList* current = head;
        cout << "To be Approve Tenancy History for " << username << "\n";
        cout << "=============================================\n";
        bool found = false;

        while (current != nullptr) {
            if (current->data.username == username && current->data.status == "To be Approve") {
                cout << "Tenancy ID\t\t: " << current->data.tenancyID << endl;
                cout << "Tenant Username\t\t: " << current->data.username << endl;
                cout << "Tenant Name\t\t: " << current->data.tenant_name << endl;
                cout << "Property ID\t\t: " << current->data.property_id << endl;
                cout << "Property Name\t\t: " << current->data.property_name << endl;
                cout << "Start Date\t\t: " << current->data.start_date << endl;
                cout << "Duration\t\t: " << current->data.duration << endl;
                cout << "End Date\t\t: " << current->data.end_date << endl;
                cout << "Rental\t\t\t: " << current->data.rental << endl;
                cout << "Tenancy Status\t\t: " << current->data.status << endl;
                cout << "----------------------------------------\n\n";
                found = true;
            }
            current = current->next;
            //add at menu
            // tenancy.displayUserToBeApproveTenancy(tenancy_root, "kante");
        }

        if (!found) {
            cout << "No to be approve tenancy history found for " << username << ".\n";
        }
    }

    // Display specific tenant's renting history with "To Pay" status
    void displayUserToPayTenancy(TenancyLinkedList* head, string username) {
        TenancyLinkedList* current = head;
        cout << "To Pay Tenancy History for " << username << "\n";
        cout << "=============================================\n";
        bool found = false;

        while (current != nullptr) {
            if (current->data.username == username && current->data.status == "To Pay") {
                cout << "Tenancy ID\t\t: " << current->data.tenancyID << endl;
                cout << "Tenant Username\t\t: " << current->data.username << endl;
                cout << "Tenant Name\t\t: " << current->data.tenant_name << endl;
                cout << "Property ID\t\t: " << current->data.property_id << endl;
                cout << "Property Name\t\t: " << current->data.property_name << endl;
                cout << "Start Date\t\t: " << current->data.start_date << endl;
                cout << "Duration\t\t: " << current->data.duration << endl;
                cout << "End Date\t\t: " << current->data.end_date << endl;
                cout << "Rental\t\t\t: " << current->data.rental << endl;
                cout << "Tenancy Status\t\t: " << current->data.status << endl;
                cout << "----------------------------------------\n\n";
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No to pay tenancy history found for " << username << ".\n";
        }
    }

    // Display specific tenant's renting history with "Confirmed" status
    void displayUserConfirmedTenancy(TenancyLinkedList* head, string username) {
        TenancyLinkedList* current = head;
        cout << "Confirmed Tenancy History for " << username << "\n";
        cout << "=============================================\n";
        bool found = false;

        while (current != nullptr) {
            if (current->data.username == username && current->data.status == "Confirmed") {
                cout << "Tenancy ID\t\t: " << current->data.tenancyID << endl;
                cout << "Tenant Username\t\t: " << current->data.username << endl;
                cout << "Tenant Name\t\t: " << current->data.tenant_name << endl;
                cout << "Property ID\t\t: " << current->data.property_id << endl;
                cout << "Property Name\t\t: " << current->data.property_name << endl;
                cout << "Start Date\t\t: " << current->data.start_date << endl;
                cout << "Duration\t\t: " << current->data.duration << endl;
                cout << "End Date\t\t: " << current->data.end_date << endl;
                cout << "Rental\t\t\t: " << current->data.rental << endl;
                cout << "Tenancy Status\t: " << current->data.status << endl;
                cout << "----------------------------------------\n\n";
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No confirmed tenancy history found for " << username << ".\n";
        }
    }


    // Function to check if the propertyID exists in the Tenancy History with either "Confirmed" or "To Pay" status
    bool checkPropertyStatusInTenancy(TenancyLinkedList* head, string propertyID) {
        TenancyLinkedList* current = head;
        while (current != nullptr) {
            if (current->data.property_id == propertyID && (current->data.status == "Confirmed" || current->data.status == "To Pay")) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};
