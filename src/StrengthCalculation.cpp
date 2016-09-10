#include "StrengthCalculation.h"
#include <random>

//Define Muliplier for Value if More Entities can be targeted
float StrengthCalculation::TeamTargetMali = 3.0f;
float StrengthCalculation::AllTargetMali = 6.0f;

StrengthCalculation::StrengthCalculation()
{
    //ctor
}

StrengthCalculation::~StrengthCalculation()
{
    //dtor
}

void StrengthCalculation::AddStrengthValue(float multiplyWith, float minValue, float maxValue)
{
    m_multiplyWith.push_back(multiplyWith);
    m_minValue.push_back(minValue);
    m_maxValue.push_back(maxValue);
}

float StrengthCalculation::GetValue(std::vector<float>* strength, BattleEnums::Target target)
{
    float value = 0.0f;
    for(unsigned int i = 0; i < m_multiplyWith.size(); i++)
    {
        value += strength->at(i) * m_multiplyWith.at(i);
    }

    if(target == BattleEnums::TargetEnemyTeam || target == BattleEnums::TargetOwnTeam)
    {
        value *= TeamTargetMali;
    }
    else if(target == BattleEnums::TargetAll)
    {
        value *= AllTargetMali;
    }

    return value;
}

std::vector<float>* StrengthCalculation::GetStrengthVector(float value, BattleEnums::Target target)
{
    if(target == BattleEnums::TargetEnemyTeam || target == BattleEnums::TargetOwnTeam)
    {
        value /= TeamTargetMali;
    }
    else if(target == BattleEnums::TargetAll)
    {
        value /= AllTargetMali;
    }

    float minV = 0.0f;
    float maxV = 0.0f;

    for(unsigned int i = 0; i < m_multiplyWith.size(); i++)
    {
        minV += m_minValue[i] * m_multiplyWith[i];
        maxV += m_maxValue[i] * m_multiplyWith[i];
    }

    //if getting nr to actually get the value is impossible return closed to it
    if(minV > value)
    {
        return new std::vector<float>(m_minValue.begin(), m_minValue.end());
    }
    if(maxV < value)
    {
        return new std::vector<float>(m_maxValue.begin(), m_maxValue.end());
    }

    //calculate random values and check if for the last a correct is still possible
    bool finished;
    float retVal[m_multiplyWith.size()];
    float calculatedValue;
    do
    {
        finished = true;
        calculatedValue = 0.0f;
        int lastValueId = m_multiplyWith.size() - 1;
        for(int i = 0; i < lastValueId; i++)
        {
            retVal[i] = m_minValue[i] + (m_maxValue[i] - m_minValue[i]) * ((float)std::rand() / RAND_MAX);
            calculatedValue += retVal[i] * m_multiplyWith[i];
        }
        retVal[lastValueId] = (value - calculatedValue) / m_multiplyWith[lastValueId];
        if(retVal[lastValueId] < m_minValue[lastValueId] || retVal[lastValueId] > m_maxValue[lastValueId])
        {
            finished = false;
        }
    }
    while(!finished);
    return new std::vector<float>(retVal, retVal + m_multiplyWith.size());
}
