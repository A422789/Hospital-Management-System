#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H

#include <iostream>
using namespace std;

struct PatientRecord
{
    int id;
    string name;
    string disease;
    int severity;

    // Default Constructor (needed for array declaration in EmergencyRoom.h)
    PatientRecord() {
        id = -1;
        name = "";
        disease = "";
        severity = 0;
    }

    // Parameterized Constructor
    PatientRecord(int i, string n, string d, int s) {
        id = i;
        name = n;
        disease = d;
        severity = s;
    }

    void updateDiagnosis(string newDisease)
    {
        disease = newDisease;
    }
};

#endif
