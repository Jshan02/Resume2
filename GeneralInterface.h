#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
using namespace std;

#include "Interface.h"

struct GeneralInterface {
    TenantTree tenant;
    ManagerTree manager;
    Admin admin;

    int homepage(){
        system("CLS");
        int opt;
        cout << "\n Welcome to Asia Pacific Home (APH)\n";
        cout << "===================================\n";
        cout << "1. Log In\n2. Sign Up\n0. Quit Program\n\n";

        while (true) {
            cout << "Please enter your option: ";
            cin >> opt;

            if (opt >= 0 && opt <=2) {
                break;
            } else {
                cout << "\nInvalid input. Please enter a number between 0 and 2.\n";
            }
        }
        return opt;
    }

    int userLogIn() {
        system("CLS");
        int opt;
        cout << "\n Log In As\n-----------\n";
        cout << "1. Tenant\n2. Manager\n3. Admin\n\n";

        while (true) {
            cout << "Select your user role: ";
            cin >> opt;

            if (cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
            cout << "\nInvalid input. Please enter a number.\n";
            continue; // continue with the next iteration of the loop
        }

            if (opt >= 1 && opt <=3) {
                break;
            } else {
                cout << "\nInvalid input. Please enter a number between 1 and 3.\n";
            }
        }
        return opt;
    }

    bool tenantLogIn(TenantTree* tenant_root) {
        system("CLS");
        string uname, pw;
        cout << "\n Tenant Login\n";
        cout << "--------------\n";
        cout << "Enter Your Username: ";
        cin >> uname;
        cout << "Enter Your Password: ";
        cin >> pw;

        transform(uname.begin(), uname.end(), uname.begin(), ::tolower);

        if (tenant.login(tenant_root, uname, pw)) {
            system("CLS");
            cout << "Login Successfully!\n";
            cout << "Welcome Back " << uname << "!\n\n";
            return true;
        } else {
            return false;
        }
    }

    bool managerLogIn(ManagerTree* manager_root) {
        system("CLS");
        string uname, pw;
        cout << "\n Manager Login\n";
        cout << "---------------\n";
        cout << "Enter Your Username: ";
        cin >> uname;
        cout << "Enter Your Password: ";
        cin >> pw;

        transform(uname.begin(), uname.end(), uname.begin(), ::tolower);

        if (manager.login(manager_root, uname, pw)) {
            system("CLS");
            cout << "Login Successfully!\n";
            cout << "Welcome Back Manager " << uname << "!\n\n";
            return true;
        } else {
            return false;
        }
    }

    bool adminLogIn() {
        system("CLS");
        string uname, pw;
        cout << "\n Admin Login\n";
        cout << "-------------\n";
        cout << "Enter Your Username: ";
        cin >> uname;
        cout << "Enter Your Password: ";
        cin >> pw;

        transform(uname.begin(), uname.end(), uname.begin(), ::tolower);

        if (admin.login(uname, pw)) {
            ofstream Myfile("loggedInUser.txt");
            Myfile << uname;
            Myfile.close();

            system("CLS");
            cout << "Login Successfully!\n";
            cout << "Welcome Back Admin!\n\n";
            return true;
        } else {
            cout << "\nLogin Fail. Username or Password Wrong.\n";
            return false;
        }
    }

    int backHomepage() {
        int opt;
        cout << "\n1. Back to Homepage\n";
        cout << "0. Quit Program\n";

        while (true) {
            cout << "Please enter an option: ";
            cin >> opt;

            if (cin.fail() || opt < 0 || opt > 1) {
                cout << "\n\nInvalid input. Please enter number 0 or 1 only.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            } else {
                return opt;
            }
        }
    }

    bool newAccDetails(TenantTree* tenant_root) {
        system("CLS");
        char yesNo;
        bool addSuccess;

        cout << "\n New Account Registration\n";
        cout << "--------------------------\n";
        cout << "Please fill in the following details: \n";
        string uname, pw, name, email, tel, format_uname;
        char gender, format_gender;
        cout << "Username - ";
        cin >> uname;
        cout << "Password - ";
        cin >> pw;        
        cout << "Full Name as per IC - ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining characters in the input buffer
        getline(cin, name);
        cout << "Email - ";
        cin >> email;
        cout << "Contact Number - ";
        cin >> tel;
        

        while (true) {
            cout << "Gender (M/F) - ";
            cin >> gender;

            if (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f') {
                cout << "\nInvalid input. Only 'M' and 'F' is allowed.\n";
                continue;
            } else {
                break;
            }
        }
        

        transform(uname.begin(), uname.end(), uname.begin(), ::tolower);
        format_gender = toupper(gender);

        addSuccess = tenant.signUp(tenant_root, uname, pw, name, email, tel, format_gender);
        return addSuccess;
    }

    bool proceedLogin() {
        char yesNo;
        cout << "\nSuccessfully Sign Up. Proceed to Login? (Y/N) - ";
        cin >> yesNo;
        if (toupper(yesNo) == 89) {
            return true;
        } else if (toupper(yesNo) == 78) {
            return false;
        }
    }
    
    void logOut() {
        int status;
        char yesNo;
        status = remove("loggedInUser.txt");
        if (status == 0) {
            cout << "\n=====================\n";
            cout << " You are logged out.\n";
            cout << "=====================\n";
        } else {
            cout << "\n=======================\n";
            cout << " No logged in account.\n";
            cout << "=======================\n";
        }
    }

    void quitProgram() {
        cout << "\n===================================================\n";
        cout << " Thank You for Using APH Accomodation Rent System!\n";
        cout << "===================================================\n\n";
    }

    
};