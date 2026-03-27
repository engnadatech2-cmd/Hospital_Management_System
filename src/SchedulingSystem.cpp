#include "SchedulingSystem.h"
#include <iostream>

SchedulingSystem::SchedulingSystem() : currentTicket(1) {}

void SchedulingSystem::addRequest(int patientId, Priority priorityLevel) {
    ScheduleRequest req{patientId, priorityLevel, currentTicket++};
    queue.push(req);
}

bool SchedulingSystem::processNext(int doctorId, const std::string& date, const std::string& time) {
    if (queue.empty()) {
        return false;
    }
    ScheduleRequest nextItem = queue.top();
    queue.pop();

    Appointment appt(nextItem.patientId, doctorId, date, time, "Scheduled");
    appointments.push_back(appt);
    return true;
}

const std::vector<Appointment>& SchedulingSystem::getAllAppointments() const {
    return appointments;
}

void SchedulingSystem::setAppointments(const std::vector<Appointment>& loadedAppointments) {
    appointments = loadedAppointments;
}

const PriorityQueue<ScheduleRequest>& SchedulingSystem::getQueue() const {
    return queue;
}

void SchedulingSystem::setQueue(const std::vector<ScheduleRequest>& loadedQueueData, int nextTicket) {
    queue.buildHeap(loadedQueueData);
    currentTicket = nextTicket;
}

void SchedulingSystem::cancelAppointment(int patientId, int doctorId) {
    for (auto& appt : appointments) {
        if (appt.getPatientId() == patientId && appt.getDoctorId() == doctorId && appt.getStatus() == "Scheduled") {
            appt.setStatus("Cancelled");
            return;
        }
    }
}

void SchedulingSystem::displayAppointments() const {
    if (appointments.empty()) {
        std::cout << "No appointments registered.\n";
        return;
    }
    for (const auto& appt : appointments) {
        std::cout << "Patient ID: " << appt.getPatientId() 
                  << " | Doctor ID: " << appt.getDoctorId() 
                  << " | Date: " << appt.getDate() 
                  << " | Time: " << appt.getTime() 
                  << " | Status: " << appt.getStatus() << "\n";
    }
}
