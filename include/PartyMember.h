#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include <Entity.h>


class PartyMember : public Entity
{
    public:
        PartyMember(int teamId);
        virtual ~PartyMember();
        void AddExp(int ammount);
    protected:
        int m_exp;
        int m_lvl;
    private:
};

#endif // PARTYMEMBER_H
