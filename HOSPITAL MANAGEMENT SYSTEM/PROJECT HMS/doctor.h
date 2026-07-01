#ifndef DOCTOR_H
#define DOCTOR_H

// ═══════════════════════════════════════════════════════════════
//  Doctor.h  |  Derived from Person
//  Adds doctor-specific attributes: ID, specialization,
//  availability schedule, and consultation fee.
// ═══════════════════════════════════════════════════════════════

#include "Person.h"
using namespace std;

class Doctor : public Person
{
private:
    string doctorId;        // Unique ID: "D001" – "D020"
    string specialization;  // e.g. "Cardiologist"
    string availability;    // e.g. "Mon–Fri  09:00–17:00"
    double consultationFee; // In PKR

public:
    // ── Constructors & Destructor ─────────────────────────────
    Doctor();
    Doctor(const string &name, int age,
           const string &cnic, const string &phone,
           const string &gender, const string &doctorId,
           const string &specialization, const string &availability,
           double consultationFee);
    ~Doctor() override;

    // ── Getters ───────────────────────────────────────────────
    string getDoctorId() const;
    string getSpecialization() const;
    string getAvailability() const;
    double getConsultationFee() const;

    // ── Setters ───────────────────────────────────────────────
    void setDoctorId(const string &id);
    void setSpecialization(const string &spec);
    void setAvailability(const string &avail);
    void setConsultationFee(double fee);

    // ── Polymorphic display override ──────────────────────────
    void displayInfo() const override;

    // ── Serialisation overrides ───────────────────────────────
    string serialize() const override;
    void deserialize(const string &line) override;
};

#endif // DOCTOR_H