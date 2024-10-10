#ifndef PROJETO_TERMINAL_H
#define PROJETO_TERMINAL_H


#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "Course.h"



/**
 * @brief Terminal auxiliar struct storing the sorting options of a table.
 */
struct sortingOptions {
    /**
     * Column, currently displaying, to order by
     */
    int orderBy = -1;
    bool ascending = true;
};

/**
 * @brief Terminal auxiliar struct storing the filtering options for occupation table.
 */
struct occupationOptions {
    // Filtering options
    // Column appears
    bool years=true;
    bool UCs=true;
    bool classes=true;
    // Restrict to a specific
    std::string year = "all";
    std::string ucCode = "all";
    std::string classCode = "all";

    /**
     * Checks if there is any column to display based on the filtering options
     * @return true if none of the columns needs to be displayed
     */
    bool displayNothing() const {
        return !(years || UCs || classes);
    }

    /**
     * Gets what is the real column to order by is.
     * @param orderBy Column number, of the column currently being displayed, to order by
     * @return returns true if it was a valid column
     */
    bool getRealOrderBy(int &orderBy) const {
        if (orderBy == -1) {
            // Default
            return true;
        }
        bool columns[3] = {years, UCs, classes};
        orderBy++;
        int columnsDisplayed = 0;
        for (int i = 0; i < 3; i++) {
            if (columns[i])
                columnsDisplayed++;
            if (columnsDisplayed == orderBy) {
                orderBy = i;
                return true;
            }
        }
        // Order by occupation
        if (orderBy == columnsDisplayed + 1) {
            orderBy = 3;
            return true;
        }
        return false;
    }

};


/**
 * @brief Terminal is used to create an interface between the user and the program.
 * Uses the console to output and to receive inputs. There are some functionalities available only for Ubuntu.
 * */
class Terminal {

private:
    /**
     * @brief Course that is being managed
     */
    Course course;
    /**
     * @brief Stack containing all the requests that were accepted, stored by chronological order
     */
    std::stack<Request*> requestRecord;
    /**
     * @brief Queue with the requests made before the Terminal started running
     */
    std::queue<Request*> pastRequests;
    const static int MENU_WIDTH = 60;
    const static int SCHEDULE_COL_WIDTH = 20;
    const static int SCHEDULE_LINE_HEIGHT = 1;
    const static int STUDENT_CODE_COL_WIDTH = 11;
    const static int STUDENT_NAME_COL_WIDTH = 15;
    const static int OVERLAPPED_COL_WIDTH = 15;


public:
    Terminal(const Course &course);
    ~Terminal();
    void run();

private:
    void redoPastRequests();

    // Wait for inputs
    void waitMenu();
    char getInput();
    void getSortingOptions(sortingOptions &sortOptions);
    void getFilteringOptions(occupationOptions &filterOptions);

    // Print menus
    void printMainMenu();
    void studentMenu();
    void OccupationMenu();
    void endDisplayMenu();
    void printBackToMenu();
    void printSortingOptions();
    void printFilteringOptions();
    void printUndo();
    void printUndoMenu();
    void printExit();

    // Assess requests
    void assessRequest(Request *request);

    void undoLastRequest();

    // Print schedules
    void printUcSchedule(std::string& ucCode);
    void printClassSchedule(std::string& classCode);
    void printStudentSchedule(std::string& studentCode);

    void printSchedule(const Schedule& schedule);
    void printOverlappedLectures(const std::set<Lecture>& lectures);

    // Auxiliar formatting functions
    std::string formatUcAndType(const std::string& ucCode, const std::string& type);
    std::string formatHour(float hour);
    std::string formatHourRange(float startHour, float endHour);
    std::string formatWeekday(int weekday);
    std::string fill(char c, int width);
    std::string center(const std::string &str, char sep, int width);
    int getMiddleOfLectureBox(float duration);


    // Print students
    void printStudentsInClass(std::string classCode, std::string ucCode);
    void printStudentsInUC(std::string ucCode);
    void printStudentsInYear(std::string year);
    void printStudentsInCourse();
    void printStudentsInAtLeastUCs(int n);

    void printStudents(std::vector<Student*> &students, std::string message, sortingOptions &sortOptions);

    // Print UCs
    void printUCsInYear(std::string year);

    // Print classes
    void printClassesInUC(std::string ucCode);

    void printStudentClasses(std::string studentCode);

    void printOccupationHeaders(const occupationOptions &filterOptions);
    void printOccupationHeader(int line, std::string header, int width);

    void printClassOccupation(sortingOptions &sortOptions, occupationOptions &filterOptions);
    void printClassOccupationLine(const Class &class_, const occupationOptions &filterOptions);
    void printUcOccupation(sortingOptions &sortOptions, occupationOptions &filterOptions);
    void printUcOccupationLine(const UC &uc, const occupationOptions &filterOptions);
    void printYearOccupation(sortingOptions &sortOptions, occupationOptions &filterOptions);
    void printYearOccupationLine(const std::pair<std::string, int> &yearOcc, const occupationOptions &filterOptions);

    void printCourseOccupation(sortingOptions &sortOptions , occupationOptions &filterOptions);

    // Auxiliar sorting functions
    // Sort students
    bool static byStudentName(Student *student1, Student *student2);
    bool static byStudentCode(Student *student1, Student *student2);
    // Sort lectures
    bool static byWeekday(Lecture lecture1, Lecture lecture2);


    bool static classesByYear(Class class1, Class class2);
    bool static classesByUcCode(Class class1, Class class2);
    bool static classesByOccupation(Class class1, Class class2);

    bool static ucsByYear(UC uc1, UC uc2);
    bool static ucsByOccupation(UC uc1, UC uc2);

    bool static yearsByYear(std::pair<std::string, int> pair1, std::pair<std::string, int> pair2);
    bool static yearsByOccupation(std::pair<std::string, int> pair1, std::pair<std::string, int> pair2);
};


#endif //PROJETO_TERMINAL_H
