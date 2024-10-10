#include "UC.h"

/**
 * @brief Constructor of the UC class
 * @param ucCode code of the UC that is being created
 */

UC::UC(std::string ucCode) : ucCode(ucCode) {}

/**
 * @brief Adds a Class to the UC
 * @param class_
 * @details Time Complexity O(log n) n = number of classesEnrolled
 */
void UC::addClass(Class class_) {
    classesEnrolled.insert(class_);
}

/**
 * @brief Adds a student to the UC, through adding him to a Class of the UC
 * @param student
 * @param classCode code of the Class which the student is being added
 * @details Time Complexity O(n) n = number of classesEnrolled
 */
void UC::addStudent(Student* student,std::string classCode) {
    for (Class class_ : classesEnrolled) {
        if (class_.getClassCode() == classCode) {
           classesEnrolled.erase(class_);
           class_.addStudent(student);
           classesEnrolled.insert(class_);
           return;
        }
    }
}

/**
 * @brief Get the students registered in the UC
 * @return studentsInUc
 * @details Time Complexity O(n*m) n= number of classes, m= number of students in each class
 */
std::set<Student*, cmp> UC::getStudents() const {
    std::set<Student*, cmp> studentsInUc;
    for (Class class_ : classesEnrolled) {
        for (Student* student : class_.getStudents()) {
            studentsInUc.insert(student);
        }
    }
    return studentsInUc;
}

/**
 * @brief Get the Classes registered in the UC
 * @return classesEnrolled
 */
std::set<Class> UC::getClasses() const {
    return classesEnrolled;
}

/**
 * @brief Compares UC's through its ucCode
 * @param uc
 */
bool UC::operator<(const UC &uc) const {
    return ucCode<uc.ucCode;
}

/**
 * @brief Get the ucCode of the UC
 * @return ucCode
 */
std::string UC::getUcCode() const {
    return ucCode;
}

/**
 * @brief Adds a lecture to a certain Class of the UC
 * @param classCode code of the class that the Lecture is going to be added
 * @param ucCode code of the UC which the Lecture is being added
 * @param type type of the Lecture
 * @param weekday
 * @param startHour
 * @param duration
 * @details Time Complexity O(n) n = size of classesEnrolled
 */
void UC::addLecture(std::string classCode, std::string ucCode, std::string type, std::string weekday, float startHour,float duration) {
  for(Class class_:classesEnrolled){
    if(class_.getClassCode()==classCode){
      classesEnrolled.erase(class_);
      class_.addLecture(classCode,ucCode,weekday,startHour,duration,type);
      classesEnrolled.insert(class_);
      return;
    }
  }
}

/**
 * @brief Gets the year of the UC
 */
std::string UC::getYear() const{
    return (*classesEnrolled.begin()).getYear();
}

/**
 * @brief Gets the Schedule of the UC
 * @return ucSchedule (sum of all the Schedules of the classesEnrolled)
 * @details Time Complexity O(n) n = size of classesEnrolled
 */
Schedule UC::getSchedule()const {
    Schedule ucSchedule;
    for (Class class_ : classesEnrolled) {
        ucSchedule += class_.getSchedule();
    }
    return ucSchedule;
}

/**
 * @brief Get the occupation of the UC
 * @return occupation (sum of the occupation of all classesEnrolled)
 * @details Time Complexity O(n) n = size of classesEnrolled
 */
int UC::getOccupation() const {
    int occupation = 0;
    for (const Class &class_ : classesEnrolled) {
        occupation += class_.getOccupation();
    }
    return occupation;
}

/**
 * @brief Removes a Class from the UC
 * @param class_ Class which is going to be removed
 * @details Time Complexity O(log n) n = size of classesEnrolled
 */
void UC::removeClass(Class class_) {
    classesEnrolled.erase(class_);
}

/**
 * @brief Removes a Student from the UC
 * @param student Student which is going to be removed
 * @details Time Complexity O(n log m) n = size of classesEnrolled, m= number of students of a class
 */
void UC::removeStudent(Student *student) {
    for (Class class_ : classesEnrolled) {
        auto studentIt = class_.getStudents().find(student);
        auto end = class_.getStudents().end();
        if (studentIt != end) {
            classesEnrolled.erase(class_);
            class_.removeStudent(student);
            classesEnrolled.insert(class_);
            return;
        }
    }
}

