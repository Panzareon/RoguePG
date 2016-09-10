#ifndef STRENGTHCALCULATION_H
#define STRENGTHCALCULATION_H

#include <vector>
#include "Enums.h"

class StrengthCalculation
{
    public:
        StrengthCalculation();
        virtual ~StrengthCalculation();

        void AddStrengthValue(float multiplyWith, float minValue, float maxValue);

        std::vector<float>* GetStrengthVector(float value, BattleEnums::Target target);

    protected:

    private:
        std::vector<float> m_multiplyWith;
        std::vector<float> m_minValue;
        std::vector<float> m_maxValue;
};

#endif // STRENGTHCALCULATION_H
