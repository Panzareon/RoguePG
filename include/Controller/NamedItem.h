#ifndef NAMEDITEM_H
#define NAMEDITEM_H

#include <string>

class NamedItem
{
    public:
        NamedItem();
        virtual ~NamedItem();
        virtual std::string GetName() = 0;
        virtual std::string GetLocalizedDescription() = 0;

    protected:

    private:
};

#endif // NAMEDITEM_H
