#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <cctype>
using namespace std;

struct Tenant {
    string username;
    string password;
	string tenantName;
	string tenantEmail;
	string tenantTel;
	char tenantGender;
	string tenantStatus;
};

struct TenantTree {
    Tenant data;
    TenantTree* leftChild;
    TenantTree* rightChild;

    // Create new tenant account
    TenantTree* bstNewTenant(TenantTree* root, string tUName, string tPassword, string tName, string tEmail, string tTel, char tGender, string tStatus) {

        // If root is null, direct add in the new account into BST
        if (root == nullptr) {
            root = new TenantTree();
            root->data.username = tUName;
            root->data.password = tPassword;
            root->data.tenantName = tName;
            root->data.tenantEmail = tEmail;
            root->data.tenantTel = tTel;
            root->data.tenantGender = tGender;
            root->data.tenantStatus = tStatus;

        // If new username is lower (in alphabet) than root's username, call again this function to check if it should be enter to the left of this root or not
        } else if (tUName < root->data.username) {
            root->leftChild = bstNewTenant(root->leftChild, tUName, tPassword, tName, tEmail, tTel, tGender, tStatus);

        // If new username is higher (in alphabet) than root's username, call again this function to check if it should be enter to the right of this root or not
        } else {
            root->rightChild = bstNewTenant(root->rightChild, tUName, tPassword, tName, tEmail, tTel, tGender, tStatus);
        }
        return root;
    }

    // Display All Tenant Details Function
    void dispAllTenant(TenantTree* root) {
        int maxUsername = 0, maxName = 0, maxEmail = 0;
        calMaxLength(root, maxUsername, maxName, maxEmail);

        cout << "\n\n====================================================================================================\n";
        cout << "                                     All Tenant Details\n";
        cout << "====================================================================================================\n\n";
        cout << left;
        cout << setw(maxUsername + 5) << "Username";
        cout << setw(maxName + 5) << "Name";
        cout << setw(maxEmail + 5) << "Email";
        cout << setw(16) << "Contact Number";
        cout << setw(10) << "Gender";
        cout << setw(33) << "Status" << endl;
        cout << "----------------------------------------------------------------------------------------------------\n";

        dispInOrder(root, maxUsername, maxName, maxEmail);
    }

    // Get Maximum Length of Username, Name, and Email
    void calMaxLength(TenantTree* root, int& maxUsername, int& maxName, int& maxEmail) {
        if (root == nullptr) return;
        maxUsername = max(maxUsername, (int)root->data.username.length());              // Compare both and save the maximum one
        maxName = max(maxName, (int)root->data.tenantName.length());
        maxEmail = max(maxEmail, (int)root->data.tenantEmail.length());

        calMaxLength(root->leftChild, maxUsername, maxName, maxEmail);
        calMaxLength(root->rightChild, maxUsername, maxName, maxEmail);
    }

    // Display Tenant Details from Username A to Z order
    void dispInOrder(TenantTree* root, int& maxUsername, int& maxName, int& maxEmail) {
        if (root == nullptr) return;
        dispInOrder(root->leftChild, maxUsername, maxName, maxEmail);

        cout << left;
        cout << setw(maxUsername + 5) << root->data.username;
        cout << setw(maxName + 5) << root->data.tenantName;
        cout << setw(maxEmail + 5) << root->data.tenantEmail;
        cout << setw(16) << root->data.tenantTel;
        cout << setw(10) << root->data.tenantGender;
        cout << setw(33) << root->data.tenantStatus << endl;

        dispInOrder(root->rightChild, maxUsername, maxName, maxEmail);
    }

    // Sign Up Function
    bool signUp(TenantTree* root, string uname, string pw, string name, string email, string tel, char gender) {
        // If root is null, direct add in the new account into BST
        if (root == nullptr) {
            root = new TenantTree();
            root->data.username = uname;
            root->data.password = pw;
            root->data.tenantName = name;
            root->data.tenantEmail = email;
            root->data.tenantTel = tel;
            root->data.tenantGender = gender;
            root->data.tenantStatus = "Active";
            return true;

        // If new username is lower (in alphabet) than root's username, call again this function to check if it should be enter to the left of this root or not
        } else if (uname < root->data.username) {
            root->leftChild = bstNewTenant(root->leftChild, uname, pw, name, email, tel, gender, "Active");
            return true;

        // If new username is higher (in alphabet) than root's username, call again this function to check if it should be enter to the right of this root or not
        } else {
            root->rightChild = bstNewTenant(root->rightChild, uname, pw, name, email, tel, gender, "Active");
            return true;
        }        
    }

