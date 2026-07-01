#ifndef HOSPITAL_H
#define HOSPITAL_H

// ═══════════════════════════════════════════════════════════════
//  Hospital.h  |  Manager / Controller Class
//  Owns all Doctor*, Patient*, Appointment*, and MedicalRecord*
//  objects.  Handles menus, validation prompts, and File I/O.
// ═══════════════════════════════════════════════════════════════

#include "doctor.h"
#include "patient.h"
#include "appointment.h"
#include "medicalrecord.h"
#include <vector>
using namespace std;

class Hospital
{
private:
    // ── Data stores (Hospital OWNS these heap objects) ────────
    vector<Doctor *> doctors;
    vector<Patient *> patients;
    vector<Appointment *> appointments;
    vector<MedicalRecord *> records;

    // ── Session metadata ──────────────────────────────────────
    string todayDate;   // Set once at startup: "DD/MM/YYYY"
    int nextPatientNum; // Auto-incrementing counters
    int nextApptNum;
    int nextRecordNum;

    // ── Private helpers ───────────────────────────────────────
    void populateDoctors(); // Load the 20 pre-set doctors
    string generatePatientId();
    string generateApptId();
    string generateRecordId();

    Doctor *findDoctorById(const string &id);
    Patient *findPatientById(const string &id);

    // ── Menu sub-handlers ─────────────────────────────────────
    void menuAddPatient();
    void menuViewAllPatients();
    void menuViewAllDoctors();
    void menuSearchDoctor();
    void menuBookAppointment();
    void menuViewAppointments();
    void menuUpdateApptStatus();
    void menuAddMedicalRecord();
    void menuViewPatientRecords();
    void menuViewAllRecords();
    void menuDeletePatient();
    void menuSaveAndExit();

    // ── UI helpers ────────────────────────────────────────────
    void printHeader(const string &title) const;
    void printDivider() const;
    string promptValidPhone(const string &label) const;
    string promptValidCnic(const string &label) const;

public:
    // ── Constructor / Destructor ──────────────────────────────
    explicit Hospital(const string &todayDate);
    ~Hospital();

    // ── File I/O ──────────────────────────────────────────────
    void saveData(); // Writes to hospital_data.txt
    void loadData(); // Reads  from hospital_data.txt

    // ── Entry point ───────────────────────────────────────────
    void run(); // Main menu loop
};

#endif // HOSPITAL_H