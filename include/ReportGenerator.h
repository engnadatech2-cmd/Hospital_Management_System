#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include "PatientManager.h"
#include "DoctorManager.h"
#include "WardManager.h"

class ReportGenerator {
public:
    static void displayTotalPatientsToday(const PatientManager& pm, const std::string& todayDate);
    static void displayBusiestDoctor(const DoctorManager& dm);
    static void displayBedOccupancyRate(const WardManager& wm);
    
    // Exports full report to .txt file in data folder
    static bool exportReport(const std::string& filepath, const PatientManager& pm, const DoctorManager& dm, const WardManager& wm);
};

#endif
