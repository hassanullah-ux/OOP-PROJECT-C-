// ═══════════════════════════════════════════════════════════════
//  Hospital.cpp  |  Implementation of the Hospital manager class
// ═══════════════════════════════════════════════════════════════

#include "Hospital.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

// ════════════════════════════════════════════════════════════════
//  Constructor & Destructor
// ════════════════════════════════════════════════════════════════

Hospital::Hospital(const string &date)
    : todayDate(date),
      nextPatientNum(1),
      nextApptNum(1),
      nextRecordNum(1)
{
    populateDoctors(); // Always load the 20 built-in doctors first
    loadData();        // Then restore any saved patients / appts / records
}

Hospital::~Hospital()
{
    // Hospital is responsible for freeing every heap object it owns
    for (auto d : doctors)
        delete d;
    for (auto p : patients)
        delete p;
    for (auto a : appointments)
        delete a;
    for (auto r : records)
        delete r;
}

// ════════════════════════════════════════════════════════════════
//  20 Pre-populated Pakistani Doctors
// ════════════════════════════════════════════════════════════════

void Hospital::populateDoctors()
{
    // Format: name, age, cnic (13 digits), phone (11 digits),
    //         gender, doctorId, specialization, availability, fee (PKR)
    struct DoctorData
    {
        string name;
        int age;
        string cnic, phone, gender, id, spec, avail;
        double fee;
    };

    vector<DoctorData> data = {
        {"Dr. Faisal Khan", 45, "4210112345001", "03001234501", "Male", "D001", "Cardiologist", "Mon-Sat  09:00-17:00", 2000},
        {"Dr. Sana Ahmed", 38, "4210212345002", "03002234502", "Female", "D002", "Dermatologist", "Mon-Fri  10:00-16:00", 1500},
        {"Dr. Zohaib Hassan", 50, "4210312345003", "03003234503", "Male", "D003", "Neurologist", "Tue-Sat  08:00-14:00", 2500},
        {"Dr. Mehwish Raza", 42, "4210412345004", "03004234504", "Female", "D004", "Gynecologist", "Mon-Wed-Fri 09-15", 1800},
        {"Dr. Usman Pirzada", 47, "4210512345005", "03005234505", "Male", "D005", "Urologist", "Mon-Thu  10:00-17:00", 2000},
        {"Dr. Amna Malik", 35, "4210612345006", "03006234506", "Female", "D006", "Pediatrician", "Mon-Sat  09:00-14:00", 1200},
        {"Dr. Bilal Siddiqui", 52, "4210712345007", "03007234507", "Male", "D007", "Orthopedic Surgeon", "Mon-Fri  08:00-16:00", 3000},
        {"Dr. Hina Javeed", 44, "4210812345008", "03008234508", "Female", "D008", "Oncologist", "Mon-Thu  09:00-15:00", 3500},
        {"Dr. Kamran Akram", 48, "4210912345009", "03009234509", "Male", "D009", "ENT Specialist", "Tue-Sat  10:00-17:00", 1500},
        {"Dr. Nida Yasir", 39, "4211012345010", "03010234510", "Female", "D010", "Psychiatrist", "Mon-Wed-Fri 14-19", 2000},
        {"Dr. Rizwan Shah", 55, "4211112345011", "03011234511", "Male", "D011", "Nephrologist", "Mon-Sat  08:00-14:00", 2500},
        {"Dr. Sadia Imam", 41, "4211212345012", "03012234512", "Female", "D012", "Endocrinologist", "Mon-Thu  09:00-16:00", 2200},
        {"Dr. Tariq Mahmood", 58, "4211312345013", "03013234513", "Male", "D013", "Gastroenterologist", "Tue-Fri  10:00-15:00", 2000},
        {"Dr. Uzma Gillani", 36, "4211412345014", "03014234514", "Female", "D014", "Ophthalmologist", "Mon-Sat  09:00-13:00", 1500},
        {"Dr. Waqas Ali", 43, "4211512345015", "03015234515", "Male", "D015", "Pulmonologist", "Mon-Fri  09:00-17:00", 2000},
        {"Dr. Zainab Abbas", 37, "4211612345016", "03016234516", "Female", "D016", "Rheumatologist", "Mon-Wed-Fri 10-16", 2200},
        {"Dr. Adnan Siddiqui", 53, "4211712345017", "03017234517", "Male", "D017", "General Surgeon", "Mon-Thu  08:00-15:00", 3000},
        {"Dr. Mariam Nawaz", 40, "4211812345018", "03018234518", "Female", "D018", "Pathologist", "Mon-Fri  09:00-17:00", 1500},
        {"Dr. Omer Butt", 46, "4211912345019", "03019234519", "Male", "D019", "Anesthesiologist", "Mon-Sat  08:00-14:00", 2500},
        {"Dr. Kiran Haq", 34, "4212012345020", "03020234520", "Female", "D020", "Radiologist", "Mon-Fri  10:00-16:00", 1800},
    };

    for (const auto &d : data)
    {
        doctors.push_back(new Doctor(
            d.name, d.age, d.cnic, d.phone, d.gender,
            d.id, d.spec, d.avail, d.fee));
    }
}

