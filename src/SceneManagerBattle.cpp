#include "SceneManagerBattle.h"
#include "GameController.h"
#include "SFML/Graphics.hpp"
#include "TextureList.h"
#include "Configuration.h"

namespace BattleFunctions
{
    void AttackOnTarget(SceneManagerBattle* sm, SceneManagerBattle::Target targetType, Entity* toAttack, Entity* attacking)
    {
        attacking->Attack();
        toAttack->GetHit(attacking->GetAttack(), attacking->GetAttackType());
        sm->TurnIsFinished();
    }
    void Attack(SceneManagerBattle* sm, Entity* attacking)
    {
        std::function<void(SceneManagerBattle::Target, Entity*)>* func = new std::function<void(SceneManagerBattle::Target, Entity*)>(std::bind(&AttackOnTarget, sm, std::placeholders::_1, std::placeholders::_2, attacking));
        sm->UseOnTarget(func, SceneManagerBattle::TargetEnemyTeamEntity);
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
    m_mainNode->addChild(m_eventLayer);
    m_gui = new Node();
    m_mainNode->addChild(m_gui);
    m_mainMenu = new MenuNode(m_windowWidth);
    m_mainMenu->setVisibility(false);
    m_gui->addChild(m_mainMenu);

    m_party = GameController::getInstance()->getParty();

    m_next = 0;
    m_useOnTarget = 0;
}

SceneManagerBattle::~SceneManagerBattle()
{
    //dtor
    for(int i = 0; i < m_enemies.size(); i++)
    {
        delete m_enemies[i];
    }
}

void SceneManagerBattle::UseOnTarget(std::function<void(Target, Entity*)>* func, Target defaultTarget)
{
    if(m_useOnTarget != 0)
        delete m_useOnTarget;
    m_useOnTarget = func;
    m_targetType = defaultTarget;
    m_targetEntity = 0;
    m_targetNr = 0;
    if(m_targetType == TargetEnemyTeamEntity)
    {
        m_targetEntity = m_enemies[0];
    }
    else if(m_targetType == TargetOwnTeamEntity)
    {
        m_targetEntity = m_party->GetActivePartyMembers()->at(0);
    }
}


void SceneManagerBattle::Tick()
{
    Configuration* conf = Configuration::GetInstance();
    //Battle Logic
    if(m_useOnTarget != 0)
    {
        //Selecting target
        //TODO: move only one target at a time and not one per tick
        if(sf::Keyboard::isKeyPressed(conf->GetMoveDownKey()))
        {
            if(m_targetType == TargetEnemyTeamEntity)
            {
                if(m_targetNr < m_enemies.size() - 1)
                {
                    m_targetNr++;
                    m_targetEntity = m_enemies[m_targetNr];
                }
            }
            else if(m_targetType == TargetOwnTeamEntity)
            {
                if(m_targetNr < m_party->GetActivePartyMembers()->size() - 1)
                {
                    m_targetNr++;
                    m_targetEntity = m_party->GetActivePartyMembers()->at(m_targetNr);
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(conf->GetMoveUpKey()))
        {
            if(m_targetType == TargetEnemyTeamEntity)
            {
                if(m_targetNr > 0)
                {
                    m_targetNr--;
                    m_targetEntity = m_enemies[m_targetNr];
                }
            }
            else if(m_targetType == TargetOwnTeamEntity)
            {
                if(m_targetNr > 0)
                {
                    m_targetNr--;
                    m_targetEntity = m_party->GetActivePartyMembers()->at(m_targetNr);
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(conf->GetAcceptKey()))
        {
            if(m_targetType == TargetOwnTeamEntity || m_targetType == TargetEnemyTeamEntity)
            {
                (*m_useOnTarget)(m_targetType, m_targetEntity);
            }
            else
            {
                (*m_useOnTarget)(m_targetType, 0);
            }
            delete m_useOnTarget;
            m_useOnTarget = 0;
        }
        else if(sf::Keyboard::isKeyPressed(conf->GetCancelKey()))
        {
            delete m_useOnTarget;
            m_useOnTarget = 0;
        }
        else
        {
            //TODO: Show which entities are targeted
        }
    }
    else if(m_next != 0)
    {
        m_next->CalculateMove();
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
}

void SceneManagerBattle::TurnIsFinished()
{
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
    m_mainMenu->AddOption("Attack", std::function<void()>(std::bind(&BattleFunctions::Attack, this, m_next)));
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
    for(int i = 0; i < m_enemies.size(); i++)
    {
        if(!m_enemies[i]->IsDead())
        {
            finished = false;
        }
    }
    if(finished)
        return true;
    finished = true;
    for(int i = 0; i < m_party->GetActivePartyMembers()->size(); i++)
    {
        if(!m_party->GetActivePartyMembers()->at(i)->IsDead())
        {
            finished = false;
        }
    }
    return finished;
}