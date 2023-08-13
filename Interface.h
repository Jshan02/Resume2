#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <windows.h> // For Sleep on Windows
#endif

#include "Tenant.h"
#include "Manager.h"
#include "Admin.h"
#include "Property.h"
#include "FavouriteProperty.h"
#include "TenancyHistory.h"
using namespace std;

struct TenantInterface {
    TenantTree tenant;
    PropertyTree prop;
    FavouritePropertyLinkedList fav;
    TenancyLinkedList tenancy;
    
    void tenantDashboard(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root, int autoOption = 0) {
        int dashboardOption = autoOption;
        if (dashboardOption == 0) {
            cout << " Welcome to Tenant Dashboard\n";
            cout << "=============================\n\n";
            cout << "1. View All Properties\n";
            cout << "2. Sort Properties by Monthly Rent, Location, and Size as per Square Feet in Descending Order\n";
            cout << "3. Search and Display Properties\n";
            cout << "4. View Favourite Properties\n";
            cout << "5. View Rent Request Status\n";
            cout << "6. View Property Renting History\n";
            cout << "7. Deactivate Account\n";
            cout << "8. Logout\n\n";

            while (true) {
                cout << "Please enter your option: ";
                cin >> dashboardOption;

                if (cin.fail() || dashboardOption < 1 || dashboardOption > 8) {
                    cout << "\nInvalid input. Please enter a number between 1 and 7.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

            if (dashboardOption == 1) {                 // Display All Properties
                system("CLS");
                displayAllProperty(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root, 1);

            } else if (dashboardOption == 2) {          // Sort n Display + Mark Fav
                sortProperties(tenant_root, prop_root, fav_root, tenancy_root, propertyArray, sort_root);

                } else if (dashboardOption == 3) {          // Search n Display + Mark Fav
                    

            } else if (dashboardOption == 4) {          // View Favourite + Option to place rent request
                favouritePropertyMenu(fav_root, prop_root, tenancy_root, propertyArray, tenant_root, sort_root);

            } else if (dashboardOption == 5) {          // Check Rent Request Status (Wait for Approval / Wait for Payment) + Option to Make Payment if Wait for Payment
                system("CLS");
                rentRequestStatusMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);

            } else if (dashboardOption == 6) {          // view all completed status
                system("CLS");
                string username = getCurrentUsername();
                tenancy.displayCompletedTenancy(tenancy_root, username);
                completedTenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);

                } else if (dashboardOption == 7) {
                    tenantDeactivateMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                }
                break;
            }
        }
    }

    // display propety data
    void displayAllProperty(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root, int currentPage) {
        // int page = 1;
        int page = currentPage; // Initialize with the currentPage argument
        int totalPages = (prop_root->countProperties(prop_root) + 9) / 10; // Calculate the total number of pages

        while (true) {
            prop_root->navigateProperties(prop_root, page);
            cout << "Page " << page << " of " << totalPages << endl << endl;

            cout << "1. Next 10 properties\n";
            cout << "2. Previous 10 Properties\n";
            cout << "3. Add to favourite\n";
            cout << "4. Back to Main Menu\n\n";
            cout << "Please select an option: ";
            int choice;
            cin >> choice;

            if (choice == 1 && page < totalPages) {
                page++;
            }
            else if (choice == 2 && page > 1) {
                page--;
            }
            else if (choice == 3) {
                addFavouritePropertyMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root, page);
                break;
            }
            else if (choice == 4) {
                system("CLS");
                tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                break;
            }
        }
    }

    // Sort properties menu
    void sortProperties(TenantTree* tenant_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, PropertyTree* sort_root) {
        system("CLS");
        // vector<Property> propertySortArray = propertyArray;
        // prop.quickSort(propertySortArray, 0, propertyArray.size()-1);
        dispProperties(tenant_root, prop_root, fav_root, tenancy_root, propertyArray, sort_root);
    }

    // Display sorted properties (prop id, name, location, rental, size)
    void dispProperties(TenantTree* tenant_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, PropertyTree* sort_root) {
        int page = 1;       // initial page = 1
        int totalPages = (prop.countProperties(sort_root) + 29) / 30;       // get to know total of pages if 30 properties per page (+29 to include the page that is not full with properties)

        while (true) {
            prop.navProperties(sort_root, page);
            cout << "Page " << page << " of " << totalPages << endl << endl;
            cout << "1. Next 30 Properties\n";
            cout << "2. Previous 30 Properties\n";
            cout << "3. Add to Favourite\n";
            cout << "4. Back to Main Menu\n\n";

            int choice = checkOpt();
            if (choice == 1 && page < totalPages) {
                page++;
            } else if (choice == 2 && page > 1) {
                page--;
            } else if (choice == 3) {
                system("CLS");
                favouritePropertyMenu(fav_root, prop_root, tenancy_root, propertyArray,tenant_root, sort_root);
                break;
            } else if (choice == 4) {
                system("CLS");
                tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                break;
            }
        }
    }

    // second while loop for display sorted properties (for input validation)
    int checkOpt() {
        while (true) {
            cout << "Please select an option: ";
            int choice;
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 4) {
                cout << "\nInvalid input. Please enter a number between 1 and 4.\n";
                cin.clear();
                cin.ignore(numeric_limits <streamsize> :: max(), '\n');
                continue;
            } else {
                return choice;
                break;
            }
        }
    }

    // get current user's username
    string getCurrentUsername() {
        string username;
        ifstream file("loggedInUser.txt");
        if (file.is_open()) {
            getline(file, username);
            file.close();
        } else {
            cout << "Unable to open the file.\n";
        }
        return username;
    }

    void addFavouritePropertyMenu(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root, int currentPage) {
        string username = getCurrentUsername();
        string propertyID;
        bool propertyExists;

        while (true) { // Infinite loop to keep prompting the user
            propertyExists = false; // Reset propertyExists for each iteration
            cout << "\nEnter the Property ID to add to favorites: ";
            cin >> propertyID;

            // Search for the property in the PropertyTree
            propertyExists = prop.searchProperty(prop_root, propertyID);

            if (propertyExists) {
                // Check if the property ID is already in the favorite list for this user
                if (fav_root->isInFavouriteList(fav_root, username, propertyID)) {
                    cout << "\nThis property is already in your favorite list.\n";
                } else {
                    fav_root->presetData(&fav_root, username, propertyID); // Use fav_root to call the method
                    cout << "Property added to favorites!\n";
                    #ifdef _WIN32
                    Sleep(2000); // Sleep for 2000 milliseconds (2 seconds) on Windows
                    #else
                    // You can add sleep code for other platforms here if needed
                    #endif
                    displayAllProperty(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root, currentPage); // Return to the same page
                    break; // Exit the loop as the property has been added to favorites
                }
            } else {
                cout << "Property not found. Please enter a valid Property ID.\n";
            }
        }
    }


    // display favourite property for current user
    void favouritePropertyMenu(FavouritePropertyLinkedList* fav_root, PropertyTree* prop_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root) {
        string username = getCurrentUsername();
        if (!username.empty()) {
            system("CLS");
            fav.displayUserFavourite(fav_root, username, prop_root);

            string choiceStr;
            char choice;
            while (true) { // Infinite loop to keep prompting the user until valid input
                cout << "\nWould you like to place a rent request for a favorite property? (Y/N): ";
                cin >> choice;

                if (toupper(choice) == 'Y') {
                    placeRentRequest(fav_root, prop_root, tenancy_root, propertyArray, tenant_root, sort_root);
                    // put place request function

                    break; // Exit the loop as the choice has been handled
                } else if (toupper(choice) == 'N') {
                    // back to main menu
                    system("CLS");
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root,sort_root);
                    break; // Exit the loop as the choice has been handled
                } else {
                    cout << "Invalid input. Please enter only 'Y' or 'N'.\n";
                    // Continue to prompt the user until a valid input is entered
                }
            }
        } else {
            cout << "No user is currently logged in.\n";
        }
    }

    // Current user place rent request
    void placeRentRequest(FavouritePropertyLinkedList* fav_root, PropertyTree* prop_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root) {
        string username = getCurrentUsername();
        if (!username.empty()) {
            system("CLS");
            fav.displayUserFavourite(fav_root, username, prop_root);

            string tenantName = tenant.getTenantName(tenant_root, username);
            if (!tenantName.empty()) {
                cout << "Tenant Name: " << tenantName << "\n";
            } else {
                cout <<"Username not found.\n";
            }
            string propertyID;
            cout << "Enter the Property ID you want to rent: ";
            cin >> propertyID;

            if (!fav.isInFavouriteList(fav_root, username, propertyID)) {
                cout << " The property ID is not in your favourite list.\n";

                char choice;
                while (true) { // Infinite loop to keep prompting the user until valid input
                    cout << "\nWould you like to view favourite property list again? (Y/N) ";
                    cin >> choice;

                    if (toupper(choice) == 'Y') {
                        favouritePropertyMenu(fav_root, prop_root, tenancy_root, propertyArray,tenant_root, sort_root);
                        // put place request function

                        break; // Exit the loop as the choice has been handled
                    } else if (toupper(choice) == 'N') {
                        // back to main menu
                        system("CLS");
                        tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                        break; // Exit the loop as the choice has been handled
                    } else {
                        cout << "Invalid input. Please enter only 'Y' or 'N'.\n";
                        // Continue to prompt the user until a valid input is entered
                    }
                }
            }  

            Property property = getPropertyById(prop_root, propertyID);
            if (!property.propertyID.empty()) { // Check if a valid property was found
                cout << "Property Name: " << property.propertyName << "\n";
                cout << "Completion Year: " << property.completion_year << "\n";
                cout << "Monthly Rental: " << property.monthly_rental << "\n";
                // Print other property details...
            } else {
                cout << "Property ID not found.\n";
                // Handle error...
            }

            string startDate;
            cout << "Enter the starting date of rental: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input stream
            getline(cin, startDate);

            string Duration;
            cout << "\nEnter the duration of rental: ";
            getline(cin, Duration);

            string tenancyID = tenancy.generateTenancyID(tenancy_root);
            tenancy.presetData(&tenancy_root, tenancyID, username, tenantName, propertyID, property.propertyName, startDate, Duration, "", property.monthly_rental, "Pending Manager Approval");
            system("CLS");
            tenancy.displayPendingApprovalTenancy(tenancy_root, username);
            cout << "\n1. Back to Dashboard\n\n";
            int opt;

            while (true) {
                cout << "Select an option: ";
                cin >> opt;

                if (cin.fail() || opt != 1) {
                    cout << "\nInvalid input. Only 1 is allowed.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                system("CLS");
                tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                break;
            }
        } else {
            cout << "No user is currently logged in. \n";
        }
    }


    // view renting request status menu
    void rentRequestStatusMenu(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root) {
        int choice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nChoose an option to view rent request status:\n";
            cout << "1. Pending Manager Approval\n";
            cout << "2. Rejected\n";
            cout << "3. Pending Payment\n";
            cout << "4. Pending Verification\n";
            cout << "5. Back to Main Menu\n\n";
            cout << "Please enter your choice (1 to 5): ";
            cin >> choice;
            string username = getCurrentUsername();
            if (cin.fail() || choice < 1 || choice > 5) {
                system("CLS");
                cout << "Invalid input. Please enter a number between 1 and 5.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
            } else {
                if (choice == 1) {
                    system("CLS");
                    // Call the function to display rent requests with "Pending Manager Approval" status
                    tenancy.displayPendingApprovalTenancy(tenancy_root, username);
                    tenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                    break;

                } else if (choice == 2) {
                    system("CLS");
                    // Call the function to display rent requests with "Rejected" status
                    tenancy.displayRejectedTenancy(tenancy_root, username);
                    tenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                    break;

                } else if (choice == 3) {
                    system("CLS");
                    // Call the function to display rent requests with "Pending Payment" status
                    tenancy.displayPendingPaymentTenancy(tenancy_root, username);
                    pendingPaymentOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                    break;

                } else if (choice == 4) {
                    system("CLS");
                    // Call the function to display rent requests with "Pending Verification" status
                    tenancy.displayPendingPaymentVerificationTenancy(tenancy_root, username);
                    tenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray,  tenant_root, sort_root);
                    break;

                } else {
                    system("CLS");
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root); // go back to main menu
                    break;
                }
            }
        }
    }

    // navigation for pending manager approval, rejected, and pending payment verification
    void tenancyStatusOption(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root) {
        string choiceStr;
        char otherStatus;
        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nWould you like to see other tenancy status? (Y/N): ";
            cin >> ws; // Ignore leading whitespace
            getline(cin, choiceStr); // Read the entire line
            if (!choiceStr.empty()) {
                otherStatus = toupper(choiceStr[0]); // Consider the first character only
                if (otherStatus == 'N') {
                    system("CLS");
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                    break;
                } else if (otherStatus == 'Y') {
                    system("CLS");
                    rentRequestStatusMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                    break; // Break out of the inner loop to return to the gender filter options
                } else {
                    cout << "\nInvalid input. Please enter Y or N.";
                }
            } else {
                cout << "\nInvalid input. Please enter Y or N.";
                // Continue to prompt the user until a valid input is entered
            }
        }
    }

    // navigation for pending payment menu
    void pendingPaymentOption(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root){
        int option;
        cout << "\n\n1. Make Payment\n";
        cout << "2. Back to Previos Page\n";
        cout << "3. Back to Main Menu\n\n";

        while (true) { // Inner loop for the otherFilter input
            cout << "Please enter your choice (1 to 3): ";
            cin >> option;

            if (cin.fail() || option < 1 || option > 3) {
                cout << "\n\nInvalid input. Please enter a number between 1 and 3 only.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

             if (option == 1) {
                //make payment
                break;

            } else if (option == 2) {
                system("CLS");
                rentRequestStatusMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                break; // Break out of the inner loop to return to the gender filter options

            } else if (option == 3) {
                system("CLS");
                tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                break;
            }
        }
    }

    // navigation for completed tenancy menu
    void completedTenancyStatusOption(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root) {
        string choiceStr;
        char otherStatus;
        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nDo you want to go back to main menu? (Enter y to go back):";
            cin >> ws; // Ignore leading whitespace
            getline(cin, choiceStr); // Read the entire line
            
            if (!choiceStr.empty()) {
                otherStatus = toupper(choiceStr[0]); // Consider the first character only
                if (otherStatus == 'Y') {
                    system("CLS");
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root, sort_root);
                    break;
                } else {
                    cout << "\nInvalid input. Please enter Y only.";
                }
            } else {
                cout << "\nInvalid input. Please enter Y only.";
                // Continue to prompt the user until a valid input is entered
            }
        }
    }

    void tenantDeactivateMenu(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root, PropertyTree* sort_root) {
        string username = getCurrentUsername(); // Assume this function gets the currently logged-in username
        if (username.empty()) {
            cout << "No user is currently logged in.\n";
            return;
        }

        char choice;
        cout << "Are you sure you want to deactivate your account? (Y/N): ";
        cin >> choice;

        if (toupper(choice) == 'Y') {
            if (tenant.deactivateTenantAccount(tenant_root, username)) {
                system("CLS");
                cout << "Account deactivated successfully.\n";
                tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root,sort_root, 8);
            } else {
                cout << "Failed to deactivate account.\n";
            }
        } else {
            system("CLS");
            tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root,sort_root);
        }
    }
};


