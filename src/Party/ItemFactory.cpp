#include "Party/ItemFactory.h"
#include "Exception/InvalidArgumentException.h"
#include "Controller/MathHelper.h"

namespace PassiveEffectFunctions
{
    void AddAttackType(Attack* att, Entity* attacker, BattleEnums::AttackType type, bool physical);
    void Heal(Entity* target, IPassiveEffect* passiveEffect, int hp);
    void MultiplyDmg(Attack* att, Entity* attacker, float multiply, bool physical);
}

ItemFactory* ItemFactory::m_instance = nullptr;

ItemFactory::ItemFactory()
{
    //ctor
    m_equipmentIds[Equipment::MainHand][StartingItem].push_back(1);
    m_equipmentIds[Equipment::MainHand][StartingItem].push_back(2);
    m_equipmentIds[Equipment::MainHand][StartingItem].push_back(3);
    m_equipmentIds[Equipment::MainHand][StartingItem].push_back(4);

    m_equipmentIds[Equipment::MainHand][BaseItem].push_back(101);
    m_equipmentIds[Equipment::MainHand][BaseItem].push_back(102);
    m_equipmentIds[Equipment::MainHand][BaseItem].push_back(103);
    m_equipmentIds[Equipment::MainHand][BaseItem].push_back(104);

    m_equipmentIds[Equipment::MainHand][SpecialItem].push_back(1001);
    m_equipmentIds[Equipment::MainHand][SpecialItem].push_back(1101);
    m_equipmentIds[Equipment::MainHand][SpecialItem].push_back(1201);
    m_equipmentIds[Equipment::MainHand][SpecialItem].push_back(1301);
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

Item* ItemFactory::GetRandomItem(Item::ItemType type, ItemRarity rarity)
{
    if(type == Item::ItemTypeEquipment)
        return GetRandomEquipment(rarity);
    int random = rand() % m_itemIds[type][rarity].size();
    int itemId = m_itemIds[type][rarity][random];
    return GetItem(type, itemId);
}

Item* ItemFactory::GetRandomEquipment(ItemRarity rarity)
{
    int random = rand() % Equipment::EQUIPMENT_POSITION_END;
    return GetRandomEquipment((Equipment::EquipmentPosition) random, rarity);
}

Item* ItemFactory::GetRandomEquipment(Equipment::EquipmentPosition pos, ItemRarity rarity)
{
    int random = rand() % m_equipmentIds[pos][rarity].size();
    int itemId = m_equipmentIds[pos][rarity][random];
    return GetEquipment(pos, itemId);
}

Item* ItemFactory::GetItem(Item::ItemType type, int itemId)
{
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

Item* ItemFactory::GetEquipment(Equipment::EquipmentPosition pos, int itemId)
{
    Equipment* retval = new Equipment(itemId,pos);
    SkillGenerator* gen = retval->GetSkillGenerator();

    MathHelper* mathHelper = MathHelper::GetInstance();
    switch(itemId)
    {
    case 1:
        retval->SetAttributeBuff(BattleEnums::AttributeStrength, mathHelper->GetRandomInt(6,3,true));
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(3,0,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(3,0,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(3,0,true));

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
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(3,1,true));

        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::MultiplyDmg,std::placeholders::_1,std::placeholders::_2,1.5f, true)));
        break;

    case 2:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(6,3,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(6,3,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(6,3,true));

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.2f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.1f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.3f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.05f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.05f);
        gen->AddSkillTarget(BattleEnums::TargetPassive, 0.3f);


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
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(3,1,true));
        break;

    case 3:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(3,0,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(6,3,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(6,3,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(6,3,true));

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
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(3,1,true));
        break;

    case 4:
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(3,0,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxMp, mathHelper->GetRandomInt(6,3,true));
        retval->SetAttributeBuff(BattleEnums::AttributeInt, mathHelper->GetRandomInt(6,3,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(3,0,true));

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
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(3,1,true));

        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::MultiplyDmg,std::placeholders::_1,std::placeholders::_2,1.5f, false)));
        break;

    case 101:
        retval->SetAttributeBuff(BattleEnums::AttributeStrength, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(5,2,true));

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

        retval->SetSkillStrength(20);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(4,2,true));

        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::MultiplyDmg,std::placeholders::_1,std::placeholders::_2,1.75f, true)));
        break;

    case 102:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(10,5,true));

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

        retval->SetSkillStrength(20);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(4,2,true));
        break;

    case 103:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(10,5,true));

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

        retval->SetSkillStrength(20);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(4,2,true));
        break;

    case 104:
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxMp, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeInt, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(5,2,true));

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

        retval->SetSkillStrength(20);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(4,2,true));

        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::MultiplyDmg,std::placeholders::_1,std::placeholders::_2,1.75f, false)));
        break;

    case 1001:
        retval->SetAttributeBuff(BattleEnums::AttributeStrength, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(5,2,true));

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.8f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.09f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.09f);

        gen->AddSkillAttackType(BattleEnums::AttackTypePhysical, 0.4f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 0.5f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeEarth, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeAir, 0.05f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.5f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffDefense, 0.2f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 0.3f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.5f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.25f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 0.25f, false);

        retval->SetSkillStrength(30);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(5,2,true));

        retval->SetTypeResistance(BattleEnums::AttackTypeFire, 1.3f);
        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::AddAttackType,std::placeholders::_1,std::placeholders::_2,BattleEnums::AttackTypeFire, true)));
        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::MultiplyDmg,std::placeholders::_1,std::placeholders::_2,2.0f, true)));
        break;

    case 1101:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(10,5,true));

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.4f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.1f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.4f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.05f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.05f);

        gen->AddSkillAttackType(BattleEnums::AttackTypePhysical, 0.4f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 0.5f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeEarth, 0.05f);
        gen->AddSkillAttackType(BattleEnums::AttackTypeAir, 0.05f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.1f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffDefense, 0.5f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 0.4f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.3f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.35f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 0.35f, false);

        retval->SetSkillStrength(30);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(5,2,true));

        retval->SetTypeResistance(BattleEnums::AttackTypeFire, 2.0f);
        break;

    case 1201:
        retval->SetAttributeBuff(BattleEnums::AttributeDefense, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxHp, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(10,5,true));

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

        retval->SetSkillStrength(30);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(5,2,true));

        //Heals 2 hp every turn
        retval->AddOnTurnEffect(new std::function<void(Entity*, IPassiveEffect*)>(
                std::bind(&PassiveEffectFunctions::Heal,std::placeholders::_1,std::placeholders::_2,2)));
        break;

    case 1301:
        retval->SetAttributeBuff(BattleEnums::AttributeMagicDefense, mathHelper->GetRandomInt(5,2,true));
        retval->SetAttributeBuff(BattleEnums::AttributeMaxMp, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeInt, mathHelper->GetRandomInt(10,5,true));
        retval->SetAttributeBuff(BattleEnums::AttributeSpeed, mathHelper->GetRandomInt(5,2,true));

        gen->AddSkillTarget(BattleEnums::TargetEnemyTeamEntity, 0.6f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeam, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetSelf, 0.09f);
        gen->AddSkillTarget(BattleEnums::TargetOwnTeamEntity, 0.01f);
        gen->AddSkillTarget(BattleEnums::TargetEnemyTeam, 0.29f);

        gen->AddSkillAttackType(BattleEnums::AttackTypeFire, 1.0f);
        gen->AddSkillEffectType(BattleEnums::EffectTypeBuffOffense, 0.7f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeHeal, 0.3f, true);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDamage, 0.7f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffOffense, 0.15f, false);
        gen->AddSkillEffectType(BattleEnums::EffectTypeDebuffDefense, 0.15f, false);

        retval->SetSkillStrength(30);
        retval->AddSkillsToLearn(mathHelper->GetRandomInt(5,2,true));
        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::AddAttackType,std::placeholders::_1,std::placeholders::_2,BattleEnums::AttackTypeFire, false)));
        retval->AddAttack(new std::function<void(Attack* att, Entity* attacker)>(
                std::bind(&PassiveEffectFunctions::MultiplyDmg,std::placeholders::_1,std::placeholders::_2,2.0f, false)));
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
