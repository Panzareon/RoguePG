#include "MapGeneration/MapEventHero.h"
#include "Party/CharacterClass.h"
#include "Controller/GameController.h"
#include "SceneManager/SceneManagerDungeon.h"

MapEventHero::MapEventHero()
{
    m_node = nullptr;
}

MapEventHero::MapEventHero(int x, int y): MapEventTile(true,x,y,false)
{
    m_node = nullptr;
}

MapEventHero::~MapEventHero()
{
    //dtor
}

void MapEventHero::SetNode(Node* node)
{
    m_node = node;
}


void MapEventHero::AfterLoad(SceneManager* sm)
{
    ((SceneManagerDungeon*)sm)->PlaceHeroSprite(this);
}

void MapEventHero::Activate()
{
    PartyMember* p = CharacterClass::GetRandomCharacterClass()->GetNewPartyMember();
    p->SetTeamId(0);
    Party* party = GameController::getInstance()->getParty();
    p->AddExp(party->GetActivePartyMembers()->at(0)->GetExp());
    p->GetStartingSkills(p->GetLevel() - 1);
    party->AddPartyMember(p);

    m_finished = true;
    m_node->GetParent()->removeChild(m_node);
    delete m_node;
}
