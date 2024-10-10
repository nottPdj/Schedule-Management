#include <iostream>
#include <algorithm>
#include "Course.h"
#include <sstream>

/**
 * @brief Constructor of Course
 */
Course::Course() { name = "LEIC";}

Course::~Course(){}

/**
 * @brief Get Course name
 * @return name
 */
std::string Course::getName() const { return name;}

/**
 * @brief Adds UC to the Course
 * @param ucCode
 * @details Time Complexity O(log n) n = number of UC's
 */
void Course::addUC(std::string ucCode) {
    UC newUC(ucCode);
    UCs.insert(newUC);
}

/**
 * @brief Adds a Class to the Course
 * @param classCode
 * @param ucCode
 * @details Time Complexity O(n) n= number of UC's
 */
void Course::addClass(std::string classCode, std::string ucCode) {
    for (UC uc : UCs) {
        if (uc.getUcCode() == ucCode) {
            UCs.erase(uc);
            uc.addClass(Class(classCode, ucCode));
            UCs.insert(uc);
            return;
        }
    }
}

/**
 * @brief Adds Student to the Course
 * @param studentCode
 * @param studentName
 * @param ucCode
 * @param classCode
 * @details Time Complexity O(n) = number of UC's
 */
void Course::addStudent(std::string studentCode, std::string studentName, std::string ucCode, std::string classCode) {
    Student* newStudent = new Student(studentCode, studentName);
    auto student = students.find(newStudent);
    // Not in course
    if (student == students.end()) {
        students.insert(newStudent);
        for (UC uc : UCs) {
            if (uc.getUcCode() == ucCode) {
                UCs.erase(uc);
                uc.addStudent(newStudent, classCode);
                UCs.insert(uc);
                return;
            }
        }
    }
    // In course
    else {
        delete newStudent;
        for (UC uc: UCs) {
            if (uc.getUcCode() == ucCode) {
                UCs.erase(uc);
                uc.addStudent(*student, classCode);
                UCs.insert(uc);
                return;
            }
        }
    }
}

/**
 * @brief Adds Lecture to a UC of the Course
 * @param classCode
 * @param ucCode
 * @param type
 * @param weekday
 * @param startHour
 * @param duration
 * @details Time Complexity O(n) n = number of UC's
 */
void Course::addLecture(std::string classCode, std::string ucCode, std::string type, std::string weekday, float startHour, float duration) {
    for (UC uc : UCs) {
        if (uc.getUcCode() == ucCode) {
            UCs.erase(uc);
            uc.addLecture(classCode, ucCode, type, weekday, startHour, duration);
            UCs.insert(uc);
            return;
        }
    }
}

/**
 * @brief Gets the Schedule of a Student from the Course
 * @param studentCode
 * @details Time Complexity O(n) n= number of students
 */
Schedule Course::getStudentSchedule(std::string studentCode) const {
    for (Student* student : students){
        if (student->getStudentCode() == studentCode)
            return student->getSchedule();
    }
}

/**
 * @brief Gets the Class Schedule from a Class of the Course
 * @param classCode
 * @return classSchedule
 * @details Time Complexity O(n*m) n= number of UC', m= number of classes per UC
 */
Schedule Course::getClassSchedule(std::string classCode) const {
    Schedule classSchedule;
    for (const UC &uc : UCs) {
        for (const Class &class_ : uc.getClasses()) {
            if (class_.getClassCode() == classCode)
                classSchedule += class_.getSchedule();
        }
    }
    return classSchedule;
}

/**
 * @brief Gets the Schedule of a certain UC of the Course
 * @param ucCode
 * @details Time Complexity O(n) n = number of UC's
 */
Schedule Course::getUcSchedule(std::string ucCode) const {
    for (const UC &uc : UCs) {
        if (uc.getUcCode() == ucCode)
            return uc.getSchedule();
    }
}

/**
 * @brief Gets all the Students registered in the Course
 * @return studentsInCourse
 * @details Time Complexity O(n) n= number of students
 */
