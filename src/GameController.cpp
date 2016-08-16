#include "GameController.h"
GameController* GameController::m_instance = 0;
GameController::GameController()
{
    //ctor
    m_party = 0;
}

GameController::~GameController()
{
    //dtor
    delete m_party;
}

void GameController::setParty(Party* party)
{
    m_party = party;
}

Party* GameController::getParty()
{
    return m_party;
}









GameController* GameController::getInstance()
{
    if(m_instance == 0)
    {
        m_instance = new GameController();
    }
    return m_instance;
}
