#include "InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(std::string msg) : GenericException(msg)
{
    //ctor
}

InvalidArgumentException::~InvalidArgumentException()
{
    //dtor
}
