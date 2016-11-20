#include "EnemyFactory.h"
#include "EffectFactoryList.h"
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
        //Exp to give after Battle
        ret = new Entity(10);
        ret->InitAllAttributes(10,5,2,5,6);
        ret->SetBattleSprite(TextureList::BatBattleSprite);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(4)->GetEffectWithValue(2,target),true);
        ret->AddSkill(sk);
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
