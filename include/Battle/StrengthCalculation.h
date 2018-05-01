#ifndef STRENGTHCALCULATION_H
#define STRENGTHCALCULATION_H

#include <vector>
#include "Controller/Enums.h"

class StrengthCalculation
{
    public:
        StrengthCalculation();
        virtual ~StrengthCalculation();

        void SetMultiplier(float multiplyWith);
        void AddStrengthValue(float minValue, float maxValue, float step = 0.0f);

        std::vector<float>* GetStrengthVector(float value, BattleEnums::Target target);

        float GetValue(std::vector<float>* strength, BattleEnums::Target target);

    protected:

    private:
        float m_multiplyWith;
        std::vector<float> m_minValue;
        std::vector<float> m_maxValue;
        std::vector<float> m_step;

        static float TeamTargetMali;
        static float SelfTargetBoni;
        static float RandomTargetBoni;
        static float AllTargetMali;
};

#endif // STRENGTHCALCULATION_H
