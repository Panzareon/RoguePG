#include "Battle/StrengthCalculation.h"
#include <random>

//Define Muliplier for Value if More Entities can be targeted
float StrengthCalculation::SelfTargetBoni = 1.5f;
float StrengthCalculation::RandomTargetBoni = 2.0f;
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

void StrengthCalculation::AddStrengthValue(float minValue, float maxValue, float step, float multiplier, CombiningType type)
{
    m_minValue.push_back(minValue);
    m_maxValue.push_back(maxValue);
    m_step.push_back(step);
    m_multiply.push_back(multiplier);
    m_combiningType.push_back(type);
}

void StrengthCalculation::SetMultiplier(float multiplyWith)
{
    m_multiplyWith = multiplyWith;
}

float StrengthCalculation::GetValue(std::vector<float>* strength, BattleEnums::Target target)
{
    bool firstValue = true;
    float value = 1.0f;
    for(unsigned int i = 0; i < m_minValue.size(); i++)
    {
        if(firstValue)
        {
            value = strength->at(i) * m_multiply[i];
            firstValue = false;
        }
        else
        {
            switch(m_combiningType[i])
            {
                case MULTIPLY:
                    value *= strength->at(i) * m_multiply[i];
                    break;
                case ADD:
                    value += strength->at(i) * m_multiply[i];
                    break;
            }
        }
    }

    value *= m_multiplyWith;

    if(target == BattleEnums::TargetEnemyTeam || target == BattleEnums::TargetOwnTeam)
    {
        value *= TeamTargetMali;
    }
    else if(target == BattleEnums::TargetAll)
    {
        value *= AllTargetMali;
    }
    else if(target == BattleEnums::TargetSelf)
    {
        value /= SelfTargetBoni;
    }
    else if(target == BattleEnums::TargetOwnTeamRandomEntity || target == BattleEnums::TargetEnemyTeamRandomEntity)
    {
        value /= RandomTargetBoni;
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
    else if(target == BattleEnums::TargetSelf)
    {
        value *= SelfTargetBoni;
    }
    else if(target == BattleEnums::TargetOwnTeamRandomEntity || target == BattleEnums::TargetEnemyTeamRandomEntity)
    {
        value *= RandomTargetBoni;
    }

    value /= m_multiplyWith;


    bool firstValue = true;
    float minV = 1.0f;
    float maxV = 1.0f;
    for(unsigned int i = 0; i < m_minValue.size(); i++)
    {
        if(firstValue)
        {
            minV = m_minValue[i] * m_multiply[i];
            maxV = m_maxValue[i] * m_multiply[i];
            firstValue = false;
        }
        else
        {
            switch(m_combiningType[i])
            {
                case MULTIPLY:
                        minV *= m_minValue[i] * m_multiply[i];
                        maxV *= m_maxValue[i] * m_multiply[i];
                    break;
                case ADD:
                        minV += m_minValue[i] * m_multiply[i];
                        maxV += m_maxValue[i] * m_multiply[i];
                    break;
            }
        }
    }

    //if getting nr to actually get the value is impossible return closed to it
    if(minV >= value)
    {
        return new std::vector<float>(m_minValue.begin(), m_minValue.end());
    }
    if(maxV <= value)
    {
        return new std::vector<float>(m_maxValue.begin(), m_maxValue.end());
    }

    //calculate random values and check if for the last a correct is still possible
    bool finished;
    std::vector<float>* retVal = new std::vector<float>(m_minValue.size());
    float calculatedValue;
    int lastValueId = m_minValue.size() - 1;
    do
    {
        finished = true;
        calculatedValue = 1;
        for(int i = 0; i < lastValueId; i++)
        {
            if(m_step[i] == 0.0f)
                (*retVal)[i] = m_minValue[i] + (m_maxValue[i] - m_minValue[i]) * ((float)std::rand() / RAND_MAX);
            else
            {
                int steps = (m_maxValue[i] - m_minValue[i]) / m_step[i] + 1;
                (*retVal)[i] = m_minValue[i] + m_step[i] * (std::rand() % steps);
            }

            if(i == 0)
            {
                calculatedValue = (*retVal)[i] * m_multiply[i];
            }
            else
            {
                switch(m_combiningType[i])
                {
                    case MULTIPLY:
                        calculatedValue *= (*retVal)[i] * m_multiply[i];
                        break;
                    case ADD:
                        calculatedValue += (*retVal)[i] * m_multiply[i];
                        break;
                }
            }
        }

        switch(m_combiningType[lastValueId])
        {
            case MULTIPLY:
                (*retVal)[lastValueId] = (value / calculatedValue) / m_multiply[lastValueId];
                break;
            case ADD:
                (*retVal)[lastValueId] = (value - calculatedValue) / m_multiply[lastValueId];
                break;
        }

        if((*retVal)[lastValueId] < m_minValue[lastValueId] || (*retVal)[lastValueId] > m_maxValue[lastValueId])
        {
            finished = false;
        }
    }
    while(!finished);
    if(m_step[lastValueId] != 0.0f)
    {
        //Check which Step ist closest to given Value
        int steps = (int)((*retVal)[lastValueId] - m_minValue[lastValueId]) / m_step[lastValueId];
        float lowerValue = m_minValue[lastValueId] + steps * m_step[lastValueId];
        float upperValue = lowerValue + m_step[lastValueId];
        if((*retVal)[lastValueId] - lowerValue < upperValue - (*retVal)[lastValueId])
            (*retVal)[lastValueId] = lowerValue;
        else
            (*retVal)[lastValueId] = upperValue;
    }
    return retVal;
}
