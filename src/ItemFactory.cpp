#include "ItemFactory.h"
#include "InvalidArgumentException.h"

ItemFactory* ItemFactory::m_instance = nullptr;

ItemFactory::ItemFactory()
{
    //ctor
    //TODO: init all ItemIds
    m_equipmentIds[Equipment::MainHand].push_back(1);
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
    int nrSkills;
    switch(itemId)
    {
    case 1:
        retval->SetAttributeBuff(BattleEnums::AttributeStrength, GetRandomInt());
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, GetRandomInt(5,0));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, GetRandomInt(5,0));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, GetRandomInt(5,0));

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.8f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.81f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.9f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.91f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 1.0f);

        gen->AddSkillAttackType(BattleEnums::AttackTypePhysical, 0.8f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeWater, 0.85f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 0.9f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeEarth, 0.95f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeAir, 1.0f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.7f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.8f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffDefense, 0.9f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 1.0f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.5f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 1.0f, false);

        retval->SetSkillStrength(10);
        nrSkills = GetRandomInt(4,2);
        break;


        //TODO: Init Equipment with Id itemId
    default:
        std::string msg("Invalid ItemId ");
        msg.append(std::to_string(itemId));
        msg.append(" given.");
        throw GenericException(msg);
    }
    for(int i = 0; i < nrSkills; i++)
    {
        retval->AddSkillsToLearn(i + 1);
    }
    return retval;
}

int ItemFactory::GetRandomInt(int max, int min)
{
    return rand()%(max - min + 1) + min;
}
