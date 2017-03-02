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

Entity* EnemyFactory::GetEntity(EnemyList type, int lvl)
{
    Entity* ret = nullptr;

    switch(type)
    {
    case EnemyListBat:
    {
        //Exp to give after Battle
        ret = new Entity(10);
        ret->InitAllAttributes(11 + lvl,9 + lvl,7 + lvl,2 + lvl/3,7 + lvl,6 + lvl/2,9 + lvl);
        ret->SetBattleSprite(TextureList::BatBattleSprite);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(4)->GetEffectWithValue(2 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListDeadWizard:
    {

        //Exp to give after Battle
        ret = new Entity(20);
        ret->InitAllAttributes(28 + lvl*2,35 + lvl*3,7 + lvl,14 + lvl,11 + lvl,15 + lvl,14 + lvl);
        ret->SetBattleSprite(TextureList::DeadWizardBattleSprite);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(1)->GetEffectWithValue(10 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListStoneGolem:
    {

        //Exp to give after Battle
        ret = new Entity(15);
        ret->InitAllAttributes(28 + lvl*2,10 + lvl,5 + lvl/2,5 + lvl/2,16 + lvl,15 + lvl,10 + lvl);
        ret->SetBattleSprite(TextureList::StoneGolemBattleSprite);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeam;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(1)->GetEffectWithValue(4 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    }

    if(ret == nullptr)
    {
        std::string msg = "Cannot create Enemy with Type: ";
        msg.append(std::to_string(type));
        throw InvalidArgumentException(msg);
    }
    return ret;
}
