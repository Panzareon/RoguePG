#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <string>
#include <map>

class Localization
{
    public:
        enum Languages{English};
        virtual ~Localization();
        static Localization* GetInstance();

        std::string GetLocalization(std::string toLocalize);

    protected:

    private:
        Localization();
        static Localization* m_instance;
        Languages language;
};

#endif // LOCALIZATION_H
