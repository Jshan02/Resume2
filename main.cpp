#include <iostream>
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
    tenant_root = tenant.bstNewTenant(tenant_root, "Js0207", "123", "Low Jye Shan", "js@gmail.com", "012-7173702", 'F', "Active");
    tenant_root = tenant.bstNewTenant(tenant_root, "Hjw02", "456", "Hoong Jhen Wei", "hjw@gmail.com", "012-4501715", 'M', "Inactive");
    tenant_root = tenant.bstNewTenant(tenant_root, "Suyinsss", "789", "Teo Su Yin", "tsy@gmail.com", "011-11281358", 'F', "Active");
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
    fav.presetData(&fav_root, "Hjw02", "100493997");
    fav.presetData(&fav_root, "Hjw02", "100239196");
    fav.presetData(&fav_root, "Hjw02", "100202252");
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
    fav.presetData(&fav_root, "Suyinsss", "100088258");
    fav.presetData(&fav_root, "Suyinsss", "100493687");
    fav.presetData(&fav_root, "Suyinsss", "100202252");

    // Struct Declaration
    GeneralInterface general_interface;


    // homepage
    general_interface.homepage(tenant_root, manager_root, prop_root, fav_root, tenancy_root);
    

    /*// testing functions start

    //testing functions end*/

    return 0;
};