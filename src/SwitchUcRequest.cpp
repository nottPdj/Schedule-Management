#include <sstream>
#include "SwitchUcRequest.h"

/**
 * @brief Constructor of the SwitchUcRequest
 * @param studentCode code of the student that requested
 * @param ucCodeCurrent
 * @param ucCodeNext
 */
SwitchUcRequest::SwitchUcRequest(std::string studentCode, std::string ucCodeCurrent, std::string ucCodeNext)
: Request(studentCode),ucCodeCurrent(ucCodeCurrent),ucCodeNext(ucCodeNext){}

/**
 * @brief Gets the code of the UC which the student is currently registered
 * @return ucCodeCurrent
 */
std::string SwitchUcRequest::getUcCodeCurrent() const{
    return ucCodeCurrent;
}

/**
 * @brief Gets the code of the UC which the student wants to switch
 * @return ucCodeNext
 */
std::string SwitchUcRequest::getUcCodeNext() const{
    return ucCodeNext;
}

/**
 * @brief Auxiliar function to print after the SwitchUcRequest is done
 */
std::string SwitchUcRequest::toStr() const {
    std::ostringstream oss;
    oss << "Student " << getStudentCode() << " switched from UC " << ucCodeCurrent << " to UC " << ucCodeNext;
    return oss.str();
}

