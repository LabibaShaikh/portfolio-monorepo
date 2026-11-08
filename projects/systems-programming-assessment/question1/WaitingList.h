#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <queue>
#include <stdexcept>
#include <unordered_set>

/**
 * @class WaitingList
 * @brief Represents a waiting list for patients to start surgery.
 *
 * The WaitingList class manages a queue of patients waiting to start surgery.
 * Each patient is assigned a unique queue number and can be added, removed, and
 * accessed from the queue. The class also provides methods to retrieve
 * information about the queue, such as the number of remaining patients.
 * It assigns unique queue numbers to each patient and ensures that patients are
 * not duplicated.
 *
 * The choice of using a queue data structure for the waiting list is sensible
 * because it follows the First-In-First-Out (FIFO) principle, which is
 * appropriate for managing a queue of patients waiting for surgery. When a new
 * patient is added, they are placed at the end of the queue, and when a patient
 * starts the surgery, they are removed from the front of the queue. This
 * ensures that patients are served in the order they arrived, which is fair and
 * efficient.
 *
 * Additionally, using a queue allows for constant-time insertion and removal
 * operations, making it efficient for managing a large number of patients. The
 * use of an unordered set ensures that patients are not duplicated in the
 * queue, preventing any confusion or errors that may arise from having multiple
 * instances of the same patient in the waiting list.
 */
class WaitingList {
private:
  std::queue<int> queueNumbers; // Queue to store the unique queue numbers
  std::unordered_set<int>
      patientSet; // Set to ensure patients are not duplicated

public:
  /**
   * @brief Add a patient to the starting queue and assign a unique queue
   * number.
   *
   * @param queueNumber The unique queue number to assign to the patient.
   */
  void addPatient(int queueNumber);

  /**
   * @brief Remove a patient from the queue as they start the surgery.
   *
   * This method removes the next patient from the queue as they start the
   * surgery. If the queue is empty, a std::out_of_range exception is thrown.
   */
  void removePatient();

  /**
   * @brief Get the next patient to start the surgery.
   *
   * @return The queue number of the next patient to start the surgery.
   * @throw std::out_of_range If the queue is empty.
   */
  int getNextPatient();

  /**
   * @brief Get the unique queue number for a patient.
   *
   * @param patient The patient for which to retrieve the queue number.
   * @return The unique queue number assigned to the patient.
   * @throw std::out_of_range If the patient is not found in the queue.
   */
  int getQueueNumber(int patient);

  /**
   * @brief Get the number of patients remaining in the queue yet to start the
   * surgery.
   *
   * @return The number of patients remaining in the queue.
   */
  int getRemainingPatients();
};

#endif // WAITINGLIST_H
