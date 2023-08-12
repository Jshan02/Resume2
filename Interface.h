#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>

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
    
    void tenantDashboard(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root) {
        int dashboardOption;
        cout << " Welcome to Tenant Dashboard\n";
        cout << "=============================\n\n";
        cout << "1. View All Properties\n";
        cout << "2. Sort and Display Properties\n";
        cout << "3. Search and Display Properties\n";
        cout << "4. View Favourite Properties\n";
        cout << "5. View Rent Request Status\n";
        cout << "6. View Property Renting History\n";
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

            if (dashboardOption == 1) {                 // Display All Properties
                system("CLS");
                displayAllProperty(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);

            } else if (dashboardOption == 2) {          // Sort n Display + Mark Fav

            } else if (dashboardOption == 3) {          // Search n Display + Mark Fav
                

            } else if (dashboardOption == 4) {          // View Favourite + Option to place rent request
                favouritePropertyMenu(fav_root, prop_root, tenancy_root, propertyArray, tenant_root);

            } else if (dashboardOption == 5) {          // Check Rent Request Status (Wait for Approval / Wait for Payment) + Option to Make Payment if Wait for Payment
                system("CLS");
                rentRequestStatusMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);

            } else if (dashboardOption == 6) {          // view all completed status
                system("CLS");
                string username = getCurrentUsername();
                tenancy.displayCompletedTenancy(tenancy_root, username);
                completedTenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);

            }
            break;
        }
    }

    void displayAllProperty(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root) {
        int page = 1;
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
                favouritePropertyMenu(fav_root, prop_root, tenancy_root, propertyArray,tenant_root);
                break;
            }
            else if (choice == 4) {
                system("CLS");
                tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
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

    // Tenant add favourite property menu
    void addFavouritePropertyMenu(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root) {
        string username = getCurrentUsername();
        string propertyID;
        bool propertyExists;

        while (true) { // Infinite loop to keep prompting the user
            propertyExists = false; // Reset propertyExists for each iteration
            cout << "Enter the Property ID to add to favorites: ";
            cin >> propertyID;

            // Search for the property in the PropertyTree
            propertyExists = prop.searchProperty(prop_root, propertyID);

            if (propertyExists) {
                fav.presetData(&fav_root, username, propertyID);
                cout << "Property added to favorites!\n";
                break; // Exit the loop as the property has been added to favorites
            } else {
                cout << "Property not found. Please enter a valid Property ID.\n";
            }
        }
    }

    // display favourite property for current user
    void favouritePropertyMenu(FavouritePropertyLinkedList* fav_root, PropertyTree* prop_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root) {
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
                    placeRentRequest(fav_root, prop_root, tenancy_root, propertyArray, tenant_root);
                    // put place request function

                    break; // Exit the loop as the choice has been handled
                } else if (toupper(choice) == 'N') {
                    // back to main menu
                    system("CLS");
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
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
    void placeRentRequest(FavouritePropertyLinkedList* fav_root, PropertyTree* prop_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root) {
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
                        favouritePropertyMenu(fav_root, prop_root, tenancy_root, propertyArray,tenant_root);
                        // put place request function

                        break; // Exit the loop as the choice has been handled
                    } else if (toupper(choice) == 'N') {
                        // back to main menu
                        system("CLS");
                        tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
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

            tenancy.presetData(&tenancy_root, "NULL", username, tenantName, propertyID, property.propertyName, startDate, Duration, "NULL", property.monthly_rental, "Pending Manager Approval");

        } else {
            cout << "No user is currently logged in. \n";
        }
    }


    // view renting request status menu
    void rentRequestStatusMenu(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root) {
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
                    tenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
                    break;

                } else if (choice == 2) {
                    system("CLS");
                    // Call the function to display rent requests with "Rejected" status
                    tenancy.displayRejectedTenancy(tenancy_root, username);
                    tenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
                    break;

                } else if (choice == 3) {
                    system("CLS");
                    // Call the function to display rent requests with "Pending Payment" status
                    tenancy.displayPendingPaymentTenancy(tenancy_root, username);
                    pendingPaymentOption(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
                    break;

                } else if (choice == 4) {
                    system("CLS");
                    // Call the function to display rent requests with "Pending Verification" status
                    tenancy.displayPendingPaymentVerificationTenancy(tenancy_root, username);
                    tenancyStatusOption(prop_root, fav_root, tenancy_root, propertyArray,  tenant_root);
                    break;

                } else {
                    system("CLS");
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root); // go back to main menu
                    break;
                }
            }
        }
    }

    // navigation for pending manager approval, rejected, and pending payment verification
    void tenancyStatusOption(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root) {
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
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
                    break;
                } else if (otherStatus == 'Y') {
                    system("CLS");
                    rentRequestStatusMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
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
    void pendingPaymentOption(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root){
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
                rentRequestStatusMenu(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
                break; // Break out of the inner loop to return to the gender filter options

            } else if (option == 3) {
                system("CLS");
                tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
                break;
            }
        }
    }

    // navigation for completed tenancy menu
    void completedTenancyStatusOption(PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root, const vector<Property>& propertyArray, TenantTree* tenant_root) {
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
                    tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
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

            } else if (dashboardOption == 3) {                                                                                  // Delete Inactive Tenant

            } else if (dashboardOption == 4) {                                                                                  // View All Rent Request + Confirm Them (Give RentID...)

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
};

struct AdminInterface {
    TenantTree tenant;
    ManagerTree manager;
    Admin admin;
    
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

            } else if (dashboardOption == 5) {                                              // Displat All Property + Filtering Criteria

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
};