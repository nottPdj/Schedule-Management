#include <map>
#include "Lecture.h"

std::map<std::string, int> mapday =
        {{"Monday",0},
         {"Tuesday",1},
         {"Wednesday",2},
         {"Thursday",3},
         {"Friday",4},
         {"Saturday",5}};

/**
 * @brief Constructor of Lecture class. Stores all the parameters and calculates end hour.
 * @param classCode Class code of the lecture
 * @param uc UC code of the lecture
 * @param weekday Weekday the lecture occurs
 * @param startHour Start hour of the lecture
 * @param duration Duration of the lecture
 * @param type Type of lecture
 */
Lecture::Lecture(std::string classCode, std::string uc, std::string weekday, float startHour, float duration, std::string type):
        classCode(classCode),ucCode(uc),weekday(mapday[weekday]), startHour(startHour),duration(duration),type(type){
    this->endHour=startHour+duration;
}

/**
 * @brief Compare lecture by, following the order, start hour, end hour, weekday, type, class code and uc code.
 * @param lecture
 * @return
 */
bool Lecture::operator<(const Lecture &lecture) const {
    if(startHour < lecture.getStartHour())
        return true;
    else if(startHour == lecture.getStartHour()) {
        if (endHour < lecture.getEndHour())
            return true;
        else if (endHour == lecture.getEndHour()) {
            if (weekday < lecture.getWeekday())
                return true;
            else if (weekday == lecture.getWeekday()) {
                if (type > lecture.getType())
                    return true;
                else if (type == lecture.getType()) {
                    if (classCode < lecture.getClass())
                        return true;
                    else if (classCode == lecture.getClass())
                        return ucCode < lecture.getUC();
                }
            }
        }
    }
    return false;
}

/**
 * @brief Returns class code
 * @return class code
 */
std::string Lecture::getClass() const {
    return classCode;
}

/**
 * @brief Returns UC code
 * @return UC code
 */
std::string Lecture::getUC() const {
    return ucCode;
}

/**
 * @brief Returns weekday
 * @return Number representing a weekday
 */
int Lecture::getWeekday() const {
    return weekday;
}

/**
 * @brief Returns the start hour
 * @return start hour in hours
 */
float Lecture::getStartHour() const {
    return startHour;
}

/**
 * @brief Returns the end hour
 * @return end hour in hours
 */
float Lecture::getEndHour() const {
    return endHour;
}

/**
 * @brief Returns the duration
 * @return duration in ours
 */
float Lecture::getDuration() const {
    return duration;
}

/**
 * @brief Returns the type of lecture
 * @return type of lecture
 */
std::string Lecture::getType() const {
    return type;
}

/**
 * @brief Checks if lecture is occurring during an hour
 * @param hour
 * @return
 */
bool Lecture::isOccurring(float hour) const {
    return (hour >= startHour &&  hour < endHour);
}

/**
 * @brief Checks if a lecture occurs at the same time as another
 * @param lecture
 * @return
 */
bool Lecture::overlaps(const Lecture &lecture) const {
    if (weekday != lecture.getWeekday()) {
        return false;
    }
    return !(startHour >= lecture.getEndHour() || endHour <= lecture.getStartHour());
}