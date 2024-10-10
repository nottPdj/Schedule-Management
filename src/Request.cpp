#include "Request.h"

/**
 * @brief Constructor of the Request
 * @param studentCode
 */
Request::Request(std::string studentCode):studentCode(studentCode)
{
    undo = false;
}
/**
 * @brief Gets the code of the Student that requested
 * @return studentCode
 */
std::string Request::getStudentCode() const {
    return studentCode;
}

/**
 * @brief Gets the message of the Request
 * @return message
 */
std::string Request::getMessage() const {
    return message;
}

/**
 * @brief Sets the message of the Request
 * @param message
 */
void Request::setMessage(std::string message) {
    this->message=message;
}

/**
 * @brief Sets the Request to undo
 */
void Request::setUndo() {
    undo = true;
}

/**
 * @brief Checks if it is a undo Request
 */
bool Request::isUndo() const {
    return undo;
}


