#ifndef PROJETO_REQUEST_H
#define PROJETO_REQUEST_H


#include <string>
#include "Student.h"
#include "Class.h"

/**
 * @brief Request is the base class for all types of requests
 * @details Time Complexity O(1) for all function of the class
 */

class Request {
private:

    std::string studentCode;
    std::string message;
    bool undo;

public:
    Request(std::string studentCode);
    std::string getStudentCode()const;
    std::string getMessage() const;
    void setMessage(std::string message);
    void setUndo();
    bool isUndo() const;
    virtual std::string toStr() const = 0;
};


#endif //PROJETO_REQUEST_H
