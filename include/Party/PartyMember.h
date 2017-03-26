#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include "Battle/Entity.h"
#include "Party/Equipment.h"
#include "CharacterClass.h"
#include <cereal/types/map.hpp>


class PartyMember : public Entity
{
    public:
        PartyMember();
        PartyMember(CharacterClass* chrClass);

        void SetCharacterClass(CharacterClass* chrClass);
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
        CharacterClass* GetClass() const;

        void SaveBeforeEquipping();
        void ResetAfterEquipping();

        bool ShowEnemyHealth();
        float MovementSpeed(float base);


        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            CharacterClass::CharacterClassEnum characterClass = m_chrClass->GetClassType();
            archive(m_hp, m_mp,m_lvl, m_exp, characterClass, m_attributes, m_resistances);
        }

        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            CharacterClass::CharacterClassEnum characterClass;
            archive(m_hp, m_mp,m_lvl, m_exp, characterClass, m_attributes, m_resistances);
            SetCharacterClass(CharacterClass::GetCharacterClass(characterClass));
        }
    protected:
        void Init();
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
