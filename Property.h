#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

struct Property {
    string propertyID;
    string propertyName;
    string completion_year;
    string monthly_rental;
    string location;
    string propertyType;
    string rooms;
    string parking;
    string bathroom;
    string size;
    string furnished;
    string facilities;
    string additional_facilities;
    string region;
};

struct PropertyTree{
    Property data;
    PropertyTree* leftChild;
    PropertyTree* rightChild;

    // BST Insertion based pn Property ID
    PropertyTree* bstInsert(PropertyTree* root, string propertyID, string propertyName, string completion_year, 
    string monthly_rental, string location, string propertyType, string rooms, string parking, string bathroom, 
    string size, string furnished, string facilities, string additional_facilities, string region) {
        if (root == nullptr) {
            root = new PropertyTree();
            root->data.propertyID = propertyID;
            root->data.propertyName = propertyName;
            root->data.completion_year = completion_year;
            root->data.monthly_rental = monthly_rental;
            root->data.location = location;
            root->data.propertyType = propertyType;
            root->data.rooms = rooms;
            root->data.parking = parking;
            root->data.bathroom = bathroom;
            root->data.size = size;
            root->data.furnished = furnished;
            root->data.facilities = facilities;
            root->data.additional_facilities = additional_facilities;
            root->data.region = region;
            root->leftChild = root->rightChild = nullptr;
        }
        else if (propertyID < root->data.propertyID) {
            root->leftChild = bstInsert(root->leftChild, propertyID, propertyName, completion_year, monthly_rental, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
        }
        else {
            root->rightChild = bstInsert(root->rightChild, propertyID, propertyName, completion_year, monthly_rental, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
        }
        return root;
    }

    // import property data from csv file
    PropertyTree* importProperty(PropertyTree* root, string filename, vector<Property>& propertyArray, string type, 
    vector<Property>& propSortArray) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open the file: " << filename << endl;
            return root;
        }
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            Property property;

            property.propertyID = getNextField(ss);
            property.propertyName = getNextField(ss);
            property.completion_year = getNextField(ss);
            property.monthly_rental = getNextField(ss);
            property.location = getNextField(ss);
            property.propertyType = getNextField(ss);
            property.rooms = getNextField(ss);
            property.parking = getNextField(ss);
            property.bathroom = getNextField(ss);
            property.size = getNextField(ss);
            property.furnished = getNextField(ss);
            property.facilities = getNextField(ss);
            property.additional_facilities = getNextField(ss);
            property.region = getNextField(ss);

            // BST Insert based on Property ID
            if (type == "General") {
                root = bstInsert(root, property.propertyID, property.propertyName, property.completion_year, property.monthly_rental, property.location, property.propertyType, property.rooms, property.parking, property.bathroom, property.size, property.furnished, property.facilities, property.additional_facilities, property.region);
                propertyArray.push_back(property);      // Store Data in Array
                propSortArray.push_back(property);

            // BST Insert based on Monthly Rent, Location, Size as Per Square Feet
            } else if (type == "Sort") {
                root = bstByRentLocationSize(root, property);
            } else if (type == "Property Name"){
                root = bstByPropName(root, property);
            } else if (type == "Location"){
                root = bstLocation(root, property);
            }
        }

