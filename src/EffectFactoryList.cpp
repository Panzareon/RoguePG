#include "EffectFactoryList.h"
#include "InvalidArgumentException.h"
#include "Entity.h"
#include "Enums.h"
#include "PassiveEffect.h"
#include <random>

namespace PassiveEffectFunctions
{
    float BuffAttribute(float baseValue,BattleEnums::Attribute attr, float strength, BattleEnums::Attribute toBuff)
    {
        if(toBuff != attr)
            return baseValue;
        return baseValue * (1 + strength);
    }
    float BuffResistance(float baseValue, BattleEnums::AttackType type, float strength, BattleEnums::AttackType toBuff)
    {
        if(toBuff != type)
            return baseValue;
        return baseValue + strength;
    }
    float DebuffAttribute(float baseValue,BattleEnums::Attribute attr, float strength, BattleEnums::Attribute toBuff)
    {
        if(toBuff != attr)
            return baseValue;
        return baseValue * (1 - strength);
    }
    float DebuffResistance(float baseValue, BattleEnums::AttackType type, float strength, BattleEnums::AttackType toBuff)
    {
        if(toBuff != type)
            return baseValue;
        return baseValue - strength;
    }
}

namespace EffectFunctions
{
    //Strength: one value with strength of dmg
    void DealMagicDmg(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::AttackType type = BattleEnums::AttackTypePhysical)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            Attack att(strength->at(0) + user->GetAttribute(BattleEnums::AttributeInt), false, type);
            user->AttackEntity(targets->at(i), &att);
        }
    }

    //Strength: one value with strength of dmg
    void DealPhysicalDmg(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::AttackType type = BattleEnums::AttackTypePhysical)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            Attack att(strength->at(0) + user->GetAttribute(BattleEnums::AttributeStrength), true, type);
            user->AttackEntity(targets->at(i), &att);
        }
    }

    //Strength: one value with strength of heal
    void Heal(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            targets->at(i)->Heal(strength->at(0));
        }
    }

    //Strength: two values, fist: duration in turns, second: strength of Buff
    void BuffAttribute(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::Attribute attribute)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            PassiveEffect* eff = new PassiveEffect(targets->at(i), true, (int)strength->at(0));
            eff->AddAttributeEffect(new std::function<float(float,BattleEnums::Attribute)>(
                std::bind(&PassiveEffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,strength->at(1), attribute)));
        }
    }

    //Strength: two values, fist: duration in turns, second: strength of Buff
    void BuffResistance(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::AttackType type)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            PassiveEffect* eff = new PassiveEffect(targets->at(i), true, (int)strength->at(0));
            eff->AddGetResistance(new std::function<float(float,BattleEnums::AttackType)>(
                std::bind(&PassiveEffectFunctions::BuffResistance,std::placeholders::_1,std::placeholders::_2,strength->at(1), type)));
        }
    }

    //Strength: two values, fist: duration in turns, second: strength of Buff
    void DebuffAttribute(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::Attribute attribute)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            PassiveEffect* eff = new PassiveEffect(targets->at(i), true, (int)strength->at(0));
            eff->AddAttributeEffect(new std::function<float(float,BattleEnums::Attribute)>(
                std::bind(&PassiveEffectFunctions::DebuffAttribute,std::placeholders::_1,std::placeholders::_2,strength->at(1), attribute)));
        }
    }

    //Strength: two values, fist: duration in turns, second: strength of Buff
    void DebuffResistance(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::AttackType type)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            PassiveEffect* eff = new PassiveEffect(targets->at(i), true, (int)strength->at(0));
            eff->AddGetResistance(new std::function<float(float,BattleEnums::AttackType)>(
                std::bind(&PassiveEffectFunctions::DebuffResistance,std::placeholders::_1,std::placeholders::_2,strength->at(1), type)));
        }
    }
}
EffectFactoryList* EffectFactoryList::m_instance = 0;


