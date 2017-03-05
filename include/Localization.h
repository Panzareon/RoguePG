#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include "FileConfig.h"

#include <vector>

class Localization : FileConfig
{
    public:
        enum Languages{English};
        virtual ~Localization();
        static Localization* GetInstance();
        void LoadLocalizationFile(std::string filename, Languages language);

        std::string GetLocalization(std::string toLocalize);
        std::string GetLocalizationWithFloats(std::string toLocalize, std::vector<float>* values);
        std::string GetLocalizationWithStrings(std::string toLocalize, std::vector<std::string>* values);

    protected:

    private:
        Localization();
        static Localization* m_instance;
        Languages m_language;
};

#endif // LOCALIZATION_H
