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

    Property* left;
    Property* right;


    //void preOrder(Property* node) {
    //    if (node == nullptr) return;
    //    cout << "Property ID: " << node->propertyID << endl
    //        << "Property Name: " << node->propertyName << endl
    //        << "Completion Year: " << node->completion_year << endl
    //        << "Monthly Year: " << node->monthly_rental << endl
    //        << "Location: " << node->location << endl
    //        << "Property Type: " << node->propertyType << endl
    //        << "Rooms: " << node->rooms << endl
    //        << "Parking: " << node->parking << endl
    //        << "Bathroom: " << node->bathroom << endl
    //        << "Size: " << node->size << endl
    //        << "Furnished: " << node->furnished << endl
    //        << "Facilities: " << node->facilities << endl
    //        << "Additional Facilities: " << node->additional_facilities << endl
    //        << "Region: " << node->region << endl << endl << endl;
    //    preOrder(node->left);
    //    preOrder(node->right);
    //}

    // BST Insertion
    Property* bstInsert(Property* root, string propertyID, string propertyName, string completion_year, string monthly_rental, string location, string propertyType, string rooms, string parking, string bathroom, string size, string furnished, string facilities, string additional_facilities, string region) {
        if (root == nullptr) {
            root = new Property();
            root->propertyID = propertyID;
            root->propertyName = propertyName;
            root->completion_year = completion_year;
            root->monthly_rental = monthly_rental;
            root->location = location;
            root->propertyType = propertyType;
            root->rooms = rooms;
            root->parking = parking;
            root->bathroom = bathroom;
            root->size = size;
            root->furnished = furnished;
            root->facilities = facilities;
            root->additional_facilities = additional_facilities;
            root->region = region;
            root->left = root->right = nullptr;
        }
        else if (propertyID < root->propertyID) {
            root->left = bstInsert(root->left, propertyID, propertyName, completion_year, monthly_rental, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
        }
        else {
            root->right = bstInsert(root->right, propertyID, propertyName, completion_year, monthly_rental, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
        }
        return root;
    }

    //// Import Property data from CSV
    //Property* importProperty(Property* root, string filename) {
    //    ifstream file(filename);
    //    if (!file.is_open()) {
    //        cout << "Failed to open the file: " << filename << endl;
    //        return root;
    //    }

    //    string line;
    //    getline(file, line);    //skip the first row

    //    while (getline(file, line)) {
    //        stringstream ss(line);
    //        string propertyID, propertyName, completion_year, monthly_rental, location, propertyType, bathroom, size, furnished, facilities, additional_facilities, region, rooms, parking;

    //        propertyID = getNextField(ss);
    //        propertyName = getNextField(ss);
    //        completion_year = getNextField(ss);
    //        monthly_rental = getNextField(ss);
    //        location = getNextField(ss);
    //        propertyType = getNextField(ss);
    //        rooms = getNextField(ss);
    //        parking = getNextField(ss);
    //        bathroom = getNextField(ss);
    //        size = getNextField(ss);
    //        furnished = getNextField(ss);
    //        facilities = getNextField(ss);
    //        additional_facilities = getNextField(ss);
    //        region = getNextField(ss);

    //        // the propertyID as the key for the BST.
    //        // object being inserted into the BST based on propertyID
    //        root = bstInsert(root, propertyID, propertyName, completion_year, monthly_rental, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
    //    }

    //    file.close();
    //    return root;
    //}

    Property* importProperty(Property* root, string filename, vector<Property>& propertyArray) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open the file: " << filename << endl;
            return root;
        }

        string line;
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

            // Insert the property into the BST
            root = bstInsert(root, property.propertyID, property.propertyName, property.completion_year, property.monthly_rental, property.location, property.propertyType, property.rooms, property.parking, property.bathroom, property.size, property.furnished, property.facilities, property.additional_facilities, property.region);

            // Push the property object into the array
            propertyArray.push_back(property);
        }

        file.close();
        return root;
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


    void displayPage(Property* root, int page) {
        int propertiesPerPage = 10;   //showing 10 properties at 1 page
        int start = (page - 1) * propertiesPerPage;
        int end = start + propertiesPerPage;
        int count = 0;

        // Create a function to traverse the tree and display the properties
        // for the specified page.
        displayPropertiesInRange(root, start, end, count);
    }

    void displayPropertiesInRange(Property* node, int start, int end, int& count) {
        if (node == nullptr || count >= end) return;

        displayPropertiesInRange(node->left, start, end, count);

        if (count >= start && count < end) {
            // Display the property information
            cout << "Property ID: " << node->propertyID << endl
                << "Property Name: " << node->propertyName << endl
                << "completion Year: " << node->completion_year << endl
                << "Monthly Year: " << node->monthly_rental << endl
                << "Location: " << node->location << endl
                << "Property Type: " << node->propertyType << endl
                << "Rooms: " << node->rooms << endl
                << "Parking: " << node->parking << endl
                << "Bathroom: " << node->bathroom << endl
                << "Size: " << node->size << endl
                << "Furnished: " << node->furnished << endl
                << "Facilities: " << node->facilities << endl
                << "Additional Facilities: " << node->additional_facilities << endl
                << "Region: " << node->region << endl
                << "----------------------------------------------------------------------------------------------------------------------\n";

        }

        if (count >= end) return; // Stop further processing once the end of the range is reached

        count++;

        displayPropertiesInRange(node->right, start, end, count);
    }

    int countProperties(Property* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + countProperties(root->left) + countProperties(root->right);
    }

    void navigateProperties(Property* root) {
        int page = 1;
        int totalPages = (countProperties(root) + 9) / 10; // Calculate the total number of pages

        while (true) {
            cout << "Page " << page << " of " << totalPages << endl << endl;
            displayPage(root, page); 

            cout << "1. Next 10 properties\n2. Previous 10 Properties\n3. Add to favourite\n4. Back to Main Menu" << endl;
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
                break;
            }
            else if (choice == 4) {
                break;
            }
        }
    }

    // binary search by property name
    void bstSearchByPropName(Property* root, string searchPropName) {
        bool found = false; // Flag to track if a property is found
        cout << "\n=================\n";
        cout << "Search Result:\n";
        cout << "=================\n\n";

        function<void(Property*)> search = [&](Property* node) {
            if (node == nullptr) {
                return;
            }

            search(node->left);

            if (node->propertyName.find(searchPropName) != string::npos) {
                // Display the property information
                cout << "Property ID: " << node->propertyID << endl
                    << "Property Name: " << node->propertyName << endl
                    << "completion Year: " << node->completion_year << endl
                    << "Monthly Year: " << node->monthly_rental << endl
                    << "Location: " << node->location << endl
                    << "Property Type: " << node->propertyType << endl
                    << "Rooms: " << node->rooms << endl
                    << "Parking: " << node->parking << endl
                    << "Bathroom: " << node->bathroom << endl
                    << "Size: " << node->size << endl
                    << "Furnished: " << node->furnished << endl
                    << "Facilities: " << node->facilities << endl
                    << "Additional Facilities: " << node->additional_facilities << endl
                    << "Region: " << node->region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";
                found = true; // Set the flag to true as property is found
            }

            search(node->right);
        };

        search(root);

        if (!found) {
            cout << "Property Not found\n"; // Print "Not found" if no property is found
        }
    }

    void addPropertiesToArray(Property* root, vector<Property>& propertyArray) {
        if (root == nullptr) return;

        // Traverse left subtree
        addPropertiesToArray(root->left, propertyArray);

        // Create a property object and populate it with the data from the current node
        Property property;
        property.propertyID = root->propertyID;
        property.propertyName = root->propertyName;
        property.completion_year = root->completion_year;
        property.monthly_rental = root->monthly_rental;
        property.location = root->location;
        property.propertyType = root->propertyType;
        property.rooms = root->rooms;
        property.parking = root->parking;
        property.bathroom = root->bathroom;
        property.size = root->size;
        property.furnished = root->furnished;
        property.facilities = root->facilities;
        property.additional_facilities = root->additional_facilities;
        property.region = root->region;

        // Add the property to the array
        propertyArray.push_back(property);

        // Traverse right subtree
        addPropertiesToArray(root->right, propertyArray);
    }


    void displayProperties(const vector<Property>& propertyArray) {
        cout << "Properties:\n";
        for (const Property& property : propertyArray) {
            cout << "Property ID: " << property.propertyID << endl
                << "Property Name: " << property.propertyName << endl
                << "Completion Year: " << property.completion_year << endl
                << "Monthly Rental: " << property.monthly_rental << endl
                << "Location: " << property.location << endl
                << "Property Type: " << property.propertyType << endl
                << "Rooms: " << property.rooms << endl
                << "Parking: " << property.parking << endl
                << "Bathroom: " << property.bathroom << endl
                << "Size: " << property.size << endl
                << "Furnished: " << property.furnished << endl
                << "Facilities: " << property.facilities << endl
                << "Additional Facilities: " << property.additional_facilities << endl
                << "Region: " << property.region << endl
                << "---------------------------------------------\n";
        }
    }
};
