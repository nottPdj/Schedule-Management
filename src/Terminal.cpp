#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <cmath>
#include <utility>
#include "Terminal.h"
#include "Auxiliar.h"

/**
 * @brief Constructor of the Terminal class. Stores the course in the private field so that it can communicate
 * with the course throughout the program.
 * @param course Course being managed by the Terminal
 */
Terminal::Terminal(const Course &course) {
    this->course = course;
}

/**
 * @brief Destructor of the Terminal class. Frees the memory associated with the requests.
 */
Terminal::~Terminal() {
    while (!requestRecord.empty()) {
        Request *request = requestRecord.top();
        requestRecord.pop();
        delete request;
    }
}

/**
 * @brief This method is called to start the interface. Loads the requests previously made, redoes them, starts the interface
 * and before returning saves the requests done.
 */
void Terminal::run(){
    Auxiliar::loadRequestRecord(pastRequests);
    redoPastRequests();
    system("clear");
    printMainMenu();
    system("clear");
    Auxiliar::saveRequestRecord(requestRecord);
    system("clear");
}


/**
 * @brief Redoes the past requests in chronological order.
 */
void Terminal::redoPastRequests() {
    while (!pastRequests.empty()) {
        course.assessRequest(pastRequests.front());
        requestRecord.push(pastRequests.front());
        pastRequests.pop();
    }
}

/**
 * @brief Prints the main menu.
 */
void Terminal::printMainMenu() {
    system("clear");
    std::cout << center("SCHEDULE LEIC", '*', MENU_WIDTH) << "\n\n"
    << center("CONSULTS", ' ', MENU_WIDTH) << "\n"
    << "\t0 - Consult the UC's of a year" << "\n"
    << "\t1 - Consult the classes of a UC" << "\n"
    << "\t2 - Consult the classes of a student" << "\n"
    << "\tConsult the students of:" << "\n"
        << "\t\t3 - a course" << "\n"
        << "\t\t4 - a year" << "\n"
        << "\t\t5 - a UC" << "\n"
        << "\t\t6 - a class" << "\n"
    << "\tConsult the schedule of:" << "\n"
        << "\t\t7 - a student" << "\n"
        << "\t\t8 - a class" << "\n"
        << "\t\t9 - a UC" << "\n"
    << "\t10 - Consult the number of students in at least " << "n" << " UC's" << "\n"
    << "\t11 - Consult course occupation" << "\n"
    << "\n" << center("REQUESTS", ' ', MENU_WIDTH) << "\n"
    << "\t12 - Request to join a UC" << "\n"
    << "\t13 - Request to leave a UC" << "\n"
    << "\t14 - Request a UC switch" << "\n"
    << "\t15 - Request a class switch" << "\n\n";

    if (!requestRecord.empty())
        printUndo();
    printExit();
    std::cout << "Press the number corresponding the action you want." << "\n";
    waitMenu();
}

/**
 * @brief Waits for the input and depending on it, calls the method responsible for accomplishing what was asked.
 */
