#ifndef NAMEGENERATOR_H
#define NAMEGENERATOR_H

#include "FileConfig.h"
#include <map>

class NameGenerator : FileConfig
{
    public:
        virtual ~NameGenerator();
        static NameGenerator* GetInstance();

        std::string GetName(int minLength, int maxLength);
        std::string GetCapitalizedName(int minLength, int maxLength);

    protected:

    private:
        bool AddLetterToString(std::string & s, bool canEnd);

        std::map<unsigned char, float> m_first;
        std::map<unsigned char, std::map<unsigned char, float> > m_second;
        std::map<unsigned char, std::map<unsigned char, std::map<unsigned char, float> > > m_third;

        bool m_invalidName;

        NameGenerator();
        static NameGenerator* m_instance;
};

#endif // NAMEGENERATOR_H
