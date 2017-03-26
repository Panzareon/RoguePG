#include "Battle/Effect.h"
#include "Controller/GameController.h"
#include "Battle/EffectFactoryBase.h"

Effect::Effect(EffectFactoryBase* factory, std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, NamedItem* effect)>* func, std::vector<float>* strength, float value, BattleEnums::Target target)
                :EffectBase(factory,strength,value,target)
{
    m_effectFunction = func;
}

Effect::~Effect()
{
    //dtor
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

void Effect::SetAnimation(AnimationFactory::AnimationList anim)
{
    m_anim = anim;
}
