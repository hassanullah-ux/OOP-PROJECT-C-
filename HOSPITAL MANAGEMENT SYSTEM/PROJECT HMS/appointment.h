#ifndef APPOINTMENT_H
#define APPOINTMENT_H

// ═══════════════════════════════════════════════════════════════
//  Appointment.h  |  Composition Class
//  Composes a Doctor* and a Patient* to represent a scheduled
//  consultation.  Date is inherited from the hospital session;
//  a specific time-slot is stored per appointment.
// ═══════════════════════════════════════════════════════════════

#include "Doctor.h"
#include "Patient.h"
using namespace std;

class Appointment
{
private:
    string appointmentId; // e.g. "A001"
    Doctor *doctor;       // Non-owning pointer (Hospital owns Doctor objects)
    Patient *patient;     // Non-owning pointer (Hospital owns Patient objects)
    string date;          // "DD/MM/YYYY" — set from hospital session date
    string timeSlot;      // e.g. "10:00 AM"
    string status;        // "Scheduled" | "Completed" | "Cancelled"

public:
    // ── Constructors & Destructor ─────────────────────────────
    Appointment();
    Appointment(const string &appointmentId,
                Doctor *doctor, Patient *patient,
                const string &date, const string &timeSlot,
                const string &status = "Scheduled");
    ~Appointment();

    // ── Getters ───────────────────────────────────────────────
    string getAppointmentId() const;
    Doctor *getDoctor() const;
    Patient *getPatient() const;
    string getDate() const;
    string getTimeSlot() const;
    string getStatus() const;

    // ── Setters ───────────────────────────────────────────────
    void setAppointmentId(const string &id);
    void setDoctor(Doctor *d);
    void setPatient(Patient *p);
    void setDate(const string &date);
    void setTimeSlot(const string &slot);
    void setStatus(const string &status);

    // ── Display ───────────────────────────────────────────────
    void displayInfo() const;

    // ── Serialisation (stores IDs — pointers resolved by Hospital) ──
    // Format: APPT|appointmentId|doctorId|patientId|date|timeSlot|status
    string serialize() const;

    // Deserialise metadata only; call setDoctor/setPatient after lookup
    void deserializeMeta(const string &line,
                         string &outDoctorId,
                         string &outPatientId);
};

#endif // APPOINTMENT_H