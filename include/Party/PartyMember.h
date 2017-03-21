#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include "Battle/Entity.h"
#include "Party/Equipment.h"

class CharacterClass;


class PartyMember : public Entity
{
    public:
        PartyMember(CharacterClass* chrClass);
        virtual ~PartyMember();
        void AddExp(int ammount);
        void BattleFinished();

        void GetStartingSkills(int nr);
        void LevelUp();
        int GetLevel();
        int GetExp();
        int NeededExp(int lvl);
        float GetExpPercent();
        void SetEquipment(Equipment::EquipmentPosition position, Equipment* equipment = nullptr);
        Equipment* GetEquipment(Equipment::EquipmentPosition position);
        CharacterClass* GetClass();

        void SaveBeforeEquipping();
        void ResetAfterEquipping();
    protected:
        int m_exp;
        int m_lvl;
        float m_neededExpMultiplier;

        //For changing Equipment
        float m_missingHp;
        float m_missingMp;
        std::map<Equipment::EquipmentPosition, Equipment*> m_lastEquipment;


        std::map<Equipment::EquipmentPosition, Equipment*> m_equipment;



        CharacterClass* m_chrClass;
    private:
};

#endif // PARTYMEMBER_H
