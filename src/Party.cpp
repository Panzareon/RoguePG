#include "Party.h"

Party::Party()
{
    //ctor
}

Party::~Party()
{
    //dtor
}
std::vector<PartyMember*> * Party::GetActivePartyMembers()
{
    return &m_activePartyMembers;
}
