#include "Localization.h"
Localization* Localization::m_instance = nullptr;

Localization::Localization()
{
    //ctor
    //TODO: load Localization file
}

Localization::~Localization()
{
    //dtor
}

Localization* Localization::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new Localization();
    return m_instance;
}

std::string Localization::GetLocalization(std::string toLocalize)
{
    //TODO: Get actual Translation

    //If not found return unlocalized string
    return toLocalize;
}