// ════════════════════════════════════════════════════════════════
//  ID Generators
// ════════════════════════════════════════════════════════════════

string Hospital::generatePatientId()
{
    ostringstream oss;
    oss << "P" << setw(3) << setfill('0') << nextPatientNum++;
    return oss.str();
}

string Hospital::generateApptId()
{
    ostringstream oss;
    oss << "A" << setw(3) << setfill('0') << nextApptNum++;
    return oss.str();
}

string Hospital::generateRecordId()
{
    ostringstream oss;
    oss << "MR" << setw(3) << setfill('0') << nextRecordNum++;
    return oss.str();
}

// ════════════════════════════════════════════════════════════════
//  Lookup Helpers
// ════════════════════════════════════════════════════════════════

Doctor *Hospital::findDoctorById(const string &id)
{
    for (auto d : doctors)
        if (d->getDoctorId() == id)
            return d;
    return nullptr;
}

Patient *Hospital::findPatientById(const string &id)
{
    for (auto p : patients)
        if (p->getPatientId() == id)
            return p;
    return nullptr;
}

// ════════════════════════════════════════════════════════════════
//  File I/O
// ════════════════════════════════════════════════════════════════

void Hospital::saveData()
{
    ofstream file("hospital_data.txt");
    if (!file.is_open())
    {
        cerr << "  [Error] Cannot open hospital_data.txt for writing!\n";
        return;
    }

    // ── Save counters so IDs continue correctly on reload ─────
    file << "[META]\n";
    file << nextPatientNum << "|" << nextApptNum << "|" << nextRecordNum << "\n";

    // ── Patients ──────────────────────────────────────────────
    file << "[PATIENTS]\n";
    for (auto p : patients)
        file << p->serialize() << "\n";

    // ── Appointments ──────────────────────────────────────────
    file << "[APPOINTMENTS]\n";
    for (auto a : appointments)
        file << a->serialize() << "\n";

    // ── Medical Records ───────────────────────────────────────
    file << "[RECORDS]\n";
    for (auto r : records)
        file << r->serialize() << "\n";

    file.close();
    cout << "\n    Data saved to hospital_data.txt\n";
}

void Hospital::loadData()
{
    ifstream file("hospital_data.txt");
    if (!file.is_open())
        return; // First run — no file yet

    string line;
    string section = "";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        // ── Section headers ──────────────────────────────────
        if (line == "[META]")
        {
            section = "META";
            continue;
        }
        if (line == "[PATIENTS]")
        {
            section = "PAT";
            continue;
        }
        if (line == "[APPOINTMENTS]")
        {
            section = "APPT";
            continue;
        }
        if (line == "[RECORDS]")
        {
            section = "REC";
            continue;
        }

        if (section == "META")
        {
            istringstream iss(line);
            string t;
            getline(iss, t, '|');
            nextPatientNum = stoi(t);
            getline(iss, t, '|');
            nextApptNum = stoi(t);
            getline(iss, t, '|');
            nextRecordNum = stoi(t);
        }
        else if (section == "PAT" && line.substr(0, 7) == "PATIENT")
        {
            Patient *p = new Patient();
            p->deserialize(line);
            patients.push_back(p);
        }
        else if (section == "APPT" && line.substr(0, 4) == "APPT")
        {
            Appointment *a = new Appointment();
            string dId, pId;
            a->deserializeMeta(line, dId, pId);
            a->setDoctor(findDoctorById(dId));
            a->setPatient(findPatientById(pId));
            appointments.push_back(a);
        }
        else if (section == "REC" && line.substr(0, 3) == "REC")
        {
            MedicalRecord *r = new MedicalRecord();
            r->deserialize(line);
            records.push_back(r);
        }
    }
    file.close();
}

