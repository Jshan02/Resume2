#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>

#include "Tenant.h"
#include "Manager.h"
#include "Admin.h"

using namespace std;

struct ManagerInterface {
    void managerDashboard(TenantTree* root) {
        int dashboardOption;
        system("CLS");
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
                managerViewAllTenantMenu(root);

            } else if (dashboardOption == 2) {
                managerSearchMenu(root);

            }
            
            break;
        }
    }

    void managerViewAllTenantMenu(TenantTree* root){
        system("CLS");
        TenantTree tenant;
        tenant.dispAllTenant(root);

        cout << "1. Back to Main Menu\n\n";

        int option;
        cout << "Please select an option: ";
        cin >> option;

        if (option == 1){
            managerDashboard(root);
        }

    }


    void managerSearchMenu(TenantTree* root){
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
                    bool found = tenant.tenantUsernameSearch(root, searchUsername);
                
                    if (!found) {
                    cout << "No result found" << endl;
                    }
                    cout << "\n\nDo you want to continue searching? (Y/N): ";
                    cin >> continueSearch;
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                } 
                while (toupper(continueSearch) == 'Y');
                managerSearchMenu(root);
                
                
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
                    bool found = tenant.tenantNameSearch(root, searchName);
                
                    if (!found) {
                    cout << "No result found" << endl;
                    }

                    cout << "\n\nDo you want to continue searching? (Y/N): ";
                    cin >> continueSearchName;

                } 
                while (toupper(continueSearchName) == 'Y');
                managerSearchMenu(root);
                
                
                
            } else if (searchOption == 3) {
                system("CLS");
                managerDashboard(root);
            }
        }
    }
};

struct GeneralInterface {
    TenantTree tenant;
    ManagerTree manager;
    Admin admin;
    ManagerInterface manager_interface;

    void homepage(TenantTree* root1, ManagerTree* root2) {
        system("CLS");
        int homepgOpt;
        cout << "\n Welcome to Asia Pacific Home (APH)\n";
        cout << "===================================\n";
        cout << "1. Log In\n2. Sign Up\n0. Quit Program\n\n";

        while (true) {
            cout << "Select Your Option: ";
            cin >> homepgOpt;

            if (homepgOpt == 1) {
                logInUser(root1, root2);
                break;
            } else if (homepgOpt == 2) {
                newAccDetails(root1, root2);
                break;
            } else if (homepgOpt == 0) {
                quitProgram();
                break;
            } else {
                cout << "\nInvalid option. Please choose again.\n";
            }
        }
    }

    void logInUser(TenantTree* root1, ManagerTree* root2) {
        system("CLS");
        int userOpt;
        cout << "\nLog In As\n-----------\n";
        cout << "1. Tenant\n2. Manager\n3. Admin\n\n";
        
        while (true) {
            cout << "Select Your User Role: ";
            cin >> userOpt;

            if (userOpt == 1) {
                tenantLogIn(root1, root2);
                break;
            } else if (userOpt == 2) {
                managerLogin(root1, root2);
                break;
            } else if (userOpt == 3) {
                adminLogin(root1,root2);
                break;
            } else {
                cout << "\nInvalid option. Please choose again.\n";
            }
        }
    }

    void tenantLogIn(TenantTree* tenant_root, ManagerTree* root2) {
        system("CLS");
        string uname, pw;
        cout << "\n Tenant Login\n";
        cout << "--------------\n";
        cout << "Enter Your Username: ";
        cin >> uname;
        cout << "Enter Your Password: ";
        cin >> pw;

        if (tenant.login(tenant_root, uname, pw)) {
            system("CLS");
            cout << "Login Successful!\n";
            cout << "Welcome Back " << uname << "!\n\n";
            cout << "Display Tenant Dashboard\n";
        } else {
            loginFail(tenant_root, root2);
        }
    }

    void managerLogin(TenantTree* tenant_root, ManagerTree* manager_root) {
        system("CLS");
        string uname, pw;
        cout << "\n Manager Login\n";
        cout << "---------------\n";
        cout << "Enter Your Username: ";
        cin >> uname;
        cout << "Enter Your Password: ";
        cin >> pw;

        if (manager.login(manager_root, uname, pw)) {
            system("CLS");
            cout << "Login Successful!\n";
            cout << "Welcome Back Manager " << uname << "!\n\n";
            manager_interface.managerDashboard(tenant_root);
        } else {
            loginFail(tenant_root, manager_root);
        }
    }

    void adminLogin(TenantTree* root1, ManagerTree* root2) {
        system("CLS");
        string uname, pw;
        cout << "\n Admin Login\n";
        cout << "-------------\n";
        cout << "Enter Your Username: ";
        cin >> uname;
        cout << "Enter Your Password: ";
        cin >> pw;

        if (admin.login(uname, pw)) {
            system("CLS");
            cout << "Login Success!\n";
            cout << "Welcome Back Admin!\n\n";
            cout << "Display Admin Dashboard\n";
        } else {
            cout << "Login Fail. Username or Password Wrong.\n\n";
            loginFail(root1, root2);
        }
    }

    void loginFail(TenantTree* root1, ManagerTree* root2) {
        char yesNo;
        cout << "Back to Homepage? (Y/N) - ";
        cin >> yesNo;

        if (toupper(yesNo) == 89) {
            homepage(root1, root2);
        } else if (toupper(yesNo) == 78) {
            quitProgram();
        } else {
            cout << "\nInvalid option. Please choose again.\n";
            loginFail(root1, root2);
        }
    }

    void newAccDetails(TenantTree* root1, ManagerTree* root2) {
        system("CLS");
        char yesNo;
        cout << "\n New Account Registration\n";
        cout << "--------------------------\n";
        cout << "Please fill in the following details: \n";
        string uname, pw, name, email, tel, gender;
        cout << "Username - ";
        cin >> uname;
        cout << "Password - ";
        cin >> pw;
        cout << "Full Name as per IC - ";
        cin >> name;
        cout << "Email - ";
        cin >> email;
        cout << "Contact Number - ";
        cin >> tel;
        cout << "Gender (M/F) - ";
        cin >> gender;

        while (true) {
            if (tenant.signUp(root1, uname, pw, name, email, tel, gender)) {
                // tenant.dispAllTenant(root1);
                cout << "\nSuccessfully Sign Up. Proceed to Login? (Y/N) - ";
                cin >> yesNo;

                if (toupper(yesNo) == 89) {
                    tenantLogIn(root1, root2);
                    break;
                } else if (toupper(yesNo) == 78) {
                    homepage(root1, root2);
                    break;
                } else {
                    cout << "\nInvalid option. Please choose again.\n";
                }

            } else {
                cout << "\nSign Up Fail. Try Sign Up Again? (Y/N) - ";
                cin >> yesNo;

                if (toupper(yesNo) == 89) {
                    newAccDetails(root1, root2);
                    break;
                } else if (toupper(yesNo) == 78) {
                    quitProgram();
                    break;
                } else {
                    cout << "\nInvalid option. Please choose again.\n";
                }
            }
        }
    }

    void quitProgram() {
        cout << "\n===================================================\n";
        cout << " Thank You for Using APH Accomodation Rent System!\n";
        cout << "===================================================\n\n";
    }
};

struct AdminInterface {
    void adminDashboard(TenantTree* root) {
        int dashboardOption;
        system("CLS");
        cout << "Welcome to Admin Dashboard\n";
        cout << "=============================\n\n";
        cout << "1. Manage Manager User\n";
        cout << "2. Display\n";
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
                

            } else if (dashboardOption == 2) {
               

            }
            
            break;
        }
    }
}
