#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include "PartyMember.h"

class Party
{
    public:
        Party();
        virtual ~Party();
        std::vector<PartyMember*> * GetActivePartyMembers();
        void UpdateActiveParty();

        void AddPartyMember(PartyMember* member);
    protected:
    private:
        std::vector<PartyMember*> m_partyMembers;
        std::vector<PartyMember*> m_activePartyMembers;
};

#endif // PARTY_H
