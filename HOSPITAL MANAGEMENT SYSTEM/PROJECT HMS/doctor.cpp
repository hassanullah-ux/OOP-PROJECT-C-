// ═══════════════════════════════════════════════════════════════
//  Doctor.cpp  |  Implementation of the Doctor derived class
// ═══════════════════════════════════════════════════════════════

#include "Doctor.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// ── Constructors ──────────────────────────────────────────────
Doctor::Doctor()
    : Person(), doctorId("D000"), specialization("General"),
      availability("N/A"), consultationFee(0.0) {}

Doctor::Doctor(const string &name, int age,
               const string &cnic, const string &phone,
               const string &gender, const string &doctorId,
               const string &specialization, const string &availability,
               double consultationFee)
    : Person(name, age, cnic, phone, gender),
      doctorId(doctorId),
      specialization(specialization),
      availability(availability),
      consultationFee(consultationFee) {}

Doctor::~Doctor() {}

// ── Getters ───────────────────────────────────────────────────
string Doctor::getDoctorId() const { return doctorId; }
string Doctor::getSpecialization() const { return specialization; }
string Doctor::getAvailability() const { return availability; }
double Doctor::getConsultationFee() const { return consultationFee; }

// ── Setters ───────────────────────────────────────────────────
void Doctor::setDoctorId(const string &id) { doctorId = id; }
void Doctor::setSpecialization(const string &spec) { specialization = spec; }
void Doctor::setAvailability(const string &avail) { availability = avail; }
void Doctor::setConsultationFee(double fee) { consultationFee = fee; }

// ── displayInfo ───────────────────────────────────────────────
// Polymorphic override — prints a formatted doctor profile card.
void Doctor::displayInfo() const
{
    cout << "\n|------------------------------------------|\n";
    cout << "  |               DOCTOR PROFILE             |\n";
    cout << "  |------------------------------------------|\n";
    cout << "  |  ID             : " << left << setw(22) << doctorId << "|\n";
    cout << "  |  Name           : " << setw(22) << getName() << "|\n";
    cout << "  |  Gender         : " << setw(22) << getGender() << "|\n";
    cout << "  |  Age            : " << setw(22) << getAge() << "|\n";
    cout << "  |  CNIC           : " << setw(22) << getCnic() << "|\n";
    cout << "  |  Phone          : " << setw(22) << getPhone() << "|\n";
    cout << "  |  Specialization : " << setw(22) << specialization << "|\n";
    cout << "  |  Availability   : " << setw(22) << availability << "|\n";
    cout << "  |  Fee (PKR)      : " << setw(22) << fixed << setprecision(0)
         << consultationFee << "|\n";
    cout << "  |------------------------------------------|\n";
}

// ── Serialisation ─────────────────────────────────────────────
// Format: DOCTOR|name|age|cnic|phone|gender|doctorId|spec|avail|fee
string Doctor::serialize() const
{
    ostringstream oss;
    oss << "DOCTOR|" << Person::serialize()
        << "|" << doctorId
        << "|" << specialization
        << "|" << availability
        << "|" << fixed << setprecision(2) << consultationFee;
    return oss.str();
}

// Parses a full DOCTOR record line (including the "DOCTOR|" prefix).
void Doctor::deserialize(const string &line)
{
    istringstream iss(line);
    string token;

    getline(iss, token, '|'); // consume "DOCTOR" tag

    // Reconstruct the base-class section (5 fields)
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
    doctorId = token;
    getline(iss, token, '|');
    specialization = token;
    getline(iss, token, '|');
    availability = token;
    getline(iss, token, '|');
    consultationFee = stod(token);
}