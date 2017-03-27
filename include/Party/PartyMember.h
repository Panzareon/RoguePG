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
        void SetEquipment(Equipment::EquipmentPosition position, std::shared_ptr<Equipment> equipment = nullptr);
        std::shared_ptr<Equipment> GetEquipment(Equipment::EquipmentPosition position);
        CharacterClass* GetClass() const;

        void SaveBeforeEquipping();
        void ResetAfterEquipping();

        bool ShowEnemyHealth();
        float MovementSpeed(float base);


        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            CharacterClass::CharacterClassEnum characterClass = m_chrClass->GetClassType();
            archive(m_name, m_hp, m_mp,m_lvl, m_exp, characterClass, m_attributes, m_resistances, m_skills, m_equipment, m_teamId, m_battleSpriteTexture);
        }

        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            CharacterClass::CharacterClassEnum characterClass;
            std::vector<std::shared_ptr<Skill>> m_skills;
            std::map<Equipment::EquipmentPosition, std::shared_ptr<Equipment>> m_equipment;
            archive(m_name, m_hp, m_mp,m_lvl, m_exp, characterClass, m_attributes, m_resistances, m_skills, m_equipment, m_teamId, m_battleSpriteTexture);
            SetCharacterClass(CharacterClass::GetCharacterClass(characterClass));
            SetBattleSprite(m_battleSpriteTexture);
            for(int i = 0; i < m_skills.size(); i++)
            {
                AddSkill(m_skills[i]);
            }
            for(auto it = m_equipment.begin(); it != m_equipment.end(); it++)
            {
                SetEquipment(it->first, it->second);
            }
        }
    protected:
        void Init();
        int m_exp;
        int m_lvl;
        float m_neededExpMultiplier;

        //For changing Equipment
        float m_missingHp;
        float m_missingMp;
        std::map<Equipment::EquipmentPosition, std::shared_ptr<Equipment>> m_lastEquipment;


        std::map<Equipment::EquipmentPosition, std::shared_ptr<Equipment>> m_equipment;



        CharacterClass* m_chrClass;
    private:
};

#endif // PARTYMEMBER_H
