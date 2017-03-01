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
        retval->AddSkillsToLearn(GetRandomInt(2,1));
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