    // Login function
    bool login(TenantTree* root, string uname, string password) {

        // Search if username entered exists
        if (bstSearchUsername(root, uname)) {

            // check if status is active, allow log in
            if (checkStatus(root, uname) == "Active") {

                // if exists, get its password and compare with password entered
                if (bstGetPassword(root, uname) == password) {

                    // If login success, record the username in text file for future use
                    ofstream Myfile("loggedInUser.txt");
                    Myfile << uname;
                    Myfile.close();
                    return true;
                    
                // If not same, login fail
                } else {
                    cout << "\nLogin Fail, Wrong Password Entered.\n";
                    return false;
                }

            // if status is not active, reject login
            } else {
                cout << "\nLogin fail. Your account status is inactive, request admin to change status before login.\n";
                return false;
            }
            
        // If username not exists, login fail
        } else {
            cout << "\nLogin Fail, Username Not Exists.\n";
            return false;
        }
    }

    // Check if username entered registered in the system
    bool bstSearchUsername(TenantTree* root, string uname) {

        // If the root of BST has nothing, means no username is registered.
        if (root == nullptr) return false;

        // If username matches, return username exists.
        if (root->data.username == uname) return true;

        // If username of root not matches, go check the root's left and right node.
        return bstSearchUsername(root->leftChild, uname) || bstSearchUsername(root->rightChild, uname);
    }

    string checkStatus (TenantTree* root, string uname) {

        // Check current username same with the entered username
        int cmp = strcmp(uname.c_str(), root->data.username.c_str());

        // Username is same, return its status
        if (cmp == 0) {
            return root->data.tenantStatus;

        // Result is negative, means username entered is smaller then current username, go to check its left node
        } else if (cmp < 0) {
            return checkStatus(root->leftChild, uname);

        // Result is positive, means username entered is greater then current username, go to check its right node
        } else {
            return checkStatus(root->rightChild, uname);
        }
    }

    // Get the entered username's correct password
    string bstGetPassword(TenantTree* root, string uname) {

        // Check current username same with the entered username
        int cmp = strcmp(uname.c_str(), root->data.username.c_str());

        // Username is same, return its password
        if (cmp == 0) {
            return root->data.password;
        } else if (cmp < 0) {
            return bstGetPassword(root->leftChild, uname);
        } else {
            return bstGetPassword(root->rightChild, uname);
        }
    }

    // Search tenant by username
	bool tenantUsernameSearch(TenantTree* root, string searchUsername) {
    if (root == nullptr) return false;

    // Convert the search name to lowercase
    string searchUsernameLower = toLower(searchUsername);

    // Search in the left subtree
    bool foundLeft = tenantUsernameSearch(root->leftChild, searchUsername);

    // Check current node
    bool foundCurrent = false;
    string tenantUsernameLower = toLower(root->data.username);
    if (tenantUsernameLower.find(searchUsernameLower) != string::npos) {
        // Display the tenant information
        cout << "Tenant Username: " << root->data.username << endl
             << "Tenant Name: " << root->data.tenantName << endl
             << "Tenant Email: " << root->data.tenantEmail << endl
             << "Tenant Tel: " << root->data.tenantTel << endl
             << "Gender: " << root->data.tenantGender << endl
             << "Status: " << root->data.tenantStatus << "\n\n"
             << "------------------------------------------------\n";
        foundCurrent = true;
    }

    // Search in the right subtree
    bool foundRight = tenantUsernameSearch(root->rightChild, searchUsername);

    return foundLeft || foundCurrent || foundRight;
}

    // Search tenant by name
	bool tenantNameSearch(TenantTree* root, string searchName) {
    if (root == nullptr) return false;

    // Convert the search name to lowercase
    string searchNameLower = toLower(searchName);

    // Search in the left subtree
    bool foundLeft = tenantNameSearch(root->leftChild, searchName);

    // Check current node
    bool foundCurrent = false;
    string tenantNameLower = toLower(root->data.tenantName);
    if (tenantNameLower.find(searchNameLower) != string::npos) {
        // Display the tenant information
        cout << "Tenant Username: " << root->data.username << endl
             << "Tenant Name: " << root->data.tenantName << endl
             << "Tenant Email: " << root->data.tenantEmail << endl
             << "Tenant Tel: " << root->data.tenantTel << endl
             << "Gender: " << root->data.tenantGender << endl
             << "Status: " << root->data.tenantStatus << "\n\n"
             << "------------------------------------------------\n";
        foundCurrent = true;
    }

    // Search in the right subtree
    bool foundRight = tenantNameSearch(root->rightChild, searchName);

    return foundLeft || foundCurrent || foundRight;
}


string toLower(const std::string &input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}


