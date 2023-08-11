#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

struct Tenant {
    string username;
    string password;
	string tenantName;
	string tenantEmail;
	string tenantTel;
	string tenantGender;
	string tenantStatus;
};

struct TenantTree {
    Tenant data;
    TenantTree* left;
    TenantTree* right;

    // Create new tenant account
    TenantTree* bstNewTenant(TenantTree* root, string tUName, string tPassword, string tName, string tEmail, string tTel, string tGender, string tStatus) {

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
            root->left = bstNewTenant(root->left, tUName, tPassword, tName, tEmail, tTel, tGender, tStatus);

        // If new username is higher (in alphabet) than root's username, call again this function to check if it should be enter to the right of this root or not
        } else {
            root->right = bstNewTenant(root->right, tUName, tPassword, tName, tEmail, tTel, tGender, tStatus);
        }
        return root;
    }

    // Display All Tenant Details Function
    void dispAllTenant(TenantTree* root) {
        cout << "\n\n==================\n";
        cout << "All Tenant Details\n";
        cout << "==================\n";
        dispInOrder(root);
    }

    // Display Tenant Details from Username A to Z order
    void dispInOrder (TenantTree* root) {
        if (root == nullptr) return;
        dispInOrder (root->left);
        cout << "Username: " << root->data.username << endl;
        cout << "Name\t: " << root->data.tenantName << endl;
        cout << "Email\t: " << root->data.tenantEmail << endl;
        cout << "Tel\t: " << root->data.tenantTel << endl;
        cout << "Gender\t: " << root->data.tenantGender << endl;
        cout << "Status\t: " << root->data.tenantStatus << endl;
        cout << "---------------------------------------\n\n";
        dispInOrder (root->right);
    }

    // Sign Up Function
    bool signUp(TenantTree* root, string uname, string pw, string name, string email, string tel, string gender) {
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
            root->left = bstNewTenant(root->left, uname, pw, name, email, tel, gender, "Active");
            return true;

        // If new username is higher (in alphabet) than root's username, call again this function to check if it should be enter to the right of this root or not
        } else {
            root->right = bstNewTenant(root->right, uname, pw, name, email, tel, gender, "Active");
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
        return bstSearchUsername(root->left, uname) || bstSearchUsername(root->right, uname);
    }

    string checkStatus (TenantTree* root, string uname) {

        // Check current username same with the entered username
        int cmp = strcmp(uname.c_str(), root->data.username.c_str());

        // Username is same, return its status
        if (cmp == 0) {
            return root->data.tenantStatus;

        // Result is negative, means username entered is smaller then current username, go to check its left node
        } else if (cmp < 0) {
            return checkStatus(root->left, uname);

        // Result is positive, means username entered is greater then current username, go to check its right node
        } else {
            return checkStatus(root->right, uname);
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
            return bstGetPassword(root->left, uname);
        } else {
            return bstGetPassword(root->right, uname);
        }
    }


    // Search tenant by name
	bool tenantNameSearch(TenantTree* root, string searchName) {
		if (root == nullptr) {
			return false;
		}

		// Search in the left subtree
		tenantNameSearch(root->left, searchName);

		// Check current node
		// bool foundCurrent = false;
		if (root->data.tenantName.find(searchName) != string::npos) { //display all the data that have the search username
			// Display the tenant information
			cout << "Tenant Username: " << root->data.username << endl
                << "Tenant Name: " << root->data.tenantName << endl
                << "Tenant Email: " << root->data.tenantEmail << endl
				<< "Tenant Tel: " << root->data.tenantTel << endl
				<< "Gender: " << root->data.tenantGender << endl
				<< "Status: " << root->data.tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
			// foundCurrent = true;
		}

		// Search in the right subtree
		tenantNameSearch(root->right, searchName);

		//remenber to add
		/*cout << "Enter name want to search: ";
		string searchName;
		getline(cin, searchName);
		bool found = tenant.tenantNameSearch(root, searchName);

		if (!found) {
			cout << "No result found" << endl;
		}*/

	}
};