struct ManagerInterface {
    TenantTree tenant;
    FavouritePropertyLinkedList favorite;

    void managerDashboard(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray) {
        int dashboardOption;
        cout << " Welcome to Manager Dashboard\n";
        cout << "==============================\n\n";
        cout << "1. View All Tenant\n";
        cout << "2. Search Tenant\n";
        cout << "3. Delete Tenant Account\n";
        cout << "4. Manage Tenancy\n";
        cout << "5. Manage Payment\n";
        cout << "6. View Report\n";
        cout << "7. Logout\n\n";
        while (true) {
            
            cout << "Please enter your option: ";
            cin >> dashboardOption;

            if (cin.fail() || dashboardOption < 1 || dashboardOption > 7) {
                cout << "\nInvalid input. Please enter a number between 1 and 7.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (dashboardOption == 1) {                                                                                         // View All Tenants
                managerViewAllTenantMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root,  propertyArray);

            } else if (dashboardOption == 2) {                                                                                  // Search Tenant
                managerSearchMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root,  propertyArray);

            } else if (dashboardOption == 3) {                    
                manageInactiveUsers(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);                                                              // Delete Inactive Tenant

            } else if (dashboardOption == 4) {                                                                                  // View All Rent Request + Confirm Them (Give RentID...)
                manageTenancy(tenant_root, manager_root, prop_root, fav_root, tenancy_root,  propertyArray);
            } else if (dashboardOption == 5) {                                                                                  // View Tenant Payment + Confirm Them
                

            } else if (dashboardOption == 6) {                                                                                  // View Report
                managerViewTop10Report(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);

            }
            
