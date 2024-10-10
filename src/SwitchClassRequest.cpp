#include <sstream>
#include "SwitchClassRequest.h"

/**
 * @brief Constructor of the SwitchClassRequest
 * @param studentCode code of the student that requested
 * @param ucCode code of the UC which classes are registered
 * @param classCodeCurrent
 * @param classCodeNext
 */
SwitchClassRequest::SwitchClassRequest(std::string studentCode, std::string ucCode, std::string classCodeCurrent,std::string classCodeNext)
: Request(studentCode),ucCode(ucCode),classCodeCurrent(classCodeCurrent),classCodeNext(classCodeNext){}

/**
 * @brief Gets the code of the UC which classes are registered
 * @return ucCode
 */
std::string SwitchClassRequest::getUcCode() const{
    return ucCode;
}

/**
 * @brief Get the code of the Class which the student is currently registered
 * @return classCodeCurrent
 */
std::string SwitchClassRequest::getClassCodeCurrent() const{
    return classCodeCurrent;
}

/**
 * @brief Gets the code of the Class which the student wants to switch
 * @return classCodeNext
 */
std::string SwitchClassRequest::getClassCodeNext() const{
    return classCodeNext;
}
/**
 * @brief Auxiliar function to print after the SwitchClassRequest is done
 */
std::string SwitchClassRequest::toStr() const {
    std::ostringstream oss;
    oss << "Student " << getStudentCode() << " switched from class " << classCodeCurrent << " to class " << classCodeNext << " for the UC " << ucCode;
    return oss.str();
}

