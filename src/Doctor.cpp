#include "Doctor.h"
#include <algorithm>
#include <sstream>

Doctor::Doctor(int id, const std::string& name, const std::string& specialization)
    : HospitalMember(id, name), specialization(specialization), available(true) {}

std::string Doctor::getSpecialization() const { return specialization; }
bool Doctor::isAvailable() const { return available; }
void Doctor::setAvailability(bool status) { available = status; }

size_t Doctor::getAssignedPatientCount() const { return assignedPatientIds.size(); }
const std::vector<int>& Doctor::getAssignedPatients() const { return assignedPatientIds; }

void Doctor::assignPatient(int patientId) {
    if (std::find(assignedPatientIds.begin(), assignedPatientIds.end(), patientId) == assignedPatientIds.end()) {
        assignedPatientIds.push_back(patientId);
    }
}

void Doctor::removePatient(int patientId) {
    assignedPatientIds.erase(
        std::remove(assignedPatientIds.begin(), assignedPatientIds.end(), patientId),
        assignedPatientIds.end()
    );
}

void Doctor::displayDetails() const {
    std::cout << "Doctor ID: " << id << " | Name: " << name
              << " | Specialization: " << specialization
              << " | Available: " << (available ? "Yes" : "No")
              << " | Patients Assigned: " << assignedPatientIds.size() << "\n";
}

std::string Doctor::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << name << "," << specialization << "," << (available ? 1 : 0);
    oss << ",";
    for (size_t i = 0; i < assignedPatientIds.size(); ++i) {
        oss << assignedPatientIds[i];
        if (i < assignedPatientIds.size() - 1) oss << " ";
    }
    return oss.str();
}
