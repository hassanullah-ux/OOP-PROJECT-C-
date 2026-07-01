// ═══════════════════════════════════════════════════════════════
//  Appointment.cpp  |  Implementation of the Appointment class
// ═══════════════════════════════════════════════════════════════

#include "Appointment.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// ── Constructors ──────────────────────────────────────────────
Appointment::Appointment()
    : appointmentId("A000"), doctor(nullptr), patient(nullptr),
      date("N/A"), timeSlot("N/A"), status("Scheduled") {}

Appointment::Appointment(const string &appointmentId,
                         Doctor *doctor, Patient *patient,
                         const string &date, const string &timeSlot,
                         const string &status)
    : appointmentId(appointmentId),
      doctor(doctor), patient(patient),
      date(date), timeSlot(timeSlot),
      status(status) {}

Appointment::~Appointment()
{
    // Pointers are non-owning — Hospital manages the lifetime of
    // Doctor and Patient objects, so we do NOT delete them here.
}

// ── Getters ───────────────────────────────────────────────────
string Appointment::getAppointmentId() const { return appointmentId; }
Doctor *Appointment::getDoctor() const { return doctor; }
Patient *Appointment::getPatient() const { return patient; }
string Appointment::getDate() const { return date; }
string Appointment::getTimeSlot() const { return timeSlot; }
string Appointment::getStatus() const { return status; }

// ── Setters ───────────────────────────────────────────────────
void Appointment::setAppointmentId(const string &id) { appointmentId = id; }
void Appointment::setDoctor(Doctor *d) { doctor = d; }
void Appointment::setPatient(Patient *p) { patient = p; }
void Appointment::setDate(const string &d) { date = d; }
void Appointment::setTimeSlot(const string &slot) { timeSlot = slot; }
void Appointment::setStatus(const string &s) { status = s; }

// ── displayInfo ───────────────────────────────────────────────
void Appointment::displayInfo() const
{
    string dName = doctor ? doctor->getName() : "N/A";
    string dSpec = doctor ? doctor->getSpecialization() : "N/A";
    string pName = patient ? patient->getName() : "N/A";
    string pid = patient ? patient->getPatientId() : "N/A";

    cout << "\n|----------------------------------------|\n";
    cout << "  |            APPOINTMENT DETAILS         |\n";
    cout << "  |----------------------------------------|\n";
    cout << "  |  Appt ID        : " << left << setw(22) << appointmentId << "|\n";
    cout << "  |  Date           : " << setw(22) << date << "|\n";
    cout << "  |  Time Slot      : " << setw(22) << timeSlot << "|\n";
    cout << "  |  Status         : " << setw(22) << status << "|\n";
    cout << "  |----------------------------------------|\n";
    cout << "  |  Doctor         : " << setw(22) << dName << "|\n";
    cout << "  |  Specialization : " << setw(22) << dSpec << "|\n";
    cout << "  |----------------------------------------|\n";
    cout << "  |  Patient ID     : " << setw(22) << pid << "|\n";
    cout << "  |  Patient        : " << setw(22) << pName << "|\n";
    cout << "  |----------------------------------------|\n";
}

// ── Serialisation ─────────────────────────────────────────────
// Format: APPT|appointmentId|doctorId|patientId|date|timeSlot|status
string Appointment::serialize() const
{
    string dId = doctor ? doctor->getDoctorId() : "NONE";
    string pId = patient ? patient->getPatientId() : "NONE";

    ostringstream oss;
    oss << "APPT|" << appointmentId << "|" << dId << "|" << pId
        << "|" << date << "|" << timeSlot << "|" << status;
    return oss.str();
}

// Parses all scalar fields and outputs doctorId / patientId so
// Hospital can look up the actual pointer objects.
void Appointment::deserializeMeta(const string &line,
                                  string &outDoctorId,
                                  string &outPatientId)
{
    istringstream iss(line);
    string token;
    getline(iss, token, '|'); // "APPT"
    getline(iss, token, '|');
    appointmentId = token;
    getline(iss, token, '|');
    outDoctorId = token;
    getline(iss, token, '|');
    outPatientId = token;
    getline(iss, token, '|');
    date = token;
    getline(iss, token, '|');
    timeSlot = token;
    getline(iss, token, '|');
    status = token;
}