            break;
        }
    }

    void managerViewAllTenantMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root,  const vector<Property>& propertyArray){
        system("CLS");
        tenant.dispAllTenant(tenant_root);

        cout << "\n1. Back to Main Menu\n\n";

        int option;
        cout << "Please select an option: ";
        cin >> option;

        if (option == 1){
            system("CLS");
            managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);
        }

    }

    void managerViewTop10Report(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root,  const vector<Property>& propertyArray) {
        system("CLS");
        map<string, string> propertyNames = createPropertyMap(propertyArray);
        favorite.displayTop10Favourite(fav_root, propertyNames);

        cout << "\n1. Back to Dashboard\n\n";
            int opt;

            while (true) {
                cout << "Select an option: ";
                cin >> opt;

                if (cin.fail() || opt != 1) {
                    cout << "\nInvalid input. Only 1 is allowed.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                system("CLS");
                managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);
                break;
            }
    }


    void managerSearchMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray){
        int searchOption;
        system("CLS");
        cout << "Search Tenant\n";
        cout << "==================\n\n";
        cout << "1. Search by Username\n";
        cout << "2. Search by Tenant Name\n";
        cout << "3. Back to Main Menu\n\n";
        
        while (true){
        
            cout << "Please enter an option: ";
            cin >> searchOption;
            

            if (cin.fail() || searchOption < 1 || searchOption > 3) {
                cout << "\n\nInvalid input. Please enter a number between 1 and 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } 
                while (toupper(continueSearch) == 'Y');
                managerSearchMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);
                
                
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
                managerSearchMenu(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);

            } else if (searchOption == 3) {
                system("CLS");
                managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);
            }

            break;
        }
    }

    void manageInactiveUsers(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root,  const vector<Property>& propertyArray) {
        system("CLS");
        cout << "Inactive Users:\n";
        cout << "----------------\n";

        // Display all inactive users
        tenant.filterInactive(tenant_root);

        int option = 0;
        while (option != 2) {
            cout << "\n1. Delete an Inactive User\n";
            cout << "2. Back to Manager Dashboard\n";
            cout << "Please choose an option: ";
            cin >> option;

            if (option == 1) {
                string username;
                cout << "Enter the Username of the user you want to delete: ";
                cin >> username;

                if (tenant.deleteTenantByUsername(tenant_root, username)) {
                    tenant.filterInactive(tenant_root);
                    cout << "User deleted successfully.\n";
                } else {
                    cout << "User not found or user is not inactive.\n";
                }
            } else if (option == 2) {
                // Back to Manager Dashboard
                system("CLS");
                managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);
            } else {
                cout << "Invalid option. Please choose again.\n";
            }
        }
    }

    void manageTenancy(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray) {
        system("CLS");
        int option = 0;

        while (option != 2) {
            int maxTenancyIDLength = strlen("Tenancy ID");
            int maxUsernameLength = strlen("Username");
            int maxTenantNameLength = strlen("Tenant Name");
            int maxPropertyIDLength = strlen("Property ID");
            int maxPropertyNameLength = strlen("Property Name");
            int maxStartDateLength = strlen("Start Date");
            int maxDurationLength = strlen("Duration");
            int maxEndDateLength = strlen("End Date");
            int maxRentalLength = strlen("Rental");
            int maxStatusLength = strlen("Status");

            TenancyLinkedList* current = tenancy_root;
            while (current != nullptr) {
                if (current->data.status == "Pending Manager Approval") {
                    maxTenancyIDLength = max(maxTenancyIDLength, static_cast<int>(current->data.tenancyID.length()));
                    maxUsernameLength = max(maxUsernameLength, static_cast<int>(current->data.username.length()));
                    maxTenantNameLength = max(maxTenantNameLength, static_cast<int>(current->data.tenant_name.length()));
                    maxPropertyIDLength = max(maxPropertyIDLength, static_cast<int>(current->data.property_id.length()));
                    maxPropertyNameLength = max(maxPropertyNameLength, static_cast<int>(current->data.property_name.length()));
                    maxStartDateLength = max(maxStartDateLength, static_cast<int>(current->data.start_date.length()));
                    maxDurationLength = max(maxDurationLength, static_cast<int>(current->data.duration.length()));
                    maxEndDateLength = max(maxEndDateLength, static_cast<int>(current->data.end_date.length()));
                    maxRentalLength = max(maxRentalLength, static_cast<int>(current->data.rental.length()));
                    maxStatusLength = max(maxStatusLength, static_cast<int>(current->data.status.length()));
                }
                current = current->next;
            }

            // Print the header
            cout << "Tenancy Requests Pending Manager Approval:\n";
            cout << string(maxTenancyIDLength + maxUsernameLength + maxTenantNameLength + maxPropertyIDLength + maxPropertyNameLength + maxStartDateLength + maxDurationLength + maxEndDateLength + maxRentalLength + maxStatusLength + 55, '=') << '\n';
            cout << left << setw(maxTenancyIDLength + 5) << "Tenancy ID" << setw(maxUsernameLength + 5) << "Username" << setw(maxTenantNameLength + 5) << "Tenant Name" << setw(maxPropertyIDLength + 5) << "Property ID" << setw(maxPropertyNameLength + 5) << "Property Name" << setw(maxStartDateLength + 5) << "Start Date" << setw(maxDurationLength + 5) << "Duration" << setw(maxEndDateLength + 5) << "End Date" << setw(maxRentalLength + 5) << "Rental" << setw(maxStatusLength + 5) << "Status" << '\n';
            cout << string(maxTenancyIDLength + maxUsernameLength + maxTenantNameLength + maxPropertyIDLength + maxPropertyNameLength + maxStartDateLength + maxDurationLength + maxEndDateLength + maxRentalLength + maxStatusLength + 55, '=') << '\n';

            // Print the rows
            current = tenancy_root;
            while (current != nullptr) {
                if (current->data.status == "Pending Manager Approval") {
                    cout << left << setw(maxTenancyIDLength + 5) << current->data.tenancyID << setw(maxUsernameLength + 5) << current->data.username << setw(maxTenantNameLength + 5) << current->data.tenant_name << setw(maxPropertyIDLength + 5) << current->data.property_id << setw(maxPropertyNameLength + 5) << current->data.property_name << setw(maxStartDateLength + 5) << current->data.start_date << setw(maxDurationLength + 5) << current->data.duration << setw(maxEndDateLength + 5) << current->data.end_date << setw(maxRentalLength + 5) << current->data.rental << setw(maxStatusLength + 5) << current->data.status << '\n';
                }
                current = current->next;
            }

            cout << "\n1. Select a Tenancy to Manage\n";
            cout << "2. Back to Manager Dashboard\n";
            cout << "Please choose an option: ";
            cin >> option;
            if (cin.fail()) {
                    cin.clear(); // Clear the error flags
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input on the line
                    cout << "Invalid option. Please enter a number.\n";
                    continue; // Skip the rest of the loop and start again
            }

            if (option == 1) {
                string selectedID;
                cout << "Enter the Tenancy ID you want to manage: ";
                cin >> selectedID;

                current = tenancy_root;
                while (current != nullptr) {
                    if (current->data.tenancyID == selectedID && current->data.status == "Pending Manager Approval") {

                        // Request the manager to enter the end date
                        cout << "Enter the end date of rental (e.g., \"1 Sept 2023\"): ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input stream
                        getline(cin, current->data.end_date);

                        // Update the status
                        current->data.status = "Pending Payment";
                        system("CLS");
                        cout << "Tenancy request has been updated.\n";
                        // ... additional management options ...
                        break;
                    }
                    current = current->next;
                }
            } else if (option == 2) {
                // Back to Manager Dashboard
                system("CLS");
                managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);
            } else {
                cout << "Invalid option. Please choose again.\n";
            }
        }
    }
};

