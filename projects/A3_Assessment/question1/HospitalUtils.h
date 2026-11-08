#ifndef HOSPITALUTILS_H
#define HOSPITALUTILS_H

#include "Patient.h"
#include "PatientRegister.h"
#include "WaitingList.h"
#include <iostream>
#include <string>

/**
 * @brief Creates a new patient with the given name, date of birth, and
 * registration number.
 *
 * @param name The name of the patient.
 * @param dob The date of birth of the patient.
 * @param regNum The registration number of the patient.
 * @return The newly created patient.
 */
Patient createPatient(const std::string &name, const std::string &dob,
                      int regNum);

// Function to print patient details from the register
void printPatientDetails(PatientRegister &reg, int regNum);

// Function to process the waiting list
void processWaitingList(WaitingList &list);

#endif // HOSPITALUTILS_H
