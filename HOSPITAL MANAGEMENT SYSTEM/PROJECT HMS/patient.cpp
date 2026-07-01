// ═══════════════════════════════════════════════════════════════
//  Patient.cpp  |  Implementation of the Patient derived class
// ═══════════════════════════════════════════════════════════════

#include "Patient.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// ── Constructors ──────────────────────────────────────────────
Patient::Patient()
    : Person(), patientId("P000"), bloodGroup("Unknown"),
      medicalHistory("None") {}

Patient::Patient(const string &name, int age,
                 const string &cnic, const string &phone,
                 const string &gender, const string &patientId,
                 const string &bloodGroup, const string &medicalHistory)
    : Person(name, age, cnic, phone, gender),
      patientId(patientId),
      bloodGroup(bloodGroup),
      medicalHistory(medicalHistory) {}

Patient::~Patient() {}

// ── Getters ───────────────────────────────────────────────────
string Patient::getPatientId() const { return patientId; }
string Patient::getBloodGroup() const { return bloodGroup; }
string Patient::getMedicalHistory() const { return medicalHistory; }

// ── Setters ───────────────────────────────────────────────────
void Patient::setPatientId(const string &id) { patientId = id; }
void Patient::setBloodGroup(const string &bg) { bloodGroup = bg; }
void Patient::setMedicalHistory(const string &hist) { medicalHistory = hist; }

// ── displayInfo ───────────────────────────────────────────────
// Polymorphic override — prints a formatted patient profile card.
void Patient::displayInfo() const
{
    cout << "\n|----------------------------------------------------------|\n";
    cout << "  |                     PATIENT PROFILE                      |\n";
    cout << "  |----------------------------------------------------------|\n";
    cout << "  |  ID             : " << left << setw(22) << patientId << "|\n";
    cout << "  |  Name           : " << setw(22) << getName() << "        |\n";
    cout << "  |  Gender         : " << setw(22) << getGender() << "      |\n";
    cout << "  |  Age            : " << setw(22) << getAge() << "         |\n";
    cout << "  |  CNIC           : " << setw(22) << getCnic() << "        |\n";
    cout << "  |  Phone          : " << setw(22) << getPhone() << "       |\n";
    cout << "  |  Blood Group    : " << setw(22) << bloodGroup << "       |\n";
    cout << "  |  Medical History: " << setw(22) << medicalHistory << "   |\n";
    cout << "  |----------------------------------------------------------|\n";
}

// ── Serialisation ─────────────────────────────────────────────
// Format: PATIENT|name|age|cnic|phone|gender|patientId|bloodGroup|history
// Note: medicalHistory uses '^' internally to avoid pipe conflicts.
string Patient::serialize() const
{
    // Replace any '|' in free-text with '^' to keep delimiter clean
    string safeHistory = medicalHistory;
    for (char &c : safeHistory)
        if (c == '|')
            c = '^';

    ostringstream oss;
    oss << "PATIENT|" << Person::serialize()
        << "|" << patientId
        << "|" << bloodGroup
        << "|" << safeHistory;
    return oss.str();
}

// Parses a full PATIENT record line (including the "PATIENT|" prefix).
void Patient::deserialize(const string &line)
{
    istringstream iss(line);
    string token;

    getline(iss, token, '|'); // consume "PATIENT" tag

    // Reconstruct base-class section (5 fields)
    string basePart;
    for (int i = 0; i < 5; ++i)
    {
        string t;
        getline(iss, t, '|');
        if (i > 0)
            basePart += "|";
        basePart += t;
    }
    Person::deserialize(basePart);

    getline(iss, token, '|');
    patientId = token;
    getline(iss, token, '|');
    bloodGroup = token;
    getline(iss, token, '|');
    medicalHistory = token;

    // Restore '^' back to spaces for display
    for (char &c : medicalHistory)
        if (c == '^')
            c = ' ';
}