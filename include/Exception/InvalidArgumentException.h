#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include "GenericException.h"
#include <string>

class InvalidArgumentException: public GenericException
{
    public:
        InvalidArgumentException(std::string msg);
        virtual ~InvalidArgumentException();

    protected:

    private:
};

#endif // INVALIDARGUMENTEXCEPTION_H
