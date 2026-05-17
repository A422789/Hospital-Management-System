#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

#include "AccountManager.h"
#include "PatientManager.h"
#include "AppointmentQueue.h"
#include "EmergencyRoom.h"
#include "ActionTracker.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

class SystemInterface {
private:
    AccountManager  accountMgr;
    PatientManager  patientMgr;
    AppointmentQueue queueMgr;
    EmergencyRoom   emergencyMgr;
    ActionTracker   undoMgr;

    // ==============================
    //       UI Helpers
    // ==============================
    void displayHeader(string title) {
        cout << "\n=================================================" << endl;
        cout << "   " << title << endl;
        cout << "=================================================" << endl;
    }

    // Input validation — يمنع crash لو أدخل نص بدل رقم
    int getIntInput() {
        int val;
        while (!(cin >> val)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Enter a valid number: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return val;
    }

    string getLineInput() {
        string s;
        getline(cin, s);
        return s;
    }

    void pause() {
        cout << "\n  Press Enter to continue...";
        cin.get();
    }

    // ==============================
    //       Admin Menu
    // ==============================
    void adminMenu(StaffUser user) {
        int choice;
        do {
            displayHeader("ADMIN DASHBOARD");
            cout << "  Welcome, " << user.getName() << "\n" << endl;
            cout << "  [1] Register New Employee" << endl;
            cout << "  [2] View All Employees" << endl;
            cout << "  [3] Delete User Account" << endl;
            cout << "  [4] Undo Last Action" << endl;
            cout << "  [5] Logout" << endl;
            cout << "\n  Choice: ";
            choice = getIntInput();

            switch (choice) {
                case 1: {
                    displayHeader("REGISTER NEW EMPLOYEE");
                    int id; string name, pass, role;
                    cout << "  Enter ID              : "; id   = getIntInput();
                    cout << "  Enter Name            : "; name = getLineInput();
                    cout << "  Enter Password        : "; pass = getLineInput();
                    cout << "  Role (Admin/Doctor/Receptionist): "; role = getLineInput();

                    StaffUser newUser(id, name, pass, role);
                    accountMgr.addUser(newUser);

                    Action a; a.type = "ADD"; a.target = "Staff"; a.sData = newUser;
                    undoMgr.pushAction(a);
                    pause(); break;
                }
                case 2: {
                    displayHeader("ALL EMPLOYEES");
                    accountMgr.displayAll();
                    pause(); break;
                }
                case 3: {
                    displayHeader("DELETE USER ACCOUNT");
                    int id;
                    cout << "  Enter Employee ID to delete: "; id = getIntInput();

                    StaffUser toDelete = accountMgr.getUser(id);
                    if (toDelete.getId() == -1) {
                        cout << "  [!] Employee not found." << endl;
                        pause(); break;
                    }
                    accountMgr.deleteUser(id);

                    Action a; a.type = "DELETE"; a.target = "Staff"; a.sData = toDelete;
                    undoMgr.pushAction(a);
                    pause(); break;
                }
                case 4: {
                    displayHeader("UNDO LAST ACTION");
                    undoMgr.undo(accountMgr, patientMgr);
                    pause(); break;
                }
                case 5:
                    cout << "\n  [→] Logging out...\n" << endl;
                    break;
                default:
                    cout << "  [!] Invalid choice.\n" << endl;
            }
        } while (choice != 5);
    }

    // ==============================
    //    Receptionist Menu
    // ==============================
    void receptionMenu(StaffUser user) {
        int choice;
        do {
            displayHeader("RECEPTIONIST DASHBOARD");
            cout << "  Welcome, " << user.getName() << "\n" << endl;
            cout << "  [1] Register New Patient" << endl;
            cout << "  [2] Add Patient to Waiting Queue" << endl;
            cout << "  [3] View Current Waiting Queue" << endl;
            cout << "  [4] Patient Discharge" << endl;
            cout << "  [5] Logout" << endl;
            cout << "\n  Choice: ";
            choice = getIntInput();

            switch (choice) {
                case 1: {
                    displayHeader("REGISTER NEW PATIENT");
                    int id, sev; string name, disease;
                    cout << "  Enter Patient ID     : "; id      = getIntInput();
                    cout << "  Enter Name           : "; name    = getLineInput();
                    cout << "  Enter Disease        : "; disease = getLineInput();
                    cout << "  Enter Severity (1-5) : "; sev     = getIntInput();

                    PatientRecord newP(id, name, disease, sev);
                    patientMgr.addPatient(newP);

                    Action a; a.type = "ADD"; a.target = "Patient"; a.pData = newP;
                    undoMgr.pushAction(a);
                    pause(); break;
                }
                case 2: {
                    displayHeader("ADD TO WAITING QUEUE");
                    int id;
                    cout << "  Enter Patient ID: "; id = getIntInput();
                    PatientRecord p = patientMgr.getPatient(id);
                    if (p.id == -1)
                        cout << "  [!] Patient not found. Register the patient first." << endl;
                    else {
                        queueMgr.enqueue(id);
                        cout << "  Patient: " << p.name << endl;
                    }
                    pause(); break;
                }
                case 3: {
                    displayHeader("CURRENT WAITING QUEUE");
                    queueMgr.displayQueue();
                    pause(); break;
                }
                case 4: {
                    displayHeader("PATIENT DISCHARGE");
                    int id;
                    cout << "  Enter Patient ID to discharge: "; id = getIntInput();
                    PatientRecord toDelete = patientMgr.getPatient(id);
                    if (toDelete.id == -1) {
                        cout << "  [!] Patient not found." << endl;
                        pause(); break;
                    }
                    patientMgr.deletePatient(id);

                    Action a; a.type = "DELETE"; a.target = "Patient"; a.pData = toDelete;
                    undoMgr.pushAction(a);
                    pause(); break;
                }
                case 5:
                    cout << "\n  [→] Logging out...\n" << endl;
                    break;
                default:
                    cout << "  [!] Invalid choice.\n" << endl;
            }
        } while (choice != 5);
    }

    // ==============================
    //       Doctor Menu
    // ==============================
    void doctorMenu(StaffUser user) {
        int choice;
        do {
            displayHeader("DOCTOR DASHBOARD");
            cout << "  Welcome, Dr. " << user.getName() << "\n" << endl;
            cout << "  [1] Call Next Patient" << endl;
            cout << "  [2] Search Patient Medical Record" << endl;
            cout << "  [3] Add Emergency Case" << endl;
            cout << "  [4] View Emergency Cases by Severity" << endl;
            cout << "  [5] Update Patient Diagnosis" << endl;
            cout << "  [6] Logout" << endl;
            cout << "\n  Choice: ";
            choice = getIntInput();

            switch (choice) {
                case 1: {
                    displayHeader("CALL NEXT PATIENT");
                    int id = queueMgr.dequeue();
                    if (id != -1) {
                        cout << "  Full record:" << endl;
                        patientMgr.searchById(id);
                    }
                    pause(); break;
                }
                case 2: {
                    displayHeader("SEARCH PATIENT RECORD");
                    int id;
                    cout << "  Enter Patient ID: "; id = getIntInput();
                    patientMgr.searchById(id);
                    pause(); break;
                }
                case 3: {
                    displayHeader("ADD EMERGENCY CASE");
                    int id;
                    cout << "  Enter Patient ID: "; id = getIntInput();
                    PatientRecord p = patientMgr.getPatient(id);
                    if (p.id == -1)
                        cout << "  [!] Patient not found. Cannot add to ER." << endl;
                    else {
                        emergencyMgr.addCase(p);
                        cout << "  [+] " << p.name << " added to Emergency Room." << endl;
                    }
                    pause(); break;
                }
                case 4: {
                    displayHeader("EMERGENCY CASES BY SEVERITY");
                    emergencyMgr.bubbleSort();
                    emergencyMgr.displayER();
                    pause(); break;
                }
                case 5: {
                    displayHeader("UPDATE PATIENT DIAGNOSIS");
                    int id; string newDisease;
                    cout << "  Enter Patient ID    : "; id         = getIntInput();
                    cout << "  Enter New Diagnosis : "; newDisease = getLineInput();
                    patientMgr.updateDiagnosis(id, newDisease);
                    pause(); break;
                }
                case 6:
                    cout << "\n  [→] Logging out...\n" << endl;
                    break;
                default:
                    cout << "  [!] Invalid choice.\n" << endl;
            }
        } while (choice != 6);
    }

public:
    // ==============================
    //     Constructor — Global Admin
    // ==============================
    SystemInterface() {
        // Admin إلزامي عشان يقدر يدخل أول مرة
        accountMgr.addUser(StaffUser(1, "System Admin", "123", "Admin"));
        cout << endl;
    }

    // ==============================
    //        Main Run Loop
    // ==============================
    void run() {
        int choice;
        do {
            displayHeader("HOSPITAL MANAGEMENT SYSTEM");
            cout << "  [1] Login to System" << endl;
            cout << "  [2] About System" << endl;
            cout << "  [3] Exit" << endl;
            cout << "\n  Choice: ";
            choice = getIntInput();

            switch (choice) {
                case 1: {
                    int id; string pass;
                    cout << "\n  Enter User ID   : "; id   = getIntInput();
                    cout << "  Enter Password  : "; pass = getLineInput();

                    StaffUser logged = accountMgr.login(id, pass);
                    if (logged.getId() == -1) break; // فشل الـ login

                    string role = logged.getRole();
                    if      (role == "Admin")        adminMenu(logged);
                    else if (role == "Doctor")       doctorMenu(logged);
                    else if (role == "Receptionist") receptionMenu(logged);
                    else cout << "  [!] Unknown role. Contact admin." << endl;
                    break;
                }
                case 2:
                    displayHeader("ABOUT THE SYSTEM");
                    cout << "  Hospital Management System v1.0" << endl;
                    cout << "  Built with: BST, Queue, Stack, Bubble Sort" << endl;
                    cout << "  Team: 4 Programmers | Data Structures Course" << endl;
                    pause();
                    break;
                case 3:
                    cout << "\n  Goodbye! Stay healthy.\n" << endl;
                    break;
                default:
                    cout << "  [!] Invalid choice.\n" << endl;
            }
        } while (choice != 3);
    }
};

#endif