// ════════════════════════════════════════════════════════════════
//  UI Utility Helpers
// ════════════════════════════════════════════════════════════════

void Hospital::printHeader(const string &title) const
{
    cout << "\n";
    cout << "  |----------------------------------------------|\n";
    cout << "  |  " << left << setw(44) << title << "         |\n";
    cout << "  |----------------------------------------------|\\n";
}

void Hospital::printDivider() const
{
    cout << "  ------------------------------------------------\n";
}

// Keeps prompting until user enters a valid 11-digit phone
string Hospital::promptValidPhone(const string &label) const
{
    string val;
    while (true)
    {
        cout << "  " << label;
        cin >> val;
        if (Person::isValidPhone(val))
            return val;
        cout << "    Phone must be exactly 11 digits. Try again.\n";
    }
}

// Keeps prompting until user enters a valid 13-digit CNIC
string Hospital::promptValidCnic(const string &label) const
{
    string val;
    while (true)
    {
        cout << "  " << label;
        cin >> val;
        if (Person::isValidCnic(val))
            return val;
        cout << "    CNIC must be exactly 13 digits (no dashes). Try again.\n";
    }
}

// ════════════════════════════════════════════════════════════════
//  Menu Sub-Handlers
// ════════════════════════════════════════════════════════════════

// ── 1. Add new patient ────────────────────────────────────────
void Hospital::menuAddPatient()
{
    printHeader("  ADD NEW PATIENT");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name, gender, bloodGroup, history;
    int age;

    cout << "  Full Name       : ";
    getline(cin, name);
    cout << "  Age             : ";
    cin >> age;
    cin.ignore();

    string cnic = promptValidCnic("CNIC (13 digits) : ");
    string phone = promptValidPhone("Phone (11 digits): ");
    cin.ignore();

    cout << "  Gender (Male/Female/Other): ";
    getline(cin, gender);
    cout << "  Blood Group (e.g. A+)     : ";
    getline(cin, bloodGroup);
    cout << "  Medical History (brief)   : ";
    getline(cin, history);

    string pid = generatePatientId();
    Patient *p = new Patient(name, age, cnic, phone, gender,
                             pid, bloodGroup, history);
    patients.push_back(p);

    cout << "\n    Patient registered successfully!\n";
    p->displayInfo();
}

// ── 2. View all patients ──────────────────────────────────────
void Hospital::menuViewAllPatients()
{
    printHeader("  ALL REGISTERED PATIENTS");
    if (patients.empty())
    {
        cout << "  No patients registered yet.\n";
        return;
    }
    for (auto p : patients)
        p->displayInfo();
    cout << "\n  Total: " << patients.size() << " patient(s).\n";
}

// ── 3. View all doctors ───────────────────────────────────────
void Hospital::menuViewAllDoctors()
{
    printHeader("  AVAILABLE DOCTORS");
    for (auto d : doctors)
    {
        cout << "  [" << d->getDoctorId() << "]  \n"
             << left << setw(22) << d->getName()
             << setw(22) << d->getSpecialization()
             << "PKR " << d->getConsultationFee() << "\n";
    }
    cout << "\n  Total: " << doctors.size() << " doctor(s).\n";
}

// ── 4. Search doctor by specialization or name ────────────────
void Hospital::menuSearchDoctor()
{
    printHeader("  SEARCH DOCTOR");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string keyword;
    cout << "  Enter name or specialization: ";
    getline(cin, keyword);

    // Case-insensitive substring match
    string kl = keyword;
    transform(kl.begin(), kl.end(), kl.begin(), ::tolower);

    bool found = false;
    for (auto d : doctors)
    {
        string nl = d->getName();
        transform(nl.begin(), nl.end(), nl.begin(), ::tolower);
        string sl = d->getSpecialization();
        transform(sl.begin(), sl.end(), sl.begin(), ::tolower);
        if (nl.find(kl) != string::npos || sl.find(kl) != string::npos)
        {
            d->displayInfo();
            found = true;
        }
    }
    if (!found)
        cout << "  No doctor found matching \"" << keyword << "\".\n";
}

