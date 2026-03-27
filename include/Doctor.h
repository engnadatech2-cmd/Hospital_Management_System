#ifndef DOCTOR_H
#define DOCTOR_H

#include "HospitalMember.h"
#include <string>
#include <vector>

class Doctor : public HospitalMember {
private:
    std::string specialization;
    bool available;
    std::vector<int> assignedPatientIds;

public:
    Doctor(int id, const std::string& name, const std::string& specialization);

    std::string getSpecialization() const;
    bool isAvailable() const;
    void setAvailability(bool status);
    
    size_t getAssignedPatientCount() const;
    const std::vector<int>& getAssignedPatients() const;
    
    void assignPatient(int patientId);
    void removePatient(int patientId);

    void displayDetails() const override;

    // For serialization format
    std::string toCSV() const;
};

#endif
