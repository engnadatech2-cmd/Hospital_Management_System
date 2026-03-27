#ifndef DOCTOR_MANAGER_H
#define DOCTOR_MANAGER_H

#include "Doctor.h"
#include <vector>

class DoctorManager {
private:
    std::vector<Doctor> doctors;

public:
    DoctorManager();

    void addDoctor(const Doctor& d);
    bool editDoctor(int id, const Doctor& newData);
    bool deleteDoctor(int id);
    Doctor* getDoctor(int id);
    const std::vector<Doctor>& getAllDoctors() const;
    void setDoctors(const std::vector<Doctor>& loadedDoctors);

    // Recommend doc based on specialization and lowest patient count
    Doctor* recommendDoctor(const std::string& specialization);

    void displayAll() const;
};

#endif
