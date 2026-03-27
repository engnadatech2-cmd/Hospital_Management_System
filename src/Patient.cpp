#include "Patient.h"
#include <sstream>

Patient::Patient(int id, const std::string& name, int age, const std::string& disease, const std::string& admissionDate, Priority priorityLevel)
    : HospitalMember(id, name), age(age), disease(disease), admissionDate(admissionDate), priorityLevel(priorityLevel),
      assignedDoctorId(-1), assignedWardId(-1) {}

int Patient::getAge() const { return age; }
std::string Patient::getDisease() const { return disease; }
std::string Patient::getAdmissionDate() const { return admissionDate; }
Priority Patient::getPriorityLevel() const { return priorityLevel; }
int Patient::getAssignedDoctorId() const { return assignedDoctorId; }
int Patient::getAssignedWardId() const { return assignedWardId; }

void Patient::setAssignedDoctorId(int doctorId) { assignedDoctorId = doctorId; }
void Patient::setAssignedWardId(int wardId) { assignedWardId = wardId; }

std::string priorityToString(Priority p) {
    switch (p) {
        case Priority::Emergency: return "Emergency";
        case Priority::Urgent: return "Urgent";
        default: return "Normal";
    }
}

Priority stringToPriority(const std::string& s) {
    if (s == "Emergency") return Priority::Emergency;
    if (s == "Urgent") return Priority::Urgent;
    return Priority::Normal;
}

void Patient::displayDetails() const {
    std::cout << "Patient ID: " << id << " | Name: " << name 
              << " | Age: " << age << " | Disease: " << disease
              << " | Admitted: " << admissionDate 
              << " | Priority: " << priorityToString(priorityLevel)
              << " | Doc ID: " << (assignedDoctorId == -1 ? "None" : std::to_string(assignedDoctorId))
              << " | Ward ID: " << (assignedWardId == -1 ? "None" : std::to_string(assignedWardId)) << "\n";
}

std::string Patient::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << name << "," << age << "," << disease << "," << admissionDate << "," 
        << priorityToString(priorityLevel) << "," << assignedDoctorId << "," << assignedWardId;
    return oss.str();
}
