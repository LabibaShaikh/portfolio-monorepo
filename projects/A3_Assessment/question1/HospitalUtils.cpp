#include "HospitalUtils.h"

// Function to create and return a Patient object
Patient createPatient(const std::string &name, const std::string &dob,
                      int regNum) {
  Patient patient(name, dob, regNum);
  // Add admission entries if necessary
  return patient;
}

// Function to print patient details from the register
void printPatientDetails(PatientRegister &reg, int regNum) {
  try {
    std::cout << "Patient " << regNum << " Details:\n";
    std::cout << reg.getPatient(regNum) << std::endl;
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

// Function to process the waiting list
void processWaitingList(WaitingList &list) {
  try {
    while (list.getRemainingPatients() > 0) {
      std::cout << "Next patient in the surgery queue: "
                << list.getNextPatient() << std::endl;
      list.removePatient();
    }
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
