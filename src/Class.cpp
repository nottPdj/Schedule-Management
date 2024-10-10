#include "Class.h"

/**
 * @brief Constructor of the Class
 * @param classCode
 * @param uc
 */
Class::Class(std::string classCode, std::string uc):classCode(classCode),uc(uc) {
    this->year=classCode.at(0);
}

/**
 * @brief Gets the code of the Class
 * @return classCode
 */
std::string Class::getClassCode() const {
    return classCode;
}

/**
 * @brief Gets the UC which the Class is registered
 * @return uc
 */
std::string Class::getUC() const {
    return uc;
}

/**
 * @brief Gets the year of the Class
 * @return year
 */
std::string Class::getYear() const {
    return year;
}

/**
 * @brief Adds Student to the Class
 * @param student
 * @note Also adds the Class Lecture to the Student Schedule
 * @details Time Complexity O(n log m) n = number of lectures of Class schedule, m =number of lectures of student schedule
 */
void Class::addStudent(Student* student) {
    students.insert(student);
    for (const Lecture &newLecture : schedule.getLectures()) {
        student->addLecture(newLecture);
    }
}

/**
 * @brief Adds a Lecture to the Class Schedule
 * @param classCode
 * @param ucCode
 * @param weekday
 * @param startHour
 * @param duration
 * @param type
 * @note Also adds the Lecture to the Schedule of all the Students of the Class
 * @details Time Complexity O(n log m) n= number of students of the Class, m= number of lectures of student schedule
 */
void Class::addLecture(std::string classCode,std::string ucCode,std::string weekday,float startHour,float duration,std::string type){
    Lecture newLecture(classCode,ucCode,weekday,startHour,duration,type);
    schedule.addLecture(newLecture);
    for (Student* student : students) {
       student->addLecture(newLecture);
    }
}

/**
 * @brief Removes Student from Class
 * @param student
 * @note Also removes the Lectures of the Class from the Student Schedule
 * @details Time Complexity O(n log m) n = number of lectures of Class schedule, m =number of lectures of student schedule
 */
void Class::removeStudent(Student* student) {
    students.erase(student);
    for (const Lecture &lecture : schedule.getLectures()) {
        student->removeLecture(lecture);
    }
}

/**
 * @brief Gets the Students registered in the Class
 * @return students
 */
std::set<Student*, cmp> Class::getStudents() const {
    return students;
}

/**
 * @brief Gets the Schedule of the Class
 * @return schedule
 */
Schedule Class::getSchedule()const {
    return schedule;
}

/**
 * @brief Gets the occupation of the Class
 */
int Class::getOccupation() const {
    return students.size();
}

/**
 * @brief Compares Classes based on the following: code of the Class, UC of the Class
 * @param class_
 */
bool Class::operator<(const Class &class_) const {
    if (classCode < class_.getClassCode())
        return true;
    else if (classCode == class_.getClassCode())
        return this->getUC() < class_.getUC();
    return false;
}