void Terminal::waitMenu(){
    std::string choice;
    std::cin >> choice;             // Fetch the option chosen
    if (choice == "q")              // Quit
        return;
    if (choice == "u" && !requestRecord.empty()) {               // Undo last request
        printUndoMenu();
        return;
    }
    system("clear");
    switch (stoi(choice)) {
        // Consult the UC's of a year
        case 0: {
            std::cout << "Enter the year: ";
            std::string year;
            std::cin >> year;        // Fetch year
            printUCsInYear(year);
            break;
        }
        // Consult the classes of a UC
        case 1: {
            std::cout << "Enter the UC code: ";
            std::string ucCode;
            std::cin >> ucCode;        // Fetch UC code
            printClassesInUC(ucCode);
            break;
        }
        // Consult the classes of a student
        case 2: {
            std::cout << "Enter the student code: ";
            std::string studentCode;
            std::cin >> studentCode;        // Fetch student code
            printStudentClasses(studentCode);
            break;
        }
        // Consult the students of a course
        case 3: {
            printStudentsInCourse();
            break;
        }
        // Consult the students of a year
        case 4: {
            std::cout << "Enter the year: ";
            std::string year;
            std::cin >> year;        // Fetch year
            printStudentsInYear(year);
            break;
        }
        // Consult the students of a UC
        case 5: {
            std::cout << "Enter the UC code: ";
            std::string ucCode;
            std::cin >> ucCode;        // Fetch UC code
            printStudentsInUC(ucCode);
            break;
        }
        // Consult the students of a class
        case 6: {
            std::cout << "Enter the UC code: ";
            std::string ucCode;
            std::cin >> ucCode;        // Fetch class code
            std::cout << "\n" << "Enter the class code: ";
            std::string classCode;
            std::cin >> classCode;        // Fetch class code
            printStudentsInClass(classCode, ucCode);
            break;
        }
        // Consult the schedule of a student
        case 7: {
            std::cout << "Enter the student code: ";
            std::string studentCode;
            std::cin >> studentCode;        // Fetch student code
            printStudentSchedule(studentCode);
            break;
        }
        // Consult the schedule of a class
        case 8: {
            std::cout << "Enter the class code: ";
            std::string classCode;
            std::cin >> classCode;        // Fetch class code
            printClassSchedule(classCode);
            break;
        }
        // Consult the schedule of a UC
        case 9: {
            std::cout << "Enter the UC code: ";
            std::string ucCode;
            std::cin >> ucCode;        // Fetch UC code
            printUcSchedule(ucCode);
            break;
        }
        // Consult the number of students in at least n UC's
        case 10: {
            std::cout << "Enter the number of UC's: ";
            int n;
            std::cin >> n;      // Fetch number of UC's
            printStudentsInAtLeastUCs(n);
            break;
        }
        // Consult course occupation
        case 11: {
            sortingOptions sortOptions;
            occupationOptions filterOptions;
            printCourseOccupation(sortOptions, filterOptions);
            break;
        }
        // Request to join a UC
        case 12: {
            std::cout << "Enter the student code: ";
            std::string studentCode;
            std::cin >> studentCode;        // Fetch student code
            std::cout << "Enter the UC code: ";
            std::string ucCode;
            std::cin >> ucCode;        // Fetch UC code

            Request *request = new JoinRequest(studentCode, ucCode);
            assessRequest(request);
            break;
        }
        // Request to leave a UC
        case 13: {
            std::cout << "Enter the student code: ";
            std::string studentCode;
            std::cin >> studentCode;        // Fetch student code
            std::cout << "Enter the UC code: ";
            std::string ucCode;
            std::cin >> ucCode;        // Fetch UC code

            Request *request = new LeaveRequest(studentCode, ucCode);
            assessRequest(request);
            break;
        }
        // Request a UC switch
        case 14: {
            std::cout << "Enter the student code: ";
            std::string studentCode;
            std::cin >> studentCode;        // Fetch student code
            std::cout << "Enter the code of the UC you are currently registered: ";
            std::string ucCodeCurrent;
            std::cin >> ucCodeCurrent;        // Fetch current UC code
            std::cout << "Enter the code of the UC you want to switch to: ";
            std::string ucCodeNext;
            std::cin >> ucCodeNext;        // Fetch UC code to switch to

            Request *request = new SwitchUcRequest(studentCode, ucCodeCurrent, ucCodeNext);
            assessRequest(request);
            break;
        }
        // Request a class switch
        case 15: {
            std::cout << "Enter the student code: ";
            std::string studentCode;
            std::cin >> studentCode;        // Fetch student code
            std::cout << "Enter the UC code: ";
            std::string ucCode;
            std::cin >> ucCode;        // Fetch UC code
            std::cout << "Enter the code of the class you are currently registered: ";
            std::string classCodeCurrent;
            std::cin >> classCodeCurrent;        // Fetch current class code
            std::cout << "Enter the code of the class you want to switch to: ";
            std::string classCodeNext;
            std::cin >> classCodeNext;        // Fetch class code to switch to

            Request *request = new SwitchClassRequest(studentCode, ucCode, classCodeCurrent, classCodeNext);
            assessRequest(request);
            break;
        }
        default: {
            printMainMenu();
        }
    }
}

/**
 * @brief Sends the request to course so that it can be assessed.
 * @param request Request to be assessed
 */
void Terminal::assessRequest(Request *request) {
    system("clear");
    if (course.assessRequest(request)) {
        if (!request->isUndo())
            requestRecord.push(request);
        std::cout << "Your request was accepted.\n" << request->toStr();
    } else {
        std::cout << request->getMessage();
        delete request;
    }
    endDisplayMenu();
    getInput();
}

/**
 * @brief Undoes the last request, if possible.
 */
void Terminal::undoLastRequest() {
    Request *request = requestRecord.top();
    requestRecord.pop();
    if (JoinRequest* joinReq = dynamic_cast<JoinRequest*>(request)) {
        Request *undoRequest = new LeaveRequest(joinReq->getStudentCode(), joinReq->getUcCode());
        undoRequest->setUndo();
        assessRequest(undoRequest);
    }
    else if (LeaveRequest* leaveReq = dynamic_cast<LeaveRequest*>(request)) {
        Request *undoRequest = new JoinRequest(leaveReq->getStudentCode(), leaveReq->getUcCode());
        undoRequest->setUndo();
        assessRequest(undoRequest);
    }
    else if (SwitchUcRequest* switchUcReq = dynamic_cast<SwitchUcRequest*>(request)) {
        Request *undoRequest = new SwitchUcRequest(switchUcReq->getStudentCode(), switchUcReq->getUcCodeNext(), switchUcReq->getUcCodeCurrent());
        undoRequest->setUndo();
        assessRequest(undoRequest);
    }
    else if (SwitchClassRequest* switchClassReq = dynamic_cast<SwitchClassRequest*>(request)) {
        Request *undoRequest = new SwitchClassRequest(switchClassReq->getStudentCode(), switchClassReq->getUcCode(), switchClassReq->getClassCodeNext(), switchClassReq->getClassCodeCurrent());
        undoRequest->setUndo();
        assessRequest(undoRequest);
    }
    delete request;
}

void Terminal::printUndo() {
    std::cout << "Press 'u' to undo the most recent request.\n";
}

void Terminal::printUndoMenu() {
    system("clear");
    std::cout << "The most recent request is: " << requestRecord.top()->toStr() << ".\n\n";
    std::cout << "Are you sure you want to undo this request? (y/n)";
    char input;
    std::cin >> input;
    if (input == 'y') {
        undoLastRequest();
    } else {
        endDisplayMenu();
        getInput();
    }
}

/**
 * @brief Prints UCs in a year
 * @param year
 */
