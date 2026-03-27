#include "PatientManager.h"
#include <iostream>

PatientManager::PatientManager() {}

void PatientManager::addPatient(const Patient& p) {
    patients.push_back(p);
}

bool PatientManager::editPatient(int id, const Patient& newData) {
    for (auto& p : patients) {
        if (p.getId() == id) {
            p = newData;
            return true;
        }
    }
    return false;
}

bool PatientManager::deletePatient(int id) {
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (it->getId() == id) {
            patients.erase(it);
            return true;
        }
    }
    return false;
}

Patient* PatientManager::getPatient(int id) {
    for (auto& p : patients) {
        if (p.getId() == id) return &p;
    }
    return nullptr;
}

const std::vector<Patient>& PatientManager::getAllPatients() const {
    return patients;
}

void PatientManager::setPatients(const std::vector<Patient>& loadedPatients) {
    patients = loadedPatients;
}

void PatientManager::displayAll() const {
    if (patients.empty()) {
        std::cout << "No patients registered.\n";
        return;
    }
    for (const auto& p : patients) {
        p.displayDetails();
    }
}
