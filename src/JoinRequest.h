#ifndef PROJETO_JOINREQUEST_H
#define PROJETO_JOINREQUEST_H
#include "Request.h"

/**
 * @brief JoinRequest is the class that contains the information for a join request
 * @details Time Complexity O(1) for all function of the class
 */

class JoinRequest : public Request{

private:
    std::string ucCode;
public:
    JoinRequest(std::string studentCode,std::string ucCode);
    std::string getUcCode()const;
    std::string toStr() const override;
};

#endif //PROJETO_JOINREQUEST_H
