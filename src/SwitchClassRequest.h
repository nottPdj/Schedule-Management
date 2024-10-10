#ifndef PROJETO_SWITCHCLASSREQUEST_H
#define PROJETO_SWITCHCLASSREQUEST_H


#include "Request.h"

/**
 * @brief SwitchClassRequest is a request for a class switch
 * @details Time Complexity O(1) for all function of the class
 */

class SwitchClassRequest : public Request{
private:
    std::string ucCode;
    std::string classCodeCurrent;
    std::string classCodeNext;

public:
    SwitchClassRequest(std::string studentCode,std::string ucCode,std::string classCodeCurrent, std::string classCodeNext);
    std::string getUcCode() const;
    std::string getClassCodeCurrent() const;
    std::string getClassCodeNext() const;
    std::string toStr() const override;
};


#endif //PROJETO_SWITCHCLASSREQUEST_H
