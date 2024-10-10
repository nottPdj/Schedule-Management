#ifndef PROJETO_SWITCHUCREQUEST_H
#define PROJETO_SWITCHUCREQUEST_H

#include "Request.h"

/**
 * @brief SwitchUcRequest is a request for a uc switch
 * @details Time Complexity O(1) for all function of the class
 */

class SwitchUcRequest : public Request{
private:
    std::string ucCodeCurrent;
    std::string ucCodeNext;

public:
    SwitchUcRequest(std::string studentCode,std::string ucCodeCurrent,std::string ucCodeNext);
    std::string getUcCodeCurrent() const;
    std::string getUcCodeNext() const;
    std::string toStr() const override;
};



#endif //PROJETO_SWITCHUCREQUEST_H
