#include "DoctorManager.h"
#include <iostream>
#include <limits>

DoctorManager::DoctorManager() {}

void DoctorManager::addDoctor(const Doctor& d) {
    doctors.push_back(d);
}

bool DoctorManager::editDoctor(int id, const Doctor& newData) {
    for (auto& d : doctors) {
        if (d.getId() == id) {
            d = newData;
            return true;
        }
    }
    return false;
}

bool DoctorManager::deleteDoctor(int id) {
    for (auto it = doctors.begin(); it != doctors.end(); ++it) {
        if (it->getId() == id) {
            doctors.erase(it);
            return true;
        }
    }
    return false;
}

Doctor* DoctorManager::getDoctor(int id) {
    for (auto& d : doctors) {
        if (d.getId() == id) return &d;
    }
    return nullptr;
}

const std::vector<Doctor>& DoctorManager::getAllDoctors() const {
    return doctors;
}

void DoctorManager::setDoctors(const std::vector<Doctor>& loadedDoctors) {
    doctors = loadedDoctors;
}

Doctor* DoctorManager::recommendDoctor(const std::string& specialization) {
    Doctor* bestDoc = nullptr;
    size_t minPatients = std::numeric_limits<size_t>::max();

    for (auto& d : doctors) {
        if (d.isAvailable() && (d.getSpecialization() == specialization || specialization.empty())) { 
            if (d.getAssignedPatientCount() < minPatients) {
                minPatients = d.getAssignedPatientCount();
                bestDoc = &d;
            }
        }
    }
    return bestDoc;
}

void DoctorManager::displayAll() const {
    if (doctors.empty()) {
        std::cout << "No doctors registered.\n";
        return;
    }
    for (const auto& d : doctors) {
        d.displayDetails();
    }
}
