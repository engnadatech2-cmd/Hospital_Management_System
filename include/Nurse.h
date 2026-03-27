#ifndef NURSE_H
#define NURSE_H

#include "HospitalMember.h"
#include <string>

class Nurse : public HospitalMember {
private:
    std::string shift; // e.g. "Morning", "Night"
    int assignedWardId;

public:
    Nurse(int id, const std::string& name, const std::string& shift);

    std::string getShift() const;
    void setShift(const std::string& newShift);
    
    int getAssignedWardId() const;
    void setAssignedWardId(int wardId);

    void displayDetails() const override;

    std::string toCSV() const;
};

#endif
