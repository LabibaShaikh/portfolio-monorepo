/*                                           */
/* DO NOT MOFIFY ANY CODE IN THIS FILE       */
/*                                           */

#include <exception>
#include <iostream>

#include "Date.h"

int main() {

  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  std::cout << std::endl << "*** Q3 PART 1 ***" << std::endl;

  // Create a date object: examDate and initialize it to 10/06/2021
  Date examDate(2021, 6, 10);
  // Print the examDate and the "day number" for examDate
  std::cout << "Exam date: " << examDate << " (" << examDate.getDayNumber()
            << ") " << std::endl;

  // Create a date object: resultDate and initialize it to 12/07/2021
  Date resultDate(2021, 7, 12);
  // Print the resultDate and the "day number" for resultDate
  std::cout << "Result release date: " << resultDate << " ("
            << resultDate.getDayNumber() << ") " << std::endl;

  // Print #days between resultDate and examDate
  std::cout << "Days to get results = " << resultDate - examDate << std::endl;

  // Compute exam end date. This is one day after examDate
  examDate += 1;
  std::cout << "Exam end date: " << examDate << std::endl;

  // Compute the resultDate last year: 365 days before this resultDate
  Date resultDateLastYear = resultDate - 365;
  std::cout << "Result Date Last Year: " << resultDateLastYear << std::endl;

  std::cout << std::endl << "*** Q3 PART 2 ***" << std::endl;

  // Create two date objects
  Date date1(2020, 6, 10);
  Date date2(2017, 2, 28);
  std::cout << "date1: " << date1 << ", date2: " << date2 << std::endl;

  // Compare the two dates and print
  if (date1 == date2) {
    std::cout << "date1 == date2" << std::endl;
  } else if (date1 < date2) {
    std::cout << "date1 < date2" << std::endl;
  } else {
    std::cout << "date1 > date2" << std::endl;
  }

  std::cout << std::endl << "*** Q3 PART 3 ***" << std::endl;

  // Create a date object
  Date date3(1913, 6, 10);
  std::cout << "date3: " << date3 << std::endl;

  // Print the next date from date3
  ++date3;
  std::cout << "++date3: " << date3 << std::endl;

  // Print the previous date from date3
  --date3;
  std::cout << "date3--: " << date3 << std::endl;

  std::cout << std::endl << "*** Q3 PART 4 ***" << std::endl;
  // Update the month of date3
  std::cout << "date3: " << date3 << std::endl;

  try {
    date3['m'] = 12;
    std::cout << "date2: " << date3['d'] << "/" << date3['m'] << "/"
              << date3['y'] << std::endl;
  } catch (std::exception &e) {
    std::cout << "*** caught: " << e.what() << std::endl;
  }

  std::cout << std::endl;

  return EXIT_SUCCESS;
}