void Terminal::printUCsInYear(std::string year) {
    system("clear");
    std::cout << "These are the UC's in year " << year << "\n\n";

    std::vector<UC> UCs = course.getUCsInYear(year);
    int UCsPerLine = 0;
    int maxUCsPerLine = 6;
    for (auto UC = UCs.begin(); UC != UCs.end(); UC++) {
        std::cout << UC->getUcCode() << " ";
        UCsPerLine++;
        if (UCsPerLine == maxUCsPerLine) {
            UCsPerLine = 0;
            std::cout << "\n";
        }
    }
    endDisplayMenu();
    getInput();
}

/**
 * @brief Prints classes in a UC
 * @param ucCode
 */
void Terminal::printClassesInUC(std::string ucCode) {
    system("clear");
    std::cout << "These are the classes of UC " << ucCode << "\n\n";

    std::vector<Class> classes = course.getClassesInUC(ucCode);
    int classesPerLine = 0;
    int maxClassesPerLine = 6;
    for (auto class_ = classes.begin(); class_ != classes.end(); class_++) {
        std::cout << class_->getClassCode() << " ";
        classesPerLine++;
        if (classesPerLine == maxClassesPerLine) {
            classesPerLine = 0;
            std::cout << "\n";
        }
    }
    endDisplayMenu();
    getInput();
}

/**
 * @brief Prints the classes and respective UC's of a student.
 * @param studentCode
 */
void Terminal::printStudentClasses(std::string studentCode) {
    system("clear");
    std::cout << "These are the classes of student " << studentCode << "\n\n";

    std::cout << center("UC", ' ', OVERLAPPED_COL_WIDTH) << "|" << center("Class", ' ', OVERLAPPED_COL_WIDTH) << "\n";        // Column titles
    std::cout << fill('-', OVERLAPPED_COL_WIDTH) << "|" << fill('-', OVERLAPPED_COL_WIDTH) << "\n";           // Separators

    std::set<Class> classes = course.getStudentClasses(studentCode);
    std::vector<Class> sortedClasses;
    for (Class class_ : classes) {
        sortedClasses.push_back(class_);
    }
    std::sort(sortedClasses.begin(), sortedClasses.end(), classesByUcCode);
    for (const Class &class_ : sortedClasses) {
        std::cout << center(class_.getUC(), ' ', OVERLAPPED_COL_WIDTH) << "|" << center(class_.getClassCode(), ' ', OVERLAPPED_COL_WIDTH) << "\n";
    }
    endDisplayMenu();
    getInput();
}

/**
 * @brief Prints the schedule of a UC.
 * @param ucCode
 */
void Terminal::printUcSchedule(std::string& ucCode) {
    system("clear");
    std::cout << "This is the schedule of UC " << ucCode << "\n\n";

    Schedule schedule = course.getUcSchedule(ucCode);
    printSchedule(schedule);
}

/**
 * @brief Prints the schedule of a class.
 * @param classCode
 */
void Terminal::printClassSchedule(std::string& classCode) {
    system("clear");
    std::cout << "This is the schedule of class " << classCode << "\n\n";

    Schedule schedule = course.getClassSchedule(classCode);
    printSchedule(schedule);
}

/**
 * @brief Prints the schedule of a student.
 * @param studentCode
 */
void Terminal::printStudentSchedule(std::string& studentCode) {
    system("clear");
    std::cout << "This is the schedule of student " << studentCode << "\n\n";

    Schedule schedule = course.getStudentSchedule(studentCode);
    printSchedule(schedule);
}

/**
 * @brief Main method to print a schedule. Prints a schedule table and overlapped lectures table, if there are any.
 * @details Time complexity O(nlog(n)), n = number of lectures in the schedule
 * @param schedule
 */
