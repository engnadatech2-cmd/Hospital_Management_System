#include "FileHandler.h"
#include <fstream>
#include <sstream>

static std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    // Handle trailing empty element if needed, though getline normally suppresses it.
    if (!s.empty() && s.back() == delimiter) tokens.push_back("");
    return tokens;
}

FileHandler::FileHandler(const std::string& directory) : dataDir(directory) {}

bool FileHandler::savePatients(const PatientManager& pm) const {
    std::ofstream out(dataDir + "patients.csv");
    if (!out) return false;
    for (const auto& p : pm.getAllPatients()) { out << p.toCSV() << "\n"; }
    return true;
}

bool FileHandler::loadPatients(PatientManager& pm) const {
    std::ifstream in(dataDir + "patients.csv");
    if (!in) return false;
    std::vector<Patient> patients;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ',');
        if (tokens.size() >= 8) {
            int id = std::stoi(tokens[0]);
            std::string name = tokens[1];
            int age = std::stoi(tokens[2]);
            std::string disease = tokens[3];
            std::string date = tokens[4];
            Priority prio = stringToPriority(tokens[5]);
            Patient p(id, name, age, disease, date, prio);
            p.setAssignedDoctorId(std::stoi(tokens[6]));
            p.setAssignedWardId(std::stoi(tokens[7]));
            patients.push_back(p);
        }
    }
    pm.setPatients(patients);
    return true;
}

bool FileHandler::saveDoctors(const DoctorManager& dm) const {
    std::ofstream out(dataDir + "doctors.csv");
    if (!out) return false;
    for (const auto& d : dm.getAllDoctors()) { out << d.toCSV() << "\n"; }
    return true;
}

bool FileHandler::loadDoctors(DoctorManager& dm) const {
    std::ifstream in(dataDir + "doctors.csv");
    if (!in) return false;
    std::vector<Doctor> doctors;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            int id = std::stoi(tokens[0]);
            std::string name = tokens[1];
            std::string spec = tokens[2];
            bool avail = (std::stoi(tokens[3]) == 1);
            Doctor d(id, name, spec);
            d.setAvailability(avail);
            if (tokens.size() > 4 && !tokens[4].empty()) {
                auto pids = split(tokens[4], ' ');
                for (const auto& pidStr : pids) {
                    if(!pidStr.empty()) d.assignPatient(std::stoi(pidStr));
                }
            }
            doctors.push_back(d);
        }
    }
    dm.setDoctors(doctors);
    return true;
}

bool FileHandler::saveWards(const WardManager& wm) const {
    std::ofstream out(dataDir + "wards.csv");
    if (!out) return false;
    for (const auto& w : wm.getAllWards()) { out << w.toCSV() << "\n"; }
    return true;
}

bool FileHandler::loadWards(WardManager& wm) const {
    std::ifstream in(dataDir + "wards.csv");
    if (!in) return false;
    std::vector<Ward> wards;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            int id = std::stoi(tokens[0]);
            int cap = std::stoi(tokens[1]);
            int occ = std::stoi(tokens[2]);
            WardType type = stringToWardType(tokens[3]);
            Ward w(id, cap, type);
            w.setCurrentOccupancy(occ);
            wards.push_back(w);
        }
    }
    wm.setWards(wards);
    return true;
}

bool FileHandler::saveAppointments(const SchedulingSystem& ss) const {
    std::ofstream out(dataDir + "appointments.csv");
    if (!out) return false;
    for (const auto& a : ss.getAllAppointments()) { out << a.toCSV() << "\n"; }
    return true;
}

bool FileHandler::loadAppointments(SchedulingSystem& ss) const {
    std::ifstream in(dataDir + "appointments.csv");
    if (!in) return false;
    std::vector<Appointment> apps;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ',');
        if (tokens.size() >= 5) {
            apps.emplace_back(std::stoi(tokens[0]), std::stoi(tokens[1]), tokens[2], tokens[3], tokens[4]);
        }
    }
    ss.setAppointments(apps);
    return true;
}

bool FileHandler::saveQueue(const SchedulingSystem& ss) const {
    std::ofstream out(dataDir + "queue.csv");
    if (!out) return false;
    out << ss.getCurrentTicket() << "\n";
    for (const auto& req : ss.getQueue().getSequence()) {
        out << req.patientId << "," << priorityToString(req.priorityLevel) << "," << req.ticketNumber << "\n";
    }
    return true;
}

bool FileHandler::loadQueue(SchedulingSystem& ss) const {
    std::ifstream in(dataDir + "queue.csv");
    if (!in) return false;
    std::string line;
    if (!std::getline(in, line)) return false;
    int nextTicket = std::stoi(line);
    
    std::vector<ScheduleRequest> reqs;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ',');
        if (tokens.size() >= 3) {
            reqs.push_back({std::stoi(tokens[0]), stringToPriority(tokens[1]), std::stoi(tokens[2])});
        }
    }
    ss.setQueue(reqs, nextTicket);
    return true;
}

bool FileHandler::saveAll(const PatientManager& pm, const DoctorManager& dm, const WardManager& wm, const SchedulingSystem& ss) const {
    return savePatients(pm) && saveDoctors(dm) && saveWards(wm) && saveAppointments(ss) && saveQueue(ss);
}

bool FileHandler::loadAll(PatientManager& pm, DoctorManager& dm, WardManager& wm, SchedulingSystem& ss) const {
    loadPatients(pm);
    loadDoctors(dm);
    loadWards(wm);
    loadAppointments(ss);
    loadQueue(ss);
    return true;
}
