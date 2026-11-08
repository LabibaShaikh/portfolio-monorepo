#include "WaitingList.h"
#include <stdexcept>

// Add a patient to the starting queue and assign a unique queue number
void WaitingList::addPatient(int queueNumber) {
  if (patientSet.find(queueNumber) != patientSet.end()) {
    throw std::runtime_error("Patient is already in the queue.");
  }
  queueNumbers.push(queueNumber);
  patientSet.insert(queueNumber);
}

// Remove a patient from the queue as they start the surgery
void WaitingList::removePatient() {
  if (queueNumbers.empty()) {
    throw std::runtime_error("Cannot remove a patient from an empty queue.");
  }
  int queueNumber = queueNumbers.front();
  queueNumbers.pop();
  patientSet.erase(queueNumber);
}

// Get the next patient to start the surgery
int WaitingList::getNextPatient() {
  if (queueNumbers.empty()) {
    throw std::runtime_error("Cannot get next patient from an empty queue.");
  }
  return queueNumbers.front();
}

// Get the unique queue number for a patient
int WaitingList::getQueueNumber(int patient) {
  if (patientSet.find(patient) == patientSet.end()) {
    throw std::runtime_error("Patient not found in the queue.");
  }
  return patient;
}

// Get the number of patients remaining in the queue yet to start the surgery
int WaitingList::getRemainingPatients() { return queueNumbers.size(); }