void Terminal::printSchedule(const Schedule& schedule) {

    // lines printed within a lecture
    std::vector weekdays = {-1,-1,-1,-1,-1,-1};

    // stores the lectures who were overlapped and couldn't be displayed
    std::set<Lecture> overlapped;

    // stores the lectures
    std::set<Lecture> lectures = schedule.getLectures();

    // HEADERS
    for (int i = 0; i < 3; i++) {
        if (i == 0 || i == 2) {
            for (int j = 0; j < 7; j++) {
                std::cout << "|" << fill('-', SCHEDULE_COL_WIDTH);
            }
        }
        else {
            std::cout << "|" << center("HOURS", ' ', SCHEDULE_COL_WIDTH);
            std::cout << "|" << center("MONDAY", ' ', SCHEDULE_COL_WIDTH);
            std::cout << "|" << center("TUESDAY", ' ', SCHEDULE_COL_WIDTH);
            std::cout << "|" << center("WEDNESDAY", ' ', SCHEDULE_COL_WIDTH);
            std::cout << "|" << center("THURSDAY", ' ', SCHEDULE_COL_WIDTH);
            std::cout << "|" << center("FRIDAY", ' ', SCHEDULE_COL_WIDTH);
            std::cout << "|" << center("SATURDAY", ' ', SCHEDULE_COL_WIDTH);
        }
        std::cout << "|\n";
    }

    float hour = 8;         // Start hour of the first possible lecture
    // SCHEDULE
    while (hour < 22) {
        // Print a block of lines (ex. 08:00 - 08:30)
        for (int line = 0; line < 2; line++) {
            // Print a line

            // Hours
            if (line == 0) {
                std::cout << "|" << center(formatHourRange(hour, hour + 0.5), ' ', SCHEDULE_COL_WIDTH);
            } else {
                std::cout << "|" << fill('-', SCHEDULE_COL_WIDTH);
            }

            // Weekdays
            for (int weekday = 0; weekday < 6; weekday++) {
                bool printedLine = false;           // Already printed a line for this weekday
                bool foundOverlapped = false;
                do {
                    for (auto lecture = lectures.begin(); lecture != lectures.end(); lecture++) {
                        if (lecture->getWeekday() == weekday && lecture->isOccurring(hour)) {
                            // Overlapped
                            if ((weekdays[weekday] == -1 && hour != lecture->getStartHour()) ||
                                (weekdays[weekday] > 1 && hour == lecture->getStartHour())) {
                                overlapped.insert(*lecture);
                                lectures.erase(lecture);
                                foundOverlapped = true;
                                break;
                            }


                            // Done printing this lecture
                            if (lecture->getEndHour() == (hour + 0.5) && line == 1) {
                                std::cout << "|" << fill('-', SCHEDULE_COL_WIDTH);
                                weekdays[weekday] = -1;
                                printedLine = true;
                                foundOverlapped = false;
                                lectures.erase(lecture);
                                break;
                            }

                            // Currently printing the 0 line (first blank of the lecture)
                            if (weekdays[weekday] == -1 && hour == lecture->getStartHour()) {
                                weekdays[weekday] = 0;
                            }

                            // Print UC (type)
                            if (weekdays[weekday] == getMiddleOfLectureBox(lecture->getDuration()) - 1) {
                                std::cout << "|" << center(formatUcAndType(lecture->getUC(), lecture->getType()), ' ',
                                                           SCHEDULE_COL_WIDTH);
                            }
                            // Print Class
                            else if (weekdays[weekday] == getMiddleOfLectureBox(lecture->getDuration()) + 1) {
                                std::cout << "|" << center(lecture->getClass(), ' ', SCHEDULE_COL_WIDTH);
                            }
                            // Otherwise print blank
                            else {
                                std::cout << "|" << fill(' ', SCHEDULE_COL_WIDTH);
                            }

                            weekdays[weekday]++;        // Increment lines printed

                            printedLine = true;
                            foundOverlapped = false;
                            break;
                        }
                        foundOverlapped = false;
                    }
                } while (foundOverlapped);
                // No lectures occurring
                if (!printedLine) {
                    if (line == 0)
                        std::cout << "|" << fill(' ', SCHEDULE_COL_WIDTH);
                    else
                        std::cout << "|" << fill('-', SCHEDULE_COL_WIDTH);
                }
            }
            std::cout << "|\n";
        }
        hour += 0.5;
    }
    for (Lecture lecture : lectures) {
        overlapped.insert(lecture);
    }

    if (!overlapped.empty())
        printOverlappedLectures(overlapped);

    endDisplayMenu();
    getInput();
}

/**
 * @brief Prints the overlapped lectures that couldn't be printed in the schedule table.
 * @details Time complexity O(nlog(n)), n = number of overlapped lectures
 * @param lectures
 */
void Terminal::printOverlappedLectures(const std::set<Lecture> &lectures) {
    // Table title
    std::cout << "\n|" << fill('-', 4 * OVERLAPPED_COL_WIDTH + 3) << "|\n";
    std::cout << "|" << center("OVERLAPPED LECTURES", ' ', 4 * OVERLAPPED_COL_WIDTH + 3) << "|\n";

    // Separate tile from headers
    std::cout << "|" << fill('-', OVERLAPPED_COL_WIDTH);
    for (int i = 0; i < 3; i++) {
        std::cout << "-" << fill('-', OVERLAPPED_COL_WIDTH);
    }
    std::cout << "|\n";

    // Table headers
    std::cout << "|" << center("UC", ' ', OVERLAPPED_COL_WIDTH)
            << "|" << center("WEEKDAY", ' ', OVERLAPPED_COL_WIDTH)
            << "|" << center("HOUR", ' ', OVERLAPPED_COL_WIDTH)
            << "|" << center("CLASS", ' ', OVERLAPPED_COL_WIDTH) << "|\n";
    // Separate headers from lectures
    for (int i = 0; i < 4; i++) {
        std::cout << "|" << fill('-', OVERLAPPED_COL_WIDTH);
    }
    std::cout << "|\n";

    // Sort lectures by weekday
    std::vector<Lecture> orderedLectures;
    for (Lecture lecture : lectures) {
        orderedLectures.push_back(lecture);
    }
    sort(orderedLectures.begin(), orderedLectures.end(), byWeekday);

    // Print lectures
    for (auto lecture = orderedLectures.begin(); lecture != orderedLectures.end(); lecture++) {
        std::cout << "|" << center(formatUcAndType(lecture->getUC(), lecture->getType()), ' ', OVERLAPPED_COL_WIDTH);
        std::cout << "|" << center(formatWeekday(lecture->getWeekday()), ' ', OVERLAPPED_COL_WIDTH);
        std::cout << "|" << center(formatHourRange(lecture->getStartHour(), lecture->getEndHour()), ' ', OVERLAPPED_COL_WIDTH);
        std::cout << "|" << center(lecture->getClass(), ' ', OVERLAPPED_COL_WIDTH) << "|\n";
    }
    // Close table
    std::cout << "|" << fill('-', OVERLAPPED_COL_WIDTH);
    for (int i = 0; i < 3; i++) {
        std::cout << "-" << fill('-', OVERLAPPED_COL_WIDTH);
    }
    std::cout << "|\n";
}

/**
 * @brief Returns a string with c repeated width times.
 * @param c Character to fill with
 * @param width Width of the string
 * @return String with length width filled with c
 */
std::string Terminal::fill(char c, int width) {
    std::ostringstream oss;
    oss << std::setw(width) << std::setfill(c) << "";
    return oss.str();
}

