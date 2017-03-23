#include "EffectBase.h"
#include "Battle/EffectFactoryBase.h"
#include <sstream>
#include "Controller/Localization.h"
#include "Exception/InvalidFunctionException.h"

EffectBase::EffectBase(EffectFactoryBase* factory, std::vector<float> *strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target)
{
    //ctor
    m_strength = strength;
    m_strengthCalculation = strengthCalculation;
    m_defaultTarget = target;
    m_factory = factory;
}

EffectBase::~EffectBase()
{
    //dtor
}

float EffectBase::GetValue()
{
    return m_strengthCalculation->GetValue(m_strength, m_defaultTarget);
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

void EffectBase::SetAnimation(AnimationFactory::AnimationList anim)
{
    m_anim = anim;
}

void EffectBase::UseEffectOn(Entity* user, std::vector<Entity*>* targets)
{
    std::string out = "EffectBase::UseEffectOn not available for Effect: ";
    out += std::to_string(GetFactory()->GetId());
    throw InvalidFunctionException(out);
}
