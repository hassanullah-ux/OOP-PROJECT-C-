// ═══════════════════════════════════════════════════════════════
//  main.cpp  |  Entry Point
//  1. Displays a welcome banner.
//  2. Prompts for today's date (DD/MM/YYYY) — used across the
//     entire session for appointments and medical records.
//  3. Constructs the Hospital object (which auto-loads data and
//     populates the 20 built-in doctors).
//  4. Hands control to Hospital::run() — the main menu loop.
// ═══════════════════════════════════════════════════════════════

#include "Hospital.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;

// ── Simple date format validator (DD/MM/YYYY) ─────────────────
static bool isValidDate(const string &date)
{
    // Matches DD/MM/YYYY where DD: 01-31, MM: 01-12, YYYY: 4 digits
    regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/[0-9]{4}$)");
    return regex_match(date, pattern);
}

int main()
{
    // ── Welcome Banner ────────────────────────────────────────
    cout << "\n";
    cout << "  ----------------------------------------------------\n";
    cout << "  |           HOSPITAL MANAGEMENT SYSTEM             |\n";
    cout << "  |--------------------------------------------------|\n";
    cout << "  |  Features:                                       |\n";
    cout << "  |  - 20 Pre-loaded Pakistani Specialist Doctors    |\n";
    cout << "  |  - Patient Registration & Management             |\n";
    cout << "  |  - Appointment Booking System                    |\n";
    cout << "  |  - Medical Records with Diagnosis & Prescription |\n";
    cout << "  |  - Persistent File I/O (hospital_data.txt)       |\n";
    cout << "  |  - CNIC (13-digit) & Phone (11-digit) Validation |\n";
    cout << "  ----------------------------------------------------\n\n";

    // ── Step 1: Date Input (required before anything else) ────
    string todayDate;
    while (true)
    {
        cout << "  Enter today's date (DD/MM/YYYY): ";
        cin >> todayDate;

        if (isValidDate(todayDate))
        {
            cout << "    Session date set to: " << todayDate << "\n";
            break;
        }
        cout << "    Invalid date format. Please use DD/MM/YYYY "
                "(e.g. 29/06/2025).\n";
    }

    // ── Step 2: Launch the Hospital system ────────────────────
    // Constructor calls populateDoctors() then loadData() internally
    Hospital hospital(todayDate);

    // ── Step 3: Enter the main menu loop ─────────────────────
    hospital.run();
    return 0;
}