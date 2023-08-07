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
};

struct TenantTree{
	Tenant data;
	TenantTree* left;
	TenantTree* right;

	//BST Tenant Data Insertion
	TenantTree* tenantDataInsert(TenantTree* root, string tenantID, string username, string tenantName, string tenantEmail, string tenantPassword,
		string tenantTel, string tenantGender, string tenantStatus) {
		if (root == nullptr) {
			root = new TenantTree();
			root->data.tenantID = tenantID;
			root->data.username = username;
			root->data.tenantName = tenantName;
			root->data.tenantEmail = tenantEmail;
			root->data.password = tenantPassword;
			root->data.tenantTel = tenantTel;
			root->data.tenantGender = tenantGender;
			root->data.tenantStatus = tenantStatus;
			root->left = root->right = nullptr;
		}
		else if (tenantID < root->data.tenantID) {
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
	void preOrder(TenantTree* node) {
	    if (node == nullptr) return;
		cout << "Tenant ID: " << node->data.tenantID << endl
			<< "Tenant Username: " << node->data.username << endl
			<< "Tenant Name: " << node->data.tenantName << endl
			<< "Tenant Email: " << node->data.tenantEmail << endl
			<< "Tenant Tel: " << node->data.tenantTel << endl
			<< "Gender: " << node->data.tenantGender << endl
			<< "Status: " << node->data.tenantStatus << "\n\n"
			<< "------------------------------------------------\n";
	    preOrder(node->left);
	    preOrder(node->right);
	}

	// Display only female tenant
	bool preOrderFemale(TenantTree* node) {
		if (node == nullptr) return false;

		bool found = (node->data.tenantGender == "female");

		if (found) {
			cout << "Tenant ID: " << node->data.tenantID << endl
				<< "Tenant Username: " << node->data.username << endl
				<< "Tenant Name: " << node->data.tenantName << endl
				<< "Tenant Email: " << node->data.tenantEmail << endl
				<< "Tenant Tel: " << node->data.tenantTel << endl
				<< "Gender: " << node->data.tenantGender << endl
				<< "Status: " << node->data.tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
		}

		bool left = preOrderFemale(node->left);
		bool right = preOrderFemale(node->right);

		return found || left || right;
	}

	//Display only male tenant
	bool preOrderMale(TenantTree* node) {
		if (node == nullptr) return false;

		bool found = (node->data.tenantGender == "male");

		if (found) {
			cout << "Tenant ID: " << node->data.tenantID << endl
				<< "Tenant Username: " << node->data.username << endl
				<< "Tenant Name: " << node->data.tenantName << endl
				<< "Tenant Email: " << node->data.tenantEmail << endl
				<< "Tenant Tel: " << node->data.tenantTel << endl
				<< "Gender: " << node->data.tenantGender << endl
				<< "Status: " << node->data.tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
		}

		bool left = preOrderMale(node->left);
		bool right = preOrderMale(node->right);

		return found || left || right;
	}

	// Dispaly Tenant with active status only
	bool preOrderActive(TenantTree* node) {
		if (node == nullptr) return false;

		// Perform the check for inactive tenants
		bool left = preOrderActive(node->left);
		bool found = (node->data.tenantStatus == "active");
		bool right = preOrderActive(node->right);

		if (found) {
			cout << "Tenant ID: " << node->data.tenantID << endl
				<< "Tenant Username: " << node->data.username << endl
				<< "Tenant Name: " << node->data.tenantName << endl
				<< "Tenant Email: " << node->data.tenantEmail << endl
				<< "Tenant Tel: " << node->data.tenantTel << endl
				<< "Gender: " << node->data.tenantGender << endl
				<< "Status: " << node->data.tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
		}

		return left || found || right;
	}

	// Display tenant with inactive status
	bool preOrderInactive(TenantTree* node) {
		if (node == nullptr) return false;

		// Perform the check for inactive tenants
		bool left = preOrderInactive(node->left);
		bool found = (node->data.tenantStatus == "inactive");
		bool right = preOrderInactive(node->right);

		if (found) {
			cout << "Tenant ID: " << node->data.tenantID << endl
				<< "Tenant Username: " << node->data.username << endl
				<< "Tenant Name: " << node->data.tenantName << endl
				<< "Tenant Email: " << node->data.tenantEmail << endl
				<< "Tenant Tel: " << node->data.tenantTel << endl
				<< "Gender: " << node->data.tenantGender << endl
				<< "Status: " << node->data.tenantStatus << "\n\n"
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
	bool tenantIdSearch(TenantTree* root, string searchID) {
		if (root == nullptr) {
			return false;
		}

		// Search in the left subtree
		tenantIdSearch(root->left, searchID);

		// Check current node
		// bool foundCurrent = false;
		if (root->data.tenantName.find(searchID) != string::npos) { //display all the data that have the search username
			// Display the tenant information
			cout << "Tenant ID: " << root->data.tenantID << endl
				<< "Tenant Username: " << root->data.username << endl
				<< "Tenant Name: " << root->data.tenantName << endl
				<< "Tenant Email: " << root->data.tenantEmail << endl
				<< "Tenant Tel: " << root->data.tenantTel << endl
				<< "Gender: " << root->data.tenantGender << endl
				<< "Status: " << root->data.tenantStatus << "\n\n"
				<< "------------------------------------------------\n";
			// foundCurrent = true;
		}

		// Search in the right subtree
		tenantIdSearch(root->right, searchID);

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
	bool tenantUsernameSearch(TenantTree* root, string searchUsername) {
		if (root == nullptr) {
			return false;
		}

		// Search in the left subtree
		tenantUsernameSearch(root->left, searchUsername);

		// Check current node
		// bool foundCurrent = false;
		if (root->data.username.find(searchUsername) != string::npos) { //display all the data that have the search username
			// Display the tenant information
			cout << "Tenant ID: " << root->data.tenantID << endl
				<< "Tenant Username: " << root->data.username << endl
				<< "Tenant Name: " << root->data.tenantName << endl
				<< "Tenant Email: " << root->data.tenantEmail << endl
				<< "Tenant Tel: " << root->data.tenantTel << endl
				<< "Gender: " << root->data.tenantGender << endl
				<< "Status: " << root->data.tenantStatus << "\n\n"
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
			cout << "Tenant ID: " << root->data.tenantID << endl
				<< "Tenant Username: " << root->data.username << endl
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