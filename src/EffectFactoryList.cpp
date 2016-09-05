#include "EffectFactoryList.h"
#include "Entity.h"
#include "Enums.h"
#include <random>

namespace EffectFunctions
{
    //targets:
    //Strength: 1 value with strength of dmg
    void DealMagicDmg(std::vector<float>* strength, Entity* user, std::vector<Entity*>* targets, BattleEnums::AttackType type = BattleEnums::AttackTypePhysical)
    {
        for(int i = 0; i < targets->size(); i++)
        {
            targets->at(i)->GetHit(strength->at(1) * user->GetInt(), type);
            //TODO: Animation
        }
    }
}
namespace EffectStrengthFunctions
{
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


    func = new std::function<void(std::vector<float>* strength, Entity* user, std::vector<Entity*>*targets)>(std::bind(&EffectFunctions::DealMagicDmg,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, BattleEnums::AttackTypeFire));
    valueToStrength = new std::function<std::vector<float>*(float, BattleEnums::Target)>(std::bind(&EffectStrengthFunctions::MultiplyAndAddResult,std::placeholders::_1,std::placeholders::_2, std::vector<float>(1, 1.0f), std::vector<float>(1,1.0f), std::vector<float>(1,100.0f)));

    EffectFactory* newEffect = new EffectFactory(func, valueToStrength);
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

EffectFactory* EffectFactoryList::getRandom()
{
    int i = rand() % m_effects.size();
    return m_effects[i];
}


EffectFactoryList* EffectFactoryList::GetInstance()
{
    if(m_instance == 0)
    {
        m_instance = new EffectFactoryList();
    }
    return m_instance;
}
