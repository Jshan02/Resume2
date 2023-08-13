#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

struct Manager {
    string username;
    string password;
    string employeeID;
    string managerName;
    string managerTel;
    string managerEmail;
    string managerStatus;
    string managerPosition;
};

struct ManagerTree {
    Manager data;
    ManagerTree* leftChild;
    ManagerTree* rightChild;

    // Create new manager account
    ManagerTree* bstNewManager(ManagerTree* root, string mUName, string mPassword, string empId, string mName, string mTel, string mEmail, string mStatus, string mPosition) {

        if (root == nullptr) {
            root = new ManagerTree();
            root->data.username = mUName;
            root->data.password = mPassword;
            root->data.employeeID = empId;
            root->data.managerName = mName;
            root->data.managerTel = mTel;
            root->data.managerEmail = mEmail;
            root->data.managerStatus = mStatus;
            root->data.managerPosition = mPosition;

        } else if (mUName < root->data.username) {
            root->leftChild = bstNewManager(root->leftChild, mUName, mPassword, empId, mName, mTel, mEmail, mStatus, mPosition);

        } else {
            root->rightChild= bstNewManager(root->rightChild, mUName, mPassword, empId, mName, mTel, mEmail, mStatus, mPosition);
        }
        return root;
    }

    // Login function
    bool login(ManagerTree* root, string uname, string pw) {
        if (bstSearchManagerUsername(root, uname)) {
            if (checkManagerStatus(root, uname) == "Active") {
                if (bstGetManagerPassword(root, uname) == pw) {
                    ofstream Myfile("loggedInUser.txt");
                    Myfile << uname;
                    Myfile.close();
                    return true;
                } else {
                    cout << "\nLogin Fail, Wrong Password Entered.\n";
                    return false;
                }
            } else {
                cout << "\nLogin fail. Your account status is inactive, request admin to change status before login.\n";
                return false;
            }
        } else {
            cout << "\nLogin Fail, Username Not Exists.\n";
            return false;
        }
    }

    bool bstSearchManagerUsername(ManagerTree* root, string uname) {
        if (root == nullptr) return false;
        if (root->data.username == uname) return true;
        return bstSearchManagerUsername(root->leftChild,uname) || bstSearchManagerUsername(root->rightChild, uname);
    }

    string checkManagerStatus (ManagerTree* root, string uname) {
        int cmp = strcmp(uname.c_str(), root->data.username.c_str());

        if (cmp == 0) {
            return root->data.managerStatus;
        } else if (cmp < 0) {
            return checkManagerStatus(root->leftChild, uname);
        } else {
            return checkManagerStatus(root->rightChild, uname);
        }
    }

    string bstGetManagerPassword(ManagerTree* root, string uname) {
        int cmp = strcmp(uname.c_str(), root->data.username.c_str());
        if (cmp == 0) {
            return root->data.password;
        } else if (cmp < 0) {
            return bstGetManagerPassword(root->leftChild, uname);
        } else {
            return bstGetManagerPassword(root->rightChild, uname);
        }
    }

    bool resignManager(ManagerTree*& root, const string& username) {
        if (root == nullptr) return false;

        if (username < root->data.username) {
            return resignManager(root->leftChild, username);
        } else if (username > root->data.username) {
            return resignManager(root->rightChild, username);
        } else {
            // Found the manager's record; updating the Position field
            root->data.managerPosition = "Resigned";
            return true;
        }
    }

    void filterResignedManagers(ManagerTree* root) {
        if (root == nullptr) return;
        filterResignedManagers(root->leftChild);
        if (root->data.managerPosition == "Resigned" && root->data.managerStatus == "Active") {
            cout << "Username: " << root->data.username << endl;
            cout << "Employee ID: " << root->data.employeeID << endl;
            cout << "Name: " << root->data.managerName << endl;
            cout << "Contact Number: " << root->data.managerTel << endl;
            cout << "Email: " << root->data.managerEmail << endl;
            cout << "Status: " << root->data.managerStatus << endl;
            cout << "Position: " << root->data.managerPosition << endl;
            cout << "---------------------------------------\n\n";

        }
        filterResignedManagers(root->rightChild);
    }

    bool setManagerToInactive(ManagerTree*& root, const string& username) {
        if (root == nullptr) return false;

        if (username < root->data.username) {
            return setManagerToInactive(root->leftChild, username);
        } else if (username > root->data.username) {
            return setManagerToInactive(root->rightChild, username);
        } else if (root->data.managerPosition == "Resigned") {
            // Found the manager's record with "Resigned" position; updating the status to "Inactive"
            root->data.managerStatus = "Inactive";
            return true;
        }
        return false;
    }
};