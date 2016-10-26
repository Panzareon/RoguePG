#include "SceneManagerBattle.h"
#include "GameController.h"
#include "SFML/Graphics.hpp"
#include "TextureList.h"
#include "Configuration.h"
#include "Skill.h"
#include "Localization.h"
#include "EntityNode.h"
#include <iostream>

namespace BattleFunctions
{
    void AttackOnTarget(SceneManagerBattle* sm, BattleEnums::Target targetType, Entity* toAttack, Entity* attacking)
    {
        attacking->AttackEntity(toAttack);
        sm->TurnIsFinished();
    }
    void Attack(SceneManagerBattle* sm, Entity* attacking)
    {
        std::function<void(BattleEnums::Target, Entity*)>* func = new std::function<void(BattleEnums::Target, Entity*)>(std::bind(&AttackOnTarget, sm, std::placeholders::_1, std::placeholders::_2, attacking));
        sm->UseOnTarget(func, BattleEnums::TargetEnemyTeamEntity, attacking);
    }

    void UseSkillOnTarget(SceneManagerBattle* sm, BattleEnums::Target targetType, Entity* toAttack, Entity* attacking, Skill* skill)
    {
        skill->Use(targetType, toAttack);
        sm->TurnIsFinished();
    }

    void UseSkill(SceneManagerBattle* sm, Entity* attacking, Skill* skill)
    {
        BattleEnums::Target target = skill->GetDefaultTarget();
        if(target == BattleEnums::TargetNone)
        {
            skill->Use(target,nullptr);
            sm->TurnIsFinished();
        }
        else
        {
            std::function<void(BattleEnums::Target, Entity*)>* func = new std::function<void(BattleEnums::Target, Entity*)>(std::bind(&UseSkillOnTarget, sm, std::placeholders::_1, std::placeholders::_2, attacking, skill));
            sm->UseOnTarget(func, target, attacking);
        }
    }
    void SkillList(SceneManagerBattle* sm, Entity* attacking)
    {
        //TODO: different width?
        MenuNode* skillMenu = new MenuNode(GameController::getInstance()->GetWindowWidth());
        skillMenu->CancelAvailable(true);

        std::vector<Skill>* skillList = attacking->GetSkillList();
        for(unsigned int i = 0; i < skillList->size(); i++)
        {
            skillMenu->AddOption(skillList->at(i).GetName(),std::function<void()>(std::bind(&UseSkill, sm, attacking, &skillList->at(i))));
        }

        sm->AddSubMenu(skillMenu);
    }
}

SceneManagerBattle::SceneManagerBattle(sf::RenderTarget * target, int windowWidth, int windowHeight): SceneManager(target, windowWidth, windowHeight)
{
    //ctor
    //Build Scene Graph
    m_mainNode = new Node();
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::m_dungeonBattleBackground));
    m_background = new DrawableNode(backgroundSprite);
    m_mainNode->addChild(m_background);
    m_eventLayer = new Node();
    m_animationNode = new Node();
    m_eventLayer->addChild(m_animationNode);
    m_mainNode->addChild(m_eventLayer);
    m_gui = new Node();
    m_mainNode->addChild(m_gui);
    m_mainMenu = new MenuNode(m_windowWidth);
    m_mainMenu->setVisibility(false);
    m_gui->addChild(m_mainMenu);

    m_party = GameController::getInstance()->getParty();


    m_next = 0;
    m_useOnTarget = 0;

    //Setting Startpositions for teams
    //TODO: for more than 2 teams?
    m_posPerTeam.push_back(sf::Vector2f(50,100));
    m_posPerTeam.push_back(sf::Vector2f(GameController::getInstance()->GetWindowWidth() - 100,100));
    m_posChangePerTeam.push_back(sf::Vector2f(40,40));
    m_posChangePerTeam.push_back(sf::Vector2f(-40,40));



    for(auto member : (*m_party->GetActivePartyMembers()))
    {
        AddSpriteForEntity(member);
    }
}

SceneManagerBattle::~SceneManagerBattle()
{
    //dtor
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        delete m_enemies[i];
    }
}

