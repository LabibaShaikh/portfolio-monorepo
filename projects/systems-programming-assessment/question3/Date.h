#ifndef COSC1076_A3_DATE_H
#define COSC1076_A3_DATE_H

#include <iostream>

/**
 * @class Date
 * @brief Represents a date in the Gregorian calendar.
 *
 * The Date class provides functionality to work with dates, including
 * constructors, getters and setters, operator overloads, and stream
 * insertion/extraction operators.
 */
class Date {
public:
  // Constructors/DeConstructors

  /**
   * @brief Default constructor.
   *
   * Initializes a Date object with the current date.
   */
  Date();

  /**
   * @brief Constructor that takes the number of days since 1/3/0000.
   *
   * @param dayNumber The number of days since 1/3/0000.
   */
  Date(unsigned long dayNumber);

  /**
   * @brief Copy constructor.
   *
   * @param other The Date object to be copied.
   */
  Date(const Date &other);

  /**
   * @brief Move constructor.
   *
   * @param other The Date object to be moved.
   */
  Date(Date &&other);

  /**
   * @brief Destructor.
   */
  ~Date();

  /**
   * @brief Constructor that takes the year, month, and day.
   *
   * @param year The year of the date.
   * @param month The month of the date.
   * @param day The day of the date.
   *
   * @note The year should be a positive number, the month should be in the
   * range [1, 12], and the day should be in the range [1, 31] and valid.
   */
  Date(unsigned int year, unsigned int month, unsigned int day);

  // Getters and setters

  /**
   * @brief Get the day of the date.
   *
   * @return The day of the date.
   */
  unsigned int getDay() const;

  /**
   * @brief Get the month of the date.
   *
   * @return The month of the date.
   */
  unsigned int getMonth() const;

  /**
   * @brief Get the year of the date.
   *
   * @return The year of the date.
   */
  unsigned int getYear() const;

  /**
   * @brief Get the number of days since 1/3/0000.
   *
   * @return The number of days since 1/3/0000.
   */
  unsigned long getDayNumber() const;

  /**
   * @brief Set the date using the number of days since 1/3/0000.
   *
   * @param dayNumber The number of days since 1/3/0000.
   */
  void setDate(unsigned long dayNumber);

  /**
   * @brief Set the date using the year, month, and day.
   *
   * @param year The year of the date.
   * @param month The month of the date.
   * @param day The day of the date.
   *
   * @note The year should be a positive number, the month should be in the
   * range [1, 12], and the day should be in the range [1, 31] and valid.
   */
  void setDate(unsigned int year, unsigned int month, unsigned int day);

  // Operator overloads

  /**
   * @brief Assignment operator.
   *
   * @param other The Date object to be assigned.
   * @return A reference to the assigned Date object.
   */
  Date &operator=(const Date &other);

  /**
   * @brief Move assignment operator.
   *
   * @param other The Date object to be moved.
   * @return A reference to the moved Date object.
   */
  Date &operator=(Date &&other);

  /**
   * @brief Addition operator.
   *
   * @param days The number of days to add.
   * @return A new Date object representing the result of the addition.
   */
  Date operator+(int days) const;

  /**
   * @brief Subtraction operator.
   *
   * @param days The number of days to subtract.
   * @return A new Date object representing the result of the subtraction.
   */
  Date operator-(int days) const;

  /**
   * @brief Subtraction operator.
   *
   * @param other The Date object to subtract from.
   * @return The number of days between the two dates.
   */
  int operator-(const Date &other) const;

  /**
   * @brief Addition assignment operator.
   *
   * @param days The number of days to add.
   * @return A reference to the modified Date object.
   */
  Date &operator+=(int days);

  /**
   * @brief Subtraction assignment operator.
   *
   * @param days The number of days to subtract.
   * @return A reference to the modified Date object.
   */
  Date &operator-=(int days);

  /**
   * @brief Prefix increment operator.
   *
   * @return A reference to the incremented Date object.
   */
  Date &operator++();

  /**
   * @brief Postfix increment operator.
   *
   * @return A new Date object representing the original value before
   * incrementing.
   */
  Date operator++(int);

  /**
   * @brief Prefix decrement operator.
   *
   * @return A reference to the decremented Date object.
   */
  Date &operator--();

  /**
   * @brief Postfix decrement operator.
   *
   * @return A new Date object representing the original value before
   * decrementing.
   */
  Date operator--(int);

  /**
   * @brief Equality operator.
   *
   * @param other The Date object to compare with.
   * @return True if the two dates are equal, false otherwise.
   */
  bool operator==(const Date &other) const;

  /**
   * @brief Inequality operator.
   *
   * @param other The Date object to compare with.
   * @return True if the two dates are not equal, false otherwise.
   */
  bool operator!=(const Date &other) const;

  /**
   * @brief Less than operator.
   *
   * @param other The Date object to compare with.
   * @return True if the current date is less than the other date, false
   * otherwise.
   */
  bool operator<(const Date &other) const;

  /**
   * @brief Less than or equal to operator.
   *
   * @param other The Date object to compare with.
   * @return True if the current date is less than or equal to the other date,
   * false otherwise.
   */
  bool operator<=(const Date &other) const;

  /**
   * @brief Greater than operator.
   *
   * @param other The Date object to compare with.
   * @return True if the current date is greater than the other date, false
   * otherwise.
   */
  bool operator>(const Date &other) const;

  /**
   * @brief Greater than or equal to operator.
   *
   * @param other The Date object to compare with.
   * @return True if the current date is greater than or equal to the other
   * date, false otherwise.
   */
  bool operator>=(const Date &other) const;

  /**
   * @brief Index operator.
   *
   * @param field The field to access ('y' for year, 'm' for month, 'd' for
   * day).
   * @return A reference to the specified field.
   */
  int &operator[](char field);

  /**
   * @brief Index operator (const version).
   *
   * @param field The field to access ('y' for year, 'm' for month, 'd' for
   * day).
   * @return A const reference to the specified field.
   */
  const int &operator[](char field) const;

  /**
   * @brief Stream insertion operator.
   *
   * @param os The output stream.
   * @param date The Date object to output.
   * @return The output stream.
   */
  friend std::ostream &operator<<(std::ostream &os, const Date &date);

  /**
   * @brief Stream extraction operator.
   *
   * @param is The input stream.
   * @param date The Date object to input.
   * @return The input stream.
   */
  friend std::istream &operator>>(std::istream &is, Date &date);

private:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */
  unsigned int year;
  unsigned int month;
  unsigned int day;
};

#endif // COSC1076_A3_DATE_H
