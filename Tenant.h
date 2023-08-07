#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "User.h";

struct Tenant : public User {
	string tenantID;
	string tenantName;
	string tenantEmail;
	string tenantTel;
	string tenantGender;
	string tenantStatus;

	Tenant* left;
	Tenant* right;

	//BST Tenant Data Insertion
	Tenant* tenantDataInsert(Tenant* root, string tenantID, string username, string tenantName, string tenantEmail, string tenantPassword,
		string tenantTel, string tenantGender, string tenantStatus) {
		if (root == nullptr) {
			root = new Tenant();
			root->tenantID = tenantID;
			root->username = username;
			root->tenantName = tenantName;
			root->tenantEmail = tenantEmail;
			root->password = password;
			root->tenantTel = tenantTel;
			root->tenantGender = tenantGender;
			root->tenantStatus = tenantStatus;
			root->left = root->right = nullptr;
		}
		else if (tenantID < root->tenantID) {
			root->left = tenantDataInsert(root->left, tenantID, username, tenantName, tenantEmail, tenantPassword,
				tenantTel, tenantGender, tenantStatus);
		}
		else {
			root->right = tenantDataInsert(root->right, tenantID, username, tenantName, tenantEmail, tenantPassword,
				tenantTel, tenantGender, tenantStatus);
		}
		return root;
	}

	// Display all tenant
	void preOrder(Tenant* node) {
	    if (node == nullptr) return;
		cout << "Tenant ID: " << node->tenantID << endl
			<< "Tenant Username: " << node->username << endl
			<< "Tenant Name: " << node->tenantName << endl
			<< "Tenant Email: " << node->tenantEmail << endl
			<< "Tenant Tel: " << node->tenantTel << endl
			<< "Gender: " << node->tenantGender << endl
			<< "Status: " << node->tenantStatus << "\n\n"
			<< "------------------------------------------------\n";
	    preOrder(node->left);
	    preOrder(node->right);
	}

	// Display only female tenant
	bool preOrderFemale(Tenant* node) {
		if (node == nullptr) return false;

		bool found = (node->tenantGender == "female");

		if (found) {
			cout << "Tenant ID: " << node->tenantID << endl
				<< "Tenant Username: " << node->username << endl
				<< "Tenant Name: " << node->tenantName << endl
				<< "Tenant Email: " << node->tenantEmail << endl
				<< "Tenant Tel: " << node->tenantTel << endl
				<< "Gender: " << node->tenantGender << endl
				<< "Status: " << node->tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
		}

		bool left = preOrderFemale(node->left);
		bool right = preOrderFemale(node->right);

		return found || left || right;
	}

	//Display only male tenant
	bool preOrderMale(Tenant* node) {
		if (node == nullptr) return false;

		bool found = (node->tenantGender == "male");

		if (found) {
			cout << "Tenant ID: " << node->tenantID << endl
				<< "Tenant Username: " << node->username << endl
				<< "Tenant Name: " << node->tenantName << endl
				<< "Tenant Email: " << node->tenantEmail << endl
				<< "Tenant Tel: " << node->tenantTel << endl
				<< "Gender: " << node->tenantGender << endl
				<< "Status: " << node->tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
		}

		bool left = preOrderMale(node->left);
		bool right = preOrderMale(node->right);

		return found || left || right;
	}

	// Dispaly Tenant with active status only
	bool preOrderActive(Tenant* node) {
		if (node == nullptr) return false;

		// Perform the check for inactive tenants
		bool left = preOrderInactive(node->left);
		bool found = (node->tenantStatus == "active");
		bool right = preOrderActive(node->right);

		if (found) {
			cout << "Tenant ID: " << node->tenantID << endl
				<< "Tenant Username: " << node->username << endl
				<< "Tenant Name: " << node->tenantName << endl
				<< "Tenant Email: " << node->tenantEmail << endl
				<< "Tenant Tel: " << node->tenantTel << endl
				<< "Gender: " << node->tenantGender << endl
				<< "Status: " << node->tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
		}

		return left || found || right;
	}

