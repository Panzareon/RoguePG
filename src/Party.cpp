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

std::vector<PartyMember*> * Party::GetAllPartyMembers()
{
    return &m_partyMembers;
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
    it = m_activePartyMembers.begin();
    while(it != m_activePartyMembers.end())
    {
        if((*it)->IsDead())
        {
            it = m_activePartyMembers.erase(it);
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

void Party::AddItem(Item* item)
{
    for(int i = 0; i < m_items.size(); i++)
    {
        if(m_items[i].second == item)
        {
            m_items[i].first++;
            return;
        }
    }
    m_items.push_back(std::pair<int, Item*>(1,item));
}

int Party::GetNumberOfItem(int itemId)
{
    int retval = 0;
    for(int i = 0; i < m_items.size(); i++)
    {
        if(m_items[i].second->GetItemId() == itemId)
        {
            retval += m_items[i].first;
        }
    }
    return retval;
}

bool Party::RemoveItem(int itemId)
{
    for(int i = 0; i < m_items.size(); i++)
    {
        if(m_items[i].second->GetItemId() == itemId)
        {
            m_items[i].first--;
            if(m_items[i].first <= 0)
            {
                delete m_items[i].second;
                m_items.erase(m_items.begin() + i);
            }
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int,Item*>>* Party::GetItems()
{
    return &m_items;
}

