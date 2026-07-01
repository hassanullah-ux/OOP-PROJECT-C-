#ifndef PATIENT_H
#define PATIENT_H

// ═══════════════════════════════════════════════════════════════
//  Patient.h  |  Derived from Person
//  Adds patient-specific attributes: ID, blood group,
//  and medical history notes.
// ═══════════════════════════════════════════════════════════════

#include "Person.h"
using namespace std;

class Patient : public Person
{
private:
    string patientId;      // Unique ID: "P001", "P002", …
    string bloodGroup;     // e.g. "A+", "O-", "AB+"
    string medicalHistory; // Free-text notes (semicolon-separated internally)

public:
    // ── Constructors & Destructor ─────────────────────────────
    Patient();
    Patient(const string &name, int age,
            const string &cnic, const string &phone,
            const string &gender, const string &patientId,
            const string &bloodGroup, const string &medicalHistory);
    ~Patient() override;

    // ── Getters ───────────────────────────────────────────────
    string getPatientId() const;
    string getBloodGroup() const;
    string getMedicalHistory() const;

    // ── Setters ───────────────────────────────────────────────
    void setPatientId(const string &id);
    void setBloodGroup(const string &bg);
    void setMedicalHistory(const string &history);

    // ── Polymorphic display override ──────────────────────────
    void displayInfo() const override;

    // ── Serialisation overrides ───────────────────────────────
    string serialize() const override;
    void deserialize(const string &line) override;
};

#endif // PATIENT_H