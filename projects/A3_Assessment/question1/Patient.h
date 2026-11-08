#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct AdmissionEntry {
  std::string admissionDate;
  std::string dischargeDate;
  std::string admittedWard;
};

/**
 * @class Patient
 * @brief Represents a patient in a medical system.
 *
 * The Patient class stores information about a patient, including their name,
 * date of birth, registration number, and admission history. It provides
 * methods to access and modify this information.
 *
 * I chose the Patient class as an ADT (Abstract Data Type) because it
 * encapsulates all the necessary data and functionality related to a patient in
 * a hospital. By representing a patient as an object, we can easily manage and
 * manipulate their information in a structured and organized manner.
 *
 * The Patient class is a sensible choice because it allows us to store and
 * retrieve important details about a patient, such as their name, date of
 * birth, and registration number. Additionally, it provides a history of
 * admission entries, allowing us to track the patient's hospital visits over
 * time.
 *
 * By encapsulating the patient's data and providing methods to validate and
 * modify it, the Patient class promotes data integrity and ensures that the
 * information remains consistent and accurate throughout the program.
 */
class Patient {
private:
  std::string name;        // The name of the patient
  std::string dateOfBirth; // The date of birth of the patient
  int registrationNumber;  // The registration number of the patient
  std::vector<AdmissionEntry>
      admissionHistory; // The history of admission entries for the patient

  // Helper methods to validate data
  bool
  isValidName(const std::string &name); // Validates the name of the patient
  bool isValidDateOfBirth(
      const std::string
          &dateOfBirth); // Validates the date of birth of the patient
  bool isValidAdmissionEntry(
      const AdmissionEntry &entry); // Validates an admission entry

public:
  // Default constructor
  Patient(); // Creates a new Patient object with default values

  /**
   * @brief Constructor with error handling.
   *
   * Creates a new Patient object with the given name, date of birth, and
   * registration number.
   *
   * @param name The name of the patient.
   * @param dateOfBirth The date of birth of the patient.
   * @param registrationNumber The registration number of the patient.
   */
  Patient(const std::string &name, const std::string &dateOfBirth,
          int registrationNumber);

  // Getter methods

  /**
   * @brief Returns the name of the patient.
   *
   * @return The name of the patient.
   */
  std::string getName() const;

  /**
   * @brief Returns the date of birth of the patient.
   *
   * @return The date of birth of the patient.
   */
  std::string getDateOfBirth() const;

  /**
   * @brief Returns the registration number of the patient.
   *
   * @return The registration number of the patient.
   */
  int getRegistrationNumber() const;

  /**
   * @brief Returns the admission history of the patient.
   *
   * @return The admission history of the patient.
   */
  std::vector<AdmissionEntry> getAdmissionHistory() const;

  // Add an admission entry to the history with error handling

  /**
   * @brief Adds a new admission entry to the patient's admission history.
   *
   * This method validates the admission entry before adding it to the history.
   *
   * @param entry The admission entry to be added.
   */
  void addAdmissionEntry(const AdmissionEntry &entry);

  // Overload the operator<< to write patient data to an output stream

  /**
   * @brief Overloads the << operator to allow writing patient data to an output
   * stream.
   *
   * @param os The output stream to write to.
   * @param patient The patient object to write.
   * @return The output stream after writing the patient data.
   */
  friend std::ostream &operator<<(std::ostream &os, const Patient &patient);
};

#endif // PATIENT_H
