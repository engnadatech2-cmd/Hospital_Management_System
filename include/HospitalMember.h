#ifndef HOSPITAL_MEMBER_H
#define HOSPITAL_MEMBER_H

#include <string>
#include <iostream>

class HospitalMember {
protected:
    int id;
    std::string name;

public:
    HospitalMember(int id, const std::string& name);
    virtual ~HospitalMember() = default;

    int getId() const;
    std::string getName() const;

    virtual void displayDetails() const = 0; // Pure virtual function
};

#endif