/**
 * @brief Returns a string of the format "ucCode (type)"
 * @param ucCode
 * @param type
 * @return "ucCode (type)"
 */
std::string Terminal::formatUcAndType(const std::string &ucCode, const std::string &type) {
    std::ostringstream oss;
    oss << ucCode << " (" << type << ")";
    return oss.str();
}

/**
 * @brief Returns a string of the format "hh:mm"
 * @param hour
 * @return "hh:mm"
 */
std::string Terminal::formatHour(float hour) {
    std::ostringstream oss;
    int hours = floor(hour);
    int mins = (hour - floor(hour)) * 60;
    oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << mins;
    return oss.str();
}

/**
 * @brief Returns a string of the format "hh:mm - hh:mm" with start hour on the left and end hour on the right.
 * @param startHour
 * @param endHour
 * @return "hh:mm - hh:mm"
 */
std::string Terminal::formatHourRange(float startHour, float endHour) {
    std::ostringstream oss;
    oss << formatHour(startHour) << " - " << formatHour(endHour);
    return oss.str();
}

/**
 * @brief Returns a weekday.
 * @param weekday Number representing a weekday
 * @return Weekday as a string
 */
std::string Terminal::formatWeekday(int weekday) {
    std::map<int, std::string> mapWeekday =
            {{0, "Monday"},
             {1, "Tuesday"},
             {2, "Wednesday"},
             {3, "Thursday"},
             {4, "Friday"},
             {5, "Saturday"}};
    return mapWeekday[weekday];
}

/**
 * @brief Return a string of length width with str centered and surrounded by sep.
 * @param str
 * @param sep
 * @param width
 * @return String of length width with str centered and surrounded by sep
 */
std::string Terminal::center(const std::string &str, char sep, int width) {
    std::ostringstream oss;
    int space = (width - str.length()) / 2;
    std::cout << std::setw(space) << std::setfill(sep) << "" << str << std::setw(width - str.length() - space) << std::setfill(sep) << "";
    return oss.str();
}

/**
 * @brief Returns the middle line of a lecture being printed in a schedule table.
 * @param duration Duration of the lecture
 * @return Middle line of a lecture being printed in a schedule table
 */
int Terminal::getMiddleOfLectureBox(float duration) {
    int linesNotSeparators = ((duration * 2) / SCHEDULE_LINE_HEIGHT);
                                        // lines of seperators
    int middle = linesNotSeparators + linesNotSeparators - 1;
    return middle / 2;
}



/**
 * @brief Prints students in a class.
 * @param classCode
 * @param ucCode
 */
void Terminal::printStudentsInClass(std::string classCode, std::string ucCode) {
    std::ostringstream message;
    message << "These are the students registered in class " << classCode << " in UC " << ucCode << "\n\n";

    std::vector<Student*> students = course.getStudentsInClass(classCode, ucCode);
    sortingOptions sortOptions;
    printStudents(students, message.str(), sortOptions);
}

/**
 * @brief Prints students in a UC.
 * @param ucCode
 */
void Terminal::printStudentsInUC(std::string ucCode) {
    std::ostringstream message;
    message << "These are the students registered in UC " << ucCode << "\n\n";

    std::vector<Student*> students = course.getStudentsInUC(ucCode);
    sortingOptions sortOptions;
    printStudents(students, message.str(), sortOptions);
}

/**
 * @brief Prints students in a year.
 * @param year
 */
void Terminal::printStudentsInYear(std::string year) {
    std::ostringstream message;
    message << "These are the students registered in year " << year << "\n\n";

    std::vector<Student*> students = course.getStudentsInYear(year);
    sortingOptions sortOptions;
    printStudents(students, message.str(), sortOptions);
}

/**
 * @brief Prints students in course.
 */
void Terminal::printStudentsInCourse() {
    std::ostringstream message;
    message << "These are the students registered in this course (" << course.getName() << ")" << "\n\n";

    std::vector<Student*> students = course.getStudentsInCourse();
    sortingOptions sortOptions;
    printStudents(students, message.str(), sortOptions);
}

/**
 * @brief Prints students in at least the some number of UC's.
 * @param n Minimum number of UC's that a student needs to be registered
 */
void Terminal::printStudentsInAtLeastUCs(int n) {
    std::ostringstream message;
    message << "These are the students registered in registered in at least " << n << " UC's" << "\n\n";

    std::vector<Student*> students = course.getStudentsInAtLeastUCs(n);
    sortingOptions sortOptions;
    printStudents(students, message.str(), sortOptions);
}

/**
 * @brief Main method to print students. Prints students in a table with headers 'Code' and 'Name' of the student, that can be sorted in different ways.
 * @details Time complexity O(nlog(n)), n = number of students
 * @param students Vector containing the students to be printed
 * @param message Message to be printed before printing the table
 * @param sortOptions Sorting options
 */
