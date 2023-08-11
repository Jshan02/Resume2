#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

struct Admin {
    string username;
    string password;
    
    void presetAdmin(string uname, string pw) {
        username = uname;
        password = pw;
    }

    bool login(string uname, string pw) {
        return (uname == "admin" && pw == "admin123");
    }
};