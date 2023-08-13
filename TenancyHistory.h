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
    void presetData(TenancyLinkedList** head, string tID, string tUName, string tName,  string pID, string pName, string sDate, string duration, string eDate, string rental, string status){
        TenancyLinkedList* newTenancy = new TenancyLinkedList;
        newTenancy->data.tenancyID = tID;
        newTenancy->data.username = tUName;
        newTenancy->data.tenant_name = tName;
        newTenancy->data.property_id = pID;
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
        cout << "===================\n\n";
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

    // Display specific tenant's renting history, excluding "Rejected" status
    void displayTenancy(TenancyLinkedList* head, string username) {
        TenancyLinkedList* current = head;
        cout << "\nTenancy Status\n";
        cout << "=============================================\n\n";
        bool found = false;

        while (current != nullptr) {
            if (current->data.username == username && current->data.status != "Completed") {
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
            cout << "\nNo tenancy found.\n";
        }
    }

// Display specific tenant's renting history with "Pending Manager Approval" status
    void displayPendingApprovalTenancy(TenancyLinkedList* head, string username) {
        TenancyLinkedList* current = head;
        cout << "\nPending Manager Approval Tenancy\n";
        cout << "=============================================\n\n";
        bool found = false;

        while (current != nullptr) {
            if (current->data.username == username && current->data.status == "Pending Manager Approval") {
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
            cout << "\nNo pending manager approval tenancy found.\n";
        }
    }

    // Display specific tenant's renting history with "Completed" status
    void displayCompletedTenancy(TenancyLinkedList* head, string username) {
        TenancyLinkedList* current = head;
        cout << "\nCompleted Tenancy History\n";
        cout << "=============================================\n\n";
        bool found = false;

        while (current != nullptr) {
            if (current->data.username == username && current->data.status == "Completed") {
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
            cout << "\nNo completed tenancy history found.\n";
        }
    }


    // Function to check if the propertyID exists in the Tenancy History with either "Confirmed" or "To Pay" status
    bool checkPropertyStatusInTenancy(TenancyLinkedList* head, string propertyID) {
        TenancyLinkedList* current = head;
        while (current != nullptr) {
            if (current->data.property_id == propertyID && (current->data.status == "Confirmed" || current->data.status == "Pending Payment")) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    string generateTenancyID(TenancyLinkedList* tenancy_root) {
        int count = 0;
        TenancyLinkedList* current = tenancy_root;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return "R" + to_string(count + 1); // Increment count for the new ID
    }
};
