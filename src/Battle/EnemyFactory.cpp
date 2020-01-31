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
        ret = new Entity(10 + lvl);
        ret->SetName(localization->GetLocalization("enemy.bat"));
        ret->InitAllAttributes(8 + lvl,9 + lvl,5 + lvl,2 + lvl/3,9 + lvl,6 + lvl/2,9 + lvl);
        ret->SetBattleSprite(TextureList::BatBattleSprite);
        ret->SetResistance(BattleEnums::AttackType::Physical, 0.9f);
        ret->SetResistance(BattleEnums::AttackType::Fire, 0.7f);
        BattleEnums::Target target = BattleEnums::Target::EnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(4)->GetEffectWithValue(2 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListDeadWizard:
    {

        //Exp to give after Battle
        ret = new Entity(20 + lvl);
        ret->SetName(localization->GetLocalization("enemy.dead_wizard"));
        ret->InitAllAttributes(18 + lvl*2,35 + lvl*3,7 + lvl/2,14 + lvl,11 + lvl/2,15 + lvl,14 + lvl/2);
        ret->SetBattleSprite(TextureList::DeadWizardBattleSprite);
        ret->SetResistance(BattleEnums::AttackType::Fire, 0.7f);
        BattleEnums::Target target = BattleEnums::Target::EnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(1)->GetEffectWithValue(10 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListStoneGolem:
    {

        //Exp to give after Battle
        ret = new Entity(15 + lvl);
        ret->SetName(localization->GetLocalization("enemy.stone_golem"));
        ret->InitAllAttributes(18 + lvl*2,10 + lvl,5 + lvl,5 + lvl/2,8 + lvl,7 + lvl,10 + lvl);
        ret->SetBattleSprite(TextureList::StoneGolemBattleSprite);
        ret->SetResistance(BattleEnums::AttackType::Physical, 2.0f);
        ret->SetResistance(BattleEnums::AttackType::Earth, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Water, 0.7f);
        ret->SetResistance(BattleEnums::AttackType::Fire, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Air, 1.2f);
        BattleEnums::Target target = BattleEnums::Target::EnemyTeam;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(1)->GetEffectWithValue(4 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListWindEye:
    {

        //Exp to give after Battle
        ret = new Entity(10 + lvl);
        ret->SetName(localization->GetLocalization("enemy.wind_eye"));
        ret->InitAllAttributes(10 + lvl,9 + lvl,5 + lvl,12 + lvl,6 + lvl/2,9 + lvl,9 + lvl);
        ret->SetBattleSprite(TextureList::WindEyeBattleSprite);
        ret->SetResistance(BattleEnums::AttackType::Physical, 0.9f);
        ret->SetResistance(BattleEnums::AttackType::Earth, 0.7f);
        ret->SetResistance(BattleEnums::AttackType::Fire, 0.9f);
        ret->SetResistance(BattleEnums::AttackType::Air, 1.3f);
        BattleEnums::Target target = BattleEnums::Target::EnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(2)->GetEffectWithValue(6 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListWaterSlime:
    {

        //Exp to give after Battle
        ret = new Entity(10 + lvl);
        ret->SetName(localization->GetLocalization("enemy.water_slime"));
        ret->InitAllAttributes(7 + lvl*3,9 + lvl,3 + lvl/3,3 + lvl*2,6 + lvl*2,3 + lvl/3,7 + lvl);
        ret->SetBattleSprite(TextureList::WaterSlimeBattleSprite);
        ret->SetResistance(BattleEnums::AttackType::Physical, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Earth, 1.3f);
        ret->SetResistance(BattleEnums::AttackType::Water, 1.3f);
        ret->SetResistance(BattleEnums::AttackType::Fire, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Air, 1.2f);
        BattleEnums::Target target = BattleEnums::Target::EnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(3)->GetEffectWithValue(3 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListIceGolem:
    {

        //Exp to give after Battle
        ret = new Entity(20 + lvl);
        ret->SetName(localization->GetLocalization("enemy.ice_golem"));
        ret->InitAllAttributes(30 + lvl*3,35 + lvl*3,10 + lvl,7 + lvl/2,12 + lvl,20 + lvl*2,7 + lvl/2);
        ret->SetBattleSprite(TextureList::IceGolemBattleSprite);
        ret->SetResistance(BattleEnums::AttackType::Physical, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Water, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Fire, 0.5f);
        ret->SetResistance(BattleEnums::AttackType::Air, 1.3f);
        BattleEnums::Target target = BattleEnums::Target::EnemyTeam;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(3)->GetEffectWithValue(4 + lvl,target),true);
        ret->AddSkill(sk);
        break;
    }
    case EnemyListIceSpirit:
    {

        //Exp to give after Battle
        ret = new Entity(10 + lvl);
        ret->SetName(localization->GetLocalization("enemy.ice_spirit"));
        ret->InitAllAttributes(10 + lvl*2,25 + lvl*2,7 + lvl,9 + lvl,8 + lvl,16 + lvl*2,8 + lvl);
        ret->SetBattleSprite(TextureList::IceSpiritBattleSprite);
        ret->SetResistance(BattleEnums::AttackType::Physical, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Water, 1.5f);
        ret->SetResistance(BattleEnums::AttackType::Fire, 0.5f);
        ret->SetResistance(BattleEnums::AttackType::Air, 1.3f);
        BattleEnums::Target target = BattleEnums::Target::EnemyTeamEntity;
        Skill* sk = new Skill(target);
        sk->AddEffect(EffectFactoryList::GetInstance()->getWithId(3)->GetEffectWithValue(4 + lvl,target),true);
        ret->AddSkill(sk);
        target = BattleEnums::Target::EnemyTeamEntity;
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
