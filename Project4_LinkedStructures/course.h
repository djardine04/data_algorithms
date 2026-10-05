#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <stdexcept>
#include <iostream>

class Course {
private:
    int the_number;
    std::string the_name;
    double the_credit_hr;
    double the_grade;

public:
    Course(int number = 0,
           const std::string& name = "",
           double credit_hr = 0.0,
           double grade = 0.0);

    // Accessors
    int number() const;
    std::string name() const;
    double credit_hr() const;
    double grade() const;

    // Comparisons (compare by course number)
    bool operator==(const Course& other) const;
    bool operator!=(const Course& other) const;
    bool operator<(const Course& other) const;
    bool operator>(const Course& other) const;
    bool operator<=(const Course& other) const;
    bool operator>=(const Course& other) const;

    bool operator==(int number) const;
    bool operator<(int number) const;
    bool operator>(int number) const;

    // Output
    friend std::ostream& operator<<(std::ostream& os, const Course& c);
};

#endif