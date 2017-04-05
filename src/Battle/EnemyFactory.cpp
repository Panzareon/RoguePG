#include "Battle/EnemyFactory.h"
#include "Battle/EffectFactoryList.h"
#include "Exception/InvalidArgumentException.h"
#include "Controller/Localization.h"

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
    Localization* localization = Localization::GetInstance();

    switch(type)
    {
    case EnemyListBat:
    {
        //Exp to give after Battle
        ret = new Entity(10);
        ret->SetName(localization->GetLocalization("enemy.bat"));
        ret->InitAllAttributes(13 + lvl,9 + lvl,7 + lvl,2 + lvl/3,9 + lvl,6 + lvl/2,9 + lvl);
        ret->SetBattleSprite(TextureList::BatBattleSprite);
        ret->SetResistance(BattleEnums::AttackTypePhysical, 0.9f);
        ret->SetResistance(BattleEnums::AttackTypeFire, 0.7f);
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
        ret->SetName(localization->GetLocalization("enemy.dead_wizard"));
        ret->InitAllAttributes(28 + lvl*2,35 + lvl*3,7 + lvl,14 + lvl,11 + lvl,15 + lvl,14 + lvl);
        ret->SetBattleSprite(TextureList::DeadWizardBattleSprite);
        ret->SetResistance(BattleEnums::AttackTypeFire, 0.7f);
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
        ret->SetName(localization->GetLocalization("enemy.stone_golem"));
        ret->InitAllAttributes(28 + lvl*2,10 + lvl,5 + lvl/2,5 + lvl/2,8 + lvl,7 + lvl,10 + lvl);
        ret->SetBattleSprite(TextureList::StoneGolemBattleSprite);
        ret->SetResistance(BattleEnums::AttackTypePhysical, 2.0f);
        ret->SetResistance(BattleEnums::AttackTypeEarth, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeWater, 0.7f);
        ret->SetResistance(BattleEnums::AttackTypeFire, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeAir, 1.2f);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeam;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(1)->GetEffectWithValue(4 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListWindEye:
    {

        //Exp to give after Battle
        ret = new Entity(10);
        ret->SetName(localization->GetLocalization("enemy.wind_eye"));
        ret->InitAllAttributes(10 + lvl,9 + lvl,5 + lvl,12 + lvl,6 + lvl/2,9 + lvl,9 + lvl);
        ret->SetBattleSprite(TextureList::WindEyeBattleSprite);
        ret->SetResistance(BattleEnums::AttackTypePhysical, 0.9f);
        ret->SetResistance(BattleEnums::AttackTypeEarth, 0.7f);
        ret->SetResistance(BattleEnums::AttackTypeFire, 0.9f);
        ret->SetResistance(BattleEnums::AttackTypeAir, 1.3f);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(2)->GetEffectWithValue(6 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListWaterSlime:
    {

        //Exp to give after Battle
        ret = new Entity(10);
        ret->SetName(localization->GetLocalization("enemy.water_slime"));
        ret->InitAllAttributes(13 + lvl*2,9 + lvl,3 + lvl/3,7 + lvl,12 + lvl,3 + lvl/3,7 + lvl);
        ret->SetBattleSprite(TextureList::WaterSlimeBattleSprite);
        ret->SetResistance(BattleEnums::AttackTypePhysical, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeEarth, 1.3f);
        ret->SetResistance(BattleEnums::AttackTypeWater, 1.3f);
        ret->SetResistance(BattleEnums::AttackTypeFire, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeAir, 1.2f);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(3)->GetEffectWithValue(3 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListIceGolem:
    {

        //Exp to give after Battle
        ret = new Entity(20);
        ret->SetName(localization->GetLocalization("enemy.ice_golem"));
        ret->InitAllAttributes(30 + lvl*3,35 + lvl*3,10 + lvl,7 + lvl,12 + lvl,20 + lvl*2,7 + lvl);
        ret->SetBattleSprite(TextureList::IceGolemBattleSprite);
        ret->SetResistance(BattleEnums::AttackTypePhysical, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeWater, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeFire, 0.5f);
        ret->SetResistance(BattleEnums::AttackTypeAir, 1.3f);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeam;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(3)->GetEffectWithValue(4 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListIceSpirit:
    {

        //Exp to give after Battle
        ret = new Entity(10);
        ret->SetName(localization->GetLocalization("enemy.ice_spirit"));
        ret->InitAllAttributes(10 + lvl*2,25 + lvl*2,7 + lvl,9 + lvl,8 + lvl,16 + lvl*2,8 + lvl);
        ret->SetBattleSprite(TextureList::IceSpiritBattleSprite);
        ret->SetResistance(BattleEnums::AttackTypePhysical, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeWater, 1.5f);
        ret->SetResistance(BattleEnums::AttackTypeFire, 0.5f);
        ret->SetResistance(BattleEnums::AttackTypeAir, 1.3f);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(3)->GetEffectWithValue(4 + lvl,target),true);
        ret->AddSkill(sk);
        BattleEnums::Target target = BattleEnums::TargetEnemyTeamEntity;
        sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(10005)->GetEffectWithValue(4 + lvl,target),true);
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
