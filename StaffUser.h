#ifndef STAFFUSER_H
#define STAFFUSER_H

#include <iostream>
#include <string>
using namespace std;

struct StaffUser {
private:
    int id;
    string name;
    string password;
    string role; // "Admin", "Doctor", "Receptionist"

public:
    // ============ Getters ============
    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getRole() {
        return role;
    }

    // password ما عندها getter عشان تبقى hidden تماماً

    // ============ Setters ============
    void setId(int i) {
        id = i;
    }

    void setName(string n) {
        name = n;
    }

    void setPassword(string pass) {
        password = pass;
    }

    void setRole(string r) {
        role = r;
    }

    // ============ Methods ============

    // ترجع true إذا كانت كلمة السر مطابقة
    bool checkPassword(string pass) {
        return password == pass;
    }

    // constructor فاضي عشان يشتغل مع الـ BST
    StaffUser() {
        id = -1;
        name = "";
        password = "";
        role = "";
    }

    // constructor كامل
    StaffUser(int i, string n, string pass, string r) {
        id = i;
        name = n;
        password = pass;
        role = r;
    }
};

#endif
