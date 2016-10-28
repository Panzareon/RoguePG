#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

#include <Entity.h>

class CharacterClass;


class PartyMember : public Entity
{
    public:
        PartyMember(CharacterClass* chrClass);
        virtual ~PartyMember();
        void AddExp(int ammount);
        void BattleFinished();

        void LevelUp();
        int GetLevel();
    protected:
        int m_exp;
        int m_lvl;

        CharacterClass* m_chrClass;
    private:
};

#endif // PARTYMEMBER_H
