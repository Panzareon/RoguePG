#include "EnemyFactory.h"
#include "InvalidArgumentException.h"

EnemyFactory::EnemyFactory()
{
    //ctor
}

EnemyFactory::~EnemyFactory()
{
    //dtor
}

Entity* EnemyFactory::GetEntity(EnemyList type)
{
    Entity* ret = nullptr;

    switch(type)
    {
    case EnemyListBat:
        ret = new Entity();
        ret->InitAllAttributes(10,5,2,5,6);
        //TODO: ret->SetBattleSprite()
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        Skill* sk = new Skill(ret,target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(3)->GetEffectWithValue(2,target),true);
        ret->AddSkill()
        break;
    }

    if(ret == nullptr)
    {
        std::string msg = "Cannot create Enemy with Type: ";
        msg.append(std::to_string(type));
        throw InvalidArgumentException(msg);
    }
    return ret;
}
