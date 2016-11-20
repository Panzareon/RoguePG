#ifndef GENERICEXCEPTION_H
#define GENERICEXCEPTION_H

#include <exception>
#include <string>


class GenericException: public std::exception
{
    public:
        GenericException(std::string msg);
        virtual ~GenericException();
        virtual const char* what() const throw();

    protected:
        std::string m_msg;

    private:
};

#endif // GENERICEXCEPTION_H
