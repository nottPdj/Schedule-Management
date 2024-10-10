#ifndef PROJETO_COURSE_H
#define PROJETO_COURSE_H

#include <vector>
#include "Student.h"
#include "Request.h"
#include "UC.h"
#include "JoinRequest.h"
#include "LeaveRequest.h"
#include "SwitchClassRequest.h"
#include "SwitchUcRequest.h"

/**
 * @brief Course is the class that contains all the information within a course
 */

class Course {
private:
    std::string name;
    std::set<UC> UCs;
    std::set<Student*, cmp> students;
    static const int CLASS_CAP = 26;

public:
    Course();
    ~Course();
    std::string getName() const;
    void addUC(std::string ucCode);
    void addClass(std::string classCode, std::string ucCode);
    void addStudent(std::string studentCode, std::string studentName, std::string ucCode, std::string classCode);
    void addLecture(std::string classCode, std::string ucCode, std::string type, std::string weekday, float startHour, float duration);
    Schedule getStudentSchedule(std::string studentCode) const;
    Schedule getClassSchedule( std::string classCode) const;
    Schedule getUcSchedule( std::string ucCode) const;
    std::vector<Student*> getStudentsInClass(std::string classCode, std::string ucCode) const;
    std::vector<Student*> getStudentsInUC(std::string ucCode) const;
    std::vector<Student*> getStudentsInYear(std::string year) const;
    std::vector<Student*> getStudentsInCourse() const;
    std::vector<Student*> getStudentsInAtLeastUCs(int n) const;
    std::vector<UC> getUCsInYear(std::string year) const;
    std::vector<Class> getClassesInUC(std::string ucCode) const;
    std::set<Class> getStudentClasses(std::string studentCode) const;
    bool assessRequest(Request *request);

    std::vector<Class> getClasses() const;
    std::vector<UC> getUCs() const;
    std::vector<std::pair<std::string, int>> getYearOccupation() const;
    int getOccupation() const;
    Student* findStudentByCode(std::string studentCode) const;
    UC findUcByCode(std::string ucCode) const;
    Class findClassByCode(std::string classCode, std::string ucCode) const;

    Class chooseClassFromUC(Student *student, UC &uc, Request *request, bool &found);
    bool checkNumberUCs(Student *student, Request *request);
    bool checkUcBalance(const Student *student, const UC &uc, const Class &currentClass, const Class &nextClass, Request *request);
    bool canChooseClass(const Student *student, const UC &uc, const Class &currentClass, const Class &nextClass, Request *request);
    bool checkClassCap(const Class class_, Request *request);
    bool checkScheduleConflicts(const Student *student, const Class class_, Request *request);
};


#endif //PROJETO_COURSE_H
