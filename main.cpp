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

int main(){

    // preset data for properties
    Property prop;
    Property* prop_root = nullptr;
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
    


    // testing functions start
    // tenancy.displayTenancyHistory(tenancy_root);
    // fav.displayAllFavourite(fav_root);

    //testing functions end

    return 0;
}