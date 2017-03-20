#include "Battle/Effect.h"
#include "Controller/GameController.h"
#include "Controller/Localization.h"
#include "Battle/EffectFactory.h"
#include <sstream>

Effect::Effect(EffectFactory* factory, std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, Effect* effect)>* func, std::vector<float>* strength, StrengthCalculation* strengthCalculation, BattleEnums::Target target)
{
    m_effectFunction = func;
    m_strength = strength;
    m_strengthCalculation = strengthCalculation;
    m_defaultTarget = target;
    m_factory = factory;
}

Effect::~Effect()
{
    //dtor
    delete m_strength;
}
void Effect::UseEffectOn(Entity* user, std::vector<Entity* >* targets)
{
    if(m_defaultTarget == BattleEnums::TargetSelf)
    {
        std::vector<Entity* >* target = new std::vector<Entity* >(1, user);
        //Use the Effect
        (*m_effectFunction)(m_strength, user, target, this);
        //Play the Animation for this effect
        Animation * newAnim = AnimationFactory::GetAnimation(m_anim, target);
        GameController::getInstance()->GetActiveSceneManager()->AddAnimation(newAnim);
    }
    else
    {
        //Use the Effect
        (*m_effectFunction)(m_strength, user, targets, this);
        //Play the Animation for this effect
        Animation * newAnim = AnimationFactory::GetAnimation(m_anim, targets);
        GameController::getInstance()->GetActiveSceneManager()->AddAnimation(newAnim);
    }
}

float Effect::GetValue()
{
    return m_strengthCalculation->GetValue(m_strength, m_defaultTarget);
}

EffectFactory* Effect::GetFactory()
{
    return m_factory;
}

std::string Effect::GetName()
{
    std::stringstream out;
    out << "effect." << GetFactory()->GetId();
    return out.str();
}

std::string Effect::GetLocalizedDescription()
{
    std::stringstream out;
    out << GetName() << ".desc";
    return Localization::GetInstance()->GetLocalizationWithFloats(out.str(), m_strength);
}

void Effect::SetAnimation(AnimationFactory::AnimationList anim)
{
    m_anim = anim;
}

