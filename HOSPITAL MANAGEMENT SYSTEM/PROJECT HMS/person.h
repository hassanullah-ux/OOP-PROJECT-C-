#ifndef PERSON_H
#define PERSON_H

// ═══════════════════════════════════════════════════════════════
//  Person.h  |  Abstract Base Class
//  Every individual in the system (Doctor / Patient) inherits
//  from this class.  All data members are PRIVATE; access is
//  only through validated public getters and setters.
// ═══════════════════════════════════════════════════════════════

#include <string>
using namespace std;

class Person
{
private:
    string name;   // Full name
    int age;       // Age in years
    string cnic;   // 13-digit national ID  (no dashes)
    string phone;  // 11-digit phone number
    string gender; // "Male" | "Female" | "Other"

public:
    // ── Constructors & Destructor ─────────────────────────────
    Person();
    Person(const string &name, int age,
           const string &cnic, const string &phone,
           const string &gender);
    virtual ~Person();

    // ── Getters ───────────────────────────────────────────────
    string getName() const;
    int getAge() const;
    string getCnic() const;
    string getPhone() const;
    string getGender() const;

    // ── Setters (validated) ───────────────────────────────────
    void setName(const string &name);
    void setAge(int age);
    bool setCnic(const string &cnic);   // returns false if invalid
    bool setPhone(const string &phone); // returns false if invalid
    void setGender(const string &gender);

    // ── Static Validation Helpers ─────────────────────────────
    static bool isValidCnic(const string &cnic);   // must be exactly 13 digits
    static bool isValidPhone(const string &phone); // must be exactly 11 digits

    // ── Pure Virtual — forces derived classes to implement ────
    virtual void displayInfo() const = 0;

    // ── Serialisation (pipe-delimited) for File I/O ───────────
    virtual string serialize() const;
    virtual void deserialize(const string &line);
};

#endif // PERSON_H