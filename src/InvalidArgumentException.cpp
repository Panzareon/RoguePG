#include "InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(std::string msg)
{
    //ctor
    m_msg = msg;
}

InvalidArgumentException::~InvalidArgumentException()
{
    //dtor
}

const char* InvalidArgumentException::what() const throw()
{
    return m_msg.c_str();
}
