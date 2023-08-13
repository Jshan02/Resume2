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
    PropertyTree* importProperty(PropertyTree* root, string filename, vector<Property>& propertyArray) {
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

    // insert property data from tree to ventor
    void addPropertiesToArray(PropertyTree* root, vector<Property>& propertyArray) {
        if (root == nullptr) return;

        // Traverse left subtree
        addPropertiesToArray(root->leftChild, propertyArray);

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
        addPropertiesToArray(root->rightChild, propertyArray);
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



    //  ---------- Search Algorithm ----------
    // ========== Binary Search ==========
    // Binary Search by Property Name
    void binarySearchPropertiesByName(vector<Property>& propertyArray, string targetName) {
        int leftChild = 0;
        int rightChild = propertyArray.size() - 1;
        bool found = false;
        
        while (leftChild <= rightChild) {
            int mid = (leftChild + rightChild) / 2;
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
                leftChild = mid + 1;
            }
            else {
                rightChild = mid - 1;
            }
        }

        if (!found) {
            cout << "Property not found." << endl;
        }
    }


    // Binary search by rental
    void binarySearchPropertiesByRental(vector<Property>& propertyArray, string searchRental) {
        int leftChild = 0;
        int rightChild = propertyArray.size() - 1;
        bool found = false;
        
        while (leftChild <= rightChild) {
            int mid = (leftChild + rightChild) / 2;
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
                leftChild = mid + 1;
            }
            else {
                rightChild = mid - 1;
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



    //  ---------- Sorting Algorithm ----------
    // Display Sorted Properties
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
        cout << "                                                                      Properties in Descending Order by Location\n";
        cout << "=================================================================================================================================================================================================\n\n";
        cout << left;
        cout << setw(maxPropId + 5) << "Property ID";
        cout << setw(maxPropName + 5) << "Property Name";
        cout << setw(maxLocation + 5) << "Location";
        cout << setw(25) << "Monthly Rent";
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
            cout << setw(maxLocation + 5) << root->data.location;
            cout << setw(25) << root->data.monthly_rental;
            cout << setw(maxSize + 5) << root->data.size << endl;
        }

        if (count >= end) return;
        count++;

        dispThirtyProp(root->leftChild, maxPropId, maxPropName, maxLocation, maxSize, start, end, count);
    }

    // ========== Tree Sort ==========
    // Tree Sort by Location
    // inorder traversal of original prop tree (id) to insert its data into another BST (location)
    PropertyTree* locationSort(PropertyTree* prop_root, PropertyTree* prop_location_root) {
        if (prop_root == nullptr) return prop_location_root;

        prop_location_root = locationSort(prop_root->leftChild, prop_location_root);
        prop_location_root = bstInsertByLocation(prop_location_root, prop_root->data);
        prop_location_root = locationSort(prop_root->rightChild, prop_location_root);
        return prop_location_root;
    }

    // insert data from ID Bst to Location BST
    PropertyTree* bstInsertByLocation(PropertyTree* prop_location_root, Property data) {

        // get lowercase of location to prevent result affected by upper and lower case
        string originalLocationLower = data.location;
        transform(originalLocationLower.begin(), originalLocationLower.end(), originalLocationLower.begin(), ::tolower);
        
        if (prop_location_root == nullptr) {
            prop_location_root = new PropertyTree();
            prop_location_root->data.propertyID = data.propertyID;
            prop_location_root->data.propertyName = data.propertyName;
            prop_location_root->data.completion_year = data.completion_year;
            prop_location_root->data.monthly_rental = data.monthly_rental;
            prop_location_root->data.location = data.location;
            prop_location_root->data.propertyType = data.propertyType;
            prop_location_root->data.rooms = data.rooms;
            prop_location_root->data.parking = data.parking;
            prop_location_root->data.bathroom = data.bathroom;
            prop_location_root->data.size = data.size;
            prop_location_root->data.furnished = data.furnished;
            prop_location_root->data.facilities = data.facilities;
            prop_location_root->data.additional_facilities = data.additional_facilities;
            prop_location_root->data.region = data.region;

            prop_location_root->leftChild = prop_location_root->rightChild = nullptr;

        } else {

            // get lowercase of data in prop_location_root also to compare with the original one
            string newLocationLower = prop_location_root->data.location;
            transform(newLocationLower.begin(), newLocationLower.end(), newLocationLower.begin(),::tolower);
            
            if (originalLocationLower < newLocationLower) {
                prop_location_root->leftChild = bstInsertByLocation(prop_location_root->leftChild, data);

            } else {
                prop_location_root->rightChild = bstInsertByLocation(prop_location_root->rightChild, data);
            }
        }
        return prop_location_root;
    }

    
    // Tree Sort by Size
    // Tree Sort by Rental
    // Tree Sort for All Three


    // ========== Quick Sort ==========
    
    // Quick Sort by Location
    // Quick Sort by Size
    // Quick Sort by Rental
    // Quick Sort by All Three


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


