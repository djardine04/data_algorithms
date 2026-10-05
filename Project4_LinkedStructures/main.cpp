#include "slist.h"
#include "course.h"
#include <iostream>

double calculate_gpa(const SList<Course>& courseList) {
    double sumGrades = 0.0;
    double credits = 0.0;

    for (const Course& c : courseList) {
        sumGrades += c.grade() * c.credit_hr();
        credits += c.credit_hr();
    }
    if (credits == 0.0) return 0.0;
    return sumGrades / credits;
}

bool is_sorted(const SList<Course>& lyst) {
    for (int i = 0; i < lyst.size() - 1; i++) {
        if (lyst[i] > lyst[i + 1])
            return false;
    }
    return true;
}

int main() {
    //validate against ints...
    SList<int> ints;
    ints.insert(5);
    ints.insert(2);
    ints.insert(9);
    ints.insert(2);

    std::cout << "List contents (should be sorted): ";
    for (int x : ints) std::cout << x << " ";
    std::cout << "\nsize=" << ints.size() << "\n";

    int idx = ints.find(9);
    if (idx != -1) {
        std::cout << "find(9) -> index " << idx
                  << ", value = " << ints[idx] << "\n";
    } else {
        std::cout << "9 not found\n";
    }

    ints.remove(2);
    std::cout << "After remove(2): ";
    for (int x : ints) std::cout << x << " ";
    std::cout << "\n";

  
    //validate against Course objects...
    // std::cout << "\n=== Demo: SList<Course> ===\n";
    // SList<Course> courses;
    // courses.insert(Course(2420, "DSA", 4.0, 3.7));
    // courses.insert(Course(1410, "OOP", 4.0, 4.0));
    // courses.insert(Course(2300, "CompOrg", 3.0, 3.3));

    // std::cout << "Courses (sorted by course number):\n";
    // for (const Course& c : courses) std::cout << c << "\n";

    // std::cout << "GPA = " << calculate_gpa(courses) << "\n";

    // idx = courses.find(Course(2420, "", 0.0, 0.0));
    // if (idx != -1) {
    //     std::cout << "CS2420 found at index " << idx << "\n";
    //     std::cout << courses[idx] << "\n";
    // } else {
    //     std::cout << "CS2420 not found\n";
    // }

    // std::cout << "Remove CS2300...\n";
    // courses.remove(Course(2300, "ignored", 0.0, 0.0));
    // for (const Course& c : courses) std::cout << c << "\n";
    return 0;
}