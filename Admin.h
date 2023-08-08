#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

struct Admin {
    string username;
    string password;

    Admin(string uname, string pw) {
        username = uname;
        password = pw;
    }

    bool login(string uname, string pw) {
        return (uname == username && pw == password);
    }
};