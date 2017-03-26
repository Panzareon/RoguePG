#include "EffectBase.h"
#include "Battle/EffectFactoryBase.h"
#include <sstream>
#include "Controller/Localization.h"
#include "Exception/InvalidFunctionException.h"
#include "Entity.h"

EffectBase::EffectBase(EffectFactoryBase* factory, std::vector<float> *strength, float value, BattleEnums::Target target)
{
    //ctor
    m_strength = strength;
    m_defaultTarget = target;
    m_factory = factory;
    m_value = value;
}

EffectBase::~EffectBase()
{
    //dtor
    delete m_strength;
}

float EffectBase::GetValue()
{
    return m_value;
}

EffectFactoryBase* EffectBase::GetFactory()
{
    return m_factory;
}

std::string EffectBase::GetName()
{
    std::stringstream out;
    out << "effect." << GetFactory()->GetId();
    return out.str();
}

std::string EffectBase::GetLocalizedDescription()
{
    std::stringstream out;
    out << GetName() << ".desc";
    return Localization::GetInstance()->GetLocalizationWithFloats(out.str(), m_strength);
}

void EffectBase::UseEffectOn(Entity* user, std::vector<Entity*>* targets)
{
    std::string out = "EffectBase::UseEffectOn not available for Effect: ";
    out += std::to_string(GetFactory()->GetId());
    throw InvalidFunctionException(out);
}

void EffectBase::AddToPassiveEffect(PassiveEffect* target)
{
    std::string out = "EffectBase::AddToPassiveEffect not available for Effect: ";
    out += std::to_string(GetFactory()->GetId());
    throw InvalidFunctionException(out);
}

std::vector<float>* EffectBase::GetStrength()
{
    return m_strength;
}
