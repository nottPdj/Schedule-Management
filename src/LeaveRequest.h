#ifndef PROJETO_LEAVEREQUEST_H
#define PROJETO_LEAVEREQUEST_H

#include "Request.h"

/**
 * @brief LeaveRequest is the class that contains the information for a leave request
 * @details Time Complexity O(1) for all function of the class
 */

class LeaveRequest: public Request{
private:
    std::string ucCode;
public:
    LeaveRequest(std::string studentCode,std::string ucCode);
    std::string getUcCode() const;
    std::string toStr() const override;
};

#endif //PROJETO_LEAVEREQUEST_H
