#include "SceneManagerBattle.h"
#include "GameController.h"
#include "SFML/Graphics.hpp"
#include "TextureList.h"
#include "Configuration.h"
#include "Skill.h"
#include "Localization.h"
#include "MenuNodeItems.h"
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
        skill->Use(attacking, targetType, toAttack);
        sm->TurnIsFinished();
    }

    void SetSkillDescription(SceneManagerBattle* sm, Skill* skill)
    {
        sm->SetDescription(skill->GetLocalizedDescription());
    }

    void SetDescription(SceneManagerBattle* sm, std::string str)
    {
        sm->SetDescription(str);
    }

    void UseSkill(SceneManagerBattle* sm, Entity* attacking, Skill* skill)
    {
        BattleEnums::Target target = skill->GetDefaultTarget();
        if(target == BattleEnums::TargetNone)
        {
            skill->Use(attacking, target,nullptr);
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
        MenuNodeItems<Skill>* skillMenu = new MenuNodeItems<Skill>(GameController::getInstance()->GetWindowWidth(), std::function<void(Skill*)>(std::bind(&SetSkillDescription, sm, std::placeholders::_1)));
        skillMenu->CancelAvailable(true);
        skillMenu->SetPadding(5,0);

        Localization* localization = Localization::GetInstance();

        std::vector<std::shared_ptr<Skill>>* skillList = attacking->GetSkillList();
        bool setDescription = true;
        for(unsigned int i = 0; i < skillList->size(); i++)
        {
            if(setDescription)
            {
                SetSkillDescription(sm, skillList->at(i).get());
            }
            skillMenu->AddOptionWithItem(localization->GetLocalization(skillList->at(i)->GetName()),std::function<void()>(std::bind(&UseSkill, sm, attacking, skillList->at(i).get())), skillList->at(i).get(), attacking->GetMp() >= skillList->at(i)->GetManaUse());
            skillMenu->AddValueToOption(i, std::to_string((int)skillList->at(i)->GetManaUse()));
        }

        sm->AddSubMenu(skillMenu);
    }
}

