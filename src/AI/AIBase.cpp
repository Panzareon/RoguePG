#include "AI/AIBase.h"
#include "Exception/InvalidArgumentException.h"
#include "Controller/GameController.h"
#include "SceneManager/SceneManagerBattle.h"
#include "Battle/Entity.h"

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
    std::vector<std::shared_ptr<PartyMember> >* party = controller->getParty()->GetActivePartyMembers();
    int nr = 0;
    for(unsigned int i = 0; i < enemies->size(); i++)
    {
        //Check if teamIds are the same xor enemy is true
        if((enemies->at(i)->GetTeamId() == teamId) != enemy && !enemies->at(i)->IsDead())
            nr++;
    }
    for(unsigned int i = 0; i < party->size(); i++)
    {
        //Check if teamIds are the same xor enemy is true
        if((party->at(i)->GetTeamId() == teamId) != enemy && !party->at(i)->IsDead())
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
        if((enemies->at(i)->GetTeamId() == teamId) != enemy && !enemies->at(i)->IsDead())
        {
            if(ret == 0)
                return enemies->at(i);
            ret--;
        }
    }
    for(unsigned int i = 0; i < party->size(); i++)
    {
        //Check if teamIds are the same xor enemy is true
        if((party->at(i)->GetTeamId() == teamId) != enemy && !party->at(i)->IsDead())
        {
            if(ret == 0)
                return party->at(i).get();
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
