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

    void updateDiagnosis(string newDisease)
    {
        disease = newDisease;
    }
};

#endif