// ── 5. Book appointment ───────────────────────────────────────
void Hospital::menuBookAppointment()
{
    printHeader("  BOOK APPOINTMENT");

    if (patients.empty())
    {
        cout << "    No patients in the system. Register a patient first.\n";
        return;
    }

    // Show patients
    cout << "\n  -- Patients ------------------------------\n";
    for (auto p : patients)
        cout << "  [" << p->getPatientId() << "]  " << p->getName() << "\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string pid;
    cout << "\n  Enter Patient ID: ";
    getline(cin, pid);
    Patient *patient = findPatientById(pid);
    if (!patient)
    {
        cout << "  Patient not found!.\n";
        return;
    }

    // Show doctors
    cout << "\n  -- Doctors ---------------------------------\n";
    menuViewAllDoctors();

    string did;
    cout << "\n  Enter Doctor ID: ";
    getline(cin, did);
    Doctor *doctor = findDoctorById(did);
    if (!doctor)
    {
        cout << "    Doctor not found.\n";
        return;
    }

    string timeSlot;
    cout << "  Time Slot (e.g. 10:00 AM): ";
    getline(cin, timeSlot);

    string apptId = generateApptId();
    Appointment *a = new Appointment(apptId, doctor, patient,
                                     todayDate, timeSlot, "Scheduled");
    appointments.push_back(a);

    cout << "\n    Appointment booked!\n";
    a->displayInfo();
}

// ── 6. View all appointments ──────────────────────────────────
void Hospital::menuViewAppointments()
{
    printHeader("  ALL APPOINTMENTS");
    if (appointments.empty())
    {
        cout << "  No appointments booked yet.\n";
        return;
    }
    for (auto a : appointments)
        a->displayInfo();
    cout << "\n  Total: " << appointments.size() << " appointment(s).\n";
}

// ── 7. Update appointment status ──────────────────────────────
void Hospital::menuUpdateApptStatus()
{
    printHeader("  UPDATE APPOINTMENT STATUS");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (appointments.empty())
    {
        cout << "  No appointments to update.\n";
        return;
    }

    for (auto a : appointments)
        cout << "  [" << a->getAppointmentId() << "]  "
             << a->getDate() << "  " << a->getTimeSlot()
             << "  Status: " << a->getStatus() << "\n";

    string apptId;
    cout << "\n  Enter Appointment ID: ";
    getline(cin, apptId);

    Appointment *target = nullptr;
    for (auto a : appointments)
        if (a->getAppointmentId() == apptId)
        {
            target = a;
            break;
        }

    if (!target)
    {
        cout << "    Appointment not found.\n";
        return;
    }

    cout << "  New Status (Scheduled / Completed / Cancelled): ";
    string newStatus;
    getline(cin, newStatus);
    target->setStatus(newStatus);
    cout << "    Status updated to \"" << newStatus << "\".\n";
}

// ── 8. Add medical record ─────────────────────────────────────
void Hospital::menuAddMedicalRecord()
{
    printHeader("  ADD MEDICAL RECORD");

    if (patients.empty())
    {
        cout << "    No patients registered.\n";
        return;
    }

    cout << "\n  -- Patients --------------------------------\n";
    for (auto p : patients)
        cout << "  [" << p->getPatientId() << "]  " << p->getName() << "\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string pid;
    cout << "\n  Patient ID: ";
    getline(cin, pid);
    Patient *patient = findPatientById(pid);
    if (!patient)
    {
        cout << "  Patient not found!\n";
        return;
    }

    cout << "\n  -- Doctors ------------------------------------\n";
    for (auto d : doctors)
        cout << "  [" << d->getDoctorId() << "]  " << d->getName()
             << "  (" << d->getSpecialization() << ")\n";

    string did;
    cout << "\n  Doctor ID: ";
    getline(cin, did);
    Doctor *doctor = findDoctorById(did);
    if (!doctor)
    {
        cout << "    Doctor not found!\n";
        return;
    }

    string diagnosis, prescription, notes;
    cout << "  Diagnosis           : ";
    getline(cin, diagnosis);
    cout << "  Prescription        : ";
    getline(cin, prescription);
    cout << "  Additional Notes    : ";
    getline(cin, notes);

    string recId = generateRecordId();
    MedicalRecord *mr = new MedicalRecord(
        recId, pid, did,
        patient->getName(), doctor->getName(),
        todayDate, diagnosis, prescription, notes);
    records.push_back(mr);

    cout << "\n  Medical record added!\n";
    mr->displayInfo();
}

// ── 9. View records for a specific patient ────────────────────
void Hospital::menuViewPatientRecords()
{
    printHeader("  VIEW PATIENT RECORDS");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string pid;
    cout << "  Enter Patient ID: ";
    getline(cin, pid);

    bool found = false;
    for (auto r : records)
    {
        if (r->getPatientId() == pid)
        {
            r->displayInfo();
            found = true;
        }
    }
    if (!found)
        cout << "  No records found for patient ID \"" << pid << "\".\n";
}

