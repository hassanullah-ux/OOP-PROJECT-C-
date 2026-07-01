// ═══════════════════════════════════════════════════════════════
//  Person.cpp  |  Implementation of the Person base class
// ═══════════════════════════════════════════════════════════════

#include "Person.h"
#include <iostream>
#include <sstream>
#include <algorithm> // all_of
using namespace std;

// ── Constructors ──────────────────────────────────────────────
Person::Person()
    : name("Unknown"), age(0),
      cnic("0000000000000"), phone("00000000000"), gender("Unknown") {}

Person::Person(const string &name, int age,
               const string &cnic, const string &phone,
               const string &gender)
    : name(name), age(age), cnic(cnic), phone(phone), gender(gender) {}

Person::~Person() {}

// ── Getters ───────────────────────────────────────────────────
string Person::getName() const { return name; }
int Person::getAge() const { return age; }
string Person::getCnic() const { return cnic; }
string Person::getPhone() const { return phone; }
string Person::getGender() const { return gender; }

// ── Setters ───────────────────────────────────────────────────
void Person::setName(const string &n) { name = n; }
void Person::setAge(int a) { age = a; }
void Person::setGender(const string &g) { gender = g; }

bool Person::setCnic(const string &c)
{
    if (!isValidCnic(c))
    {
        cerr << "  [Validation Error] CNIC must be exactly 13 digits (no dashes).\n";
        return false;
    }
    cnic = c;
    return true;
}

bool Person::setPhone(const string &p)
{
    if (!isValidPhone(p))
    {
        cerr << "  [Validation Error] Phone number must be exactly 11 digits.\n";
        return false;
    }
    phone = p;
    return true;
}

// ── Static Validators ─────────────────────────────────────────
bool Person::isValidCnic(const string &c)
{
    if (c.length() != 13)
        return false;
    return all_of(c.begin(), c.end(), ::isdigit);
}

bool Person::isValidPhone(const string &p)
{
    if (p.length() != 11)
        return false;
    return all_of(p.begin(), p.end(), ::isdigit);
}

// ── Serialisation ─────────────────────────────────────────────
// Base format: name|age|cnic|phone|gender
string Person::serialize() const
{
    ostringstream oss;
    oss << name << "|" << age << "|" << cnic << "|" << phone << "|" << gender;
    return oss.str();
}

// Populates this object's Person fields from a pipe-delimited string
void Person::deserialize(const string &line)
{
    istringstream iss(line);
    string token;
    getline(iss, token, '|');
    name = token;
    getline(iss, token, '|');
    age = stoi(token);
    getline(iss, token, '|');
    cnic = token;
    getline(iss, token, '|');
    phone = token;
    getline(iss, token, '|');
    gender = token;
}