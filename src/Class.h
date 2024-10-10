#ifndef PROJETO_CLASS_H
#define PROJETO_CLASS_H


#include "Student.h"

/**
 * @brief Class is the class that contains all the information about a Class
 */

class Class {

private:
    std::string classCode;
    std::string uc;
    std::string year;
    Schedule schedule;
    std::set<Student*, cmp> students;

public:

    Class(std::string classCode, std::string uc);
    std::string getClassCode() const;
    std::string getUC() const;
    std::string getYear() const;
    int getOccupation() const;
    void addStudent(Student* student);
    void addLecture(std::string classCode,std::string ucCode,std::string weekday,float startHour,float duration,std::string type);
    void removeStudent(Student* student);
    std::set<Student*, cmp> getStudents() const;
    Schedule getSchedule() const;
    bool operator<(const Class& class_) const;

};

#endif //PROJETO_CLASS_H

