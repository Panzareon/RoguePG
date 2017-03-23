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
        //Returns true if active party was changed
        bool UpdateActiveParty();

        void AddPartyMember(PartyMember* member);

        int GetMoney();
        void AddMoney(int money);
        bool RemoveMoney(int money);

        void AddItem(Item* item);
        int GetNumberOfItem(int itemId);
        bool RemoveItem(int itemId);
        std::vector<std::pair<int,Item*>>* GetItems();

        bool ShowEnemyHealth();
        float GetMovementSpeed(float base);
    protected:
    private:
        int m_money;
        std::vector<PartyMember*> m_partyMembers;
        std::vector<PartyMember*> m_deadMembers;
        std::vector<PartyMember*> m_activePartyMembers;

        //Number of Items and actual Item
        std::vector<std::pair<int,Item*>> m_items;
};

#endif // PARTY_H
