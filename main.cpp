#include <iostream>
#include <string>
#include "HospitalMember.h"
#include "Patient.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Ward.h"
#include "Appointment.h"
#include "PriorityQueue.h"
#include "PatientManager.h"
#include "DoctorManager.h"
#include "WardManager.h"
#include "SchedulingSystem.h"
#include "FileHandler.h"
#include "ReportGenerator.h"

using namespace std;

void printMenu() {
    cout << "\n=== Hospital Management System ===\n";
    cout << "1. Patient Management\n";
    cout << "2. Doctor Management\n";
    cout << "3. Ward Management\n";
    cout << "4. Appointment Scheduling\n";
    cout << "5. Reports & Statistics\n";
    cout << "6. Save & Exit\n";
    cout << "Enter choice: ";
}

void patientMenu(PatientManager& pm, WardManager& wm, DoctorManager& dm) {
    int choice;
    cout << "\n--- Patient Management ---\n";
    cout << "1. Add Patient\n2. View Patients\n3. Recommend Doctor\nEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        int id, age, pLevel;
        string name, disease, date;
        cout << "ID: "; cin >> id;
        cout << "Name: "; cin.ignore(); getline(cin, name);
        cout << "Age: "; cin >> age;
        cout << "Disease: "; cin.ignore(); getline(cin, disease);
        cout << "Date (YYYY-MM-DD): "; getline(cin, date);
        cout << "Priority (0=Normal, 1=Urgent, 2=Emergency): "; cin >> pLevel;
        
        Patient p(id, name, age, disease, date, static_cast<Priority>(pLevel));
        pm.addPatient(p);
        cout << "Patient added successfully.\n";
    } else if (choice == 2) {
        pm.displayAll();
    } else if (choice == 3) {
        string spec;
        cout << "Enter required specialization (or leave empty): ";
        cin.ignore(); getline(cin, spec);
        Doctor* d = dm.recommendDoctor(spec);
        if (d) {
            cout << "Recommended Doctor: " << d->getName() << " (" << d->getSpecialization() << ")\n";
        } else {
            cout << "No matching doctors available.\n";
        }
    }
}

void doctorMenu(DoctorManager& dm) {
    int choice;
    cout << "\n--- Doctor Management ---\n";
    cout << "1. Add Doctor\n2. View Doctors\nEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        int id; string name, spec;
        cout << "ID: "; cin >> id;
        cout << "Name: "; cin.ignore(); getline(cin, name);
        cout << "Specialization: "; getline(cin, spec);
        Doctor d(id, name, spec);
        dm.addDoctor(d);
        cout << "Doctor added successfully.\n";
    } else if (choice == 2) {
        dm.displayAll();
    }
}

void wardMenu(WardManager& wm) {
    int choice;
    cout << "\n--- Ward Management ---\n";
    cout << "1. Add Ward\n2. View Wards\n3. Assign Bed\nEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        int id, capacity, typeInt;
        cout << "ID: "; cin >> id;
        cout << "Capacity: "; cin >> capacity;
        cout << "Type (0=General, 1=ICU, 2=Emergency): "; cin >> typeInt;
        Ward w(id, capacity, static_cast<WardType>(typeInt));
        wm.addWard(w);
        cout << "Ward added successfully.\n";
    } else if (choice == 2) {
        wm.displayAll();
    } else if (choice == 3) {
        int wid;
        cout << "Ward ID to assign bed in: "; cin >> wid;
        if (wm.assignBed(wid)) cout << "Bed assigned.\n";
        else cout << "Ward is full or not found.\n";
    }
}

void schedulingMenu(SchedulingSystem& ss, DoctorManager& dm) {
    int choice;
    cout << "\n--- Scheduling System ---\n";
    cout << "1. Request Appointment\n2. Process Next in Queue\n3. View Appointments\nEnter choice: ";
    cin >> choice;
    if (choice == 1) {
        int pid, pLevel;
        cout << "Patient ID: "; cin >> pid;
        cout << "Priority (0=Normal, 1=Urgent, 2=Emergency): "; cin >> pLevel;
        ss.addRequest(pid, static_cast<Priority>(pLevel));
        cout << "Request added to Priority Queue.\n";
    } else if (choice == 2) {
        if (ss.getQueue().empty()) {
            cout << "Queue is empty.\n";
            return;
        }
        int did; string date, time;
        cout << "Assign to Doctor ID: "; cin >> did;
        cout << "Date (YYYY-MM-DD): "; cin >> date;
        cout << "Time (HH:MM): "; cin >> time;
        if (ss.processNext(did, date, time)) cout << "Appointment processed securely.\n";
        else cout << "Failed to process.\n";
    } else if (choice == 3) {
        ss.displayAppointments();
    }
}

void reportMenu(PatientManager& pm, DoctorManager& dm, WardManager& wm) {
    cout << "\n--- Reports & Statistics ---\n";
    ReportGenerator::displayBusiestDoctor(dm);
    ReportGenerator::displayBedOccupancyRate(wm);
    cout << "Exporting to data/report.txt ...\n";
    if (ReportGenerator::exportReport("data/report.txt", pm, dm, wm)) {
        cout << "Report exported successfully.\n";
    } else {
        cout << "Failed to export report.\n";
    }
}

int main() {
    PatientManager pm;
    DoctorManager dm;
    WardManager wm;
    SchedulingSystem ss;
    FileHandler fh("data/");

    cout << "Loading data...\n";
    fh.loadAll(pm, dm, wm, ss);

    int choice;
    do {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: patientMenu(pm, wm, dm); break;
            case 2: doctorMenu(dm); break;
            case 3: wardMenu(wm); break;
            case 4: schedulingMenu(ss, dm); break;
            case 5: reportMenu(pm, dm, wm); break;
            case 6:
                cout << "Saving data...\n";
                fh.saveAll(pm, dm, wm, ss);
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
