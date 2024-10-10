#ifndef PROJETO_STUDENT_H
#define PROJETO_STUDENT_H

#include "Schedule.h"

/**
 * @brief Student is the class that contains all the information about a student
 */

class Student {
private:
    std::string name;
    std::string studentCode;
    Schedule schedule;


public:
    Student(std::string studentCode, std::string studentName);
    std::string getName() const;
    std::string getStudentCode() const;
    Schedule getSchedule() const;
    int getNumberUcs();
    void addLecture(Lecture newLecture);
    void removeLecture(const Lecture &lecture);
    bool operator<(const Student& student) const;
    bool operator==(const Student& other) const;  // Able to use find method, student is equal if it has same studentcode
};

/**
 * @brief Compares two Students pointers by its code
 */
struct cmp {
    bool operator()(const Student *s1, const Student *s2) const {
        return s1->getStudentCode() < s2->getStudentCode();
    }
};

#endif //PROJETO_STUDENT_H