SceneManagerBattle::SceneManagerBattle(sf::RenderTarget * target, int windowWidth, int windowHeight): SceneManager(target, windowWidth, windowHeight)
{
    //ctor
    //Build Scene Graph
    SetMemberStats();
    m_mainNode = new Node();
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::DungeonBattleBackground));
    m_background = new DrawableNode(backgroundSprite);
    m_mainNode->addChild(m_background);
    m_eventLayer = new Node();
    m_mainNode->addChild(m_eventLayer);
    m_mainNode->addChild(m_animationNode);
    m_description = new TextNode();
    m_description->moveNode(20.0f, GameController::getInstance()->GetWindowHeight() - 64.0f);
    m_description->SetColor(sf::Color::Black);
    m_description->SetFontSize(20);
    m_mainNode->addChild(m_description);
    m_mainMenu->SetPadding(5,0);

    m_timeDisplay = new Node();
    m_timeDisplay->moveNode(20.0f, 50.0f);
    m_gui->addChild(m_timeDisplay);
    m_timeHeight = 300.0f;

    m_party = GameController::getInstance()->getParty();


    m_next = nullptr;
    m_useOnTarget = nullptr;
    m_restoreHpPercent = 0.25f;
    m_restoreMpPercent = 0.25f;

    //Setting Startpositions for teams
    //TODO: for more than 2 teams?
    m_posPerTeam.push_back(sf::Vector2f(50,150));
    m_posPerTeam.push_back(sf::Vector2f(GameController::getInstance()->GetWindowWidth() - 100,155));
    m_posChangePerTeam.push_back(sf::Vector2f(40,40));
    m_posChangePerTeam.push_back(sf::Vector2f(-40,40));


    //Change Hero bar positions
    m_memberStats->moveNode(0.0f, -64.0f);

    std::vector<PartyMember*> * party = m_party->GetActivePartyMembers();
    for(int i = 0; i < party->size(); i++)
    {
        AddSpriteForEntity(party->at(i));
        sf::Text* text = new sf::Text("H" + std::to_string(i+1), *Configuration::GetInstance()->GetFont(), 12);
        m_partyMemberTime.push_back(text);
        DrawableNode* node = new DrawableNode(text);
        node->moveNode(-10.0f, 0.0f);
        m_timeDisplay->addChild(node);
    }

    for(PartyMember* member : (*m_party->GetAllPartyMembers()))
    {
        member->StartBattle();
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
    if(m_useOnTarget != nullptr)
        delete m_useOnTarget;
    m_useOnTarget = func;
    m_targetType = defaultTarget;
    m_targetEntity = 0;
    m_targetNr = 0;
    if(m_targetType == BattleEnums::TargetEnemyTeamEntity)
    {
        int i = 0;
        do
        {
            m_targetEntity = m_enemies[i];
            i++;
        }
        while(m_targetEntity->IsDead() && i < m_enemies.size());
    }
    else if(m_targetType == BattleEnums::TargetOwnTeamEntity)
    {
        int i = 0;
        do
        {
            m_targetEntity = m_party->GetActivePartyMembers()->at(i);
            i++;
        }
        while(m_targetEntity->IsDead() && i < m_party->GetActivePartyMembers()->size());
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
    if(m_useOnTarget != nullptr)
    {
        //Selecting target
        if(controller->IsKeyPressed(Configuration::MoveDown))
        {
            if(m_targetType == BattleEnums::TargetEnemyTeamEntity)
            {
                int nr = 0;
                do
                {
                    if(m_targetNr < m_enemies.size() - 1)
                    {
                        m_targetNr++;
                    }
                    else
                    {
                        m_targetNr = 0;
                    }
                    m_targetEntity = m_enemies[m_targetNr];
                }
                while(m_targetEntity->IsDead() && nr++ < 100);
                if(nr >= 100)
                {
                    std::cout << "Missing Enemy to target" << std::endl;
                }
            }
            else if(m_targetType == BattleEnums::TargetOwnTeamEntity)
            {
                int nr = 0;
                do
                {
                    if(m_targetNr < m_party->GetActivePartyMembers()->size() - 1)
                    {
                        m_targetNr++;
                    }
                    else
                    {
                        m_targetNr = 0;
                    }
                    m_targetEntity = m_party->GetActivePartyMembers()->at(m_targetNr);
                }
                while(m_targetEntity->IsDead() && nr++ < 100);
                if(nr >= 100)
                {
                    std::cout << "Missing Party member to target" << std::endl;
                }
            }
        }
        else if(controller->IsKeyPressed(Configuration::MoveUp))
        {
            if(m_targetType == BattleEnums::TargetEnemyTeamEntity)
            {
                int nr = 0;
                do
                {
                    if(m_targetNr > 0)
                    {
                        m_targetNr--;
                    }
                    else
                    {
                        m_targetNr = m_enemies.size() - 1;
                    }
                    m_targetEntity = m_enemies[m_targetNr];
                }
                while(m_targetEntity->IsDead() && nr++ < 100);
                if(nr >= 100)
                {
                    std::cout << "Missing Enemy to target" << std::endl;
                }
            }
            else if(m_targetType == BattleEnums::TargetOwnTeamEntity)
            {
                int nr = 0;
                do
                {
                    if(m_targetNr > 0)
                    {
                        m_targetNr--;
                    }
                    else
                    {
                        m_targetNr = m_party->GetActivePartyMembers()->size() - 1;
                    }
                    m_targetEntity = m_party->GetActivePartyMembers()->at(m_targetNr);
                }
                while(m_targetEntity->IsDead() && nr++ < 100);
                if(nr >= 100)
                {
                    std::cout << "Missing Party Member to target" << std::endl;
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
            m_useOnTarget = nullptr;
            m_targetEntity = nullptr;
            m_targetType = BattleEnums::TARGET_END;
        }
        else if(controller->IsKeyPressed(Configuration::Cancel))
        {
            delete m_useOnTarget;
            m_useOnTarget = nullptr;
            m_targetEntity = nullptr;
            m_targetType = BattleEnums::TARGET_END;
        }
    }
    else if(m_next != nullptr && !m_nextFinished)
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
        //check if all animations are over, then calculate next
        if(m_animationList.size() == 0)
            CalculateNext();
    }
}
void SceneManagerBattle::AddEnemy(Entity* enemy)
{
    m_enemies.push_back(enemy);
    AddSpriteForEntity(enemy);
    enemy->StartBattle();
    sf::Text* text = new sf::Text("E" + std::to_string(m_enemies.size()), *Configuration::GetInstance()->GetFont(), 12);
    m_enemyTime.push_back(text);
    DrawableNode* node = new DrawableNode(text);
    node->moveNode(10.0f, 0.0f);
    m_timeDisplay->addChild(node);
}


void SceneManagerBattle::TurnIsFinished()
{
    m_mainMenu->ResetOptions();
    m_mainMenu->setVisibility(false);
    m_next->FinishedTurn();
    m_nextFinished = true;
}

void SceneManagerBattle::CalculateNext()
{
    m_nextFinished = false;
    float smallestNext;
    Entity * next = 0;
    std::vector<PartyMember*>* activeParty = m_party->GetActivePartyMembers();
    float newTime;
    Entity* nextEntity;
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        nextEntity = activeParty->at(i);
        newTime = nextEntity->GetTimeToNextAttack();
        if(!nextEntity->IsDead() && (next == 0 || smallestNext > newTime))
        {
            next = nextEntity;
            smallestNext = newTime;
        }
    }
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        nextEntity = m_enemies.at(i);
        newTime = nextEntity->GetTimeToNextAttack();
        if(!nextEntity->IsDead() && (next == 0 || smallestNext > newTime))
        {
            next = nextEntity;
            smallestNext = newTime;
        }
    }
    m_next = next;
    PassTime(smallestNext);
    m_next->StartTurn();
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
    m_mainMenu->AddOption(local->GetLocalization("battle_menu.attack"), std::function<void()>(std::bind(&BattleFunctions::Attack, this, m_next)), std::function<void()>(std::bind(&BattleFunctions::SetDescription, this, local->GetLocalization("battle_menu.attack.desc"))));
    m_mainMenu->AddOption(local->GetLocalization("battle_menu.skill"), std::function<void()>(std::bind(&BattleFunctions::SkillList, this, m_next)), std::function<void()>(std::bind(&BattleFunctions::SetDescription, this, local->GetLocalization("battle_menu.skill.desc"))), m_next->GetSkillList()->size() > 0);
    SetDescription(local->GetLocalization("battle_menu.attack.desc"));
    //TODO: add other Battle Options

    m_mainMenu->setVisibility(true);
}

