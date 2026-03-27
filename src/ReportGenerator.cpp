#include "ReportGenerator.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void ReportGenerator::displayTotalPatientsToday(const PatientManager& pm, const std::string& todayDate) {
    int count = 0;
    for (const auto& p : pm.getAllPatients()) {
        if (p.getAdmissionDate() == todayDate) count++;
    }
    std::cout << "Total patients admitted today (" << todayDate << "): " << count << "\n";
}

void ReportGenerator::displayBusiestDoctor(const DoctorManager& dm) {
    const Doctor* busiest = nullptr;
    size_t maxPatients = 0;

    for (const auto& d : dm.getAllDoctors()) {
        if (d.getAssignedPatientCount() >= maxPatients) {
            if (d.getAssignedPatientCount() > maxPatients || busiest == nullptr) {
                maxPatients = d.getAssignedPatientCount();
                busiest = &d;
            }
        }
    }

    if (busiest) {
        std::cout << "Busiest Doctor: " << busiest->getName() << " (ID: " << busiest->getId() 
                  << ") with " << maxPatients << " patients.\n";
    } else {
        std::cout << "No doctors have assigned patients.\n";
    }
}

void ReportGenerator::displayBedOccupancyRate(const WardManager& wm) {
    std::cout << "Bed Occupancy Rates by Ward:\n";
    for (const auto& w : wm.getAllWards()) {
        double rate = 0.0;
        if (w.getCapacity() > 0) {
            rate = (static_cast<double>(w.getCurrentOccupancy()) / w.getCapacity()) * 100.0;
        }
        std::cout << "Ward ID " << w.getId() << " (" << w.getTypeString() << "): "
                  << std::fixed << std::setprecision(2) << rate << "% (" 
                  << w.getCurrentOccupancy() << "/" << w.getCapacity() << " occupied)\n";
    }
}

bool ReportGenerator::exportReport(const std::string& filepath, const PatientManager& pm, const DoctorManager& dm, const WardManager& wm) {
    std::ofstream out(filepath);
    if (!out) return false;

    out << "=== HOSPITAL SYSTEM REPORT ===\n\n";
    out << "Total Patients Registered: " << pm.getAllPatients().size() << "\n";
    out << "Total Doctors Registered: " << dm.getAllDoctors().size() << "\n";
    out << "Total Wards Registered: " << wm.getAllWards().size() << "\n\n";

    out << "--- Ward Occupancy ---\n";
    for (const auto& w : wm.getAllWards()) {
        out << "Ward " << w.getId() << " (" << w.getTypeString() << "): " 
            << w.getCurrentOccupancy() << "/" << w.getCapacity() << "\n";
    }

    out << "\n--- Busiest Doctors ---\n";
    for (const auto& d : dm.getAllDoctors()) {
        out << d.getName() << " (" << d.getSpecialization() << ") - " 
            << d.getAssignedPatientCount() << " patients\n";
    }

    out.close();
    return true;
}
