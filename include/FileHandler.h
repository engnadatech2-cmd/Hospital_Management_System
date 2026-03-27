#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "PatientManager.h"
#include "DoctorManager.h"
#include "WardManager.h"
#include "SchedulingSystem.h"
#include <string>

class FileHandler {
private:
    std::string dataDir;

public:
    FileHandler(const std::string& directory = "data/");

    bool savePatients(const PatientManager& pm) const;
    bool loadPatients(PatientManager& pm) const;

    bool saveDoctors(const DoctorManager& dm) const;
    bool loadDoctors(DoctorManager& dm) const;

    bool saveWards(const WardManager& wm) const;
    bool loadWards(WardManager& wm) const;

    bool saveAppointments(const SchedulingSystem& ss) const;
    bool loadAppointments(SchedulingSystem& ss) const;

    bool saveQueue(const SchedulingSystem& ss) const;
    bool loadQueue(SchedulingSystem& ss) const;

    bool saveAll(const PatientManager& pm, const DoctorManager& dm, const WardManager& wm, const SchedulingSystem& ss) const;
    bool loadAll(PatientManager& pm, DoctorManager& dm, WardManager& wm, SchedulingSystem& ss) const;
};

#endif
