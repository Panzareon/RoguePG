#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include "PartyMember.h"
#include "Item.h"

class Party
{
    public:
        Party();
        virtual ~Party();
        std::vector<PartyMember*> * GetActivePartyMembers();
        std::vector<PartyMember*> * GetAllPartyMembers();
        void UpdateActiveParty();

        void AddPartyMember(PartyMember* member);

        void AddItem(Item* item);
        int GetNumberOfItem(int itemId);
        bool RemoveItem(int itemId);
        std::vector<std::pair<int,Item*>>* GetItems();
    protected:
    private:
        std::vector<PartyMember*> m_partyMembers;
        std::vector<PartyMember*> m_deadMembers;
        std::vector<PartyMember*> m_activePartyMembers;

        //Number of Items and actual Item
        std::vector<std::pair<int,Item*>> m_items;
};

#endif // PARTY_H
