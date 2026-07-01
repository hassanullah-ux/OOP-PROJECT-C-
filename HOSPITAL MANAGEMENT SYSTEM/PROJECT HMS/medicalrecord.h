#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

// ═══════════════════════════════════════════════════════════════
//  MedicalRecord.h  |  Standalone Class
//  Represents one clinical encounter: diagnosis, prescription,
//  and the IDs of the patient and treating doctor.
// ═══════════════════════════════════════════════════════════════

#include <string>
using namespace std;

class MedicalRecord
{
private:
    string recordId;     // e.g. "MR001"
    string patientId;    // Links to Patient
    string doctorId;     // Links to Doctor
    string patientName;  // Denormalised for quick display
    string doctorName;   // Denormalised for quick display
    string recordDate;   // "DD/MM/YYYY"
    string diagnosis;    // Free-text
    string prescription; // Free-text
    string notes;        // Optional extra notes

public:
    // ── Constructors & Destructor ─────────────────────────────
    MedicalRecord();
    MedicalRecord(const string &recordId,
                  const string &patientId, const string &doctorId,
                  const string &patientName, const string &doctorName,
                  const string &recordDate,
                  const string &diagnosis, const string &prescription,
                  const string &notes = "");
    ~MedicalRecord();

    // ── Getters ───────────────────────────────────────────────
    string getRecordId() const;
    string getPatientId() const;
    string getDoctorId() const;
    string getPatientName() const;
    string getDoctorName() const;
    string getRecordDate() const;
    string getDiagnosis() const;
    string getPrescription() const;
    string getNotes() const;

    // ── Setters ───────────────────────────────────────────────
    void setRecordId(const string &id);
    void setPatientId(const string &id);
    void setDoctorId(const string &id);
    void setPatientName(const string &name);
    void setDoctorName(const string &name);
    void setRecordDate(const string &date);
    void setDiagnosis(const string &diag);
    void setPrescription(const string &presc);
    void setNotes(const string &notes);

    // ── Display ───────────────────────────────────────────────
    void displayInfo() const;

    // ── Serialisation ─────────────────────────────────────────
    // Format: REC|recordId|patientId|doctorId|pName|dName|date|diag|presc|notes
    string serialize() const;
    void deserialize(const string &line);
};

#endif // MEDICALRECORD_H