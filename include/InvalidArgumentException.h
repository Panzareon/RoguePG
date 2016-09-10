#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include <exception>
#include <string>

class InvalidArgumentException: public std::exception
{
    public:
        InvalidArgumentException(std::string msg);
        virtual ~InvalidArgumentException();
        virtual const char* what() const throw();

    protected:

    private:
        std::string m_msg;
};

#endif // INVALIDARGUMENTEXCEPTION_H
