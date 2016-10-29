#include "Party.h"
#include "Configuration.h"

Party::Party()
{
    //ctor
}

Party::~Party()
{
    //dtor
    for(unsigned int i = 0; i < m_partyMembers.size(); i++)
    {
        delete m_partyMembers[i];
    }
    for(unsigned int i = 0; i < m_deadMembers.size(); i++)
    {
        delete m_deadMembers[i];
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

void Party::UpdateActiveParty()
{
    auto it = m_partyMembers.begin();
    while(it != m_partyMembers.end())
    {
        if((*it)->IsDead())
        {
            m_deadMembers.push_back(*it);
            it = m_partyMembers.erase(it);
        }
        else
        {
            it++;
        }
    }
    //Check if there are Members that are not in the active Party
    int maxPartySize = Configuration::GetInstance()->GetMaxPartySize();
    if(m_activePartyMembers.size() < maxPartySize && m_partyMembers.size() > m_activePartyMembers.size())
    {
        for(auto it = m_partyMembers.begin(); it != m_partyMembers.end(); it++)
        {
            if(std::find(m_activePartyMembers.begin(), m_activePartyMembers.end(), *it) == m_activePartyMembers.end())
            {
                //This Party Member is not in the active party
                m_activePartyMembers.push_back(*it);
                if(m_activePartyMembers.size() == maxPartySize)
                {
                    //Do not add more to active Party, if max active party size is reached
                    break;
                }
            }
        }
    }
}
