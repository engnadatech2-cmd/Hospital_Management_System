#include "Appointment.h"
#include <sstream>

Appointment::Appointment(int patientId, int doctorId, const std::string& date, const std::string& time, const std::string& status)
    : patientId(patientId), doctorId(doctorId), date(date), time(time), status(status) {}

int Appointment::getPatientId() const { return patientId; }
int Appointment::getDoctorId() const { return doctorId; }
std::string Appointment::getDate() const { return date; }
std::string Appointment::getTime() const { return time; }
std::string Appointment::getStatus() const { return status; }

void Appointment::setStatus(const std::string& newStatus) { status = newStatus; }

std::string Appointment::toCSV() const {
    std::ostringstream oss;
    oss << patientId << "," << doctorId << "," << date << "," << time << "," << status;
    return oss.str();
}