EffectFactoryList::EffectFactoryList()
{
    //ctor
    //Add all the Effects for the game
    std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>* func;
    StrengthCalculation* calc;
    EffectFactory* newEffect;

    //Add Fire Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeFire));
    newEffect = new EffectFactory(func, 1);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);;

    //Add Air Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeAir));
    newEffect = new EffectFactory(func, 2);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);;

    //Add Water Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeWater));
    newEffect = new EffectFactory(func, 3);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);

    //Add Earth Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeEarth));
    newEffect = new EffectFactory(func, 4);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);

    //Add Physical Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealPhysicalDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypePhysical));
    newEffect = new EffectFactory(func, 5);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);

    //Add Strength Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeStrength));
    newEffect = new EffectFactory(func, 101);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    //Strength Buff fits Fire and Earth or Physical
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffOffense);
    m_effects.push_back(newEffect);

    //Add Defense Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeDefense));
    newEffect = new EffectFactory(func, 102);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Add Magic defense Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeMagicDefense));
    newEffect = new EffectFactory(func, 103);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Add Int Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeInt));
    newEffect = new EffectFactory(func, 104);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffMagic);
    m_effects.push_back(newEffect);

    //Add Speed Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeSpeed));
    newEffect = new EffectFactory(func, 105);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffOffense);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffMagic);
    m_effects.push_back(newEffect);

    //Add Elemental Resistance Buffs
    //Physical Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypePhysical));
    newEffect = new EffectFactory(func, 151);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Water Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeWater));
    newEffect = new EffectFactory(func, 152);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Air Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeAir));
    newEffect = new EffectFactory(func, 153);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Earth Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeEarth));
    newEffect = new EffectFactory(func, 154);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Fire Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeFire));
    newEffect = new EffectFactory(func, 155);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);



    //Heal
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::Heal,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    newEffect = new EffectFactory(func, 1001);
    calc = newEffect->GetStrengthCalculation();
    //Everything from 1 to 30 hp heal
    calc->AddStrengthValue(1.0f, 300.0f, 1.0f);
    calc->SetMultiplier(2.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddEffectType(BattleEnums::EffectTypeHeal);
    m_effects.push_back(newEffect);



    //Add Strength Debuff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeStrength));
    newEffect = new EffectFactory(func, 10001);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Debuff for something between 2 and 66%
    calc->AddStrengthValue(0.02f, 0.66f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffOffense);
    m_effects.push_back(newEffect);

    //Add Defense Debuff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeDefense));
    newEffect = new EffectFactory(func, 10002);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Debuff for something between 2 and 66%
    calc->AddStrengthValue(0.02f, 0.66f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffDefense);
    m_effects.push_back(newEffect);

    //Add Magic Defense Debuff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeMagicDefense));
    newEffect = new EffectFactory(func, 10003);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Debuff for something between 2 and 66%
    calc->AddStrengthValue(0.02f, 0.66f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffDefense);
    m_effects.push_back(newEffect);

    //Add Int Debuff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeInt));
    newEffect = new EffectFactory(func, 10004);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Debuff for something between 2 and 66%
    calc->AddStrengthValue(0.02f, 0.66f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffMagic);
    m_effects.push_back(newEffect);

    //Add Speed Debuff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeSpeed));
    newEffect = new EffectFactory(func, 10005);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Debuff for something between 2 and 66%
    calc->AddStrengthValue(0.02f, 0.66f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffOffense);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffMagic);
    m_effects.push_back(newEffect);


    //Add Elemental Resistance Debuffs
    //Physical Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypePhysical));
    newEffect = new EffectFactory(func, 10051);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 66% debuff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffDefense);
    m_effects.push_back(newEffect);

    //Water Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeWater));
    newEffect = new EffectFactory(func, 10052);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 66% debuff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffDefense);
    m_effects.push_back(newEffect);

    //Air Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeAir));
    newEffect = new EffectFactory(func, 10053);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 66% debuff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffDefense);
    m_effects.push_back(newEffect);

    //Earth Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeEarth));
    newEffect = new EffectFactory(func, 10054);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 66% debuff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffDefense);
    m_effects.push_back(newEffect);

    //Fire Defense
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DebuffResistance,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeFire));
    newEffect = new EffectFactory(func, 10055);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 66% debuff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeDebuffDefense);
    m_effects.push_back(newEffect);
}

EffectFactoryList::~EffectFactoryList()
{
    //dtor
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        delete m_effects[i];
    }
}

EffectFactory* EffectFactoryList::getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType)
{
    int nr = 0;
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType) && m_effects[i]->DoesContainEffectType(effectType))
            nr++;
    }
    if(nr == 0)
    {
        std::string msg = "No Effect with the AttackType:";
        msg.append(std::to_string(attackType));
        msg.append(" and the EffectType:");
        msg.append(std::to_string(effectType));
        msg.append(" avaliable!");
        throw InvalidArgumentException(msg);
    }
    int j = rand() % nr;
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType) && m_effects[i]->DoesContainEffectType(effectType))
        {
            if(j == 0)
                return m_effects[i];
            j--;
        }
    }
    throw InvalidArgumentException("EffectFactory not found");
}

EffectFactory* EffectFactoryList::getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType, bool needTarget)
{
    int nr = 0;
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType) && m_effects[i]->DoesContainEffectType(effectType) && m_effects[i]->DoesNeedTarget() == needTarget)
            nr++;
    }
    if(nr == 0)
    {
        std::string msg = "No Effect with the AttackType:";
        msg.append(std::to_string(attackType));
        msg.append(", the EffectType:");
        msg.append(std::to_string(effectType));
        msg.append(" and the Target:");
        msg.append(std::to_string(needTarget));
        msg.append(" avaliable!");
        throw InvalidArgumentException(msg);
    }
    int j = rand() % nr;
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType) && m_effects[i]->DoesContainEffectType(effectType) && m_effects[i]->DoesNeedTarget() == needTarget)
            if(j == 0)
                return m_effects[i];
            j--;
    }
    throw InvalidArgumentException("EffectFactory not found");
}

EffectFactory* EffectFactoryList::getWithId(int id)
{
    for(auto it = m_effects.begin(); it != m_effects.end(); it++)
    {
        if((*it)->GetId() == id)
        {
            return *it;
        }
    }
    std::string msg = "No Effect with id:";
    msg.append(std::to_string(id));
    throw InvalidArgumentException(msg);
}


EffectFactoryList* EffectFactoryList::GetInstance()
{
    if(m_instance == 0)
    {
        m_instance = new EffectFactoryList();
    }
    return m_instance;
}
