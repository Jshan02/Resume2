#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
using namespace std;

#include "Property.h"
#include "TenancyHistory.h"
#include "FavouriteProperty.h"
#include "Tenant.h"
#include "Manager.h"
#include "Admin.h"

int main(){

    // data import for properties
    PropertyTree prop;
    PropertyTree* prop_root = nullptr;
    vector<Property> propertyArray;
    prop_root = prop.importProperty(prop_root, "mudah-apartment-kl-selangor.csv", propertyArray);

    //preset data for tenancy history
    TenancyLinkedList tenancy;
    TenancyLinkedList* tenancy_root = nullptr;
    tenancy.presetData(&tenancy_root, "R01", "Js0207", "Low Jye Shan", "Segar Courts", "1 June 2023", "1 Year", "31 May 2024", "RM 2 300 per month", "Confirmed");
    tenancy.presetData(&tenancy_root, "R02", "Hjw02", "Hoong Jhen Wei", "Sky Meridien", "1 July 2023", "1 Year", "30 June 2024", "RM 2 900 per month", "Confirmed");
    tenancy.presetData(&tenancy_root, "R03", "Suyinsss", "Teo Su Yin", "Desa Villas", "1 September 2023", "1 Year", "31 August 2024", "RM 2 500 per month", "To Pay");
    
    // preset data for favourite property list
    FavouritePropertyLinkedList fav;
    FavouritePropertyLinkedList* fav_root = nullptr;
    fav.presetData(&fav_root, "Js0207", "100203973");
    fav.presetData(&fav_root, "Js0207", "87950203");
    fav.presetData(&fav_root, "Hjw02", "100322962");
    fav.presetData(&fav_root, "Suyinsss", "100273500");

    // preset data for tenant account
    TenantTree tenant;
    TenantTree* tenant_root = nullptr;
    tenant_root = tenant.bstNewTenant(tenant_root, "Js0207", "123", "Low Jye Shan", "js@gmail.com", "012-7173702", "F", "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "Hjw02", "456", "Hoong Jhen Wei", "hjw@gmail.com", "012-4501715", "M", "Inactive");
    tenant_root = tenant.bstNewTenant(tenant_root, "Suyinsss", "789", "Teo Su Yin", "tsy@gmail.com", "011-11281358", "F", "Active");

    // preset data for manager account
    ManagerTree manager;
    ManagerTree* manager_root = nullptr;
    manager_root = manager.bstNewManager(manager_root, "hua27", "27", "M001", "Hua Chen Yu", "011-9092313", "chenyu@gmail.com", "Inactive");
    manager_root = manager.bstNewManager(manager_root, "liu03", "0315", "M002", "Liu Shi Shi", "011-8882313", "cecelia@gmail.com", "Active");

    // preset data for admin account
    Admin admin("admin", "admin123");


    // homepage
    int homepageOpt, userOpt;
    string uname, pw;
    bool valid;
    cout << "\n Welcom to Asia Pacific Home (APH)\n";
    cout << "===================================\n";
    while (true) {
        cout << "1. Log In\n2. Sign Up\n0. Quit Program\n\n";
        cout << "Select your Option: ";
        cin >> homepageOpt;

        if (homepageOpt == 1) {
            valid = false;
            while (valid == false) {
                cout << "\nLog In As\n-----------\n";
                cout << "1. Tenant\n2. Manager\n3. Admin\n\n";
                cout << "Select you user role: ";
                cin >> userOpt;

                if (userOpt == 1) {
                    valid = true;
                    cout << "\n Tenant Login\n";
                    cout << "--------------\n";
                    cout << "Enter Your Username: ";
                    cin >> uname;
                    cout << "Enter Your Password: ";
                    cin >> pw;

                    if (tenant.login(tenant_root, uname, pw)) {
                        cout << "\n";                       
                    }
                    
                } else if (userOpt == 2) {
                    valid = true;
                    cout << "\n Manager Login\n";
                    cout << "---------------\n";
                    cout << "Enter Your Username: ";
                    cin >> uname;
                    cout << "Enter Your Password: ";
                    cin >> pw;

                    if (manager.login(manager_root, uname, pw)) {
                        cout << "\n";
                    }
                    
                } else if (userOpt == 3) {
                    valid = true;
                    cout << "\n Admin Login\n";
                    cout << "-------------\n";
                    cout << "Enter Your Username: ";
                    cin >> uname;
                    cout << "Enter Your Password: ";
                    cin >> pw;

                    if (admin.login(uname, pw)) {
                        cout << "\nLogin Success!\nWelcome Back, Admin!\n\n";
                    } else {
                        cout << "\nLogin Fail. Username or Password Wrong.\n\n";
                    }

                } else {
                    cout << "\nInvalid Option! Please choose again.\n";
                }
            }
            break;
        } else if (homepageOpt == 2) {
            break;
        } else if (homepageOpt == 0) {
            cout << "\n===================================================\n";
            cout << " Thank You for Using APH Accomodation Rent System!\n";
            cout << "===================================================\n\n";
            break;
        } else {
            cout << "\nInvalid Option! Please Choose Again.\n\n";
        }
    }
    


    /*// testing functions start
    tenant.dispAllTenant(tenant_root);

    //testing functions end*/

    return 0;
}