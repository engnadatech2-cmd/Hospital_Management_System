#ifndef SCHEDULING_SYSTEM_H
#define SCHEDULING_SYSTEM_H

#include "PriorityQueue.h"
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include <vector>

struct ScheduleRequest {
    int patientId;
    Priority priorityLevel;
    int ticketNumber;

    bool operator<(const ScheduleRequest& other) const {
        if (priorityLevel != other.priorityLevel) {
            // Higher priority enum value means higher priority (Emergency > Urgent > Normal)
            return static_cast<int>(priorityLevel) < static_cast<int>(other.priorityLevel);
        }
        // If priorities are equal, lower ticket number means higher priority (First Come First Served)
        return ticketNumber > other.ticketNumber;
    }
};

class SchedulingSystem {
private:
    PriorityQueue<ScheduleRequest> queue;
    int currentTicket;
    std::vector<Appointment> appointments;

public:
    SchedulingSystem();

    void addRequest(int patientId, Priority priorityLevel);
    
    bool processNext(int doctorId, const std::string& date, const std::string& time);
    
    const std::vector<Appointment>& getAllAppointments() const;
    void setAppointments(const std::vector<Appointment>& loadedAppointments);

    const PriorityQueue<ScheduleRequest>& getQueue() const;
    void setQueue(const std::vector<ScheduleRequest>& loadedQueueData, int nextTicket);

    int getCurrentTicket() const { return currentTicket; }
    void setCurrentTicket(int t) { currentTicket = t; }

    void displayAppointments() const;
    void cancelAppointment(int patientId, int doctorId);
};

#endif