void SceneManagerBattle::UseOnTarget(std::function<void(BattleEnums::Target, Entity*)>* func, BattleEnums::Target defaultTarget, Entity* attacker)
{
    if(m_useOnTarget != 0)
        delete m_useOnTarget;
    m_useOnTarget = func;
    m_targetType = defaultTarget;
    m_targetEntity = 0;
    m_targetNr = 0;
    if(m_targetType == BattleEnums::TargetEnemyTeamEntity)
    {
        m_targetEntity = m_enemies[0];
    }
    else if(m_targetType == BattleEnums::TargetOwnTeamEntity)
    {
        m_targetEntity = m_party->GetActivePartyMembers()->at(0);
    }
    else if(m_targetType == BattleEnums::TargetSelf)
    {
        m_targetEntity = attacker;
    }
}


void SceneManagerBattle::Tick()
{
    GameController* controller = GameController::getInstance();
    //Battle Logic
    if(m_useOnTarget != 0)
    {
        //Selecting target
        if(controller->IsKeyPressed(Configuration::MoveDown))
        {
            if(m_targetType == BattleEnums::TargetEnemyTeamEntity)
            {
                if(m_targetNr < m_enemies.size() - 1)
                {
                    m_targetNr++;
                    m_targetEntity = m_enemies[m_targetNr];
                }
            }
            else if(m_targetType == BattleEnums::TargetOwnTeamEntity)
            {
                if(m_targetNr < m_party->GetActivePartyMembers()->size() - 1)
                {
                    m_targetNr++;
                    m_targetEntity = m_party->GetActivePartyMembers()->at(m_targetNr);
                }
            }
        }
        else if(controller->IsKeyPressed(Configuration::MoveUp))
        {
            if(m_targetType == BattleEnums::TargetEnemyTeamEntity)
            {
                if(m_targetNr > 0)
                {
                    m_targetNr--;
                    m_targetEntity = m_enemies[m_targetNr];
                }
            }
            else if(m_targetType == BattleEnums::TargetOwnTeamEntity)
            {
                if(m_targetNr > 0)
                {
                    m_targetNr--;
                    m_targetEntity = m_party->GetActivePartyMembers()->at(m_targetNr);
                }
            }
        }

        if(controller->IsKeyPressed(Configuration::Accept))
        {
            if(m_targetType == BattleEnums::TargetOwnTeamEntity || m_targetType == BattleEnums::TargetEnemyTeamEntity || m_targetType == BattleEnums::TargetSelf)
            {
                (*m_useOnTarget)(m_targetType, m_targetEntity);
            }
            else
            {
                (*m_useOnTarget)(m_targetType, 0);
            }
            delete m_useOnTarget;
            m_useOnTarget = 0;
            m_targetEntity = nullptr;
            m_targetType = BattleEnums::TARGET_END;
        }
        else if(controller->IsKeyPressed(Configuration::Cancel))
        {
            delete m_useOnTarget;
            m_useOnTarget = 0;
            m_targetEntity = nullptr;
            m_targetType = BattleEnums::TARGET_END;
        }
    }
    else if(m_next != 0)
    {
        m_next->CalculateMove(this);
        if(m_next->GetControllType() == Entity::ControllUser)
        {
            //Check controlls for gui
            m_mainMenu->CheckKeyboardInput();
        }
    }
    else
    {
        //Todo: check if all animations are over, then calculate next
        CalculateNext();
    }
}
void SceneManagerBattle::AddEnemy(Entity* enemy)
{
    m_enemies.push_back(enemy);
    AddSpriteForEntity(enemy);
}

void SceneManagerBattle::AddSubMenu(MenuNode* menu)
{
    m_mainMenu->addChild(menu);
}

void SceneManagerBattle::TurnIsFinished()
{
    m_mainMenu->ResetOptions();
    m_mainMenu->setVisibility(false);
    m_next->FinishedTurn();
    CalculateNext();
}

