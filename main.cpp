#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <stdlib.h>
using namespace std;

#include "GeneralInterface.h"

int main(){

    // data import for properties
    PropertyTree prop;
    PropertyTree* prop_root = nullptr;
    vector<Property> propertyArray;
    prop_root = prop.importProperty(prop_root, "mudah-apartment-kl-selangor.csv", propertyArray);

    // preset data for tenant account
    TenantTree tenant;
    TenantTree* tenant_root = nullptr;
    tenant_root = tenant.bstNewTenant(tenant_root, "js0207", "123", "Low Jye Shan", "js@gmail.com", "012-7173702", 'F', "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "hjw02", "456", "Hoong Jhen Wei", "hjw@gmail.com", "012-4501715", 'M', "Inactive");
    tenant_root = tenant.bstNewTenant(tenant_root, "suyinsss", "789", "Teo Su Yin", "tsy@gmail.com", "011-11281358", 'F', "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "ericdiew", "abc", "Eric Diew", "ericdiew@gmail.com", "012-53575928", 'M', "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "angangpuds", "def", "Ang Chan Fwu", "angang22@gmail.com", "014-33785321", 'M', "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "shadoww", "ghi", "Shad Ng", "shadng78@gmail.com", "016-50247831", 'M', "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "seanw98", "jkl", "Sean Wong", "seanw33@gmail.com", "012-23348964", 'M', "Inactive");
    tenant_root = tenant.bstNewTenant(tenant_root, "noobmaster", "mno", "Thor Lee", "thormaster@gmail.com", "011-66249617", 'M', "Inactive");
    tenant_root = tenant.bstNewTenant(tenant_root, "kriko", "pqr", "Saeshav Subash", "kriko332@gmail.com", "010-13443015", 'M', "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "kante", "stu", "Shasivarman", "shasivarman@gmail.com", "019-94235764", 'M', "Active");

    // preset data for manager account
    ManagerTree manager;
    ManagerTree* manager_root = nullptr;
    manager_root = manager.bstNewManager(manager_root, "hua27", "27", "M001", "Hua Chen Yu", "011-9092313", "chenyu@gmail.com", "Inactive");
    manager_root = manager.bstNewManager(manager_root, "liu03", "0315", "M002", "Liu Shi Shi", "011-8882313", "cecelia@gmail.com", "Active");

    // preset data for admin account
    Admin admin;
    admin.presetAdmin("admin", "admin123");

    //preset data for tenancy history
    TenancyLinkedList tenancy;
    TenancyLinkedList* tenancy_root = nullptr;
    tenancy.presetData(&tenancy_root, "R01", "js0207", "Low Jye Shan", "100203973", "Segar Courts", "1 June 2023", "1 Year", "31 May 2024", "RM 2 300 per month", "Completed");
    tenancy.presetData(&tenancy_root, "R02", "hjw02", "Hoong Jhen Wei", "100322962", "Sky Meridien", "1 July 2023", "1 Year", "30 June 2024", "RM 2 900 per month", "Pending Payment");
    tenancy.presetData(&tenancy_root, "R03", "suyinsss", "Teo Su Yin", "100273500", "Desa Villas", "1 June 2023", "1 Year", "31 May 2024", "RM 2 500 per month", "Completed");
    tenancy.presetData(&tenancy_root, "R04", "kante", "Shasivarman", "100322962", "Sky Meridien", "1 August 2023", "1 Year", "30 July 2024", "RM 2 900 per month", "Rejected");
    tenancy.presetData(&tenancy_root, "R05", "kante", "Shasivarman", "100273500", "Desa Villas", "1 September 2023", "1 Year", "", "RM 2 500 per month", "Pending Manager Approval");
    tenancy.presetData(&tenancy_root, "R06", "shadoww", "Shad Ng", "100273500", "Desa Villas", "1 September 2023", "1 Year", "31 August 2024", "RM 2 500 per month", "Pending Payment Verification");
    tenancy.presetData(&tenancy_root, "R07", "angangpuds", "Ang Chan Fwu", "99923007", "Sentul Point Suite Apartment", "1 October 2023", "1 Year", "30 September 2024", "RM 1 700 per month", "Completed");
    tenancy.presetData(&tenancy_root, "R08", "noobmaster", "Thor Lee", "97468177", "The Hipster @ Taman Desa", "1 February 2024", "1 Year", "31 January 2025", "RM 4 200 per month", "Rejected");
    tenancy.presetData(&tenancy_root, "R09", "kriko", "Saeshav Subash", "97468177", "The Hipster @ Taman Desa", "1 September 2023", "1 Year", "", "RM 4 200 per month", "Pending Manager Approval");
    
    // preset data for favourite property list
    FavouritePropertyLinkedList fav;
    FavouritePropertyLinkedList* fav_root = nullptr;
    fav.presetData(&fav_root, "js0207", "100203973");
    fav.presetData(&fav_root, "js0207", "87950203");
    fav.presetData(&fav_root, "hjw02", "100322962");
    fav.presetData(&fav_root, "suyinsss", "100273500");
    fav.presetData(&fav_root, "hjw02", "100493997");
    fav.presetData(&fav_root, "hjw02", "100239196");
    fav.presetData(&fav_root, "hjw02", "100202252");
    fav.presetData(&fav_root, "ericdiew", "100322962");
    fav.presetData(&fav_root, "ericdiew", "100321021");
    fav.presetData(&fav_root, "ericdiew", "100170082");
    fav.presetData(&fav_root, "angangpuds", "100322962");
    fav.presetData(&fav_root, "angangpuds", "100321021");
    fav.presetData(&fav_root, "angangpuds", "100493687");
    fav.presetData(&fav_root, "shadoww", "100322962");
    fav.presetData(&fav_root, "shadoww", "100170082");
    fav.presetData(&fav_root, "shadoww", "100493997");
    fav.presetData(&fav_root, "seanw98", "100322962");
    fav.presetData(&fav_root, "seanw98", "100202252");
    fav.presetData(&fav_root, "seanw98", "100170082");
    fav.presetData(&fav_root, "kriko", "100322962");
    fav.presetData(&fav_root, "kriko", "100239196");
    fav.presetData(&fav_root, "kriko", "100493997");
    fav.presetData(&fav_root, "kante", "100322962");
    fav.presetData(&fav_root, "kante", "100170082");
    fav.presetData(&fav_root, "kante", "100494721");
    fav.presetData(&fav_root, "Js0207", "100088258");
    fav.presetData(&fav_root, "Js0207", "100493687");
    fav.presetData(&fav_root, "Js0207", "100494721");
    fav.presetData(&fav_root, "noobmaster", "100322962");
    fav.presetData(&fav_root, "noobmaster", "100239196");
    fav.presetData(&fav_root, "noobmaster", "100321021");
    fav.presetData(&fav_root, "suyinsss", "100088258");
    fav.presetData(&fav_root, "suyinsss", "100493687");
    fav.presetData(&fav_root, "suyinsss", "100202252");

    // Struct Declaration
    GeneralInterface general_interface;
    AdminInterface admin_interface;
    ManagerInterface manager_interface;
    TenantInterface tenant_interface;
    

    // Main Program Starts Here
    int homepgOpt, roleOpt, logoutOpt, quitOpt;
    bool authenticated, registered, goLogin;

    while (true) {
        homepgOpt = general_interface.homepage();                               // Login, Sign Up, or Quit Program
        if (homepgOpt == 1) {                                                   // Login Selected
            roleOpt = general_interface.userLogIn();                            // Login as Tenant, Manager, or Admin
            if (roleOpt == 1) {                                                 // Tenant Selected
                authenticated = general_interface.tenantLogIn(tenant_root);     // Verify Username and Password

                if (authenticated) {                                            // Correct
                    tenant_interface.tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root); // Call Tenant Dashboard
                    general_interface.logOut();                                 // If log out is selected
                    quitOpt = general_interface.backHomepage();                 // Prompt User Quit or Back to Homepage
                    if (quitOpt == 0) {                                         // Quit Program is Selected
                        general_interface.quitProgram();                        // Terminate
                        break;                                                  // End Loop
                    } else {                                                    // Back to Homepage is Selected
                        continue;                                               // Continue Loop
                    }
                } else {                                                        // Incorrect
                    quitOpt = general_interface.backHomepage();                 // Prompt User Quit or Back to Homepage
                    if (quitOpt == 0) {                                         // Quit Program is Selected
                        general_interface.quitProgram();                        // Terminate
                        break;                                                  // End Loop
                    } else {                                                    // Back to Homepage is Selected
                        continue;                                               // Continue Loop
                    }
                }
            } else if (roleOpt == 2) {                                          // Manager Selected
                authenticated = general_interface.managerLogIn(manager_root);
                if (authenticated) {
                    manager_interface.managerDashboard(tenant_root, manager_root, prop_root, fav_root, tenancy_root, propertyArray);
                    general_interface.logOut();
                    quitOpt = general_interface.backHomepage();
                    if (quitOpt == 0) {
                        general_interface.quitProgram();
                        break;
                    } else {
                        continue;
                    }
                } else {
                    quitOpt = general_interface.backHomepage();
                    if (quitOpt == 0) {
                        general_interface.quitProgram();
                        break;
                    } else {
                        continue;
                    }
                }
            } else {                                                            // Admin Selected
                authenticated = general_interface.adminLogIn();
                if (authenticated) {
                    admin_interface.adminDashboard(tenant_root, manager_root, prop_root, propertyArray);
                    general_interface.logOut();
                    quitOpt = general_interface.backHomepage();
                    if (quitOpt == 0) {
                        general_interface.quitProgram();
                        break;
                    } else {
                        continue;
                    }
                } else {
                    quitOpt = general_interface.backHomepage();
                    if (quitOpt == 0) {
                        general_interface.quitProgram();
                        break;
                    } else {
                        continue;
                    }
                }
            }
        } else if (homepgOpt == 2) {                                            // Sign Up is selected
            registered = general_interface.newAccDetails(tenant_root);          // Check if registered successfully
            if (registered) {                                                   // Success
                goLogin = general_interface.proceedLogin();                     // Check whether to log in as tenant
                if (goLogin) {                                                  // go login
                    authenticated = general_interface.tenantLogIn(tenant_root);
                    if (authenticated) {
                        tenant_interface.tenantDashboard(prop_root, fav_root, tenancy_root, propertyArray, tenant_root);
                        general_interface.logOut();
                        quitOpt = general_interface.backHomepage();
                        if (quitOpt == 0) {
                            general_interface.quitProgram();
                            break;
                        } else { 
                            continue;
                        }
                    } else {
                        quitOpt = general_interface.backHomepage();
                        if (quitOpt == 0) { 
                            general_interface.quitProgram();
                            break;
                        } else { 
                            continue;
                        }
                    }
                } else {                                                        // dont want login
                    quitOpt = general_interface.backHomepage();                 // ask whether back to homepage or quit
                    if (quitOpt == 0) {
                        general_interface.quitProgram();
                        break;
                    } else {
                        continue;
                    }
                }
            }
        } else {
            general_interface.quitProgram();
            break;
        }
    }


    /*// testing functions start

    //testing functions end*/

    return 0;
};