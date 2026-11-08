#include "Patient.h"

// Default constructor
Patient::Patient() : name(""), dateOfBirth(""), registrationNumber(0) {}

// Constructor with error handling
Patient::Patient(const std::string &name, const std::string &dateOfBirth,
                 int registrationNumber)
    : name(name), dateOfBirth(dateOfBirth),
      registrationNumber(registrationNumber) {
  if (name.empty() || dateOfBirth.empty() || registrationNumber <= 0) {
    throw std::invalid_argument("Invalid patient data");
  }
  if (!isValidName(name) || !isValidDateOfBirth(dateOfBirth)) {
    throw std::invalid_argument("Invalid name or date of birth");
  }
}

// Getter methods
std::string Patient::getName() const { return name; }
std::string Patient::getDateOfBirth() const { return dateOfBirth; }
int Patient::getRegistrationNumber() const { return registrationNumber; }
std::vector<AdmissionEntry> Patient::getAdmissionHistory() const {
  return admissionHistory;
}

// Add an admission entry to the history with error handling
void Patient::addAdmissionEntry(const AdmissionEntry &entry) {
  if (entry.admissionDate.empty() || entry.admittedWard.empty()) {
    throw std::invalid_argument("Invalid admission entry");
  }
  if (!isValidAdmissionEntry(entry)) {
    throw std::invalid_argument("Invalid admission entry");
  }
  admissionHistory.push_back(entry);
}

// Overload the operator<< to write patient data to an output stream
// returns the output stream
std::ostream &operator<<(std::ostream &os, const Patient &patient) {
  os << "Name: " << patient.name << "\n";
  os << "Date of Birth: " << patient.dateOfBirth << "\n";
  os << "Registration Number: " << patient.registrationNumber << "\n";
  os << "Admission History:\n";
  for (const auto &entry : patient.admissionHistory) {
    os << "  Admission Date: " << entry.admissionDate << "\n";
    os << "  Discharge Date: " << entry.dischargeDate << "\n";
    os << "  Admitted Ward: " << entry.admittedWard << "\n";
  }
  return os;
}

// Helper methods to validate data
bool Patient::isValidName(const std::string &name) { return !name.empty(); }

bool Patient::isValidDateOfBirth(const std::string &dateOfBirth) {
  return !dateOfBirth.empty();
}

bool Patient::isValidAdmissionEntry(const AdmissionEntry &entry) {
  return !entry.admissionDate.empty() && !entry.admittedWard.empty();
}
