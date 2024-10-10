#ifndef PROJETO_SCHEDULE_H
#define PROJETO_SCHEDULE_H


#include <set>
#include "Lecture.h"

/**
 * @brief Schedule is the class that contains all the information of a schedule
 */

class Schedule {

private:
    std::set<Lecture> schedule;

public:
    Schedule();
    void removeLecture(Lecture lecture);
    void addLecture(Lecture lecture);
    std::set<Lecture> getLectures() const;
    void operator+=(const Schedule& schedule);
};


#endif //PROJETO_SCHEDULE_H
