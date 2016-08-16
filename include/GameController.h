#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Party.h"

class GameController
{
    public:
        virtual ~GameController();
        static GameController* getInstance();

        void setParty(Party* party);
        Party* getParty();
    protected:
    private:
        Party* m_party;
        static GameController* m_instance;
        GameController();
};

#endif // GAMECONTROLLER_H
