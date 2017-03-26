#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include "PartyMember.h"
#include "Item.h"
#include <cereal/types/vector.hpp>
#include "Controller/Configuration.h"

class Party
{
    public:
        Party();
        virtual ~Party();
        std::vector<std::shared_ptr<PartyMember> > * GetActivePartyMembers();
        std::vector<std::shared_ptr<PartyMember> > * GetAllPartyMembers();
        //Returns true if active party was changed
        bool UpdateActiveParty();

        void AddPartyMember(PartyMember* member);

        int GetMoney() const;
        void AddMoney(int money);
        bool RemoveMoney(int money);

        void AddItem(Item* item);
        int GetNumberOfItem(int itemId);
        bool RemoveItem(int itemId);
        std::vector<std::pair<int,Item*>>* GetItems();

        bool ShowEnemyHealth();
        float GetMovementSpeed(float base);


        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(m_money, m_partyMembers);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(m_money, m_partyMembers);
            int maxPartySize = Configuration::GetInstance()->GetMaxPartySize();
            for(int i = 0; i < m_partyMembers.size() && i < maxPartySize; i++)
            {
                m_activePartyMembers.push_back(m_partyMembers[i]);
            }
        }

    protected:
    private:
        int m_money;
        std::vector<std::shared_ptr<PartyMember> > m_partyMembers;
        std::vector<std::shared_ptr<PartyMember> > m_deadMembers;
        std::vector<std::shared_ptr<PartyMember> > m_activePartyMembers;

        //Number of Items and actual Item
        std::vector<std::pair<int,Item*>> m_items;
};

#endif // PARTY_H
