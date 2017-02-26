#include "GenericException.h"

GenericException::GenericException(std::string msg)
{
    //ctor
    m_msg = msg;
}

GenericException::~GenericException()
{
    //dtor
}

const char* GenericException::what() const throw()
{
    return m_msg.c_str();
}
