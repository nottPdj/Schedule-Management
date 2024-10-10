#ifndef PROJETO_LECTURE_H
#define PROJETO_LECTURE_H

#include <string>

/**
 * @brief Lecture is a class that contains all the information about a lecture
 * @details Time Complexity O(1) for all function of the class
 */

class Lecture {
private:
    std::string classCode;
    std::string ucCode;
    int weekday;
    float startHour;
    float endHour;
    float duration;
    std::string type;

public:
    Lecture(std::string classCode, std::string ucCode, std::string weekday, float startHour, float duration, std::string type);
    bool operator<(const Lecture& lecture) const;

    std::string getClass() const;
    std::string getUC() const;
    int getWeekday() const;
    float getStartHour() const;
    float getEndHour() const;
    float getDuration() const;
    std::string getType() const;
    bool isOccurring(float hour) const;
    bool overlaps(const Lecture &lecture) const;
};


#endif //PROJETO_LECTURE_H
