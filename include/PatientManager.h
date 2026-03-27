#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H

#include "Patient.h"
#include <vector>

class PatientManager {
private:
    std::vector<Patient> patients;

public:
    PatientManager();

    void addPatient(const Patient& p);
    bool editPatient(int id, const Patient& newData);
    bool deletePatient(int id);
    Patient* getPatient(int id);
    const std::vector<Patient>& getAllPatients() const;
    void setPatients(const std::vector<Patient>& loadedPatients);

    void displayAll() const;
};

#endif
