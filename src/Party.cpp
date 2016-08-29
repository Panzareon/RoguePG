#include "Party.h"
#include "Configuration.h"

Party::Party()
{
    //ctor
}

Party::~Party()
{
    //dtor
    for(int i = 0; i < m_partyMembers.size(); i++)
    {
        delete m_partyMembers[i];
    }
}
std::vector<PartyMember*> * Party::GetActivePartyMembers()
{
    return &m_activePartyMembers;
}

void Party::AddPartyMember(PartyMember* member)
{
    m_partyMembers.push_back(member);
    Configuration* conf = Configuration::GetInstance();
    if(m_activePartyMembers.size() < conf->GetMaxPartySize())
    {
        m_activePartyMembers.push_back(member);
    }
}
