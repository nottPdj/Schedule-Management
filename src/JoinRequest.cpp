#include <sstream>
#include "JoinRequest.h"

/**
 * @brief Constructor of the JoinRequest
 * @param studentCode code of the student that requested
 * @param ucCode code of the UC which student wants to join
 */
JoinRequest::JoinRequest(std::string studentCode,std::string ucCode) : Request(studentCode),ucCode(ucCode)
{}

/**
 * @brief Gets the code of the UC to join
 * @return ucCode
 */
std::string JoinRequest::getUcCode() const{
    return ucCode;
}

/**
 * @brief Auxiliar function to print after the JoinRequest is done
 */
std::string JoinRequest::toStr() const {
    std::ostringstream oss;
    oss << "Student " << getStudentCode() << " joined UC " << ucCode;
    return oss.str();
}