    // Display only female tenant
    void filterFemale(TenantTree* node) {
        if (node == nullptr) return;

        // Traverse the left subtree
        filterFemale(node->leftChild);

        // Process the current node if the tenant is female
        if (node->data.tenantGender == 'F') {
            cout << "Username: " << node->data.username << endl;
            cout << "Name\t: " << node->data.tenantName << endl;
            cout << "Email\t: " << node->data.tenantEmail << endl;
            cout << "Tel\t: " << node->data.tenantTel << endl;
            cout << "Gender\t: " << node->data.tenantGender << endl;
            cout << "Status\t: " << node->data.tenantStatus << endl;
            cout << "---------------------------------------\n\n";
        }

        // Traverse the right subtree
        filterFemale(node->rightChild);
    }

    // Display only male tenant
    void filterMale(TenantTree* node) {
        if (node == nullptr) return;

        // Traverse the left subtree
        filterMale(node->leftChild);

        // Process the current node if the tenant is female
        if (node->data.tenantGender == 'M') {
            cout << "Username: " << node->data.username << endl;
            cout << "Name\t: " << node->data.tenantName << endl;
            cout << "Email\t: " << node->data.tenantEmail << endl;
            cout << "Tel\t: " << node->data.tenantTel << endl;
            cout << "Gender\t: " << node->data.tenantGender << endl;
            cout << "Status\t: " << node->data.tenantStatus << endl;
            cout << "---------------------------------------\n\n";
        }

        // Traverse the right subtree
        filterMale(node->rightChild);
    }

    // Display only active tenant
    void filterActive(TenantTree* node) {
        if (node == nullptr) return;

        // Traverse the left subtree
        filterActive(node->leftChild);

        // Process the current node if the tenant is female
        if (node->data.tenantStatus == "Active") {
            cout << "Username: " << node->data.username << endl;
            cout << "Name\t: " << node->data.tenantName << endl;
            cout << "Email\t: " << node->data.tenantEmail << endl;
            cout << "Tel\t: " << node->data.tenantTel << endl;
            cout << "Gender\t: " << node->data.tenantGender << endl;
            cout << "Status\t: " << node->data.tenantStatus << endl;
            cout << "---------------------------------------\n\n";
        }

        // Traverse the right subtree
        filterActive(node->rightChild);
    }

    // Display only inactive tenant
    void filterInactive(TenantTree* node) {
        if (node == nullptr) return;

        // Traverse the left subtree
        filterInactive(node->leftChild);

        // Process the current node if the tenant is female
        if (node->data.tenantStatus == "Inactive") {
            cout << "Username: " << node->data.username << endl;
            cout << "Name\t: " << node->data.tenantName << endl;
            cout << "Email\t: " << node->data.tenantEmail << endl;
            cout << "Tel\t: " << node->data.tenantTel << endl;
            cout << "Gender\t: " << node->data.tenantGender << endl;
            cout << "Status\t: " << node->data.tenantStatus << endl;
            cout << "---------------------------------------\n\n";
        }

        // Traverse the right subtree
        filterInactive(node->rightChild);
    }

    string getTenantName(TenantTree* root, const string& username) {
        if (root == nullptr) {
            return ""; // Username not found
        }

        if (root->data.username == username) {
            return root->data.tenantName; // Found the matching username, return the tenant's name
        }

        // Search the left or right subtree based on your comparison logic
        if (username < root->data.username) {
            return getTenantName(root->leftChild, username);
        } else {
            return getTenantName(root->rightChild, username);
        }
    }

    TenantTree* minValueNode(TenantTree* node) {
        TenantTree* current = node;

        // Loop down to find the leftmost leaf (smallest value)
        while (current && current->leftChild != nullptr) {
            current = current->leftChild;
        }

        return current;
    }

    bool deleteTenantByUsername(TenantTree*& root, const string& username) {
        if (root == nullptr) return false;

        if (username < root->data.username) {
            return deleteTenantByUsername(root->leftChild, username);
        } else if (username > root->data.username) {
            return deleteTenantByUsername(root->rightChild, username);
        } else {
            // Node with one child or no child
            if (root->leftChild == nullptr) {
                TenantTree* temp = root->rightChild;
                delete root;
                root = temp;
            } else if (root->rightChild == nullptr) {
                TenantTree* temp = root->leftChild;
                delete root;
                root = temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                TenantTree* temp = minValueNode(root->rightChild);

                // Copy the inorder successor's content to this node
                root->data = temp->data;

                // Delete the inorder successor
                return deleteTenantByUsername(root->rightChild, temp->data.username);
            }
            return true;
        }
    }

    bool deactivateTenantAccount(TenantTree*& root, const string& username) {
        if (root == nullptr) return false;

        if (username < root->data.username) {
            return deactivateTenantAccount(root->leftChild, username);
        } else if (username > root->data.username) {
            return deactivateTenantAccount(root->rightChild, username);
        } else {
            if (root->data.tenantStatus == "Active") {
                root->data.tenantStatus = "Inactive";
                return true;
            } else {
                cout << "Account is already inactive or status is invalid.\n";
                return false;
            }
        }
    }
};

