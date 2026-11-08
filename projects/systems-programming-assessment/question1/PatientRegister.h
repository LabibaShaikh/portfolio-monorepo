#ifndef PATIENTREGISTER_H
#define PATIENTREGISTER_H

#include "Patient.h"
#include <unordered_map>

/**
 * @class PatientRegister
 * @brief A class that represents a register of patients.
 *
 * The PatientRegister class provides functionality to add, remove, and retrieve
 * patients from the register. It uses an unordered_map for efficient retrieval
 * of patients based on their registration number.
 *
 * The choice of using an unordered_map as the underlying data structure for the
 * patient register is based on its constant-time complexity for average case
 * operations such as insertion, removal, and retrieval. This makes it highly
 * efficient for managing a large number of patients in the register.
 *
 * Additionally, the unordered_map allows for fast lookup of patients based on
 * their registration number, which is a key requirement for the register. The
 * registration number serves as the key in the unordered_map, and the
 * associated Patient object is stored as the value. This allows for direct
 * access to patients without the need for iterating through the entire
 * collection.
 *
 * Overall, the use of an unordered_map provides a balance between efficiency
 * and ease of use for managing the patient register, making it a suitable
 * choice for this application.
 */

class PatientRegister {
private:
  std::unordered_map<int, Patient>
      patients; // using unordered_map for efficient retrieval

public:
  /**
   * @brief Adds a patient to the register.
   *
   * @param patient The patient to be added.
   */
  void addPatient(const Patient &patient);

  /**
   * @brief Removes a patient from the register.
   *
   * @param registrationNumber The registration number of the patient to be
   * removed.
   */
  void removePatient(int registrationNumber);

  /**
   * @brief Checks if a patient is in the register.
   *
   * @param registrationNumber The registration number of the patient to be
   * checked.
   * @return true if the patient is in the register, false otherwise.
   */
  bool containsPatient(int registrationNumber) const;

  /**
   * @brief Retrieves an individual patient stored within the register.
   *
   * @param registrationNumber The registration number of the patient to be
   * retrieved.
   * @return A reference to the patient object.
   */
  Patient &getPatient(int registrationNumber);

  /**
   * @brief Supports the use of the operator operator[], to retrieve a patient
   * by their registration number.
   *
   * @param registrationNumber The registration number of the patient to be
   * retrieved.
   * @return A reference to the patient object.
   */
  Patient &operator[](int registrationNumber);

  /**
   * @brief Clears all entries in the register.
   */
  void clear();
};

#endif // PATIENTREGISTER_H