void SceneManagerBattle::CalculateNext()
{
    float smallestNext;
    Entity * next = 0;
    std::vector<PartyMember*>* activeParty = m_party->GetActivePartyMembers();
    float newTime;
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        newTime = activeParty->at(i)->GetTimeToNextAttack();
        if(next == 0 || smallestNext > newTime)
        {
            next = activeParty->at(i);
            smallestNext = newTime;
        }
    }
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        newTime = m_enemies.at(i)->GetTimeToNextAttack();
        if(next == 0 || smallestNext > newTime)
        {
            next = m_enemies.at(i);
            smallestNext = newTime;
        }
    }
    m_next = next;
    PassTime(smallestNext);
    if(m_next->GetControllType() == Entity::ControllUser)
    {
        //Show menu
        ShowMenuForNext();
    }
}

void SceneManagerBattle::ShowMenuForNext()
{
    //Clear the menu and add menu Options for the next
    m_mainMenu->ResetOptions();
    //add new Battle options
    Localization* local = Localization::GetInstance();
    m_mainMenu->AddOption(local->GetLocalization("battle_menu.attack"), std::function<void()>(std::bind(&BattleFunctions::Attack, this, m_next)));
    m_mainMenu->AddOption(local->GetLocalization("battle_menu.skill"), std::function<void()>(std::bind(&BattleFunctions::SkillList, this, m_next)));
    //TODO: add other Battle Options

    m_mainMenu->setVisibility(true);
}

void SceneManagerBattle::PassTime(float Time)
{
    std::vector<PartyMember*>* activeParty = m_party->GetActivePartyMembers();
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        activeParty->at(i)->PassTime(Time);
    }
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies.at(i)->PassTime(Time);
    }
}
bool SceneManagerBattle::IsFinished()
{
    bool finished = true;
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        if(!m_enemies[i]->IsDead())
        {
            Finished();
            finished = false;
        }
    }
    if(finished)
    {
        return true;
    }
    m_party->UpdateActiveParty();
    finished = true;
    for(unsigned int i = 0; i < m_party->GetActivePartyMembers()->size(); i++)
    {
        if(!m_party->GetActivePartyMembers()->at(i)->IsDead())
        {
            finished = false;
        }
    }
    if(finished)
    {
        std::cout << "Game Over!" << std::endl;
        GameController::getInstance()->GameOver();
    }
    return finished;
}

void SceneManagerBattle::Finished()
{
    //TODO: Calculate actual Exp from dead enemies
    int exp = 100;
    std::vector<PartyMember*> * activeParty = m_party->GetActivePartyMembers();
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        PartyMember* member = activeParty->at(i);
        member->AddExp(exp);
        member->BattleFinished();
    }
}

bool SceneManagerBattle::IsEntityTargeted(Entity* entity)
{
    if(m_targetEntity == entity)
        return true;
    if(m_targetType == BattleEnums::TargetAll)
        return true;
    //Only Player controlled Entities are targeting someone
    if(m_targetType == BattleEnums::TargetOwnTeam)
    {
        std::vector<PartyMember*>* party = m_party->GetActivePartyMembers();
        return std::find(party->begin(), party->end(), entity) != party->end();
    }
    if(m_targetType == BattleEnums::TargetOwnTeam)
    {
        return std::find(m_enemies.begin(), m_enemies.end(), entity) != m_enemies.end();
    }
    return false;
}

std::vector<Entity*>* SceneManagerBattle::GetEnemies()
{
    return &m_enemies;
}

void SceneManagerBattle::AddSpriteForEntity(Entity* entity)
{
    //Adding Cursor if Entity is targeted
    sf::Sprite* target = new sf::Sprite(*TextureList::getTexture(TextureList::m_targetCursor));
    DrawableNode* targetNode = new DrawableNode(target);
    //Moving Cursor
    sf::Transform targetTransform;
    targetTransform.translate(15, -10);
    targetNode->setTransform(targetTransform);

    //Create Node for Entity
    EntityNode* node = new EntityNode(this, entity);
    //Add Cursor to Entity
    node->SetTargetedNode(targetNode);
    sf::Transform trans;
    //Place at Position depending on Team
    int teamId = entity->GetTeamId();
    trans.translate(m_posPerTeam[teamId]);
    m_posPerTeam[teamId] += m_posChangePerTeam[teamId];
    m_posChangePerTeam[teamId].x *= -1;
    node->setTransform(trans);
    m_eventLayer->addChild(node);
}
