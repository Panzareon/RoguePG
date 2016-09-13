#include "PartyMember.h"

PartyMember::PartyMember(int teamId): Entity(teamId)
{
    //ctor
    m_controllTypeAtm = Entity::ControllUser;
}

PartyMember::~PartyMember()
{
    //dtor
}
