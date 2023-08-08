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
    PropertyTree* left;
    PropertyTree* right;


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
    PropertyTree* bstInsert(PropertyTree* root, string propertyID, string propertyName, string completion_year, string monthly_rental, string location, string propertyType, string rooms, string parking, string bathroom, string size, string furnished, string facilities, string additional_facilities, string region) {
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
            root->left = root->right = nullptr;
        }
        else if (propertyID < root->data.propertyID) {
            root->left = bstInsert(root->left, propertyID, propertyName, completion_year, monthly_rental, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
        }
        else {
            root->right = bstInsert(root->right, propertyID, propertyName, completion_year, monthly_rental, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
        }
        return root;
    }

    PropertyTree* importProperty(PropertyTree* root, string filename, vector<Property>& propertyArray) {
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

        displayPropertiesInRange(node->left, start, end, count);

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
                << "----------------------------------------------------------------------------------------------------------------------\n\n\n\n\n";

        }

        if (count >= end) return; // Stop further processing once the end of the range is reached

        count++;

        displayPropertiesInRange(node->right, start, end, count);
    }

    int countProperties(PropertyTree* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + countProperties(root->left) + countProperties(root->right);
    }

    void navigateProperties(PropertyTree* root) {
        int page = 1;
        int totalPages = (countProperties(root) + 9) / 10; // Calculate the total number of pages

        while (true) {
            displayPage(root, page); 
            cout << "Page " << page << " of " << totalPages << endl << endl;

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
    void bstSearchByPropName(PropertyTree* root, string searchPropName) {
        bool found = false; // Flag to track if a property is found
        cout << "\n=================\n";
        cout << "Search Result:\n";
        cout << "=================\n\n";

        function<void(PropertyTree*)> search = [&](PropertyTree* node) {
            if (node == nullptr) {
                return;
            }

            search(node->left);

            if (node->data.propertyName.find(searchPropName) != string::npos) {
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
                found = true; // Set the flag to true as property is found
            }

            search(node->right);
        };

        search(root);

        if (!found) {
            cout << "Property Not found\n"; // Print "Not found" if no property is found
        }
    }

    void addPropertiesToArray(PropertyTree* root, vector<Property>& propertyArray) {
        if (root == nullptr) return;

        // Traverse left subtree
        addPropertiesToArray(root->left, propertyArray);

        // Create a property object and populate it with the data from the current node
        Property property;
        property.propertyID = root->data.propertyID;
        property.propertyName = root->data.propertyName;
        property.completion_year = root->data.completion_year;
        property.monthly_rental = root->data.monthly_rental;
        property.location = root->data.location;
        property.propertyType = root->data.propertyType;
        property.rooms = root->data.rooms;
        property.parking = root->data.parking;
        property.bathroom = root->data.bathroom;
        property.size = root->data.size;
        property.furnished = root->data.furnished;
        property.facilities = root->data.facilities;
        property.additional_facilities = root->data.additional_facilities;
        property.region = root->data.region;

        // Add the property to the array
        propertyArray.push_back(property);

        // Traverse right subtree
        addPropertiesToArray(root->right, propertyArray);
    }


    void displayPropertiesVector(const vector<Property>& propertyArray) {
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
                << "---------------------------------------------\n\n";
        }
    }
};
