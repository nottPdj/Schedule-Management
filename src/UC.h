#ifndef PROJETO_UC_H
#define PROJETO_UC_H

#include "Student.h"
#include "Class.h"

/**
 * @brief UC is the class that contains all the information within a UC
 */

class UC {
private:
    std::string ucCode;
    std::set<Class> classesEnrolled;

public:
    UC(std::string ucCode);
    std::string getUcCode() const;
    void addClass(Class class_);
    void addStudent(Student* student, std::string classCode);
    void addLecture(std::string classCode, std::string ucCode, std::string type, std::string weekday, float startHour, float duration);
    std::set<Student*, cmp> getStudents() const;
    std::set<Class> getClasses() const;
    std::string getYear() const;
    Schedule getSchedule() const;
    int getOccupation() const;
    void removeClass(Class class_);
    void removeStudent(Student *student);
    bool operator<(const UC& uc) const;
};


#endif //PROJETO_UC_H
