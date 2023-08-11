#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
using namespace std;

#include "Tenant.h"
#include "Manager.h"
#include "Admin.h"
#include "Property.h"
#include "FavouriteProperty.h"
#include "TenancyHistory.h"

// struct LogOutAndQuit {
//     void logOut() {
//         int status;
//         char yesNo;
//         status = remove("loggedInUser.txt");
//         if (status == 0) {
//             cout << "\nYou are logged out.\n";
//             quitProgram();
//         } else {
//             cout << "\nNo logged in account.\n";
//             quitProgram();
//         }
//     }

//     void quitProgram() {
//         cout << "\n===================================================\n";
//         cout << " Thank You for Using APH Accomodation Rent System!\n";
//         cout << "===================================================\n\n";
//     }
// };

struct ManagerInterface {
    void managerDashboard(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        int dashboardOption;
        cout << "Welcome to Manager Dashboard\n";
        cout << "=============================\n\n";
        cout << "1. View All Tenant\n";
        cout << "2. Search Tenant\n";
        cout << "3. Delete Tenant Account\n";
        cout << "4. Manage Tenancy\n";
        cout << "5. View Report\n\n";
        while (true) {
            
            cout << "Please enter your option: ";
            cin >> dashboardOption;

            if (cin.fail() || dashboardOption < 1 || dashboardOption > 5) {
                cout << "\n\nInvalid input. Please enter a number between 1 and 5.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (dashboardOption == 1) {
                managerViewAllTenantMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root);

            } else if (dashboardOption == 2) {
                managerSearchMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root);

            }
            
            break;
        }
    }

    void managerViewAllTenantMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root){
        system("CLS");
        TenantTree tenant;
        tenant.dispAllTenant(tenant_root);

        cout << "1. Back to Main Menu\n\n";

        int option;
        cout << "Please select an option: ";
        cin >> option;

        if (option == 1){
            managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        }

    }


    void managerSearchMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root){
        int searchOption;
        system("CLS");
        cout << "Search Tenant\n";
        cout << "==================\n\n";
        cout << "1. Search by Username\n";
        cout << "2. Search by Tenant Name\n";
        cout << "3. Back to Main Menu\n";
        cout << "4. Log Out\n\n";
        
        while (true){
           
            cout << "Please enter an option: ";
            cin >> searchOption;
            

            if (cin.fail() || searchOption < 1 || searchOption > 3) {
                cout << "\n\nInvalid input. Please enter a number between 1 and 3.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (searchOption == 1){
                char continueSearch;
                do{
                    system("CLS");
                    cout << "Please enter username want to search: ";

                    string searchUsername;
                    cin >> searchUsername;
                    // getline(cin, searchUsername);

                    cout << "\nSearch Result for " << searchUsername << "\n";
                    cout << "................................................\n\n";
                
                    TenantTree tenant;
                    bool found = tenant.tenantUsernameSearch(tenant_root, searchUsername);
                
                    if (!found) {
                    cout << "No result found" << endl;
                    }
                    cout << "\n\nDo you want to continue searching? (Y/N): ";
                    cin >> continueSearch;
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                } 
                while (toupper(continueSearch) == 'Y');
                managerSearchMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                
                
            }
            
            else if (searchOption == 2) {
                char continueSearchName;
                do {
                    system("CLS");
                    cout << "Please enter name want to search: ";

                    string searchName;
                    cin.ignore(); // Ignore the newline character left in the input buffer
                    getline(cin, searchName); // Read the entire line

                    cout << "\nSearch Result for " << searchName << "\n";
                    cout << "................................................\n\n";
                
                    TenantTree tenant;
                    bool found = tenant.tenantNameSearch(tenant_root, searchName);
                
                    if (!found) {
                    cout << "No result found" << endl;
                    }

                    cout << "\n\nDo you want to continue searching? (Y/N): ";
                    cin >> continueSearchName;

                } 
                while (toupper(continueSearchName) == 'Y');
                managerSearchMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                
                
                
            } else if (searchOption == 3) {
                system("CLS");
                managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
            }
        }
    }
};

struct AdminInterface {
    TenantTree tenant;
    ManagerTree manager;
    Admin admin;
    
    void adminDashboard(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        int dashboardOption;

        cout << " Welcome to Admin Dashboard\n";
        cout << "============================\n\n";
        cout << "1. Add New Manager\n";
        cout << "2. Modify Manager Status\n";
        cout << "3. Modify Tenant Status\n";
        cout << "4. View Tenant\n";
        cout << "5. View Property\n";
        cout << "6. Log Out\n";

        while (true) {
            cout << "Please enter your option: ";
            cin >> dashboardOption;

            if (cin.fail() || dashboardOption < 1 || dashboardOption > 6) {
                cout << "\n\nInvalid input. Please enter a number between 1 and 6.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (dashboardOption == 1) {

            } else if (dashboardOption == 2) {

            } else if (dashboardOption == 3) {

            } else if (dashboardOption == 4) {

            } else if (dashboardOption == 5) {

            } else {
                // logOut();
            }
        }
    }
};
