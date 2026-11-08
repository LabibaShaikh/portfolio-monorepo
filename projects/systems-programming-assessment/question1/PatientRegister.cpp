#include "PatientRegister.h"
#include <stdexcept>

// Add a patient to the register
void PatientRegister::addPatient(const Patient &patient) {
  int registrationNumber = patient.getRegistrationNumber();
  if (patients.find(registrationNumber) != patients.end()) {
    throw std::runtime_error("Patient already exists in the register.");
  }
  patients[registrationNumber] = patient;
}

// Remove a patient from the register
void PatientRegister::removePatient(int registrationNumber) {
  if (patients.find(registrationNumber) == patients.end()) {
    throw std::runtime_error(
        "Cannot remove a non-existent patient from the register.");
  }
  patients.erase(registrationNumber);
}

// Check if a patient is in the register
bool PatientRegister::containsPatient(int registrationNumber) const {
  return patients.find(registrationNumber) != patients.end();
}

// Retrieve an individual patient stored within the register
Patient &PatientRegister::getPatient(int registrationNumber) {
  if (!containsPatient(registrationNumber)) {
    throw std::runtime_error("Patient not found in the register.");
  }
  return patients[registrationNumber];
}

// Support the use of the operator[], to retrieve a patient by his/her
// registration number
Patient &PatientRegister::operator[](int registrationNumber) {
  if (!containsPatient(registrationNumber)) {
    throw std::runtime_error("Patient not found in the register.");
  }
  return patients[registrationNumber];
}

// Clear all entries in the register
void PatientRegister::clear() {
  if (patients.empty()) {
    throw std::runtime_error("The register is already empty.");
  }
  patients.clear();
}
