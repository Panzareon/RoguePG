#include "EffectFactoryList.h"
#include "InvalidArgumentException.h"
#include "Entity.h"
#include "Enums.h"
#include <random>

namespace EffectFunctions
{
    //targets:
    //Strength: one value with strength of dmg
    void DealMagicDmg(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::AttackType type = BattleEnums::AttackTypePhysical)
    {
        for(int i = 0; i < targets->size(); i++)
        {
            targets->at(i)->GetHit(strength->at(0) * user->GetAttribute(BattleEnums::AttributeInt), type, false);
            //TODO: Animation
        }
    }
}
namespace EffectStrengthFunctions
{
    //Generate Strength vector with one Value
    std::vector<float>* Multiply(float value, BattleEnums::Target target, float multiplyWith, float minValue, float maxValue)
    {
        if(target == BattleEnums::TargetEnemyTeam || target == BattleEnums::TargetOwnTeam)
        {
            value /= 3.0f;
        }
        else if(target == BattleEnums::TargetAll)
        {
            value /= 6.0f;
        }
        if(multiplyWith * minValue > value)
        {
            return new std::vector<float>(1, minValue);
        }
        else if(multiplyWith * maxValue < value)
        {
            return new std::vector<float>(1, maxValue);
        }
        return new std::vector<float>(1, value / multiplyWith);

    }
    //To generate Strength vectors for more than one Strength Value
    std::vector<float>* MultiplyAndAddResult(float value, BattleEnums::Target target, std::vector<float> multiplyWith, std::vector<float> maxValue, std::vector<float> minValue)
    {
        if(target == BattleEnums::TargetEnemyTeam || target == BattleEnums::TargetOwnTeam)
        {
            value /= 3.0f;
        }
        else if(target == BattleEnums::TargetAll)
        {
            value /= 6.0f;
        }

        float minV = 0.0f;
        float maxV = 0.0f;

        for(int i = 0; i < multiplyWith.size(); i++)
        {
            minV += minValue[i] * multiplyWith[i];
            maxV += maxValue[i] * multiplyWith[i];
        }

        //if getting nr to actually get the value is impossible return closed to it
        if(minV > value)
        {
            return &minValue;
        }
        if(maxV < value)
        {
            return &maxValue;
        }

        //calculate random values and check if for the last a correct is still possible
        bool finished;
        float retVal[multiplyWith.size()];
        float calculatedValue;
        do
        {
            finished = true;
            calculatedValue = 0.0f;
            int lastValueId = multiplyWith.size() - 1;
            for(int i = 0; i < lastValueId; i++)
            {
                retVal[i] = minValue[i] + (maxValue[i] - minValue[i]) * ((float)std::rand() / RAND_MAX);
                calculatedValue += retVal[i] * multiplyWith[i];
            }
            retVal[lastValueId] = (value - calculatedValue) / multiplyWith[lastValueId];
            if(retVal[lastValueId] < minValue[lastValueId] || retVal[lastValueId] > maxValue[lastValueId])
            {
                finished = false;
            }
        }
        while(!finished);
        return new std::vector<float>(retVal, retVal + multiplyWith.size());
    }
}
EffectFactoryList* EffectFactoryList::m_instance = 0;


EffectFactoryList::EffectFactoryList()
{
    //ctor
    //Add all the Effects for the game
    std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>* func;
    std::function<std::vector<float>*(float, BattleEnums::Target)>* valueToStrength;

    //Add Fire Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeFire));
    valueToStrength = new std::function<std::vector<float>*(float, BattleEnums::Target)>(std::bind(&EffectStrengthFunctions::Multiply,std::placeholders::_1,std::placeholders::_2, 1.0f, 1.0f, 100.0f));

    EffectFactory* newEffect = new EffectFactory(func, valueToStrength);
    newEffect->AddAttackType(BattleEnums::AttackTypeFire);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);;

    //Add Air Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeAir));
    valueToStrength = new std::function<std::vector<float>*(float, BattleEnums::Target)>(std::bind(&EffectStrengthFunctions::Multiply,std::placeholders::_1,std::placeholders::_2, 1.0f, 1.0f, 100.0f));

    newEffect = new EffectFactory(func, valueToStrength);
    newEffect->AddAttackType(BattleEnums::AttackTypeAir);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);;

    //Add Water Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeWater));
    valueToStrength = new std::function<std::vector<float>*(float, BattleEnums::Target)>(std::bind(&EffectStrengthFunctions::Multiply,std::placeholders::_1,std::placeholders::_2, 1.0f, 1.0f, 100.0f));

    newEffect = new EffectFactory(func, valueToStrength);
    newEffect->AddAttackType(BattleEnums::AttackTypeWater);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);

    //Add Earth Damage
    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeEarth));
    valueToStrength = new std::function<std::vector<float>*(float, BattleEnums::Target)>(std::bind(&EffectStrengthFunctions::Multiply,std::placeholders::_1,std::placeholders::_2, 1.0f, 1.0f, 100.0f));

    newEffect = new EffectFactory(func, valueToStrength);
    newEffect->AddAttackType(BattleEnums::AttackTypeEarth);
    newEffect->AddEffectType(BattleEnums::EffectTypeDamage);
    m_effects.push_back(newEffect);
}

EffectFactoryList::~EffectFactoryList()
{
    //dtor
    for(int i = 0; i < m_effects.size(); i++)
    {
        delete m_effects[i];
    }
}


EffectFactory* EffectFactoryList::getRandom(BattleEnums::AttackType attackType)
{
    int nr = 0;
    for(int i = 0; i < m_effects.size(); i++)
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
    for(int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType))
            if(j == 0)
                return m_effects[i];
            j--;
    }
}

EffectFactory* EffectFactoryList::getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType)
{
    int nr = 0;
    for(int i = 0; i < m_effects.size(); i++)
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
    for(int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType) && m_effects[i]->DoesContainEffectType(effectType))
            if(j == 0)
                return m_effects[i];
            j--;
    }
}

EffectFactory* EffectFactoryList::getRandom(BattleEnums::AttackType attackType, BattleEnums::EffectType effectType, bool needTarget)
{
    int nr = 0;
    for(int i = 0; i < m_effects.size(); i++)
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
    for(int i = 0; i < m_effects.size(); i++)
    {
        if(m_effects[i]->DoesContainAttackType(attackType) && m_effects[i]->DoesContainEffectType(effectType) && m_effects[i]->DoesNeedTarget() == needTarget)
            if(j == 0)
                return m_effects[i];
            j--;
    }
}


EffectFactoryList* EffectFactoryList::GetInstance()
{
    if(m_instance == 0)
    {
        m_instance = new EffectFactoryList();
    }
    return m_instance;
}
