#include "Schedule.h"

/**
 * @brief Schedule Constructor
 * @note Empty Schedule
 */
Schedule::Schedule() {}

/**
 * @brief Adds a Lecture to the Schedule
 * @param lecture
 * @details Time Complexity O(log n) n= number of lectures in schedule
 */
void Schedule::addLecture(Lecture lecture) {
    schedule.insert(lecture);
}

/**
 * @brief Removes a Lecture from the Schedule
 * @param lecture
 * @details Time Complexity O(log n) n= number of lectures in schedule
 */
void Schedule::removeLecture(Lecture lecture) {
    schedule.erase(lecture);
}

/**
 * @brief Gets the Lectures of the Schedule
 * @return schedule
 */
std::set<Lecture> Schedule::getLectures() const {
    return schedule;
}

/**
 * @brief Adds Lectures to the Schedule from other Schedule
 * @param schedule
 * @details Time Complexity O(n) n= number of lectures in schedule
 */
void Schedule::operator+=(const Schedule& schedule) {
    for(const Lecture &lecture : schedule.getLectures())
        this->addLecture(lecture);
}



