#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include <Entity.h>


class PartyMember : public Entity
{
    public:
        PartyMember(int teamId);
        virtual ~PartyMember();
    protected:
    private:
};

#endif // PARTYMEMBER_H
