#include <sstream>
#include "LeaveRequest.h"
/**
 * @brief Constructor of the LeaveRequest
 * @param studentCode code of the student that requested
 * @param ucCode code of the UC which student wants to leave
 */
LeaveRequest::LeaveRequest(std::string studentCode, std::string ucCode) : Request(studentCode), ucCode(ucCode)
{}

/**
 * @brief Gets the code of the UC to leave
 * @return ucCode
 */
std::string LeaveRequest::getUcCode()const {
    return ucCode;
}

/**
 * @brief Auxiliar function to print after the LeaveRequest is done
 */
std::string LeaveRequest::toStr() const {
    std::ostringstream oss;
    oss << "Student " << getStudentCode() << " left UC " << ucCode;
    return oss.str();
}