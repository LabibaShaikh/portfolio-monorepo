#include "Date.h"
#include <cassert>
#include <iomanip>
#include <stdexcept>

// Default constructor
Date::Date() : year(1970), month(1), day(1) {
  // Postcondition: The date is initialized to 1/1/1970
  assert(year == 1970 && month == 1 && day == 1);
}

Date::Date(unsigned long dayNumber) {}

// Parameterized constructor
Date::Date(unsigned int year, unsigned int month, unsigned int day)
    : year(year), month(month), day(day) {
  // Preconditions: The provided date must be valid
  assert(year > 0);
  assert(month >= 1 && month <= 12);
  assert(day >= 1 && day <= 31);
  if (month == 2 && day > 29)
    assert(false);
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    assert(false);
  if (month == 2 && day == 29 &&
      !((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
    assert(false);

  // Postcondition: The date is initialized to the provided values
  assert(this->year == year && this->month == month && this->day == day);
}

// Copy constructor
Date::Date(const Date &other)
    : year(other.year), month(other.month), day(other.day) {
  // Postcondition: The date is a copy of the other date
  assert(this->year == other.year && this->month == other.month &&
         this->day == other.day);
}

// Move constructor
Date::Date(Date &&other)
    : year(other.year), month(other.month), day(other.day) {
  // Postcondition: The date is a copy of the other date
  assert(this->year == other.year && this->month == other.month &&
         this->day == other.day);
}

// Destructor
Date::~Date() {
  // No resources to free
}

// Getters
unsigned int Date::getDay() const { return day; }

unsigned int Date::getMonth() const { return month; }

unsigned int Date::getYear() const { return year; }

// Convert date to day number
unsigned long Date::getDayNumber() const {
  unsigned long m = ((unsigned long)month + 9) % 12;
  unsigned long y = (unsigned long)year - ((unsigned long)month / 10);
  return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 +
         ((unsigned long)day - 1);
}

// Set date from day number
void Date::setDate(unsigned long dayNumber) {
  // Preconditions: dayNumber must be a non-negative number
  assert(dayNumber >= 0);

  unsigned long y = (10000 * dayNumber + 14780) / 3652425;
  unsigned long ddd = dayNumber - (365 * y + y / 4 - y / 100 + y / 400);
  if (ddd < 0) {
    y = y - 1;
    ddd = dayNumber - (365 * y + y / 4 - y / 100 + y / 400);
  }
  unsigned long mi = (100 * ddd + 52) / 3060;
  unsigned long mm = (mi + 2) % 12 + 1;
  y = y + (mi + 2) / 12;
  unsigned long dd = ddd - (mi * 306 + 5) / 10 + 1;

  this->day = (unsigned int)dd;
  this->month = (unsigned int)mm;
  this->year = (unsigned int)y;

  // Postcondition: The date is set to the correct values based on the day
  // number
  assert(this->day == dd && this->month == mm && this->year == y);
}

// Set date
void Date::setDate(unsigned int year, unsigned int month, unsigned int day) {
  // Preconditions: The provided date must be valid
  assert(year > 0);
  assert(month >= 1 && month <= 12);
  assert(day >= 1 && day <= 31);
  if (month == 2 && day > 29)
    assert(false);
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    assert(false);
  if (month == 2 && day == 29 &&
      !((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
    assert(false);

  this->year = year;
  this->month = month;
  this->day = day;

  // Postcondition: The date is set to the provided values
  assert(this->year == year && this->month == month && this->day == day);
}

// Operator overloads
Date &Date::operator=(const Date &other) {
  if (this != &other) {
    year = other.year;
    month = other.month;
    day = other.day;
  }
  // Postcondition: The date is set to the values of the other date
  assert(this->year == other.year && this->month == other.month &&
         this->day == other.day);
  return *this;
}

Date &Date::operator=(Date &&other) {
  if (this != &other) {
    year = other.year;
    month = other.month;
    day = other.day;
  }
  // Postcondition: The date is set to the values of the other date
  assert(this->year == other.year && this->month == other.month &&
         this->day == other.day);
  return *this;
}

Date Date::operator+(int days) const {
  Date result(*this);
  result.setDate(this->getDayNumber() + days);
  // Postcondition: The result date is the current date plus the specified days
  assert(result.getDayNumber() == this->getDayNumber() + days);
  return result;
}

Date Date::operator-(int days) const {
  Date result(*this);
  result.setDate(this->getDayNumber() - days);
  // Postcondition: The result date is the current date minus the specified days
  assert(result.getDayNumber() == this->getDayNumber() - days);
  return result;
}

int Date::operator-(const Date &other) const {
  return this->getDayNumber() - other.getDayNumber();
}

Date &Date::operator+=(int days) {
  unsigned long currentDayNumber = this->getDayNumber();
  this->setDate(currentDayNumber + days);
  // Postcondition: The date is incremented by the specified days
  assert(this->getDayNumber() == currentDayNumber + days);
  return *this;
}

Date &Date::operator-=(int days) {
  unsigned long currentDayNumber = this->getDayNumber();
  this->setDate(currentDayNumber - days);
  // Postcondition: The date is decremented by the specified days
  assert(this->getDayNumber() == currentDayNumber - days);
  return *this;
}

Date &Date::operator++() {
  unsigned long currentDayNumber = this->getDayNumber();
  this->setDate(currentDayNumber + 1);
  // Postcondition: The date is incremented by 1 day
  assert(this->getDayNumber() == currentDayNumber + 1);
  return *this;
}

Date Date::operator++(int) {
  Date temp(*this);
  unsigned long currentDayNumber = this->getDayNumber();
  this->setDate(currentDayNumber + 1);
  // Postcondition: The date is incremented by 1 day
  assert(this->getDayNumber() == currentDayNumber + 1);
  return temp;
}

Date &Date::operator--() {
  unsigned long currentDayNumber = this->getDayNumber();
  this->setDate(currentDayNumber - 1);
  // Postcondition: The date is decremented by 1 day
  assert(this->getDayNumber() == currentDayNumber - 1);
  return *this;
}

Date Date::operator--(int) {
  Date temp(*this);
  unsigned long currentDayNumber = this->getDayNumber();
  this->setDate(currentDayNumber - 1);
  // Postcondition: The date is decremented by 1 day
  assert(this->getDayNumber() == currentDayNumber - 1);
  return temp;
}

bool Date::operator==(const Date &other) const {
  return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date &other) const { return !(*this == other); }

bool Date::operator<(const Date &other) const {
  return this->getDayNumber() < other.getDayNumber();
}

bool Date::operator<=(const Date &other) const {
  return this->getDayNumber() <= other.getDayNumber();
}

bool Date::operator>(const Date &other) const {
  return this->getDayNumber() > other.getDayNumber();
}

bool Date::operator>=(const Date &other) const {
  return this->getDayNumber() >= other.getDayNumber();
}

int &Date::operator[](char field) {
  if (field == 'd') {
    return (int &)day;
  } else if (field == 'm') {
    return (int &)month;
  } else if (field == 'y') {
    return (int &)year;
  } else {
    throw std::invalid_argument("Invalid field");
  }
}

const int &Date::operator[](char field) const {
  if (field == 'd') {
    return (int &)day;
  } else if (field == 'm') {
    return (int &)month;
  } else if (field == 'y') {
    return (int &)year;
  } else {
    throw std::invalid_argument("Invalid field");
  }
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
  os << date.day << "/" << date.month << "/" << date.year;
  return os;
}

std::istream &operator>>(std::istream &is, Date &date) {
  char sep;
  is >> date.day >> sep >> date.month >> sep >> date.year;
  // Check if the provided date is valid
  if (date.year <= 0 || date.month < 1 || date.month > 12 || date.day < 1 ||
      date.day > 31 || (date.month == 2 && date.day > 29) ||
      ((date.month == 4 || date.month == 6 || date.month == 9 ||
        date.month == 11) &&
       date.day > 30) ||
      (date.month == 2 && date.day == 29 &&
       !((date.year % 4 == 0 && date.year % 100 != 0) ||
         (date.year % 400 == 0)))) {
    throw std::invalid_argument("Invalid date");
  }
  return is;
}
