#include "Battle/IPassiveEffect.h"

IPassiveEffect::IPassiveEffect()
{
    //ctor
}

IPassiveEffect::~IPassiveEffect()
{
    //dtor
}

bool IPassiveEffect::IsEquipment()
{
    return false;
}

void IPassiveEffect::OnEffectStart()
{
    //NOOP
}

void IPassiveEffect::OnBattleFinished(Entity* target)
{
    //NOOP
}

