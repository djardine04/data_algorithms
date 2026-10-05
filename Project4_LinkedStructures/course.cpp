#include "course.h"

//TODO: Add default parameter values...
Course::Course(int number,
               const std::string& name,
               double credit_hr,
               double grade) {

    if (number < 0)
        throw std::invalid_argument("Invalid course number");
    //TODO: validate additional parameters...
    
    if (credit_hr < 0.0 || credit_hr > 5.0)
        throw std::invalid_argument("Invalid credit hours");

    if (grade < 0.0 || grade > 4.0)
        throw std::invalid_argument("Invalid grade");

    the_number = number;
    the_name = name;
    the_credit_hr = credit_hr;
    the_grade = grade;
}

int Course::number() const { return the_number; }
//TODO: define remaining methods...
std::string Course::name() const { return the_name; }

double Course::credit_hr() const { return the_credit_hr; }

double Course::grade() const { return the_grade; }

bool Course::operator==(const Course& other) const {
    return the_number == other.the_number;
}
//TODO: define remaining overloaded operator methods...
bool Course::operator!=(const Course& other) const {
    return the_number != other.the_number;
}

bool Course::operator<(const Course& other) const {
    return the_number < other.the_number;
}

bool Course::operator>(const Course& other) const {
    return the_number > other.the_number;
}

bool Course::operator<=(const Course& other) const {
    return the_number <= other.the_number;
}

bool Course::operator>=(const Course& other) const {
    return the_number >= other.the_number;
}

bool Course::operator==(int number) const {
    return the_number == number;
}

bool Course::operator<(int number) const {
    return the_number < number;
}

bool Course::operator>(int number) const {
    return the_number > number;
}

//TODO: Make sure you understand how this works...
std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << "\nCS" << c.the_number << " "
       << c.the_name
       << " Grade: " << c.the_grade
       << " Credit Hours: " << c.the_credit_hr;
    return os;
}