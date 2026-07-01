// ═══════════════════════════════════════════════════════════════
//  MedicalRecord.cpp  |  Implementation of MedicalRecord class
// ═══════════════════════════════════════════════════════════════

#include "MedicalRecord.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// ── Helper: replace all occurrences of a char in a string ─────
static string replaceChar(string s, char from, char to)
{
    for (char &c : s)
        if (c == from)
            c = to;
    return s;
}

// ── Constructors ──────────────────────────────────────────────
MedicalRecord::MedicalRecord()
    : recordId("MR000"), patientId("P000"), doctorId("D000"),
      patientName("N/A"), doctorName("N/A"),
      recordDate("N/A"), diagnosis("N/A"),
      prescription("N/A"), notes("") {}

MedicalRecord::MedicalRecord(const string &recordId,
                             const string &patientId, const string &doctorId,
                             const string &patientName, const string &doctorName,
                             const string &recordDate,
                             const string &diagnosis, const string &prescription,
                             const string &notes)
    : recordId(recordId), patientId(patientId), doctorId(doctorId),
      patientName(patientName), doctorName(doctorName),
      recordDate(recordDate), diagnosis(diagnosis),
      prescription(prescription), notes(notes) {}

MedicalRecord::~MedicalRecord() {}

// ── Getters ───────────────────────────────────────────────────
string MedicalRecord::getRecordId() const { return recordId; }
string MedicalRecord::getPatientId() const { return patientId; }
string MedicalRecord::getDoctorId() const { return doctorId; }
string MedicalRecord::getPatientName() const { return patientName; }
string MedicalRecord::getDoctorName() const { return doctorName; }
string MedicalRecord::getRecordDate() const { return recordDate; }
string MedicalRecord::getDiagnosis() const { return diagnosis; }
string MedicalRecord::getPrescription() const { return prescription; }
string MedicalRecord::getNotes() const { return notes; }

// ── Setters ───────────────────────────────────────────────────
void MedicalRecord::setRecordId(const string &id) { recordId = id; }
void MedicalRecord::setPatientId(const string &id) { patientId = id; }
void MedicalRecord::setDoctorId(const string &id) { doctorId = id; }
void MedicalRecord::setPatientName(const string &name) { patientName = name; }
void MedicalRecord::setDoctorName(const string &name) { doctorName = name; }
void MedicalRecord::setRecordDate(const string &date) { recordDate = date; }
void MedicalRecord::setDiagnosis(const string &diag) { diagnosis = diag; }
void MedicalRecord::setPrescription(const string &p) { prescription = p; }
void MedicalRecord::setNotes(const string &n) { notes = n; }

// ── displayInfo ───────────────────────────────────────────────
void MedicalRecord::displayInfo() const
{
    cout << "\n|---------------------------------------------------------|\n";
    cout << "  |                     MEDICAL RECORD                      |\n";
    cout << "  |---------------------------------------------------------|\n";
    cout << "  |  Record ID      : " << left << setw(22) << recordId << "|\n";
    cout << "  |  Date           : " << setw(22) << recordDate << "      |\n";
    cout << "  |  Patient ID     : " << setw(22) << patientId << "       |\n";
    cout << "  |  Patient Name   : " << setw(22) << patientName << "     |\n";
    cout << "  |  Doctor ID      : " << setw(22) << doctorId << "        |\n";
    cout << "  |  Doctor Name    : " << setw(22) << doctorName << "      |\n";
    cout << "  |---------------------------------------------------------|\n";
    cout << "  |  Diagnosis      : " << setw(22) << diagnosis << "       |\n";
    cout << "  |  Prescription   : " << setw(22) << prescription << "    |\n";
    cout << "  |  Notes          : " << setw(22) << (notes.empty() ? "None" : notes) << "|\n";
    cout << "  |---------------------------------------------------------|\n";
}

// ── Serialisation ─────────────────────────────────────────────
// Pipe '|' inside free-text is escaped to '^' before saving.
// Format: REC|recId|patId|docId|patName|docName|date|diag|presc|notes
string MedicalRecord::serialize() const
{
    auto safe = [](const string &s)
    {
        return replaceChar(s, '|', '^');
    };
    ostringstream oss;
    oss << "REC"
        << "|" << recordId
        << "|" << patientId
        << "|" << doctorId
        << "|" << safe(patientName)
        << "|" << safe(doctorName)
        << "|" << recordDate
        << "|" << safe(diagnosis)
        << "|" << safe(prescription)
        << "|" << safe(notes);
    return oss.str();
}

void MedicalRecord::deserialize(const string &line)
{
    auto restore = [](string s)
    {
        return replaceChar(s, '^', ' ');
    };
    istringstream iss(line);
    string token;
    getline(iss, token, '|'); // "REC"
    getline(iss, token, '|');
    recordId = token;
    getline(iss, token, '|');
    patientId = token;
    getline(iss, token, '|');
    doctorId = token;
    getline(iss, token, '|');
    patientName = restore(token);
    getline(iss, token, '|');
    doctorName = restore(token);
    getline(iss, token, '|');
    recordDate = token;
    getline(iss, token, '|');
    diagnosis = restore(token);
    getline(iss, token, '|');
    prescription = restore(token);
    getline(iss, token, '|');
    notes = restore(token);
}