        file.close();
        return root;
    }

    // build binary search tree for further sorting
    PropertyTree* bstByRentLocationSize(PropertyTree* sort_root, Property prop_data) {
        if (sort_root == nullptr) {
            sort_root = new PropertyTree();
            sort_root->data = prop_data;
            sort_root->leftChild = sort_root->rightChild = nullptr;
        } else {
            if (compareProp(prop_data, sort_root->data)) {      // compare property's details, if smaller insert to left
                sort_root->leftChild = bstByRentLocationSize(sort_root->leftChild, prop_data);
            } else {
                sort_root->rightChild = bstByRentLocationSize(sort_root->rightChild, prop_data);
            }
        }
        return sort_root;
    }

    // Compare rental, location and size for tree sort
    bool compareProp(const Property& a, const Property& b) {

        // a = prop_data, b = sort_root->data
        // Sort Monthly Rent (Extract Integer for Comparison, Eliminate Alphabet and Spacing)
        string RentA = a.monthly_rental, RentB = b.monthly_rental;
        string ExtractA, ExtractB;
        int rentValueA, rentValueB;

        // For prop_data
        for (char c : RentA){
            if (isdigit(c)) {
                ExtractA.push_back(c);
            }
        }
        stringstream(ExtractA) >> rentValueA;

        // For sort_root->data
        for (char c : RentB){
            if (isdigit(c)) {
                ExtractB.push_back(c);
            }
        }
        stringstream(ExtractB) >> rentValueB;

        // Compare Rent, if different return value for insertion
        if (rentValueA != rentValueB) return rentValueA < rentValueB;
        // ---------------------------------------------------------------------------------

        // Sort Location (transform to lowercase to prevent uppercase and lowercase affect the result)
        string locationA = a.location;
        string locationB = b.location;
        transform(locationA.begin(), locationA.end(), locationA.begin(), ::tolower);
        transform(locationB.begin(), locationB.end(), locationB.begin(), ::tolower);

        // Compare Location, if different return value for insertion
        if (locationA != locationB) return locationA < locationB;
        // -----------------------------------------------------------------------------------

        // Sort Size (Extract Integer for Comparison, Eliminate Alphabet and Spacing)
        string SizeA = a.size, SizeB = b.size;
        string charA, charB;
        int sizeValueA, sizeValueB;

        for (char c : SizeA) {
            if (isdigit(c)) {
                charA.push_back(c);
            }
        }
        stringstream(charA) >> sizeValueA;

        for (char c : SizeB) {
            if (isdigit(c)) {
                charB.push_back(c);
            }
        }
        stringstream(charB) >> sizeValueB;

        // Compare Size, if different return value for insertion
        return sizeValueA < sizeValueB;
    }

    // create a tree acording to property name
    PropertyTree* bstByPropName(PropertyTree* propName_root, Property prop_data) {
        if (propName_root == nullptr) {
            propName_root = new PropertyTree();
            propName_root->data = prop_data;
            propName_root->leftChild = propName_root->rightChild = nullptr;
        }
        else if (prop_data.propertyName < propName_root->data.propertyName) {
            propName_root->leftChild = bstByPropName(propName_root->leftChild, prop_data);
        }
        else {
            propName_root->rightChild = bstByPropName(propName_root->rightChild, prop_data);
        }
        return propName_root;
    }

    // Create a tree according to location
    PropertyTree* bstLocation(PropertyTree* location_root, Property prop_data) {
        if (location_root == nullptr) {
            location_root = new PropertyTree();
            location_root->data = prop_data;
            location_root->leftChild = location_root->rightChild = nullptr;
        }
        else if (prop_data.location < location_root->data.location) {
            location_root->leftChild = bstLocation(location_root->leftChild, prop_data);
        }
        else {
            location_root->rightChild = bstLocation(location_root->rightChild, prop_data);
        }
        return location_root;
    }

    // check wthether the comma is inside the double quote, ignore the comma inside the double quote
    string getNextField(stringstream& ss) {
        string field;
        if (ss.peek() == '\"') {
            ss.ignore();
            getline(ss, field, '\"');
            ss.ignore();
        }
        else {
            getline(ss, field, ',');
        }

        // Replace empty fields with "NA"
        if (field.empty()) {
            field = "NA";
        }
        return field;
    }


    void displayPage(PropertyTree* root, int page) {
        int propertiesPerPage = 10;   //showing 10 properties at 1 page
        int start = (page - 1) * propertiesPerPage;
        int end = start + propertiesPerPage;
        int count = 0;

        // Create a function to traverse the tree and display the properties
        // for the specified page.
        displayPropertiesInRange(root, start, end, count);
    }

    void displayPropertiesInRange(PropertyTree* node, int start, int end, int& count) {
        if (node == nullptr || count >= end) return;

        displayPropertiesInRange(node->leftChild, start, end, count);

        if (count >= start && count < end) {
            // Display the property information
            cout << "Property ID: " << node->data.propertyID << endl
                << "Property Name: " << node->data.propertyName << endl
                << "completion Year: " << node->data.completion_year << endl
                << "Monthly Year: " << node->data.monthly_rental << endl
                << "Location: " << node->data.location << endl
                << "Property Type: " << node->data.propertyType << endl
                << "Rooms: " << node->data.rooms << endl
                << "Parking: " << node->data.parking << endl
                << "Bathroom: " << node->data.bathroom << endl
                << "Size: " << node->data.size << endl
                << "Furnished: " << node->data.furnished << endl
                << "Facilities: " << node->data.facilities << endl
                << "Additional Facilities: " << node->data.additional_facilities << endl
                << "Region: " << node->data.region << endl
                << "----------------------------------------------------------------------------------------------------------------------\n\n";

        }

        if (count >= end) return; // Stop further processing once the end of the range is reached

        count++;

        displayPropertiesInRange(node->rightChild, start, end, count);
    }

    int countProperties(PropertyTree* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + countProperties(root->leftChild) + countProperties(root->rightChild);
    }

    // Display 10 properties at a same time (binary search tree)
    void navigateProperties(PropertyTree* root, int page) {
        system("CLS");
        displayPage(root, page); // Function to display the properties for the given page
    }

    // Function to search for a property in the PropertyTree by propertyID
    bool searchProperty(PropertyTree* root, const string& propertyID) {
        if (root == nullptr) return false;
        
        if (root->data.propertyID == propertyID) return true;

        // Search in the left and right subtrees
        return searchProperty(root->leftChild, propertyID) || searchProperty(root->rightChild, propertyID);
    }

    // function to get property data
    PropertyTree* getPropertyInfo(PropertyTree* root, string propertyID) {
        if (root == nullptr){
            return nullptr;
        }
        if (root->data.propertyID == propertyID){
            return root;
        } if (propertyID < root->data.propertyID){
            return getPropertyInfo(root->leftChild, propertyID);;
        }
        return getPropertyInfo(root->rightChild, propertyID);
    }

    // Function to filter and display properties by type
    void displayPropertiesByType(PropertyTree* node, string propertyType, int start, int end, int& totalTypeCount, int& pageCount) {
        if (node == nullptr || pageCount >= (end - start)) return;

        displayPropertiesByType(node->leftChild, propertyType, start, end, totalTypeCount, pageCount);

        if (node->data.propertyType == propertyType) {
            totalTypeCount++;
            if (totalTypeCount > start && totalTypeCount <= end) {
                // Display the property information
                cout << "Property ID: " << node->data.propertyID << endl
                    << "Property Name: " << node->data.propertyName << endl
                    << "Completion Year: " << node->data.completion_year << endl
                    << "Monthly Rental: " << node->data.monthly_rental << endl
                    << "Location: " << node->data.location << endl
                    << "Property Type: " << node->data.propertyType << endl
                    << "Rooms: " << node->data.rooms << endl
                    << "Parking: " << node->data.parking << endl
                    << "Bathroom: " << node->data.bathroom << endl
                    << "Size: " << node->data.size << endl
                    << "Furnished: " << node->data.furnished << endl
                    << "Facilities: " << node->data.facilities << endl
                    << "Additional Facilities: " << node->data.additional_facilities << endl
                    << "Region: " << node->data.region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                pageCount++;
            }
        }

        displayPropertiesByType(node->rightChild, propertyType, start, end, totalTypeCount, pageCount);
    }

    bool navigatePropertiesByType(PropertyTree* prop_root, const string& propertyType) {
        const int propertiesPerPage = 10; // Number of properties to display per page
        int page = 1;

        while (true) {
            system("CLS"); // Clear the screen for a new page
            int totalTypeCount = 0; // Total number of properties of the specified type
            int pageCount = 0; // Number of properties displayed on the current page

            cout << "=========================================\n";
            cout << "    Properties of Type: " << propertyType << "\n";
            cout << "    Page: " << page << "\n";
            cout << "=========================================\n";

            displayPropertiesByType(prop_root, propertyType, (page - 1) * propertiesPerPage, page * propertiesPerPage, totalTypeCount, pageCount);

            if (pageCount == 0) {
                cout << "No properties found for this type on the current page.\n";
            }

            cout << "\n1. Next 10 properties\n";
            cout << "2. Previous 10 Properties\n";
            cout << "3. Back to Previous Page\n\n";
            cout << "Please select an option: ";
            int choice;
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Next, 2 for Previous, or 3 for Main Menu.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == 1) {
                if (pageCount < propertiesPerPage) {
                    cout << "No more properties to display. Press Enter to continue.";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                } else {
                    page++;
                }
            } else if (choice == 2 && page > 1) {
                page--;
            } else if (choice == 3) {
                return true;
                break;
            }
        }
    }

    // Function to filter and display properties by location
    void displayPropertiesByLocation(PropertyTree* node, string location, int start, int end, int& totalLocationCount, int& pageCount) {
        if (node == nullptr || pageCount >= (end - start)) return;

        displayPropertiesByLocation(node->leftChild, location, start, end, totalLocationCount, pageCount);

        if (node->data.region == location) {
            totalLocationCount++;
            if (totalLocationCount > start && totalLocationCount <= end) {
                // Display the property information
                cout << "Property ID: " << node->data.propertyID << endl
                    << "Property Name: " << node->data.propertyName << endl
                    << "Completion Year: " << node->data.completion_year << endl
                    << "Monthly Rental: " << node->data.monthly_rental << endl
                    << "Location: " << node->data.location << endl
                    << "Property Type: " << node->data.propertyType << endl
                    << "Rooms: " << node->data.rooms << endl
                    << "Parking: " << node->data.parking << endl
                    << "Bathroom: " << node->data.bathroom << endl
                    << "Size: " << node->data.size << endl
                    << "Furnished: " << node->data.furnished << endl
                    << "Facilities: " << node->data.facilities << endl
                    << "Additional Facilities: " << node->data.additional_facilities << endl
                    << "Region: " << node->data.region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                pageCount++;
            }
        }

        displayPropertiesByLocation(node->rightChild, location, start, end, totalLocationCount, pageCount);
    }

    bool navigatePropertiesByLocation(PropertyTree* prop_root, const string& location) {
        const int propertiesPerPage = 10; // Number of properties to display per page
        int page = 1;

        while (true) {
            system("CLS"); // Clear the screen for a new page
            int totalLocationCount = 0; // Total number of properties in the specified location
            int pageCount = 0; // Number of properties displayed on the current page

            cout << "=========================================\n";
            cout << "    Properties in Location: " << location << "\n";
            cout << "    Page: " << page << "\n";
            cout << "=========================================\n";

            displayPropertiesByLocation(prop_root, location, (page - 1) * propertiesPerPage, page * propertiesPerPage, totalLocationCount, pageCount);

            if (pageCount == 0) {
                cout << "No properties found for this location on the current page.\n";
            }

            cout << "\n1. Next 10 properties\n";
            cout << "2. Previous 10 Properties\n";
            cout << "3. Back to Previous Page\n\n";
            cout << "Please select an option: ";
            int choice;
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Next, 2 for Previous, or 3 for Main Menu.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == 1) {
                if (pageCount < propertiesPerPage) {
                    cout << "No more properties to display. Press Enter to continue.";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                } else {
                    page++;
                }
            } else if (choice == 2 && page > 1) {
                page--;
            } else if (choice == 3) {
                return true;
                break;
            }
        }
    }

    // Function to filter and display properties by the number of rooms
    void displayPropertiesByRooms(PropertyTree* node, string numberOfRooms, int start, int end, int& totalRoomCount, int& pageCount) {
        if (node == nullptr || pageCount >= (end - start)) return;

        displayPropertiesByRooms(node->leftChild, numberOfRooms, start, end, totalRoomCount, pageCount);

        if (node->data.rooms == numberOfRooms) {
            totalRoomCount++;
            if (totalRoomCount > start && totalRoomCount <= end) {
                // Display the property information
                cout << "Property ID: " << node->data.propertyID << endl
                    << "Property Name: " << node->data.propertyName << endl
                    << "Completion Year: " << node->data.completion_year << endl
                    << "Monthly Rental: " << node->data.monthly_rental << endl
                    << "Location: " << node->data.location << endl
                    << "Property Type: " << node->data.propertyType << endl
                    << "Rooms: " << node->data.rooms << endl
                    << "Parking: " << node->data.parking << endl
                    << "Bathroom: " << node->data.bathroom << endl
                    << "Size: " << node->data.size << endl
                    << "Furnished: " << node->data.furnished << endl
                    << "Facilities: " << node->data.facilities << endl
                    << "Additional Facilities: " << node->data.additional_facilities << endl
                    << "Region: " << node->data.region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                pageCount++;
            }
        }

        displayPropertiesByRooms(node->rightChild, numberOfRooms, start, end, totalRoomCount, pageCount);
    }

    bool navigatePropertiesByRooms(PropertyTree* prop_root, const string& numberOfRooms) {
        const int propertiesPerPage = 10; // Number of properties to display per page
        int page = 1;

        while (true) {
            system("CLS"); // Clear the screen for a new page
            int totalRoomCount = 0; // Total number of properties with the specified number of rooms
            int pageCount = 0; // Number of properties displayed on the current page

            cout << "=========================================\n";
            cout << "    Properties with Rooms: " << numberOfRooms << "\n";
            cout << "    Page: " << page << "\n";
            cout << "=========================================\n";

            displayPropertiesByRooms(prop_root, numberOfRooms, (page - 1) * propertiesPerPage, page * propertiesPerPage, totalRoomCount, pageCount);

            if (pageCount == 0) {
                cout << "No properties found with this number of rooms on the current page.\n";
            }

            cout << "\n1. Next 10 properties\n";
            cout << "2. Previous 10 Properties\n";
            cout << "3. Back to Previous Page\n\n";
            cout << "Please select an option: ";
            int choice;
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Next, 2 for Previous, or 3 for Main Menu.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == 1) {
                if (pageCount < propertiesPerPage) {
                    cout << "No more properties to display. Press Enter to continue.";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                } else {
                    page++;
                }
            } else if (choice == 2 && page > 1) {
                page--;
            } else if (choice == 3) {
                return true;
                break;
            }
        }
    }

    // Function to filter and display properties by the number of parking spaces
    void displayPropertiesByParking(PropertyTree* node, string numberOfParking, int start, int end, int& totalParkingCount, int& pageCount) {
        if (node == nullptr || pageCount >= (end - start)) return;

        displayPropertiesByParking(node->leftChild, numberOfParking, start, end, totalParkingCount, pageCount);

        if (node->data.parking == numberOfParking) {
            totalParkingCount++;
            if (totalParkingCount > start && totalParkingCount <= end) {
                // Display the property information
                cout << "Property ID: " << node->data.propertyID << endl
                    << "Property Name: " << node->data.propertyName << endl
                    << "Completion Year: " << node->data.completion_year << endl
                    << "Monthly Rental: " << node->data.monthly_rental << endl
                    << "Location: " << node->data.location << endl
                    << "Property Type: " << node->data.propertyType << endl
                    << "Rooms: " << node->data.rooms << endl
                    << "Parking: " << node->data.parking << endl
                    << "Bathroom: " << node->data.bathroom << endl
                    << "Size: " << node->data.size << endl
                    << "Furnished: " << node->data.furnished << endl
                    << "Facilities: " << node->data.facilities << endl
                    << "Additional Facilities: " << node->data.additional_facilities << endl
                    << "Region: " << node->data.region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                pageCount++;
            }
        }

        displayPropertiesByParking(node->rightChild, numberOfParking, start, end, totalParkingCount, pageCount);
    }

    bool navigatePropertiesByParking(PropertyTree* prop_root, const string& numberOfParking) {
        const int propertiesPerPage = 10; // Number of properties to display per page
        int page = 1;

        while (true) {
            system("CLS"); // Clear the screen for a new page
            int totalParkingCount = 0; // Total number of properties with the specified number of parking spaces
            int pageCount = 0; // Number of properties displayed on the current page

            cout << "=========================================\n";
            cout << "    Properties with Parking: " << numberOfParking << "\n";
            cout << "    Page: " << page << "\n";
            cout << "=========================================\n";

            displayPropertiesByParking(prop_root, numberOfParking, (page - 1) * propertiesPerPage, page * propertiesPerPage, totalParkingCount, pageCount);

           if (pageCount == 0) {
                cout << "No properties found for this location on the current page.\n";
            }

            cout << "\n1. Next 10 properties\n";
            cout << "2. Previous 10 Properties\n";
            cout << "3. Back to Previous Page\n\n";
            cout << "Please select an option: ";
            int choice;
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Next, 2 for Previous, or 3 for Main Menu.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == 1) {
                if (pageCount < propertiesPerPage) {
                    cout << "No more properties to display. Press Enter to continue.";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                } else {
                    page++;
                }
            } else if (choice == 2 && page > 1) {
                page--;
            } else if (choice == 3) {
                return true;
                break;
            }
        }
    }

    // Function to filter and display properties by furnished status
    void displayPropertiesByFurnished(PropertyTree* node, string furnishedStatus, int start, int end, int& totalFurnishedCount, int& pageCount) {
        if (node == nullptr || pageCount >= (end - start)) return;

        displayPropertiesByFurnished(node->leftChild, furnishedStatus, start, end, totalFurnishedCount, pageCount);

        if (node->data.furnished == furnishedStatus) {
            totalFurnishedCount++;
            if (totalFurnishedCount > start && totalFurnishedCount <= end) {
                // Display the property information
                cout << "Property ID: " << node->data.propertyID << endl
                    << "Property Name: " << node->data.propertyName << endl
                    << "Completion Year: " << node->data.completion_year << endl
                    << "Monthly Rental: " << node->data.monthly_rental << endl
                    << "Location: " << node->data.location << endl
                    << "Property Type: " << node->data.propertyType << endl
                    << "Rooms: " << node->data.rooms << endl
                    << "Parking: " << node->data.parking << endl
                    << "Bathroom: " << node->data.bathroom << endl
                    << "Size: " << node->data.size << endl
                    << "Furnished: " << node->data.furnished << endl
                    << "Facilities: " << node->data.facilities << endl
                    << "Additional Facilities: " << node->data.additional_facilities << endl
                    << "Region: " << node->data.region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                pageCount++;
            }
        }

        displayPropertiesByFurnished(node->rightChild, furnishedStatus, start, end, totalFurnishedCount, pageCount);
    }

    bool navigatePropertiesByFurnished(PropertyTree* prop_root, const string& furnishedStatus) {
        const int propertiesPerPage = 10; // Number of properties to display per page
        int page = 1;

        while (true) {
            system("CLS"); // Clear the screen for a new page
            int totalFurnishedCount = 0; // Total number of properties with the specified furnished status
            int pageCount = 0; // Number of properties displayed on the current page

            cout << "=========================================\n";
            cout << "    Properties with Furnished Status: " << furnishedStatus << "\n";
            cout << "    Page: " << page << "\n";
            cout << "=========================================\n";

            displayPropertiesByFurnished(prop_root, furnishedStatus, (page - 1) * propertiesPerPage, page * propertiesPerPage, totalFurnishedCount, pageCount);

            if (pageCount == 0) {
                cout << "No properties found with this furnished status on the current page.\n";
            }

            cout << "\n1. Next 10 properties\n";
            cout << "2. Previous 10 Properties\n";
            cout << "3. Back to Previous Page\n\n";
            cout << "Please select an option: ";
            int choice;
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                system("CLS");
                cout << "Invalid input. Please enter 1 for Next, 2 for Previous, or 3 for Main Menu.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == 1) {
                if (pageCount < propertiesPerPage) {
                    cout << "No more properties to display. Press Enter to continue.";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                } else {
                    page++;
                }
            } else if (choice == 2 && page > 1) {
                page--;
            } else if (choice == 3) {
                return true;
                break;
            }
        }
    }

    //  ---------- Search Algorithm ----------
    // ========== Binary Search ==========
    // Binary Search by Property Name
    void bstSearchByPropNameHelper(PropertyTree* root, const string& searchName, bool& found) {
        if (root == nullptr) {
            return; // Base case: If the node is null, return
        }

        // Check if the searchName is a substring of the property name in the current node
        if (root->data.propertyName.find(searchName) != string::npos) {
            // Print the property details
            cout << "Property found with name containing '" << searchName << "':\n";
            cout << "Property ID: " << root->data.propertyID << endl
                << "Property Name: " << root->data.propertyName << endl
                << "Completion Year: " << root->data.completion_year << endl
                << "Monthly Rental: " << root->data.monthly_rental << endl
                << "Location: " << root->data.location << endl
                << "Property Type: " << root->data.propertyType << endl
                << "Rooms: " << root->data.rooms << endl
                << "Parking: " << root->data.parking << endl
                << "Bathroom: " << root->data.bathroom << endl
                << "Size: " << root->data.size << endl
                << "Furnished: " << root->data.furnished << endl
                << "Facilities: " << root->data.facilities << endl
                << "Additional Facilities: " << root->data.additional_facilities << endl
                << "Region: " << root->data.region << endl
                << "----------------------------------------------------------------------------------------------------------------------\n\n";
                found = true;
        }

        // Recursively search in the left and right subtrees
        bstSearchByPropNameHelper(root->leftChild, searchName, found);
        bstSearchByPropNameHelper(root->rightChild, searchName, found);
    }

    void bstSearchByPropName(PropertyTree* root, string searchName) {
        bool found = false;
        bstSearchByPropNameHelper(root, searchName, found);

        if (!found) {
            cout << "Property not found." << endl;
        }
    }

    // Binary search by monthly rental
    // Binary search by location
    void bstSearchByLocationHelper(PropertyTree* root, string searchLocation, bool& found) {
        if (root == nullptr) {
            return; // Base case: If the node is null, return
        }

        // Check if the searchLocation is a substring of the location in the current node
        if (root->data.location.find(searchLocation) != string::npos) {
            // Print the property details
            cout << "Property found with location containing '" << searchLocation << "':\n";
            cout << "Property ID: " << root->data.propertyID << endl
                << "Property Name: " << root->data.propertyName << endl
                << "Completion Year: " << root->data.completion_year << endl
                << "Monthly Rental: " << root->data.monthly_rental << endl
                << "Location: " << root->data.location << endl
                << "Property Type: " << root->data.propertyType << endl
                << "Rooms: " << root->data.rooms << endl
                << "Parking: " << root->data.parking << endl
                << "Bathroom: " << root->data.bathroom << endl
                << "Size: " << root->data.size << endl
                << "Furnished: " << root->data.furnished << endl
                << "Facilities: " << root->data.facilities << endl
                << "Additional Facilities: " << root->data.additional_facilities << endl
                << "Region: " << root->data.region << endl
                << "----------------------------------------------------------------------------------------------------------------------\n\n";
            found = true;
        }

        // Recursively search in the left and right subtrees
        bstSearchByLocationHelper(root->leftChild, searchLocation, found);
        bstSearchByLocationHelper(root->rightChild, searchLocation, found);
    }

    void bstSearchByLocation(PropertyTree* root, string searchLocation) {
        bool found = false;
        bstSearchByLocationHelper(root, searchLocation, found);

        if (!found) {
            cout << "Property not found." << endl;
        }
    }

    // ========== Linear Search ==========
    // Linear search by property name
    void linearSearchPropertiesByName(const vector<Property>& propertyArray, string targetName) {
        bool found = false;
        
        for (int i = 0; i < propertyArray.size(); i++) {
            if (propertyArray[i].propertyName.find(targetName) != string::npos) {
                // Found a property; print its information.
                cout << "Property ID: " << propertyArray[i].propertyID << endl
                    << "Property Name: " << propertyArray[i].propertyName << endl
                    << "Completion Year: " << propertyArray[i].completion_year << endl
                    << "Monthly Rental: " << propertyArray[i].monthly_rental << endl
                    << "Location: " << propertyArray[i].location << endl
                    << "Property Type: " << propertyArray[i].propertyType << endl
                    << "Rooms: " << propertyArray[i].rooms << endl
                    << "Parking: " << propertyArray[i].parking << endl
                    << "Bathroom: " << propertyArray[i].bathroom << endl
                    << "Size: " << propertyArray[i].size << endl
                    << "Furnished: " << propertyArray[i].furnished << endl
                    << "Facilities: " << propertyArray[i].facilities << endl
                    << "Additional Facilities: " << propertyArray[i].additional_facilities << endl
                    << "Region: " << propertyArray[i].region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                found = true;
            }
        }

        if (!found) {
            cout << "Property not found." << endl;
        }
    }

    // Linear search by location
    void linearSearchPropertiesByLocation(const vector<Property>& propertyArray, string targetLocation) {
        bool found = false;
        
        for (int i = 0; i < propertyArray.size(); i++) {
            if (propertyArray[i].location.find(targetLocation) != string::npos) {
                // Found the property; print its information.
                cout << "Property found with location containing '" << targetLocation << "':\n";
                cout << "Property ID: " << propertyArray[i].propertyID << endl
                    << "Property Name: " << propertyArray[i].propertyName << endl
                    << "Completion Year: " << propertyArray[i].completion_year << endl
                    << "Monthly Rental: " << propertyArray[i].monthly_rental << endl
                    << "Location: " << propertyArray[i].location << endl
                    << "Property Type: " << propertyArray[i].propertyType << endl
                    << "Rooms: " << propertyArray[i].rooms << endl
                    << "Parking: " << propertyArray[i].parking << endl
                    << "Bathroom: " << propertyArray[i].bathroom << endl
                    << "Size: " << propertyArray[i].size << endl
                    << "Furnished: " << propertyArray[i].furnished << endl
                    << "Facilities: " << propertyArray[i].facilities << endl
                    << "Additional Facilities: " << propertyArray[i].additional_facilities << endl
                    << "Region: " << propertyArray[i].region << endl
                    << "---------------------------------------------\n\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Property not found." << endl;
        }
    }




    //  ---------- Sorting Algorithm ----------
    // ========== Tree Sort ==========
    void navProperties(PropertyTree* root, int page) {
        system("CLS");
        int propPerPage = 30;
        int start = (page - 1) * propPerPage;
        int end = start + propPerPage;
        int count = 0;
        dispPropTitle(root, start, end, count);
    }

    void dispPropTitle(PropertyTree* root, int start, int end, int& count) {
        int maxPropId = 0, maxPropName = 0, maxLocation = 0, maxSize = 0;
        calculateMaxLength(root, maxPropId, maxPropName, maxLocation, maxSize);
        cout << "\n\n=================================================================================================================================================================================================\n";
        cout << "                                                        Properties in Monthly Rent, Location, Size as per Square Feet Descending Order\n";
        cout << "=================================================================================================================================================================================================\n\n";
        cout << left;
        cout << setw(maxPropId + 5) << "Property ID";
        cout << setw(maxPropName + 5) << "Property Name";
        cout << setw(25) << "Monthly Rent";
        cout << setw(maxLocation + 5) << "Location";
        cout << setw(maxSize + 5) << "Size as per Square Feet\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        dispThirtyProp(root, maxPropId, maxPropName, maxLocation, maxSize, start, end, count);
    }

    void calculateMaxLength(PropertyTree* root, int& maxPropId, int& maxPropName, int& maxLocation, int& maxSize) {
        if (root == nullptr) return;
        maxPropId = max(maxPropId, (int)root->data.propertyID.length());
        maxPropName = max(maxPropName, (int)root->data.propertyName.length());
        maxLocation = max(maxLocation, (int)root->data.location.length());
        maxSize = max(maxSize, (int)root->data.size.length());

        calculateMaxLength(root->leftChild, maxPropId, maxPropName, maxLocation, maxSize);
        calculateMaxLength(root->rightChild, maxPropId, maxPropName, maxLocation, maxSize);
    }

    void dispThirtyProp(PropertyTree* root, int& maxPropId, int& maxPropName, int& maxLocation, int& maxSize, int start, int end, int& count) {
        if (root == nullptr || count >= end) return;
        dispThirtyProp(root->rightChild, maxPropId, maxPropName, maxLocation, maxSize, start, end, count);

        if (count >= start && count < end) {
            cout << left;
            cout << setw(maxPropId + 5) << root->data.propertyID;
            cout << setw(maxPropName + 5) << root->data.propertyName;
            cout << setw(25) << root->data.monthly_rental;
            cout << setw(maxLocation + 5) << root->data.location;
            cout << setw(maxSize + 5) << root->data.size << endl;
        }

        if (count >= end) return;
        count++;

        dispThirtyProp(root->leftChild, maxPropId, maxPropName, maxLocation, maxSize, start, end, count);
    }

    // ========== Quick Sort ==========
    void quickSort(vector<Property>& propertyArray, int low, int high) {
        if (low < high) {
            int pi = partition(propertyArray, low, high);

            quickSort(propertyArray, low, pi-1);
            quickSort(propertyArray, pi + 1, high);
        }
    }

    int partition(vector<Property>& propertyArray, int low, int high) {
        Property pivot  = propertyArray[high];
        int i = (low - 1);

        for (int j = low; j <= high-1; j++) {
            if (quickSortCompare(propertyArray[j], pivot)) {
                i++;
                swap(propertyArray[i], propertyArray[j]);
            }
        }
        swap(propertyArray[i+1], propertyArray[high]);
        return (i+1);
    }

    bool quickSortCompare(const Property& a, const Property& b) {
        string RentA = a.monthly_rental, RentB = b.monthly_rental;
        string ExtractA, ExtractB;
        int rentValueA, rentValueB;
        for (char c : RentA){
            if (isdigit(c)) {
                ExtractA.push_back(c);
            }
        }
        stringstream(ExtractA) >> rentValueA;
        for (char c : RentB){
            if (isdigit(c)) {
                ExtractB.push_back(c);
            }
        }
        stringstream(ExtractB) >> rentValueB;
        if (rentValueA != rentValueB) return rentValueA > rentValueB;

        string locationA = a.location;
        string locationB = b.location;
        transform(locationA.begin(), locationA.end(), locationA.begin(), ::tolower);
        transform(locationB.begin(), locationB.end(), locationB.begin(), ::tolower);
        if (locationA != locationB) return locationA > locationB;

        string SizeA = a.size, SizeB = b.size;
        string charA, charB;
        int sizeValueA, sizeValueB;
        for (char c : SizeA) {
            if (isdigit(c)) {
                charA.push_back(c);
            }
        }
        stringstream(charA) >> sizeValueA;
        for (char c : SizeB) {
            if (isdigit(c)) {
                charB.push_back(c);
            }
        }
        stringstream(charB) >> sizeValueB;
        return sizeValueA > sizeValueB;
    }

    void navQuickSortProp(vector<Property>& propSortArray, int page) {
        system("CLS");
        int propPerPage = 30;
        int start = (page - 1) * propPerPage;
        int end = start + propPerPage;

        int maxPropId = 0, maxPropName = 0, maxLocation = 0, maxSize = 0;
        for (const Property& property : propSortArray) {
            if (property.propertyID.length() > maxPropId) maxPropId = property.propertyID.length();
            if (property.propertyName.length() > maxPropName) maxPropName = property.propertyName.length();
            if (property.location.length() > maxLocation) maxLocation = property.location.length();
            if (property.size.length() > maxSize) maxSize = property.size.length();
        }

        cout << "\n\n=================================================================================================================================================================================================\n";
        cout << "                                                        Properties in Monthly Rent, Location, Size as per Square Feet Descending Order\n";
        cout << "=================================================================================================================================================================================================\n\n";
        cout << left;
        cout << setw(maxPropId + 5) << "Property ID";
        cout << setw(maxPropName + 5) << "Property Name";
        cout << setw(25) << "Monthly Rent";
        cout << setw(maxLocation + 5) << "Location";
        cout << setw(maxSize + 5) << "Size as per Square Feet\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        for (int i = start; i < end && i < propSortArray.size(); i++) {
            const Property& prop2 = propSortArray[i];
            cout << left;
            cout << setw(maxPropId + 5) << prop2.propertyID;
            cout << setw(maxPropName + 5) << prop2.propertyName;
            cout << setw(25) << prop2.monthly_rental;
            cout << setw(maxLocation + 5) << prop2.location;
            cout << setw(maxSize + 5) << prop2.size;
            cout << endl;
        }
    }
};

    Property getPropertyById(PropertyTree* root, const string& propertyID) {
        if (root == nullptr) {
            return Property(); // Property ID not found; return an empty Property object
        }

        if (root->data.propertyID == propertyID) {
            return root->data; // Found the matching property ID; return the property
        }

        // Search the left or right subtree based on your comparison logic
        if (propertyID < root->data.propertyID) {
            return getPropertyById(root->leftChild, propertyID);
        } else {
            return getPropertyById(root->rightChild, propertyID);
        }
    }