void Terminal::printStudents(std::vector<Student*> &students, std::string message, sortingOptions &sortOptions) {
    // By default -> orders by student name and ascending
    system("clear");
    std::cout << message;

    std::cout << center("Code", ' ', STUDENT_CODE_COL_WIDTH) << "| Name" << "\n";        // Column titles
    std::cout << fill('-', STUDENT_CODE_COL_WIDTH) << "|" << fill('-', STUDENT_NAME_COL_WIDTH) << "\n";           // Separators

    // Order by the first column (Student Code)
    if (sortOptions.orderBy == 0) {
        std::sort(students.begin(), students.end(), byStudentCode);
    }
    // Order by second column (Student Name)
    else {
        std::sort(students.begin(), students.end(), byStudentName);
    }

    // Descending order
    if (!sortOptions.ascending) {
        for (auto student = students.rbegin(); student != students.rend(); student++) {
            std::cout << center((*student)->getStudentCode(), ' ', STUDENT_CODE_COL_WIDTH) << "| " << (*student)->getName() << "\n";
        }
    }
    // Ascending order
    else {
        for (auto student = students.begin(); student != students.end(); student++) {
            std::cout <<  center((*student)->getStudentCode(), ' ', STUDENT_CODE_COL_WIDTH) << "| " << (*student)->getName() << "\n";
        }
    }

    studentMenu();
    if (getInput() == 's') {
        getSortingOptions(sortOptions);
        printStudents(students, message, sortOptions);
    }
}


/**
 * @brief Prints the menu after printing students.
 */
void Terminal::studentMenu() {
    std::cout << "\n\n";
    printSortingOptions();
    printBackToMenu();
    printExit();
}

void Terminal::printBackToMenu() {
    std::cout << "Press 'm' to go back to the main menu.\n";
}

void Terminal::printSortingOptions() {
    std::cout << "Press 's' for sorting options.\n";
}

void Terminal::printFilteringOptions() {
    std::cout << "Press 'f' for filtering options.\n";
}

/**
 * @brief Receives the sorting options from the user.
 * @param sortOptions Struct where the sorting options will be stored
 */
void Terminal::getSortingOptions(sortingOptions &sortOptions) {
    std::cout << "SORTING OPTIONS\n\n";
    std::cout << "Type the number of the column (starting at 0) to order by: ";
    std::cin >> sortOptions.orderBy;
    std::cout << "Type 0 for descending order or 1 for ascending order: ";
    std::cin >> sortOptions.ascending;
}

/**
 * @brief Receives the filtering options, for course occupation table, from the user.
 * @param filterOptions Struct where the filtering options will be stored
 */
void Terminal::getFilteringOptions(occupationOptions &filterOptions) {
    std::cout << "FILTERING OPTIONS\n\n";
    std::cout << "Columns to display (0 - don't display, 1 - display):\n";
    std::cout << "\tYear: ";
    std::cin >> filterOptions.years;
    std::cout << "\tUC: ";
    std::cin >> filterOptions.UCs;
    std::cout << "\tClass: ";
    std::cin >> filterOptions.classes;

    std::cout << "Filtering options ('all' to show all elements of the column):\n";
    std::cout << "\tYear: ";
    std::cin >> filterOptions.year;
    std::cout << "\tUC code: ";
    std::cin >> filterOptions.ucCode;
    std::cout << "\tClass code: ";
    std::cin >> filterOptions.classCode;
}

void Terminal::printExit() {
    std::cout << "Press 'q' to quit.\n";
}

/**
 * @brief Receives input from the user.
 * @return
 */
char Terminal::getInput() {
    char input;
    std::cin >> input;
    if (input == 'm') {
        printMainMenu();
    }
    return input;
}

/**
 * @brief Prints default menu after displaying anything that allows to go back to the main menu or exit the program.
 */
void Terminal::endDisplayMenu() {
    std::cout << "\n\n";
    printBackToMenu();
    printExit();
}


bool Terminal::byStudentName(Student *student1, Student *student2) {
    if (student1->getName() < student2->getName()) {
        return true;
    } else if (student1->getName() == student2->getName()) {
        return student1->getStudentCode() < student2->getStudentCode();
    }
    return false;
}

bool Terminal::byStudentCode(Student* student1, Student* student2) {
    return student1->getStudentCode() <= student2->getStudentCode();
}

bool Terminal::byWeekday(Lecture lecture1, Lecture lecture2) {
    if(lecture1.getWeekday() < lecture2.getWeekday())
        return true;
    else if(lecture1.getWeekday() == lecture2.getWeekday()) {
        if (lecture1.getStartHour() < lecture2.getStartHour())
            return true;
        else if (lecture1.getStartHour() == lecture2.getStartHour()) {
            if (lecture1.getEndHour() < lecture2.getEndHour())
                return true;
            else if (lecture1.getEndHour() == lecture2.getEndHour()) {
                if (lecture1.getClass() < lecture2.getClass())
                    return true;
                else if (lecture1.getClass() == lecture2.getClass()) {
                    if (lecture1.getUC() < lecture2.getUC())
                        return true;
                    else if (lecture1.getUC() == lecture2.getUC())
                        return lecture1.getType() < lecture2.getType();
                }
            }
        }
    }
    return false;
}

/**
 * @brief Main method to print the course occupation, Prints table with headers 'Year', 'UC Code', 'Class', 'Occupation', that can be sorted and filtered in different ways.
 * @details Time Complexity O(nlog(n)), n = number of classes or number of UC's or number of years
 * @param sortOptions Sorting options
 * @param filterOptions Filtering options
 */
