#include <iostream>
#include <string>

using namespace std;

struct Interface {
    void managerDashboard(TenantTree* root) {
        cout << "Welcome to Manager Dashboard\n";
        cout << "=============================\n\n";
        cout << "1. View All Tenant\n";
        cout << "2. Search Tenant\n";
        cout << "3. Delete Tenant Account\n";
        cout << "4. Manage Tenancy\n";
        cout << "5. View Report\n";

        int dashboardOption;
        cout << "Please enter your option: ";
        cin >> dashboardOption;

        if (dashboardOption == 1){
          managerViewAllTenantMenu(root);
        }
    }

    void managerViewAllTenantMenu(TenantTree* root){
        TenantTree tenant;
        tenant.dispAllTenant(root);
    }


    // void managerSearchMenu(TenantTree* root){
    //     cout << "Search Tenant\n";
    //     cout << "==================\n\n";
    //     cout << "1. Search by Username\n";
    //     cout << "2. Search by Tenant Name\n\n";

    //     int searchOption;
    //     cout << "Please enter an option: ";
    //     cin >> searchOption;

    //     if (searchOption == 1){
    //         cout << "Please enter username: ";

    //         string searchUsername;
    //         getline(cin, searchUsername);
    //         TenantTree tenant;
    //         bool found = tenant.bstSearchUsername(root, searchUsername);

    //         if (!found) {
    //             cout << "No result found." << endl;
    //         }
    //     }
    //     else if (searchOption == 2) {
    //         cout << "Pleaser enter name: ";
            
    //         string searchName;
    //         getline(cin, searchName);
    //     }
    // }
};