	// Display tenant with inactive status
	bool preOrderInactive(Tenant* node) {
		if (node == nullptr) return false;

		// Perform the check for inactive tenants
		bool left = preOrderInactive(node->left);
		bool found = (node->tenantStatus == "inactive");
		bool right = preOrderInactive(node->right);

		if (found) {
			cout << "Tenant ID: " << node->tenantID << endl
				<< "Tenant Username: " << node->username << endl
				<< "Tenant Name: " << node->tenantName << endl
				<< "Tenant Email: " << node->tenantEmail << endl
				<< "Tenant Tel: " << node->tenantTel << endl
				<< "Gender: " << node->tenantGender << endl
				<< "Status: " << node->tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
		}

		return left || found || right;

		//Rember to add
		// If no matching tenants were found, print "No Result Found"
		/*if (!found) {
			cout << "No Result Found" << endl;
		}*/
	}

	// Search tenant by ID
	bool tenantIdSearch(Tenant* root, string searchID) {
		if (root == nullptr) {
			return false;
		}

		// Search in the left subtree
		tenantIdSearch(root->left, searchID);

		// Check current node
		// bool foundCurrent = false;
		if (root->tenantName.find(searchID) != string::npos) { //display all the data that have the search username
			// Display the tenant information
			cout << "Tenant ID: " << root->tenantID << endl
				<< "Tenant Username: " << root->username << endl
				<< "Tenant Name: " << root->tenantName << endl
				<< "Tenant Email: " << root->tenantEmail << endl
				<< "Tenant Tel: " << root->tenantTel << endl
				<< "Gender: " << root->tenantGender << endl
				<< "Status: " << root->tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
			// foundCurrent = true;
		}

		// Search in the right subtree
		tenantNameSearch(root->right, searchID);

		//remenber to add
		/*cout << "Enter tenant ID want to search: ";
		string searchID;
		getline(cin, searchName);
		bool found = tenant.tenantNameSearch(root, searchID);

		if (!found) {
			cout << "No result found" << endl;
		}*/

	}

	// Search Tenant by username
	bool tenantUsernameSearch(Tenant* root, string searchUsername) {
		if (root == nullptr) {
			return false;
		}

		// Search in the left subtree
		tenantUsernameSearch(root->left, searchUsername);

		// Check current node
		// bool foundCurrent = false;
		if (root->username.find(searchUsername) != string::npos) { //display all the data that have the search username
			// Display the tenant information
			cout << "Tenant ID: " << root->tenantID << endl
				<< "Tenant Username: " << root->username << endl
				<< "Tenant Name: " << root->tenantName << endl
				<< "Tenant Email: " << root->tenantEmail << endl
				<< "Tenant Tel: " << root->tenantTel << endl
				<< "Gender: " << root->tenantGender << endl
				<< "Status: " << root->tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
			// foundCurrent = true;
		}

		// Search in the right subtree
		tenantUsernameSearch(root->right, searchUsername);

		//remenber to add
		/*cout << "Enter username want to search: ";
		string searchUsername;
		getline(cin, searchUsername);
		bool found = tenant.bstSearch(root, searchUsername);

		if (!found) {
			cout << "No result found" << endl;
		}*/
	}

	// Search tenant by name
	bool tenantNameSearch(Tenant* root, string searchName) {
		if (root == nullptr) {
			return false;
		}

		// Search in the left subtree
		tenantNameSearch(root->left, searchName);

		// Check current node
		// bool foundCurrent = false;
		if (root->tenantName.find(searchName) != string::npos) { //display all the data that have the search username
			// Display the tenant information
			cout << "Tenant ID: " << root->tenantID << endl
				<< "Tenant Username: " << root->username << endl
				<< "Tenant Name: " << root->tenantName << endl
				<< "Tenant Email: " << root->tenantEmail << endl
				<< "Tenant Tel: " << root->tenantTel << endl
				<< "Gender: " << root->tenantGender << endl
				<< "Status: " << root->tenantStatus << "\n\n"
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