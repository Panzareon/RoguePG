#include "ItemFactory.h"
#include "InvalidArgumentException.h"

ItemFactory* ItemFactory::m_instance = nullptr;

ItemFactory::ItemFactory()
{
    //ctor
    m_equipmentIds[Equipment::MainHand].push_back(1);
    m_equipmentIds[Equipment::MainHand].push_back(2);
    m_equipmentIds[Equipment::MainHand].push_back(3);
    m_equipmentIds[Equipment::MainHand].push_back(4);
    //TODO: init all ItemIds
}

ItemFactory::~ItemFactory()
{
    //dtor
}
ItemFactory* ItemFactory::GetInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new ItemFactory();
    }
    return m_instance;
}

Item* ItemFactory::GetRandomItem(Item::ItemType type)
{
    if(type == Item::ItemTypeEquipment)
        return GetRandomEquipment();
    int random = rand() % m_itemIds[type].size();
    int itemId = m_itemIds[type][random];
    Item* retval = new Item(itemId, type);
    switch(itemId)
    {
        //TODO: Init Item with Id itemId

    default:
        std::string msg("Invalid ItemId ");
        msg.append(std::to_string(itemId));
        msg.append(" given.");
        throw GenericException(msg);
    }
    return retval;
}

Item* ItemFactory::GetRandomEquipment()
{
    int random = rand() % Equipment::EQUIPMENT_POSITION_END;
    return GetRandomEquipment((Equipment::EquipmentPosition) random);
}

Item* ItemFactory::GetRandomEquipment(Equipment::EquipmentPosition pos)
{
    int random = rand() % m_equipmentIds[pos].size();
    int itemId = m_equipmentIds[pos][random];
    Equipment* retval = new Equipment(itemId,pos);
    SkillGenerator* gen = retval->GetSkillGenerator();
    switch(itemId)
    {
    case 1:
        retval->SetAttributeBuff(BattleEnums::AttributeStrength, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, GetRandomInt(5,0));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, GetRandomInt(5,0));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, GetRandomInt(5,0));

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.8f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.09f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.09f);

        gen->AddSkillAttackType(BattleEnums::AttackTypePhysical, 0.8f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeWater, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeEarth, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeAir, 0.05f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.5f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffDefense, 0.2f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 0.3f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.5f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.25f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 0.25f, false);

        retval->SetSkillStrength(10);
        retval->AddSkillsToLearn(GetRandomInt(3,1));
        break;

    case 2:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, GetRandomInt());

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.4f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.1f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.4f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.05f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.05f);

        gen->AddSkillAttackType(BattleEnums::AttackTypePhysical, 0.8f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeWater, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeEarth, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeAir, 0.05f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.1f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffDefense, 0.5f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 0.4f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.3f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.35f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 0.35f, false);

        retval->SetSkillStrength(10);
        retval->AddSkillsToLearn(GetRandomInt(3,1));
        break;

    case 3:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, GetRandomInt(0,5));
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, GetRandomInt());

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.09f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.3f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.1f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.5f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.01f);

        gen->AddSkillAttackType(BattleEnums::AttackTypePhysical, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeWater, 0.35f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeEarth, 0.25f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeAir, 0.3f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.1f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffDefense, 0.1f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 0.8f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.3f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.35f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 0.35f, false);

        retval->SetSkillStrength(10);
        retval->AddSkillsToLearn(GetRandomInt(3,1));
        break;

    case 4:
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, GetRandomInt(5,0));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxMp, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeInt, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, GetRandomInt(5,0));

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.6f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.09f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.29f);

        gen->AddSkillAttackType(BattleEnums::AttackTypePhysical, 0.04f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeWater, 0.24f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 0.24f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeEarth, 0.24f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeAir, 0.24f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.7f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 0.3f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.7f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.15f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 0.15f, false);

        retval->SetSkillStrength(10);
        retval->AddSkillsToLearn(GetRandomInt(3,1));
        break;



        //TODO: Init Equipment with Id itemId
    default:
        std::string msg("Invalid ItemId ");
        msg.append(std::to_string(itemId));
        msg.append(" given.");
        throw GenericException(msg);
    }
    return retval;
}

int ItemFactory::GetRandomInt(int max, int min)
{
    return rand()%(max - min + 1) + min;
}
