#ifndef PROJETO_AUXILIAR_H
#define PROJETO_AUXILIAR_H


#include <stack>
#include <queue>
#include "Course.h"


/**
 * @brief Auxiliar is used to read the data files and request history
 */

class Auxiliar {
public:
    static void readClassesPerUc(Course& course);
    static void readStudentsClasses(Course& course);
    static void readClasses(Course& course);

    static void loadRequestRecord(std::queue<Request*> &pastRequests);
    static void saveRequestRecord(std::stack<Request*> requestRecord);
};


#endif //PROJETO_AUXILIAR_H
