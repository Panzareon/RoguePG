#include "Party/Party.h"
#include "Controller/Configuration.h"

Party::Party()
{
    //ctor
    m_money = 0;
}

Party::~Party()
{
    //dtor
}

std::vector<std::shared_ptr<PartyMember> > * Party::GetActivePartyMembers()
{
    return &m_activePartyMembers;
}

std::vector<std::shared_ptr<PartyMember> > * Party::GetAllPartyMembers()
{
    return &m_partyMembers;
}

void Party::AddPartyMember(PartyMember* member)
{
    std::shared_ptr<PartyMember> mem(member);
    m_partyMembers.push_back(mem);
    Configuration* conf = Configuration::GetInstance();
    if(m_activePartyMembers.size() < conf->GetMaxPartySize())
    {
        m_activePartyMembers.push_back(mem);
    }
}

bool Party::UpdateActiveParty()
{
    bool retval = false;
    auto it = m_partyMembers.begin();
    while(it != m_partyMembers.end())
    {
        if((*it)->IsDead())
        {
            m_deadMembers.push_back(*it);
            it = m_partyMembers.erase(it);
            retval = true;
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
        retval = true;
    }
    return retval;
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

int Party::GetMoney() const
{
    return m_money;
}

void Party::AddMoney(int money)
{
    if(money > 0)
        m_money += money;
}

bool Party::RemoveMoney(int money)
{
    if(money > 0 && m_money >= money)
    {
        m_money -= money;
        return true;
    }
    return false;
}

bool Party::ShowEnemyHealth()
{
    for(int i = 0; i < m_activePartyMembers.size(); i++)
    {
        if(m_activePartyMembers[i]->ShowEnemyHealth())
            return true;
    }
    return false;
}

float Party::GetMovementSpeed(float base)
{
    for(int i = 0; i < m_activePartyMembers.size(); i++)
    {
        base = m_activePartyMembers[i]->MovementSpeed(base);
    }
    return base;
}
