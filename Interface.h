#include <iostream>
#include <string>
#include <stdlib.h>

#include "Tenant.h"
#include "Manager.h"
#include "Admin.h"

using namespace std;

struct ManagerInterface {
    void managerDashboard(TenantTree* root) {
        cout << "Welcome to Manager Dashboard\n";
        cout << "=============================\n\n";
        cout << "1. View All Tenant\n";
        cout << "2. Search Tenant\n";
        cout << "3. Delete Tenant Account\n";
        cout << "4. Manage Tenancy\n";
        cout << "5. View Report\n";

        int dashboardOption;
        cout << "Please enter your option: ";
        cin >> dashboardOption;

        if (dashboardOption == 1){
          managerViewAllTenantMenu(root);
        }
    }

    void managerViewAllTenantMenu(TenantTree* root){
        TenantTree tenant;
        tenant.dispAllTenant(root);
    }


    // void managerSearchMenu(TenantTree* root){
    //     cout << "Search Tenant\n";
    //     cout << "==================\n\n";
    //     cout << "1. Search by Username\n";
    //     cout << "2. Search by Tenant Name\n\n";

    //     int searchOption;
    //     cout << "Please enter an option: ";
    //     cin >> searchOption;

    //     if (searchOption == 1){
    //         cout << "Please enter username: ";

    //         string searchUsername;
    //         getline(cin, searchUsername);
    //         TenantTree tenant;
    //         bool found = tenant.bstSearchUsername(root, searchUsername);

    //         if (!found) {
    //             cout << "No result found." << endl;
    //         }
    //     }
    //     else if (searchOption == 2) {
    //         cout << "Pleaser enter name: ";
            
    //         string searchName;
    //         getline(cin, searchName);
    //     }
    // }
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