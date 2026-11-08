#include "HospitalUtils.h"
#include "Patient.h"
#include "PatientRegister.h"
#include "WaitingList.h"

#include <iostream>

int main() {
  try {
    // Create some patients
    Patient patient1 = createPatient("John Doe", "1990-01-01", 123456);
    Patient patient2 = createPatient("Jane Smith", "1985-05-23", 654321);
    Patient patient3 = createPatient("Alice Johnson", "1979-11-12", 987654);

    // Add admission entries for patients
    patient1.addAdmissionEntry({"2024-01-01", "2024-01-10", "General"});
    patient2.addAdmissionEntry({"2024-02-01", "2024-02-05", "Surgical"});
    patient3.addAdmissionEntry({"2024-03-01", "", "ICU"}); // Ongoing admission

    // Initialize patient register and add patients
    PatientRegister patientRegister;
    patientRegister.addPatient(patient1);
    patientRegister.addPatient(patient2);
    patientRegister.addPatient(patient3);

    // Test patient register functionalities
    std::cout << "Testing PatientRegister functionalities:" << std::endl;

    // Check if a patient is in the register
    std::cout << "Contains patient 123456: "
              << patientRegister.containsPatient(123456) << std::endl;

    // Retrieve an individual patient
    Patient &retrievedPatient = patientRegister.getPatient(123456);
    std::cout << "Retrieved patient: " << retrievedPatient << std::endl;

    // Support operator[]
    Patient &retrievedPatientByOp = patientRegister[123456];
    std::cout << "Retrieved patient using operator[]: " << retrievedPatientByOp
              << std::endl;

    // Remove a patient from the register
    patientRegister.removePatient(123456);
    std::cout << "Removed patient 123456. Contains patient 123456: "
              << patientRegister.containsPatient(123456) << std::endl;

    // Check for duplicates
    patientRegister.addPatient(patient1); // Adding back the patient
    try {
      patientRegister.addPatient(
          patient1); // Trying to add the same patient again
    } catch (const std::runtime_error &e) {
      std::cout << "Caught expected error for duplicate patient: " << e.what()
                << std::endl;
    }

    // Initialize waiting list and add patients
    WaitingList waitingList;
    waitingList.addPatient(123456); // Assuming queue numbers are the same as
                                    // registration numbers for simplicity
    waitingList.addPatient(654321);
    waitingList.addPatient(987654);

    // Test waiting list functionalities
    std::cout << "Testing WaitingList functionalities:" << std::endl;

    // Get the next patient to start the surgery
    std::cout << "Next patient in the queue: " << waitingList.getNextPatient()
              << std::endl;

    // Remove patients from the queue
    waitingList.removePatient();
    std::cout << "Removed a patient. Next patient in the queue: "
              << waitingList.getNextPatient() << std::endl;

    // Get unique queue number for a patient
    std::cout << "Queue number for patient 654321: "
              << waitingList.getQueueNumber(654321) << std::endl;

    // Get the number of patients remaining in the queue
    std::cout << "Remaining patients in the queue: "
              << waitingList.getRemainingPatients() << std::endl;

    // Process the waiting list
    processWaitingList(waitingList);

  } catch (const std::invalid_argument &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  } catch (const std::runtime_error &e) {
    std::cerr << "Runtime Error: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "An unexpected error occurred." << std::endl;
  }

  return EXIT_SUCCESS;
}
