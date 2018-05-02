#ifndef SCENEMANAGEREQUIPMENT_H
#define SCENEMANAGEREQUIPMENT_H

#include "SceneManager.h"
#include "Controller/Enums.h"
#include "SceneGraph/MenuNodeItems.h"
#include "SceneGraph/TextNode.h"
#include "AttributeNodesDisplay.h"
#include <map>

class PartyMember;
class Equipment;

class SceneManagerEquipment : AttributeNodesDisplay, public SceneManager
{
    public:
        SceneManagerEquipment();
        virtual ~SceneManagerEquipment();

        virtual void Tick();
        virtual bool IsFinished();

        virtual void SelectMember(PartyMember* member);
        virtual void SelectEquipment(std::shared_ptr<Equipment> equipment);
        virtual void Equip(std::shared_ptr<Equipment> equipment);
        virtual void SelectEquipmentSkills(bool selected);
        virtual void SelectSkill(Skill* skill);
        virtual void MoveItemPosition(int from, int to);


        //returns true if Scene Manager below should be displayed first
        virtual bool IsTransparent();
        //returns false if Tick should be called for the Scene Manager below
        virtual bool PausesSceneManagerBelow();

    protected:
        void UpdateMemberStats(bool selectedOnly = false);
        void RemoveEquipmentSkillMenu();
        void SetEquipmentSkillMenu(std::shared_ptr<Equipment> equipment);

        void ReSelectEquipment();

        MenuNode* m_mainMenu;
        Node* m_equipmentSkillBase;
        MenuNodeItems<std::shared_ptr<Equipment>>* m_equipmentItems;
        MenuNodeItems<Skill*>* m_equipmentSkills;
        sf::RectangleShape* m_equipmentSkillLearned;
        sf::RectangleShape* m_equipmentSkillLearning;
        Node* m_equipmentSkillLearningNode;
        bool m_equipmentSkillsSelected;
        Equipment::EquipmentPosition m_pos;

        bool m_finished;

        TextNode* m_equipmentDescription;

        //For Equipment menu
        std::shared_ptr<Equipment> m_selectedEquipment;
        int m_maxShownHeroes;
        std::shared_ptr<PartyMember> m_selectedMember;
        std::map<BattleEnums::Attribute, int> m_memberStats;

        Node* m_background;

    private:
};

#endif // SCENEMANAGEREQUIPMENT_H