void Terminal::printCourseOccupation(sortingOptions &sortOptions, occupationOptions &filterOptions) {
    system("clear");
    // By default, shows everything
    std::cout << "This course (" << course.getName() << ") has " << course.getOccupation() << " students registered.\n\n";

    // Nothing to display, only number of students in course
    if (filterOptions.displayNothing())
        return;

    // Print headers
    std::cout << "|" << fill('-', filterOptions.years * (OVERLAPPED_COL_WIDTH + 1) +
                                  filterOptions.UCs * (OVERLAPPED_COL_WIDTH + 1) +
                                  filterOptions.classes * (OVERLAPPED_COL_WIDTH + 1) +
                                  OVERLAPPED_COL_WIDTH) << "|\n";
    printOccupationHeaders(filterOptions);

    // Print class occupation
    if (filterOptions.classes) {
        printClassOccupation(sortOptions, filterOptions);
    }
    // Print UC occupation
    else if (filterOptions.UCs) {
        printUcOccupation(sortOptions, filterOptions);
    }
    // Print year occupation
    else if (filterOptions.years) {
        printYearOccupation(sortOptions, filterOptions);
    }

    // Close table
    std::cout << "|" << fill('-', filterOptions.years * (OVERLAPPED_COL_WIDTH + 1) +
                                  filterOptions.UCs * (OVERLAPPED_COL_WIDTH + 1) +
                                  filterOptions.classes * (OVERLAPPED_COL_WIDTH + 1) +
                                  OVERLAPPED_COL_WIDTH) << "|\n";


    OccupationMenu();
    char input = getInput();
    if (input == 's') {
        getSortingOptions(sortOptions);
        printCourseOccupation(sortOptions, filterOptions);
    } else if (input == 'f') {
        getFilteringOptions(filterOptions);
        printCourseOccupation(sortOptions, filterOptions);
    }
}

/**
 * @brief Prints the rows of the class occupation table.
 * @details Time Complexity O(nlog(n)), n = number of classes
 * @param sortOptions Sorting options
 * @param filterOptions Filtering options
 */
void Terminal::printClassOccupation(sortingOptions &sortOptions, occupationOptions &filterOptions) {
    std::vector<Class> classes = course.getClasses();
    // Sort
    filterOptions.getRealOrderBy(sortOptions.orderBy);
    switch (sortOptions.orderBy) {
        case 0:
            std::sort(classes.begin(), classes.end(), classesByYear);
            break;
        case 1:
            std::sort(classes.begin(), classes.end(), classesByUcCode);
            break;
        case 2:
            std::sort(classes.begin(), classes.end());
            break;
        case 3:
            std::sort(classes.begin(), classes.end(), classesByOccupation);
            break;
        default:
            std::sort(classes.begin(), classes.end(), classesByUcCode);
            break;
    }
    // Descending order
    if (!sortOptions.ascending) {
        // Print
        for (auto it = classes.rbegin(); it != classes.rend(); it++) {
            printClassOccupationLine(*it, filterOptions);
        }
    }
    // Ascending order
    else {
        // Print
        for (auto it = classes.begin(); it != classes.end(); it++) {
            printClassOccupationLine(*it, filterOptions);
        }
    }
}

/**
 * @brief Prints a row of the class occupation table.
 * @param class_ Class that will be printed in this row
 * @param filterOptions Filtering options
 */
void Terminal::printClassOccupationLine(const Class &class_, const occupationOptions &filterOptions) {
    // Check if matches filtering options
    if (((class_.getClassCode() == filterOptions.classCode) || (filterOptions.classCode == "all")) &&
        ((class_.getUC() == filterOptions.ucCode) || (filterOptions.ucCode == "all")) &&
        ((class_.getYear() == filterOptions.year) || (filterOptions.year == "all")) ) {

        // Print line
        std::cout << "|";
        if (filterOptions.years) {
            std::cout << center(class_.getYear(), ' ', OVERLAPPED_COL_WIDTH) << "|";
        }
        if (filterOptions.UCs) {
            std::cout << center(class_.getUC(), ' ', OVERLAPPED_COL_WIDTH) << "|";
        }
        std::cout << center(class_.getClassCode(), ' ', OVERLAPPED_COL_WIDTH) << "|";
        std::cout << center(std::to_string(class_.getOccupation()), ' ', OVERLAPPED_COL_WIDTH) << "|\n";
    }
}

/**
 * @brief Prints the rows of the UC occupation table.
 * @details Time Complexity O(nlog(n)), n = number of UC's
 * @param sortOptions Sorting options
 * @param filterOptions Filtering options
 */
void Terminal::printUcOccupation(sortingOptions &sortOptions, occupationOptions &filterOptions) {
    std::vector<UC> UCs = course.getUCs();
    // Sort
    filterOptions.getRealOrderBy(sortOptions.orderBy);
    switch (sortOptions.orderBy) {
        case 0:
            std::sort(UCs.begin(), UCs.end(), ucsByYear);
            break;
        case 1:
            std::sort(UCs.begin(), UCs.end());
            break;
        case 3:
            std::sort(UCs.begin(), UCs.end(), ucsByOccupation);
            break;
        default:
            std::sort(UCs.begin(), UCs.end());
            break;
    }
    // Descending order
    if (!sortOptions.ascending) {
        // Print
        for (auto it = UCs.rbegin(); it != UCs.rend(); it++) {
            printUcOccupationLine(*it, filterOptions);
        }
    }
        // Ascending order
    else {
        // Print
        for (auto it = UCs.begin(); it != UCs.end(); it++) {
            printUcOccupationLine(*it, filterOptions);
        }
    }
}

/**
 * @brief Prints a row of the UC occupation table.
 * @param uc UC that will be printed in this row
 * @param filterOptions Filtering options
 */
