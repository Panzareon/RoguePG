#include "InvalidFunctionException.h"

InvalidFunctionException::InvalidFunctionException(std::string msg) : GenericException(msg)
{
    //ctor
}

InvalidFunctionException::~InvalidFunctionException()
{
    //dtor
}