std::vector<Student*> Course::getStudentsInCourse() const {
    std::vector<Student*> studentsInCourse;
    for (Student* student : students) {
        studentsInCourse.push_back(student);
    }
    return studentsInCourse;
}

/**
 * @brief Gets the Students from a certain Class in the Course
 * @param classCode code of the Class
 * @param ucCode code of the UC of the Class
 * @return studentsVector
 * @details Time Complexity O(n+ m +k log k) n= number of UC's m= number of classes k= number of students
 * @note Time Complexity depends on the case
 */
std::vector<Student*> Course::getStudentsInClass(std::string classCode,std::string ucCode) const {
    std::set<Student*, cmp> studentsInClass;
    for (const UC &uc : UCs) {
        if (uc.getUcCode() == ucCode) {
            for (const Class &class_ : uc.getClasses()) {
                if (class_.getClassCode() == classCode) {
                    for (Student* student : class_.getStudents())
                        studentsInClass.insert(student);
                }
            }
        }
    }
    std::vector<Student*> studentsVector;
    for (Student *student : studentsInClass) {
        studentsVector.push_back(student);
    }
    return studentsVector;
}

/**
 * @brief Gets the Students registered in a certain UC
 * @param ucCode
 * @return studentsVector
 * @details Time Complexity O(m log m) m= number of students
 */
std::vector<Student*> Course::getStudentsInUC(std::string ucCode) const {
    std::set<Student*, cmp> studentsInUC;
    for (const UC &uc : UCs) {
        if (uc.getUcCode() == ucCode) {
            for (Student* student : uc.getStudents())
                studentsInUC.insert(student);
        }
    }
    std::vector<Student*> studentsVector;
    for (Student *student : studentsInUC) {
        studentsVector.push_back(student);
    }
    return studentsVector;
}

/**
 * @brief Gets the Students registered in at least one Class from a certain Year
 * @param year
 * @return studentsVector
 * @details Time Complexity O(n * (m + k log k)) n = number of UC's m= number of classes k = number of students
 * @note Time Complexity depends on the case
 */
std::vector<Student*> Course::getStudentsInYear(std::string year) const {
    std::set<Student*> studentsInYear;
    for (const UC &uc : UCs) {
        for (const Class &class_ : uc.getClasses()) {
            if (class_.getYear() == year) {
                for (Student* student : class_.getStudents()) {
                    studentsInYear.insert(student);
                }
            }
        }
    }
    std::vector<Student*> studentsVector;
    for (Student *student : studentsInYear) {
        studentsVector.push_back(student);
    }
    return studentsVector;
}

/**
 * @brief Gets the Students registered in at least n UC's
 * @param n number of UC's
 * @return studentsInAtLeastUcs
 * @details Time Complexity O(n * m log k) n = number of students m= number of lectures  k= number of strings in checkUC
 */
std::vector<Student*> Course::getStudentsInAtLeastUCs(int n) const {
    std::vector<Student*> studentsInAtLeastUcs;
    for (Student* student : getStudentsInCourse()) {
        if (student->getNumberUcs() >= n) {
            studentsInAtLeastUcs.push_back(student);
        }
    }
    return studentsInAtLeastUcs;
}

/**
 * @brief Gets the UC's from a certain year
 * @param year
 * @return UCsInYear
 * @details Time Complexity O(n) n= number of UC's
 */
std::vector<UC> Course::getUCsInYear(std::string year) const {
    std::vector<UC> UCsInYear;
    for (const UC &uc : UCs) {
        if (uc.getYear() == year)
            UCsInYear.push_back(uc);
    }
    return UCsInYear;
}

/**
 * @brief Gets the Classes of a certain UC
 * @param ucCode
 * @return classesInUc
 * @details Time Complexity O(n + m) n= number of UC's m= number of Classes
 * @note Time Complexity depends on the case
 */
