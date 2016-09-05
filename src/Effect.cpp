#include "Effect.h"

Effect::Effect(std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)>* func, std::vector<float>* strength)
{
    m_effectFunction = func;
    m_strength = strength;
}

Effect::~Effect()
{
    //dtor
    delete m_strength;
}
void Effect::UseEffectOn(Entity* user, std::vector<Entity* >* targets)
{
    (*m_effectFunction)(m_strength, user, targets);
}
