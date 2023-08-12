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

    // import property data from csv file
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

    // Display 10 properties at a same time (binary search tree)
    void navigateProperties(PropertyTree* root, int page) {
        system("CLS");
        displayPage(root, page); // Function to display the properties for the given page
    }

    // insert property data from tree to ventor
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

    // display property data stored in vector
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

    // Function to search for a property in the PropertyTree by propertyID
    bool searchProperty(PropertyTree* root, const string& propertyID) {
        if (root == nullptr) return false;
        
        if (root->data.propertyID == propertyID) return true;

        // Search in the left and right subtrees
        return searchProperty(root->left, propertyID) || searchProperty(root->right, propertyID);
    }

    // function to get property data
    PropertyTree* getPropertyInfo(PropertyTree* root, string propertyID) {
        if (root == nullptr){
            return nullptr;
        }
        if (root->data.propertyID == propertyID){
            return root;
        } if (propertyID < root->data.propertyID){
            return getPropertyInfo(root->left, propertyID);;
        }
        return getPropertyInfo(root->right, propertyID);
    }



    //  ---------- Search Algorithm ----------
    // ========== Binary Search ==========
    // Binary Search by Property Name
    void binarySearchPropertiesByName(vector<Property>& propertyArray, string targetName) {
        int left = 0;
        int right = propertyArray.size() - 1;
        bool found = false;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (propertyArray[mid].propertyName.find(targetName) != string::npos) {
                // Found the property; print its information.
                cout << "Property found with name '" << targetName << "':\n";
                cout << "Property ID: " << propertyArray[mid].propertyID << endl
                    << "Property Name: " << propertyArray[mid].propertyName << endl
                    << "Completion Year: " << propertyArray[mid].completion_year << endl
                    << "Monthly Rental: " << propertyArray[mid].monthly_rental << endl
                    << "Location: " << propertyArray[mid].location << endl
                    << "Property Type: " << propertyArray[mid].propertyType << endl
                    << "Rooms: " << propertyArray[mid].rooms << endl
                    << "Parking: " << propertyArray[mid].parking << endl
                    << "Bathroom: " << propertyArray[mid].bathroom << endl
                    << "Size: " << propertyArray[mid].size << endl
                    << "Furnished: " << propertyArray[mid].furnished << endl
                    << "Facilities: " << propertyArray[mid].facilities << endl
                    << "Additional Facilities: " << propertyArray[mid].additional_facilities << endl
                    << "Region: " << propertyArray[mid].region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";

                // Search for and print any other properties with the same name
                // in both directions from the found index
                int i = mid - 1;
                while (i >= 0 && propertyArray[i].propertyName.find(targetName) != string::npos) {
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

                    i--;
                }
                i = mid + 1;
                while (i < propertyArray.size() && propertyArray[i].propertyName.find(targetName) != string::npos) {
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

                    i++;
                }

                found = true;
                break; // Exit the loop since we've found and printed all matching properties
            }
            else if (propertyArray[mid].propertyName < targetName) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        if (!found) {
            cout << "Property not found." << endl;
        }
    }


    // Binary search by rental
    void binarySearchPropertiesByRental(vector<Property>& propertyArray, string searchRental) {
        int left = 0;
        int right = propertyArray.size() - 1;
        bool found = false;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (propertyArray[mid].monthly_rental.find(searchRental) != string::npos) {
                // Found the property; print its information.
                cout << "Property found with month rental with '" << searchRental << "':\n";
                cout << "Property ID: " << propertyArray[mid].propertyID << endl
                    << "Property Name: " << propertyArray[mid].propertyName << endl
                    << "Completion Year: " << propertyArray[mid].completion_year << endl
                    << "Monthly Rental: " << propertyArray[mid].monthly_rental << endl
                    << "Location: " << propertyArray[mid].location << endl
                    << "Property Type: " << propertyArray[mid].propertyType << endl
                    << "Rooms: " << propertyArray[mid].rooms << endl
                    << "Parking: " << propertyArray[mid].parking << endl
                    << "Bathroom: " << propertyArray[mid].bathroom << endl
                    << "Size: " << propertyArray[mid].size << endl
                    << "Furnished: " << propertyArray[mid].furnished << endl
                    << "Facilities: " << propertyArray[mid].facilities << endl
                    << "Additional Facilities: " << propertyArray[mid].additional_facilities << endl
                    << "Region: " << propertyArray[mid].region << endl
                    << "----------------------------------------------------------------------------------------------------------------------\n\n";

                // Search for and print any other properties with the same name
                // in both directions from the found index
                int i = mid - 1;
                while (i >= 0 && propertyArray[i].monthly_rental.find(searchRental) != string::npos) {
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

                    i--;
                }
                i = mid + 1;
                while (i < propertyArray.size() && propertyArray[i].monthly_rental.find(searchRental) != string::npos) {
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

                    i++;
                }

                found = true;
                break; // Exit the loop since we've found and printed all matching properties
            }
            else if (propertyArray[mid].monthly_rental < searchRental) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        if (!found) {
            cout << "Property not found." << endl;
        }
    }


    // ========== Linear Search ==========
    // Linear search by property name
    void linearSearchPropertiesByName(vector<Property>& propertyArray, string targetName) {
        bool found = false;
        
        for (int i = 0; i < propertyArray.size(); i++) {
            if (propertyArray[i].propertyName.find(targetName) != string::npos) {
                // Found a property; print its information.
                cout << "Property found with monthly rental '" << targetName << "':\n";
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
                    << "---------------------------------------------\n";
                found = true;
            }
        }

        if (!found) {
            cout << "Property not found." << endl;
        }
    }

    // Linear search by rental
    void linearSearchPropertiesByRental(vector<Property>& propertyArray, string targetRental) {
        bool found = false;
        
        for (int i = 0; i < propertyArray.size(); i++) {
            if (propertyArray[i].monthly_rental.find(targetRental) != string::npos) {
                // Found the property; print its information.
                cout << "Property found with monthly rental '" << targetRental << "':\n";
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
                    << "---------------------------------------------\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Property not found." << endl;
        }
    }


};

    // Comparison function to compare two Property objects by their propertyName
    bool compareByName(const Property& a, const Property& b) {
        return a.propertyName < b.propertyName;
    }

    // Function to sort the propertyArray by propertyName
    void sortPropertiesByName(vector<Property>& propertyArray) {
        sort(propertyArray.begin(), propertyArray.end(), compareByName);
    }

    // Comparator function to sort properties by monthly rental
    bool compareByRental(const Property& a, const Property& b) {
        return a.monthly_rental < b.monthly_rental;
        }

    // Function to sort the properties by monthly rental
    void sortPropertiesByRental(vector<Property>& propertyArray) {
        sort(propertyArray.begin(), propertyArray.end(), compareByRental);
    }


