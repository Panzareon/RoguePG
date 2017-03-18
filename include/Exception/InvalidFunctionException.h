#ifndef INVALIDFUNCTIONEXCEPTION_H
#define INVALIDFUNCTIONEXCEPTION_H

#include "GenericException.h"


class InvalidFunctionException : public GenericException
{
    public:
        InvalidFunctionException(std::string msg);
        virtual ~InvalidFunctionException();

    protected:

    private:
};

#endif // INVALIDFUNCTIONEXCEPTION_H
