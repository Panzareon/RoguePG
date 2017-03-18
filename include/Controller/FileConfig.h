#ifndef FILECONFIG_H
#define FILECONFIG_H

#include <string>
#include <map>

class FileConfig
{
    public:
        FileConfig();
        virtual ~FileConfig();

    protected:
        void UpdateKey(std::string key, std::string value, bool safeToFile = false);

        std::string GetString(std::string key);
        void LoadFromFile(std::string filename);
        std::string m_filename;
        std::map<std::string, std::string> m_values;

    private:
};

#endif // FILECONFIG_H
