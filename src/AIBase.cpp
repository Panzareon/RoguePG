#include "AIBase.h"
#include "InvalidArgumentException.h"
#include "GameController.h"
#include "SceneManagerBattle.h"
#include "Entity.h"

AIBase::AIBase(Entity* entity)
{
    //ctor
    m_entity = entity;
}

AIBase::~AIBase()
{
    //dtor
}

Entity* AIBase::GetRandomEntity(int teamId, bool enemy)
{
    GameController* controller = GameController::getInstance();
    SceneManagerBattle* sm = (SceneManagerBattle*)controller->GetActiveSceneManager();
    std::vector<Entity*>* enemies = sm->GetEnemies();
    std::vector<PartyMember*>* party = controller->getParty()->GetActivePartyMembers();
    int nr = 0;
    for(unsigned int i = 0; i < enemies->size(); i++)
    {
        //Check if teamIds are the same xor enemy is true
        if((enemies->at(i)->GetTeamId() == teamId) != enemy)
            nr++;
    }
    for(unsigned int i = 0; i < party->size(); i++)
    {
        //Check if teamIds are the same xor enemy is true
        if((party->at(i)->GetTeamId() == teamId) != enemy)
            nr++;
    }
    if(nr == 0)
    {
        std::string msg("No Entity found ");
        if(enemy)
            msg.append("without");
        else
            msg.append("with");
        msg.append(" TeamId: ");
        msg.append(std::to_string(teamId));
        throw InvalidArgumentException(msg);
    }
    int ret = rand() % nr;
    for(unsigned int i = 0; i < enemies->size(); i++)
    {
        //Check if teamIds are the same xor enemy is true
        if((enemies->at(i)->GetTeamId() == teamId) != enemy)
        {
            if(ret == 0)
                return enemies->at(i);
            ret--;
        }
    }
    for(unsigned int i = 0; i < party->size(); i++)
    {
        //Check if teamIds are the same xor enemy is true
        if((party->at(i)->GetTeamId() == teamId) != enemy)
        {
            if(ret == 0)
                return party->at(i);
            ret--;
        }
    }
    std::string msg("No Entity found ");
    if(enemy)
        msg.append("without");
    else
        msg.append("with");
    msg.append(" TeamId: ");
    msg.append(std::to_string(teamId));
    throw InvalidArgumentException(msg);
}
