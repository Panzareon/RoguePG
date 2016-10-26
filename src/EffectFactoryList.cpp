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
}

namespace EffectFunctions
{
    //Strength: one value with strength of dmg
    void DealMagicDmg(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::AttackType type = BattleEnums::AttackTypePhysical)
    {
        for(unsigned int i = 0; i < targets->size(); i++)
        {
            Attack att(strength->at(0) + user->GetAttribute(BattleEnums::AttributeInt), type, false);
            user->AttackEntity(targets->at(i), &att);
            //TODO: Animation
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
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);;

    //Add Air Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeAir));
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);;

    //Add Water Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeWater));
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);

    //Add Earth Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeEarth));
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    calc->AddStrengthValue(1.0f, 100.0f);
    calc->SetMultiplier(1.0f);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);

    //Add Strength Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeStrength));
    newEffect = new EffectFactory(func);
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
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    //Strength Buff fits Fire and Earth or Physical
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Add Magic defense Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeMagicDefense));
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    //Strength Buff fits Fire and Earth or Physical
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffDefense);
    m_effects.push_back(newEffect);

    //Add Int Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeInt));
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    //Strength Buff fits Fire and Earth or Physical
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffMagic);
    m_effects.push_back(newEffect);

    //Add Speed Buff
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::BuffAttribute,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttributeSpeed));
    newEffect = new EffectFactory(func);
    calc = newEffect->GetStrengthCalculation();
    //Number of turns: from 2 to 10 with step of 1
    calc->AddStrengthValue(2.0f, 10.0f, 1.0f);
    //Everything from 5% to 300% buff
    calc->AddStrengthValue(0.05f, 3.0f);
    calc->SetMultiplier(25.0f);
    //Strength Buff fits Fire and Earth or Physical
    newEffect->AddAttackType(BattleEnums::AttackTypePhysical);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuff);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffOffense);
    newEffect->AddEffectType(BattleEnums::EffectTypeBuffMagic);
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


EffectFactory* EffectFactoryList::getRandom(BattleEnums::AttackType attackType)
{
    int nr = 0;
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType))
            nr++;
    }
    if(nr == 0)
    {
        std::string msg = "No Effect with the AttackType:";
        msg.append(std::to_string(attackType));
        msg.append(" avaliable!");
        throw InvalidArgumentException(msg);
    }
    int j = rand() % nr;
    for(unsigned int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType))
            if(j == 0)
                return m_effects[i];
            j--;
    }
    throw InvalidArgumentException("EffectFactory not found");
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
            if(j == 0)
                return m_effects[i];
            j--;
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


EffectFactoryList* EffectFactoryList::GetInstance()
{
    if(m_instance == 0)
    {
        m_instance = new EffectFactoryList();
    }
    return m_instance;
}