struct AdminInterface {
    TenantTree tenant;
    ManagerTree manager;
    Admin admin;
    PropertyTree prop;
    
    void adminDashboard(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        int dashboardOption;

        cout << " Welcome to Admin Dashboard\n";
        cout << "============================\n\n";
        cout << "1. Add New Manager\n";
        cout << "2. Modify Manager Status\n";
        cout << "3. Modify Tenant Status\n";
        cout << "4. View Tenant\n";
        cout << "5. View Property\n";
        cout << "6. Log Out\n\n";

        while (true) {
            cout << "Please enter your option: ";
            cin >> dashboardOption;

            if (cin.fail() || dashboardOption < 1 || dashboardOption > 6) {
                cout << "\nInvalid input. Please enter a number between 1 and 6.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (dashboardOption == 1) {                                                     // Add Manager Account
                addManagerIf(tenant_root, manager_root, prop_root, propertyArray);

            } else if (dashboardOption == 2) {                                              // Modify Manager Status (Resigned)

            } else if (dashboardOption == 3) {                                              //  Modify Tenant Status (Last Completed Rent Request Date)

            } else if (dashboardOption == 4) {
                system("CLS");
                filterTenantMenu(tenant_root, manager_root, prop_root, propertyArray);  // Display All Tenant + Filtering Criteria

            } else if (dashboardOption == 5) {        
                system("CLS");                                      // Displat All Property + Filtering Criteria
                filterPropertyMenu(tenant_root, manager_root, prop_root, propertyArray);

            } 
            break;
        }
    }

