#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:
    int patientId;
    int doctorId;
    std::string date;
    std::string time;
    std::string status; // e.g., "Scheduled", "Completed", "Cancelled"

public:
    Appointment(int patientId, int doctorId, const std::string& date, const std::string& time, const std::string& status = "Scheduled");

    int getPatientId() const;
    int getDoctorId() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;

    void setStatus(const std::string& newStatus);

    std::string toCSV() const;
};

#endif