std::vector<Class> Course::getClassesInUC(std::string ucCode) const {
    std::vector<Class> classesInUC;
    for (const UC &uc : UCs) {
        if (uc.getUcCode() == ucCode) {
            for (const Class &class_ : uc.getClasses()) {
                classesInUC.push_back(class_);
            }
            return classesInUC;
        }
    }
}

/**
 * @brief Gets the Classes of the Course
 * @return classes
 * @note The Classes of a UC from Course, are also Classes of the Course
 * @details Time Complexity O(n * m) n= number of UC's m= number of Classes
 */
std::vector<Class> Course::getClasses() const {
    std::vector<Class> classes;
    for (const UC &uc : UCs) {
        for (const Class &class_: uc.getClasses()) {
            classes.push_back(class_);
        }
    }
    return classes;
}

/**
 * @brief Gets the UC's of the Course
 * @return ucs
 * @details Time Complexity O(n) n= number of UC's
 */
std::vector<UC> Course::getUCs() const {
    std::vector<UC> ucs;
    for (const UC &uc : UCs) {
        ucs.push_back(uc);
    }
    return ucs;
}

/**
 * @brief Gets the Classes of a certain Student
 * @param studentCode
 * @return classes
 * @details Time Complexity O(n *(m+k)) n= number of lectures m = number of UC's k= number of Classes on a UC
 */
std::set<Class> Course::getStudentClasses(std::string studentCode) const {
    Student *student = findStudentByCode(studentCode);
    std::set<Class> classes;
    for (Lecture lecture : student->getSchedule().getLectures()) {
        classes.insert(findClassByCode(lecture.getClass(), lecture.getUC()));
    }
    return classes;
}

/**
 * @brief Gets the occupation of all years of the Course
 * @return yearOccupation
 * @details Time Complexity O(n * m) n= number of UC's  m= years
 */
std::vector<std::pair<std::string, int>> Course::getYearOccupation() const {
    std::vector<std::pair<std::string, int>> yearOccupation;
    for (const UC &uc : UCs) {
        bool found = false;
        for (auto &pair: yearOccupation) {
            if (pair.first == uc.getYear()) {
                found = true;
                break;
            }
        }
        if (!found)
            yearOccupation.push_back({uc.getYear(), getStudentsInYear(uc.getYear()).size()});
    }
    return yearOccupation;
}

/**
 * @brief Gets Course occupation
 */
int Course::getOccupation() const {
    return students.size();
}

/**
 * @brief Assesses a Request, if it doesn't violates any rule,the Request is done
 * @param request
 * @details Time Complexity O(n log n + m *k) n= number of classes (checkUcBalance), m= number of not theoric lectures of Student k= number of lectures of Class (checkScheduleConflicts)
 */