void SceneManagerBattle::PassTime(float Time)
{
    std::vector<PartyMember*>* activeParty = m_party->GetActivePartyMembers();
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        activeParty->at(i)->PassTime(Time);
        m_partyMemberTime[i]->setPosition(0.0f, m_timeHeight - m_timeHeight * activeParty->at(i)->GetTimeToNextAttack() * 10.0f);
    }
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies.at(i)->PassTime(Time);
        m_enemyTime[i]->setPosition(0.0f, m_timeHeight - m_timeHeight * m_enemies.at(i)->GetTimeToNextAttack() * 10.0f);
    }
}
bool SceneManagerBattle::IsFinished()
{
    if(m_animationList.size() > 0)
        return false;
    bool finished = true;
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        if(!m_enemies[i]->IsDead())
        {
            finished = false;
        }
    }
    if(finished)
    {
        Finished();
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
        GameController::getInstance()->GameOverCheck();
    }
    return finished;
}

void SceneManagerBattle::Finished()
{
    //Calculate Exp from dead enemies
    int exp = 0;
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        exp += m_enemies[i]->GetExpToGive();
    }
    std::vector<PartyMember*> * activeParty = m_party->GetActivePartyMembers();
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        PartyMember* member = activeParty->at(i);
        member->AddExp(exp);
        member->BattleFinished();
        member->Heal(member->GetAttribute(BattleEnums::AttributeMaxHp) * m_restoreHpPercent);
        member->RestoreMana(member->GetAttribute(BattleEnums::AttributeMaxMp) * m_restoreMpPercent);
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
    sf::Sprite* target = new sf::Sprite(*TextureList::getTexture(TextureList::TargetCursor));
    DrawableNode* targetNode = new DrawableNode(target);
    //Moving Cursor
    sf::Transform targetTransform;
    targetTransform.translate(entity->GetBattleSprite()->getLocalBounds().width / 2 - 8, -10);
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

void SceneManagerBattle::SetDescription(std::string str)
{
    m_description->SetText(str);
}
