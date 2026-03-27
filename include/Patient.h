#ifndef PATIENT_H
#define PATIENT_H

#include "HospitalMember.h"
#include <string>

enum class Priority {
    Normal = 0,
    Urgent = 1,
    Emergency = 2
};

class Patient : public HospitalMember {
private:
    int age;
    std::string disease;
    std::string admissionDate;
    Priority priorityLevel;
    int assignedDoctorId;
    int assignedWardId;

public:
    Patient(int id, const std::string& name, int age, const std::string& disease, const std::string& admissionDate, Priority priorityLevel);

    int getAge() const;
    std::string getDisease() const;
    std::string getAdmissionDate() const;
    Priority getPriorityLevel() const;
    int getAssignedDoctorId() const;
    int getAssignedWardId() const;

    void setAssignedDoctorId(int doctorId);
    void setAssignedWardId(int wardId);

    void displayDetails() const override;
    
    // For serialization
    std::string toCSV() const;
};

std::string priorityToString(Priority p);
Priority stringToPriority(const std::string& s);

#endif