bool Course::assessRequest(Request *request) {
    Student *student = findStudentByCode(request->getStudentCode()); //log n

    if (JoinRequest* joinReq = dynamic_cast<JoinRequest*>(request)) {
        UC uc = findUcByCode(joinReq->getUcCode()); //n
        if (checkNumberUCs(student, request)) {
            bool found;
            Class class_ = chooseClassFromUC(student, uc, request, found);
            if (found) {
                UCs.erase(uc);
                uc.removeClass(class_);
                class_.addStudent(student);
                uc.addClass(class_);
                UCs.insert(uc);
                return true;
            }
        }
    }
    else if (LeaveRequest* leaveReq = dynamic_cast<LeaveRequest*>(request)) {
        UC uc = findUcByCode(leaveReq->getUcCode());
        UCs.erase(uc);
        uc.removeStudent(student);
        UCs.insert(uc);
        return true;
    }
    else if (SwitchUcRequest* switchUcReq = dynamic_cast<SwitchUcRequest*>(request)) {
        UC currentUC = findUcByCode(switchUcReq->getUcCodeCurrent());
        UC nextUC = findUcByCode(switchUcReq->getUcCodeNext());
        bool found;
        for (const Lecture &lecture : student->getSchedule().getLectures()) {
            if (lecture.getUC() == currentUC.getUcCode())
                student->removeLecture(lecture);
        }
        Class class_ = chooseClassFromUC(student, nextUC, request, found);
        if (found) {
            // Remove from current UC
            UCs.erase(currentUC);
            currentUC.removeStudent(student);
            UCs.insert(currentUC);
            // Add to a class in the next UC
            UCs.erase(nextUC);
            nextUC.removeClass(class_);
            class_.addStudent(student);
            nextUC.addClass(class_);
            UCs.insert(nextUC);
            return true;
        }
        for (const Lecture &lecture : student->getSchedule().getLectures()) {
            if (lecture.getUC() == currentUC.getUcCode())
                student->addLecture(lecture);
        }
    }
    else if (SwitchClassRequest* switchClassReq = dynamic_cast<SwitchClassRequest*>(request)) {
        Class currentClass = findClassByCode(switchClassReq->getClassCodeCurrent(), switchClassReq->getUcCode());
        Class nextClass = findClassByCode(switchClassReq->getClassCodeNext(), switchClassReq->getUcCode());
        UC uc = findUcByCode(switchClassReq->getUcCode());
        for (const Lecture &lecture : currentClass.getSchedule().getLectures()) {
            student->removeLecture(lecture);
        }
        if (canChooseClass(student, uc, currentClass, nextClass, request)) {
            // Remove student from current class
            UCs.erase(uc);
            uc.removeClass(currentClass);
            currentClass.removeStudent(student);
            uc.addClass(currentClass);
            UCs.insert(uc);
            // Add student to next Class
            UCs.erase(uc);
            uc.removeClass(nextClass);
            nextClass.addStudent(student);
            uc.addClass(nextClass);
            UCs.insert(uc);
            return true;
        }
        for (const Lecture &lecture : currentClass.getSchedule().getLectures()) {
            student->addLecture(lecture);
        }
    }
    return false;
}

/**
 * @brief Gets a Student of the Course by its code
 * @param studentCode
 * @return currentStudent
 * @note Finding Student using BinarySearch
 * @details Time Complexity O(log n) n= number of students
 */
Student* Course::findStudentByCode(std::string studentCode) const {
    //BINARY SEARCH
    auto left = students.begin();
    auto right =students.end();

    while (left != right) {
        auto mid=left;
        std::advance(mid,std::distance(left,right)/2);
        Student* currentStudent = *mid;

        if (currentStudent->getStudentCode() == studentCode) {
            return currentStudent;
        } else if (currentStudent->getStudentCode() < studentCode) {
            left = mid++;
        } else {
            right = mid--;
        }
    }
    return *left;
}

/**
 * @brief Gets a UC of the Course using its code
 * @param ucCode
 * @return uc
 * @details Time Complexity O(n) n= number of UC's
 */
UC Course::findUcByCode(std::string ucCode) const {
    for(UC uc : UCs){
        if (uc.getUcCode() == ucCode)
            return uc;
    }
}

/**
 * @brief Gets a Class of the Course using its code
 * @param classCode
 * @param ucCode
 * @return class_
 * @details Time Complexity O(n + m) n = number of UC's m= number of Classes
 */
Class Course::findClassByCode(std::string classCode, std::string ucCode) const {
    for(UC uc : UCs){
        if (uc.getUcCode() == ucCode) {
            for (Class class_: uc.getClasses()) {
                if (class_.getClassCode() == classCode) return class_;
            }
        }
    }
}

/**
 * @brief Chooses the best Class for a Student, following a Request
 * @param student Student who requested
 * @param uc UC to join/switch
 * @param request Request
 * @param found check if Class was found for the Student
 * @details Time Complexity O(n log n + m *k) n= number of classes (sort), n= number of not theoric lectures of Student m= number of lectures of Class (CheckScheduleConflicts)
 */