    void addManagerIf(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        system("CLS");
        bool addSuccess;
        char tryAgain;

        cout << "\n Add New Manager Account\n";
        cout << "-------------------------\n";
        cout << "Please fill in the following details: \n";
        string uname, pw, eid, name, tel, email;                // Get Required Details
        cout << "Username - ";
        cin >> uname;
        cout << "Password - ";
        cin >> pw;
        cout << "Employee ID - ";
        cin >> eid;
        cout << "Full Name as per IC - ";
        cin >> name;
        cout << "Contact Number - ";
        cin >> tel;
        cout << "Email - ";
        cin >> email;

        transform(uname.begin(), uname.end(), uname.begin(), ::tolower);

        addSuccess = manager.bstNewManager(manager_root, uname, pw, eid, name, tel, email, "Active");       // Call Add Manager Algorithm

        if (addSuccess) {                                       // Add Success
            cout << "\n==========================================================\n";
            cout << "Manager account for " << uname << " is added successfully!\n";
            cout << "==========================================================\n";
            cout << "\n1. Back to Dashboard\n\n";
            int opt;

            while (true) {
                cout << "Select an option: ";
                cin >> opt;

                if (cin.fail() || opt != 1) {
                    cout << "\nInvalid input. Only 1 is allowed.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                system("CLS");
                adminDashboard(tenant_root, manager_root, prop_root, propertyArray);
                break;
            }
        } else {                                                // Add Fail
            while (true) {
                cout << "\nOops, something wrong. Try to add manager account again? (Y/N) - ";
                cin >> tryAgain;

                if (toupper(tryAgain) == 'Y') {                 // Call Add Account Again
                    addManagerIf(tenant_root, manager_root, prop_root, propertyArray);
                    break;
                } else if (toupper(tryAgain) == 'N') {          // Call Dashboard
                    adminDashboard(tenant_root, manager_root, prop_root, propertyArray);
                    break;
                } else {
                     cout << "\nInvalid input. Please enter 'Y' or 'N'.\n";
                }
            }
            
        }
    }

    void filterTenantMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        int filterChoice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nDo you want to filter tenants by:\n";
            cout << "1. Gender\n";
            cout << "2. Status\n";
            cout << "3. Back to Main Menu\n\n";
            cout << "Please enter your choice (1, 2, or 3): ";
            cin >> filterChoice;

            if (cin.fail() || filterChoice < 1 || filterChoice > 3) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Gender, 2 for Status, or 3 for Main Menu.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                if (filterChoice == 1) {
                     // Call the function to filter by gender
                     system("CLS");
                     filterTenantGenderMenu(tenant_root, manager_root, prop_root, propertyArray);
                     break;
                } else if (filterChoice == 2) {
                    // Call the function to filter by status
                    system("CLS");
                    filterTenantStatusMenu(tenant_root, manager_root, prop_root, propertyArray);
                    break;
                } else if (filterChoice == 3) {
                    system("CLS");
                    adminDashboard(tenant_root, manager_root, prop_root, propertyArray); // Call the function to go back to the main menu (Assuming you have a function for this)
                    break;
                }
                break; // Exit the loop as the choice has been handled
            }
        }
    }

    // filter gender menu
    void filterTenantGenderMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray){
        int choice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nDo you want to filter tenants' gender by?\n";
            cout << "1. Female\n";
            cout << "2. Male\n";
            cout << "3. Go Back to previous page\n";
            cout << "Please enter your choice (1, 2, or 3): ";
            cin >> choice;

            if (cin.fail() || (choice != 1 && choice != 2 && choice != 3)) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Female, 2 for Male, or 3 to go back.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            } else {
                if (choice == 1) {
                    system("CLS");
                    cout << "\nFemale Tenants\n";
                    cout << "=====================\n\n";
                    tenant.filterFemale(tenant_root); // Call the function to display only female tenants
                } else if (choice == 2) {
                    system("CLS");
                    cout << "\nMale Tenants\n";
                    cout << "=====================\n\n";
                    tenant.filterMale(tenant_root); // Call the function to display only male tenants
                } else if (choice == 3){
                    system("CLS");
                    adminDashboard(tenant_root, manager_root, prop_root, propertyArray);
                    break; // go back to main menu
                }

                char otherFilter;
                while (true) { // Inner loop for the otherFilter input
                    cout << "Would you like to see other filter options? (Y/N): ";
                    cin >> otherFilter;
                    otherFilter = toupper(otherFilter);

                    if (otherFilter == 'N') {
                        system("CLS");
                        adminDashboard(tenant_root, manager_root, prop_root, propertyArray);
                        break;
                    } else if (otherFilter == 'Y') {
                        system("CLS");
                        filterTenantGenderMenu(tenant_root, manager_root, prop_root, propertyArray);
                        break; // Break out of the inner loop to return to the gender filter options
                    } else {
                        cout << "\nInvalid input. Please enter Y or N.\n";
                    }
                }
                break;
            }
        }
    }

    // filter status
    void filterTenantStatusMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray){
        int choice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nDo you want to filter tenants' status by?\n";
            cout << "1. Active\n";
            cout << "2. Inactive\n";
            cout << "3. Go Back to previous page\n";
            cout << "Please enter your choice (1, 2, or 3): ";
            cin >> choice;

            if (cin.fail() || (choice != 1 && choice != 2 && choice != 3)) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Active, 2 for Inactive, or 3 to go back.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            } else {
                if (choice == 1) {
                    system("CLS");
                    cout << "\nActive Tenants\n";
                    cout << "=====================\n\n";
                    tenant.filterActive(tenant_root); // Call the function to display only female tenants
                } else if (choice == 2) {
                    system("CLS");
                    cout << "\nInactive Tenants\n";
                    cout << "=====================\n\n";
                    tenant.filterInactive(tenant_root); // Call the function to display only male tenants
                } else {
                    system("CLS");
                    filterTenantMenu(tenant_root, manager_root, prop_root, propertyArray); // go back to main menu
                    break;
                }

                char otherFilter;
                while (true) { // Inner loop for the otherFilter input
                    cout << "Would you like to see other filter options? (Y/N): ";
                    cin >> otherFilter;
                    otherFilter = toupper(otherFilter);

                    if (otherFilter == 'N') {
                        system("CLS");
                        adminDashboard(tenant_root, manager_root, prop_root, propertyArray);
                        break;
                    } else if (otherFilter == 'Y') {
                        system("CLS");
                        filterTenantStatusMenu(tenant_root, manager_root, prop_root, propertyArray);
                        break; // Break out of the inner loop to return to the gender filter options
                    } else {
                        cout << "\nInvalid input. Please enter Y or N.\n";
                    }
                }
                break;
            }
        }
    }

void filterPropertyMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray){
    int filterChoice;

    while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nDo you want to filter properties by:\n";
            cout << "1. Property Type\n";
            cout << "2. Monthly Rental\n";
            cout << "3. Location\n";
            cout << "4. Number of Rooms\n";
            cout << "5. Number of Parking\n";
            cout << "6. Furnishing Status\n";
            cout << "7. Back to Main Menu\n\n";
            cout << "Please enter your choice (1 to 7): ";
            cin >> filterChoice;

            if (cin.fail() || filterChoice < 1 || filterChoice > 7) {
                system("CLS");
                cout << "Invalid input. Please enter a number from 1 to 7.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                system("CLS");
                switch (filterChoice) {
                    case 1:
                        // Call the function to filter by Property Type
                        system("CLS");
                        filterPropertyByTypeMenu(tenant_root, manager_root, prop_root, propertyArray);
                        break;
                    case 2:
                        // Call the function to filter by Monthly Rental
                        
                        break;
                    case 3:
                        // Call the function to filter by Location
                        system("CLS");
                        filterPropertyByLocationMenu(tenant_root, manager_root, prop_root, propertyArray);
                        break;
                    case 4:
                        // Call the function to filter by Number of Rooms
                        system("CLS");
                        filterPropertyByRoomsMenu(tenant_root, manager_root, prop_root, propertyArray);
                        
                        break;
                    case 5:
                        // Call the function to filter by Number of Parking
                        filterPropertyByParkingMenu(tenant_root, manager_root, prop_root, propertyArray);
                        
                        break;
                    case 6:
                        // Call the function to filter by Furnishing Status
                        filterPropertyByFurnishedMenu(tenant_root, manager_root, prop_root, propertyArray);
                        
                        break;
                    case 7:
                        // Call the function to go back to the main menu (Assuming you have a function for this)
                        adminDashboard(tenant_root, manager_root, prop_root, propertyArray);
                        break;
                }
                break; // Exit the loop as the choice has been handled
            } break;
        }
    }

    void filterPropertyByTypeMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        int filterChoice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nFilter properties by type:\n";
            cout << "1. Apartment\n";
            cout << "2. Condominium\n";
            cout << "3. Flat\n";
            cout << "4. Duplex\n";
            cout << "5. Studio\n";
            cout << "6. Back to Main Menu\n\n";
            cout << "Please enter your choice (1 to 6): ";
            cin >> filterChoice;

            if (cin.fail() || filterChoice < 1 || filterChoice > 7) {
                system("CLS");
                cout << "Invalid input. Please enter a number from 1 to 7.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                string type;
                switch (filterChoice) {
                    case 1: type = "Apartment"; break;
                    case 2: type = "Condominium"; break;
                    case 3: type = "Flat"; break;
                    case 4: type = "Duplex"; break;
                    case 5: type = "Studio"; break;
                    case 6:
                        system("CLS");
                        adminDashboard(tenant_root, manager_root, prop_root, propertyArray); // Call the function to go back to the main menu (Assuming you have a function for this)
                        return;
                }
                // Call the function to filter by the selected type
                bool goBack = prop.navigatePropertiesByType(prop_root, type);
                if (goBack) {
                    // If navigatePropertiesByType returned true, recall filterPropertyByTypeMenu
                    system("CLS");
                    filterPropertyByTypeMenu(tenant_root, manager_root, prop_root, propertyArray);
                    break;
                }
            }
        }
    }

    void filterPropertyByLocationMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        int filterChoice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nFilter properties by location:\n";
            cout << "1. Kuala Lumpur\n";
            cout << "2. Selangor\n";
            cout << "3. Back to Main Menu\n\n";
            cout << "Please enter your choice (1 to 3): ";
            cin >> filterChoice;

            if (cin.fail() || filterChoice < 1 || filterChoice > 4) {
                system("CLS");
                cout << "Invalid input. Please enter a number from 1 to 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else {
                string location;
                switch (filterChoice) {
                    case 1: location = "Kuala Lumpur"; break;
                    case 2: location = "Selangor"; break;
                    case 3:
                        system("CLS");
                        adminDashboard(tenant_root, manager_root, prop_root, propertyArray); // Call the function to go back to the main menu
                        return;
                }
                // Call the function to filter by the selected location
                bool goBack = prop.navigatePropertiesByLocation(prop_root, location); // Make sure to implement this function
                if (goBack) {
                    // If navigatePropertiesByLocation returned true, recall filterPropertyByLocationMenu
                    system("CLS");
                    filterPropertyByLocationMenu(tenant_root, manager_root, prop_root, propertyArray);
                    break;
                } break;
            }
        }
    }

    // filter property by number of rooms menu
    void filterPropertyByRoomsMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        int filterChoice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nFilter properties by the number of rooms:\n";
            cout << "1. 1 Room\n";
            cout << "2. 2 Rooms\n";
            cout << "3. 3 Rooms\n";
            cout << "4. 4 Rooms\n";
            cout << "5. 5 Rooms\n";
            cout << "6. Back to Main Menu\n\n";
            cout << "Please enter your choice (1 to 6): ";
            cin >> filterChoice;

            if (cin.fail() || filterChoice < 1 || filterChoice > 6) {
                system("CLS");
                cout << "Invalid input. Please enter a number from 1 to 6.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            string numberOfRooms;
            if (filterChoice >= 1 && filterChoice <= 5) {
                numberOfRooms = to_string(filterChoice);
            } else if (filterChoice == 6) {
                system("CLS");
                adminDashboard(tenant_root, manager_root, prop_root, propertyArray); // Call the function to go back to the main menu
                return;
            }

            // Call the function to filter by the selected number of rooms
            bool goBack = prop.navigatePropertiesByRooms(prop_root, numberOfRooms);
            if (goBack) {
                // If navigatePropertiesByRooms returned true, recall filterPropertyByRoomsMenu
                system("CLS");
                filterPropertyByRoomsMenu(tenant_root, manager_root, prop_root, propertyArray);
                break;
            }
        }
    }

    // Filter property by number of parking spaces menu
    void filterPropertyByParkingMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        int filterChoice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nFilter properties by the number of parking spaces:\n";
            cout << "1. 1\n";
            cout << "2. 2\n";
            cout << "3. Back to Main Menu\n\n";
            cout << "Please enter your choice (1 to 3): ";
            cin >> filterChoice;

            if (cin.fail() || filterChoice < 1 || filterChoice > 3) {
                system("CLS");
                cout << "Invalid input. Please enter a number from 1 to 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

           string numberOfParking;
            if (filterChoice >= 1 && filterChoice <= 2) {
                numberOfParking = to_string(filterChoice);
            } else if (filterChoice == 3) {
                system("CLS");
                adminDashboard(tenant_root, manager_root, prop_root, propertyArray); // Call the function to go back to the main menu
                return;
            }

            // Call the function to filter by the selected number of parking spaces
            bool goBack = prop.navigatePropertiesByParking(prop_root, numberOfParking);
            if (goBack) {
                // If navigatePropertiesByParking returned true, recall filterPropertyByParkingMenu
                system("CLS");
                filterPropertyByParkingMenu(tenant_root, manager_root, prop_root, propertyArray);
                break;
            }
        }
    }

    // Filter property by furnished status menu
    void filterPropertyByFurnishedMenu(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, const vector<Property>& propertyArray) {
        int filterChoice;

        while (true) { // Infinite loop to keep prompting the user until valid input
            cout << "\nFilter properties by furnished status:\n";
            cout << "1. Fully Furnished\n";
            cout << "2. Partially Furnished\n";
            cout << "3. Not Furnished\n";
            cout << "4. Back to Main Menu\n\n";
            cout << "Please enter your choice (1 to 4): ";
            cin >> filterChoice;

            if (cin.fail() || filterChoice < 1 || filterChoice > 4) {
                system("CLS");
                cout << "Invalid input. Please enter a number from 1 to 4.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            string furnishedStatus;
            switch (filterChoice) {
                case 1: furnishedStatus = "Fully Furnished"; break;
                case 2: furnishedStatus = "Partially Furnished"; break;
                case 3: furnishedStatus = "Not Furnished"; break;
                case 4:
                    system("CLS");
                    adminDashboard(tenant_root, manager_root, prop_root, propertyArray); // Call the function to go back to the main menu
                    return;
            }

            // Call the function to filter by the selected furnished status
            bool goBack = prop.navigatePropertiesByFurnished(prop_root, furnishedStatus);
            if (goBack) {
                // If navigatePropertiesByFurnished returned true, recall filterPropertyByFurnishedMenu
                system("CLS");
                filterPropertyByFurnishedMenu(tenant_root, manager_root, prop_root, propertyArray);
                break;
            }
        }
    }


};