void Terminal::printUcOccupationLine(const UC &uc, const occupationOptions &filterOptions) {
    // Check if matches filtering options
    if (((uc.getUcCode() == filterOptions.ucCode) || (filterOptions.ucCode == "all")) &&
        ((uc.getYear() == filterOptions.year) || (filterOptions.year == "all")) ) {

        // Print line
        std::cout << "|";
        if (filterOptions.years) {
            std::cout << center(uc.getYear(), ' ', OVERLAPPED_COL_WIDTH) << "|";
        }
        std::cout << center(uc.getUcCode(), ' ', OVERLAPPED_COL_WIDTH) << "|";
        std::cout << center(std::to_string(uc.getOccupation()), ' ', OVERLAPPED_COL_WIDTH) << "|\n";
    }
}

/**
 * @brief Prints the rows of the year occupation table.
 * @details Time Complexity O(nlog(n)), n = number of years
 * @param sortOptions Sorting options
 * @param filterOptions Filtering options
 */
void Terminal::printYearOccupation(sortingOptions &sortOptions, occupationOptions &filterOptions) {
    std::vector<std::pair<std::string, int>> yearOccupation = course.getYearOccupation();
    // Sort
    filterOptions.getRealOrderBy(sortOptions.orderBy);
    switch (sortOptions.orderBy) {
        case 0:
            std::sort(yearOccupation.begin(), yearOccupation.end(), yearsByYear);
            break;
        case 3:
            std::sort(yearOccupation.begin(), yearOccupation.end(), yearsByOccupation);
            break;
        default:
            std::sort(yearOccupation.begin(), yearOccupation.end(), yearsByYear);
            break;
    }
    // Descending order
    if (!sortOptions.ascending) {
        // Print
        for (auto it = yearOccupation.rbegin(); it != yearOccupation.rend(); it++) {
            printYearOccupationLine(*it, filterOptions);
        }
    }
        // Ascending order
    else {
        // Print
        for (auto it = yearOccupation.begin(); it != yearOccupation.end(); it++) {
            printYearOccupationLine(*it, filterOptions);
        }
    }
}

/**
 * @brief Prints a row of the year occupation table.
 * @param yearOcc Pair containing the year that will be printed in this row and the respective occupation
 * @param filterOptions Filtering options
 */
void Terminal::printYearOccupationLine(const std::pair<std::string, int> &yearOcc, const occupationOptions &filterOptions) {
    // Check if matches filtering options
    if ((filterOptions.year == yearOcc.first) || (filterOptions.year == "all")) {
        // Print line
        std::cout << "|";
        std::cout << center(yearOcc.first, ' ', OVERLAPPED_COL_WIDTH) << "|";
        std::cout << center(std::to_string(yearOcc.second), ' ', OVERLAPPED_COL_WIDTH) << "|\n";
    }
}

/**
 * @brief Prints the headers of the occupation table.
 * @param filterOptions Filtering options
 */
void Terminal::printOccupationHeaders(const occupationOptions &filterOptions) {
    for (int i = 0; i < 2; i++) {
        std::cout << "|";
        if (filterOptions.years) {
            printOccupationHeader(i, "Year", OVERLAPPED_COL_WIDTH);
        }
        if (filterOptions.UCs) {
            printOccupationHeader(i, "UC", OVERLAPPED_COL_WIDTH);
        }
        if (filterOptions.classes) {
            printOccupationHeader(i, "Class", OVERLAPPED_COL_WIDTH);
        }
        printOccupationHeader(i, "Occupation", OVERLAPPED_COL_WIDTH);
        std::cout << "\n";
    }
}

void Terminal::printOccupationHeader(int line, std::string header, int width) {
    if (line == 0) {
        std::cout << center(header, ' ', width) << "|";
    } else {
        std::cout << fill('-', width) << "|";
    }
}

/**
 * @brief Prints menu after displaying the course occupation.
 */
void Terminal::OccupationMenu() {
    std::cout << "\n\n";
    printSortingOptions();
    printFilteringOptions();
    printBackToMenu();
    printExit();
}

bool Terminal::classesByYear(Class class1, Class class2) {
    if (class1.getYear() < class2.getYear())
        return true;
    else if (class1.getYear() < class2.getYear())
        return class1 < class2;
    return false;
}

bool Terminal::classesByUcCode(Class class1, Class class2) {
    if (class1.getUC() < class2.getUC())
        return true;
    else if (class1.getUC() == class2.getUC())
        return class1 < class2;
    return false;
}

bool Terminal::classesByOccupation(Class class1, Class class2) {
    if (class1.getOccupation() < class2.getOccupation())
        return true;
    else  if (class1.getOccupation() == class2.getOccupation())
        return class1 < class2;
    return false;
}

bool Terminal::ucsByYear(UC uc1, UC uc2) {
    if (uc1.getYear() < uc2.getYear())
        return true;
    else if (uc1.getYear() == uc2.getYear())
        return uc1 < uc2;
    return false;
}

bool Terminal::ucsByOccupation(UC uc1, UC uc2) {
    if (uc1.getOccupation() < uc2.getOccupation())
        return true;
    else if (uc1.getOccupation() == uc2.getOccupation())
        return uc1 < uc2;
    return false;
}

bool Terminal::yearsByYear(std::pair<std::string, int> pair1, std::pair<std::string, int> pair2) {
    if (pair1.first < pair2.first)
        return true;
    else if (pair1.first == pair2.first)
        return pair1.second <= pair2.second;
    return false;
}

bool Terminal::yearsByOccupation(std::pair<std::string, int> pair1, std::pair<std::string, int> pair2) {
    if (pair1.second < pair2.second)
        return true;
    else if (pair1.second < pair2.second)
        return pair1.first <= pair2.first;
    return false;
}