Class Course::chooseClassFromUC(Student *student, UC &uc, Request *request, bool &found) {
    std::set<Class> classesSet = uc.getClasses();
    std::vector<Class> classes;
    for (Class class_ : classesSet) {
        classes.push_back(class_);
    }
    std::sort(classes.begin(), classes.end(), [](Class class1, Class class2) {return ( class1.getOccupation() < class2.getOccupation()); });
    for (const Class &class_ : classes) {
        if (checkScheduleConflicts(student, class_, request) && checkClassCap(class_, request))
            found = true;
        return class_;
    }
    found = false;
    return *uc.getClasses().begin();
}

/**
 * @brief Checks if the Student is not registered in more than 7 UC's
 * @param student
 * @param request
 * @details Time Complexity O(n log m) n= number of lectures  m= number of strings in checkUC (getNumberUcs)
 */
bool Course::checkNumberUCs(Student *student, Request *request){
    if(student->getNumberUcs()<7)
        return true;
    else {
        request->setMessage("Student is already registered in maximum number of UC's (7).\n");
        return false;
    }
}

/**
 * @brief Checks if the Student can choose a certain Class
 * @param student
 * @param uc
 * @param currentClass
 * @param nextClass
 * @param request
 * @details Time Complexity O(n log n + m *k) n= number of classes (checkUcBalance), m= number of not theoric lectures of Student k= number of lectures of Class (checkScheduleConflicts)
 */
bool Course::canChooseClass(const Student *student, const UC &uc, const Class &currentClass, const Class &nextClass, Request *request) {
    if (checkScheduleConflicts(student, nextClass, request) && checkClassCap(nextClass, request) && checkUcBalance(student,uc,currentClass, nextClass, request)) {
        return true;
    }
    return false;
}

/**
 * @brief Checks the balance of the Classes of a Student
 * @param student
 * @param uc
 * @param currentClass
 * @param nextClass
 * @param request
 * @details Time Complexity O(n log n) n= number of classes (vector)
 */
bool Course::checkUcBalance(const Student *student, const UC &uc, const Class &currentClass, const Class &nextClass, Request *request) {
    std::set<Class> classesSet = uc.getClasses();
    std::vector<std::pair<Class, int>> classes;
    for (Class class_ : classesSet) {
        if (class_.getUC() ==nextClass.getUC())
            classes.push_back({class_, class_.getOccupation()+1});

        else if(class_.getUC() ==currentClass.getUC())
            classes.push_back({class_, class_.getOccupation()-1});

        else
            classes.push_back({class_, class_.getOccupation()});
    }
    std::sort(classes.begin(), classes.end(), [] (std::pair<Class, int> class1, std::pair<Class, int> class2) { return (class1.second < class2.second); });
    if ((classes[classes.size()-1].second - classes[0].second)<=4)
        return true;
    std::ostringstream oss;
    oss << "Can't switch to class " << nextClass.getClassCode() << " because it disturbs the class occupation balance.\n";
    request->setMessage(oss.str());
    return false;
}

/**
 * @brief Check if a Student can be added on a Class based on its capacity
 * @param class_
 * @param request
 */
bool Course::checkClassCap(const Class class_, Request *request){
    if (class_.getStudents().size()<CLASS_CAP)
        return true;
    std::ostringstream oss;
    oss << "Can't join class " << class_.getClassCode() << " because it's full.\n";
    request->setMessage(oss.str());
    return false;
}

/**
 * @brief Checks if the exist Schedule conflicts between the Student and Class Schedule
 * @param student
 * @param class_
 * @param request
 * @details Time Complexity O(n*m) n= number of not theoric lectures of Student m= number of lectures of Class
 */
bool Course::checkScheduleConflicts(const Student *student, const Class class_, Request *request){
    for(Lecture lecture:student->getSchedule().getLectures()){
        if(lecture.getType()!="T"){
            for(Lecture classLecture:class_.getSchedule().getLectures()){
                if(classLecture.getType()!="T" && lecture.overlaps(classLecture)){
                    std::ostringstream oss;
                    oss << "Can't join class " << class_.getClassCode() << " since this class's schedule overlaps with the student's schedule.\n";
                    request->setMessage(oss.str());
                    return false;
                }
            }
        }
    }
    return true;
}
