#include "Nurse.h"
#include <sstream>

Nurse::Nurse(int id, const std::string& name, const std::string& shift)
    : HospitalMember(id, name), shift(shift), assignedWardId(-1) {}

std::string Nurse::getShift() const { return shift; }
void Nurse::setShift(const std::string& newShift) { shift = newShift; }

int Nurse::getAssignedWardId() const { return assignedWardId; }
void Nurse::setAssignedWardId(int wardId) { assignedWardId = wardId; }

void Nurse::displayDetails() const {
    std::cout << "Nurse ID: " << id << " | Name: " << name
              << " | Shift: " << shift
              << " | Ward ID: " << (assignedWardId == -1 ? "None" : std::to_string(assignedWardId)) << "\n";
}

std::string Nurse::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << name << "," << shift << "," << assignedWardId;
    return oss.str();
}