// ── 10. View all medical records ──────────────────────────────
void Hospital::menuViewAllRecords()
{
    printHeader("  ALL MEDICAL RECORDS");
    if (records.empty())
    {
        cout << "  No medical records yet.\n";
        return;
    }
    for (auto r : records)
        r->displayInfo();
    cout << "\n  Total: " << records.size() << " record(s).\n";
}

// ── 11. Delete a patient ──────────────────────────────────────
void Hospital::menuDeletePatient()
{
    printHeader("  DELETE PATIENT");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (patients.empty())
    {
        cout << "  No patients to delete.\n";
        return;
    }

    for (auto p : patients)
        cout << "  [" << p->getPatientId() << "]  " << p->getName() << "\n";

    string pid;
    cout << "\n  Enter Patient ID to delete: ";
    getline(cin, pid);

    auto it = find_if(patients.begin(), patients.end(),
                      [&pid](Patient *p)
                      { return p->getPatientId() == pid; }); 
 
    if (it == patients.end())
    {
        cout << "    Patient not found.\n";
        return;
    }

    // Remove linked appointments (set pointer to null-guard; keep for history)
    for (auto a : appointments)
        if (a->getPatient() && a->getPatient()->getPatientId() == pid)
            a->setPatient(nullptr);

    cout << "    Patient \"" << (*it)->getName() << "\" deleted.\n";
    delete *it;
    patients.erase(it);
}

// ── 12. Save and exit ─────────────────────────────────────────
void Hospital::menuSaveAndExit()
{
    saveData();
    cout << "\n  Thank you for using Hospital Management System!\n";
    cout << "  Goodbye!\n\n";
}

// ════════════════════════════════════════════════════════════════
//  Main Menu Loop
// ════════════════════════════════════════════════════════════════

void Hospital::run()
{
    while (true)
    {
        cout << "\n";
        cout << "  |----------------------------------------------|\n";
        cout << "  |        HOSPITAL MANAGEMENT SYSTEM            |\n";
        cout << "  | Date: " << left << setw(31) << todayDate << "|\n";
        cout << "  |----------------------------------------------|\n";
        cout << "  |  PATIENT MANAGEMENT                          |\n";
        cout << "  |   [1]  Register New Patient                  |\n";
        cout << "  |   [2]  View All Patients                     |\n";
        cout << "  |   [3]  Delete Patient                        |\n";
        cout << "  |----------------------------------------------|\n";
        cout << "  |  DOCTOR MANAGEMENT                           |\n";
        cout << "  |   [4]  View All Doctors                      |\n";
        cout << "  |   [5]  Search Doctor                         |\n";
        cout << "  |----------------------------------------------|\n";
        cout << "  |  APPOINTMENTS                                |\n";
        cout << "  |   [6]  Book Appointment                      |\n";
        cout << "  |   [7]  View All Appointments                 |\n";
        cout << "  |   [8]  Update Appointment Status             |\n";
        cout << "  |----------------------------------------------|\n";
        cout << "  |  MEDICAL RECORDS                             |\n";
        cout << "  |   [9]  Add Medical Record                    |\n";
        cout << "  |  [10]  View Records by Patient               |\n";
        cout << "  |  [11]  View All Medical Records              |\n";
        cout << "  |----------------------------------------------|\n";
        cout << "  |   [12]  Save Data                            |\n";
        cout << "  |    [0]  Save & Exit                          |\n";
        cout << "  |----------------------------------------------|\n";
        cout << "  Enter choice: ";

        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "    Invalid input!. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            menuAddPatient();
            break;
        case 2:
            menuViewAllPatients();
            break;
        case 3:
            menuDeletePatient();
            break;
        case 4:
            menuViewAllDoctors();
            break;
        case 5:
            menuSearchDoctor();
            break;
        case 6:
            menuBookAppointment();
            break;
        case 7:
            menuViewAppointments();
            break;
        case 8:
            menuUpdateApptStatus();
            break;
        case 9:
            menuAddMedicalRecord();
            break;
        case 10:
            menuViewPatientRecords();
            break;
        case 11:
            menuViewAllRecords();
            break;
        case 12:
            saveData();
            break;
        case 0:
            menuSaveAndExit();
            return;
        default:
            cout << "    Invalid choice. Please try again.\n";
            break;
        }
    }
}