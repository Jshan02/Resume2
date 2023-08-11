#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

#include "Interface.h"

struct GeneralInterface {
    TenantTree tenant;
    ManagerTree manager;
    Admin admin;
    ManagerInterface manager_interface;
    AdminInterface admin_interface;

    void homepage(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        system("CLS");
        int homepgOpt;
        cout << "\n Welcome to Asia Pacific Home (APH)\n";
        cout << "===================================\n";
        cout << "1. Log In\n2. Sign Up\n0. Quit Program\n\n";

        while (true) {
            cout << "Select Your Option: ";
            cin >> homepgOpt;

            if (homepgOpt == 1) {
                logInUser(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                break;
            } else if (homepgOpt == 2) {
                newAccDetails(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                break;
            } else if (homepgOpt == 0) {
                quitProgram();
                break;
            } else {
                cout << "\nInvalid option. Please choose again.\n";
            }
        }
    }

    void logInUser(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        system("CLS");
        int userOpt;
        cout << "\nLog In As\n-----------\n";
        cout << "1. Tenant\n2. Manager\n3. Admin\n\n";
        
        while (true) {
            cout << "Select Your User Role: ";
            cin >> userOpt;

            if (userOpt == 1) {
                tenantLogIn(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                break;
            } else if (userOpt == 2) {
                managerLogin(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                break;
            } else if (userOpt == 3) {
                adminLogin(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                break;
            } else {
                cout << "\nInvalid option. Please choose again.\n";
            }
        }
    }

    void tenantLogIn(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
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
            loginFail(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        }
    }

    void managerLogin(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
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
            manager_interface.managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        } else {
            loginFail(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        }
    }

    void adminLogin(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        system("CLS");
        string uname, pw;
        cout << "\n Admin Login\n";
        cout << "-------------\n";
        cout << "Enter Your Username: ";
        cin >> uname;
        cout << "Enter Your Password: ";
        cin >> pw;

        if (admin.login(uname, pw)) {
            ofstream Myfile("loggedInUser.txt");
            Myfile << uname;
            Myfile.close();
            
            system("CLS");
            cout << "Login Success!\n";
            cout << "Welcome Back Admin!\n\n";
            admin_interface.adminDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        } else {
            cout << "Login Fail. Username or Password Wrong.\n\n";
            loginFail(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        }
    }

    void loginFail(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        char yesNo;
        cout << "Back to Homepage? (Y/N) - ";
        cin >> yesNo;

        if (toupper(yesNo) == 89) {
            homepage(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        } else if (toupper(yesNo) == 78) {
            quitProgram();
        } else {
            cout << "\nInvalid option. Please choose again.\n";
            loginFail(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
        }
    }

    void newAccDetails(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        system("CLS");
        char yesNo;
        cout << "\n New Account Registration\n";
        cout << "--------------------------\n";
        cout << "Please fill in the following details: \n";
        string uname, pw, name, email, tel;
        char gender, format_gender;
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
        format_gender = toupper(gender);

        while (true) {
            if (tenant.signUp(tenant_root, uname, pw, name, email, tel, format_gender)) {
                cout << "\nSuccessfully Sign Up. Proceed to Login? (Y/N) - ";
                cin >> yesNo;

                if (toupper(yesNo) == 89) {
                    tenantLogIn(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                    break;
                } else if (toupper(yesNo) == 78) {
                    homepage(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                    break;
                } else {
                    cout << "\nInvalid option. Please choose again.\n";
                }

            } else {
                cout << "\nSign Up Fail. Try Sign Up Again? (Y/N) - ";
                cin >> yesNo;

                if (toupper(yesNo) == 89) {
                    newAccDetails(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
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

    void logOut(TenantTree* tenant_root, ManagerTree* manager_root, PropertyTree* prop_root, FavouritePropertyLinkedList* fav_root, TenancyLinkedList* tenancy_root) {
        int status;
        char yesNo;
        status = remove("loggedInUser.txt");
        if (status == 0) {
            cout << "\nYou are logged out.\n";

            while (true) {
                cout << "Proceed to Homepage? (Y/N) - ";
                cin >> yesNo;

                if (toupper(yesNo) == 89) {
                    homepage(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
                    break;
                } else if (toupper(yesNo) == 78) {
                    quitProgram();
                    break;
                } else {
                    cout << "\nInvalid option. Please choose again.\n";
                }
            }
        } else {
            cout << "\nNo logged in account.\n";
            quitProgram();
        }
    }

    void quitProgram() {
        cout << "\n===================================================\n";
        cout << " Thank You for Using APH Accomodation Rent System!\n";
        cout << "===================================================\n\n";
    }

    
};