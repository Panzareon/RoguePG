#include "MapEventHero.h"
#include "CharacterClass.h"
#include "GameController.h"

MapEventHero::MapEventHero(Node* node, int x, int y): MapEventTile(true,x,y,false)
{
    m_node = node;
}

MapEventHero::~MapEventHero()
{
    //dtor
}

void MapEventHero::Activate()
{
    PartyMember* p = CharacterClass::GetRandomCharacterClass()->GetNewPartyMember();
    p->SetTeamId(0);
    GameController::getInstance()->getParty()->AddPartyMember(p);

    m_finished = true;
    m_node->GetParent()->removeChild(m_node);
    delete m_node;
}
