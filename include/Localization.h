#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <string>
#include <map>
#include <vector>

class Localization
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
        std::map<std::string, std::string> m_localization;
};

#endif // LOCALIZATION_H
