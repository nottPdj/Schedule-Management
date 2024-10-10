#include "Student.h"

/**
 * @brief Constructor of Student
 * @param studentCode
 * @param studentName
 */
Student::Student(std::string studentCode, std::string studentName): studentCode(studentCode), name(studentName){}

/**
 * @brief Gets the name of Student
 * @return name
 */
std::string Student::getName() const{ return name;}

/**
 * @brief Gets the code of Student
 * @return studentCode
 */
std::string Student::getStudentCode() const{return studentCode;}

/**
 * @brief Gets the Schedule of Student
 * @return schedule
 */
Schedule Student::getSchedule() const {
    return schedule;
}

/**
 * @brief Gets the number of the UC's the Student is registered
 * @return n number of UC's
 * @details Time Complexity O(n log m) n= number of lectures  m= number of strings in checkUC
 */
int Student::getNumberUcs() {
    int n=0;
    std::set<std::string>checkUC;
    for(const Lecture& lecture:schedule.getLectures()){     // If is registered in class -> is also in UC
        if(checkUC.find(lecture.getUC())==checkUC.end()){
            n++;
            checkUC.insert(lecture.getUC());
        }
    }
    return n;
}

/**
 * @brief Compares Student's through its code
 * @param student
 */
bool Student::operator<(const Student &student) const {
    return studentCode < student.studentCode;
}

/**
 * @brief Checks if its the same Student based on its code
 * @param other
 */
bool Student::operator==(const Student &other) const {
    return studentCode == other.studentCode;
}

/**
 * @brief Adds Lecture to the Student Schedule
 * @param newLecture
 * @details Time Complexity O(log n) n = number of Lectures in schedule
 */
void Student::addLecture(Lecture newLecture) {
    schedule.addLecture(newLecture);
}

/**
 * @brief Removes Lecture from Student Schedule
 * @param lecture
 * @details Time Complexity O(log n) n = number of Lectures in schedule
 */
void Student::removeLecture(const Lecture &lecture) {
    schedule.removeLecture(lecture);
}

