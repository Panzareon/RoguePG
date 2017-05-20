#ifndef PERSISTENTPROGRESS_H
#define PERSISTENTPROGRESS_H

#include <cstdint>

class PersistentProgress
{
    public:
        PersistentProgress();
        virtual ~PersistentProgress();

        int GetStartMoney();
        int GetStartMember();
        int GetShopLevel();
        int GetShopNrItems();
        int GetNrDungeonsCleared();
        void SetStartMoney(int value);
        void AddStartMoney(int value);
        void SetStartMember(int value);
        void AddStartMember(int value);
        void SetShopLevel(int value);
        void AddShopLevel(int value);
        void SetShopNrItems(int value);
        void AddShopNrItems(int value);
        void ClearedDungeon(int id);

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(m_startMoney, m_startMember, m_shopLevel, m_shopNrItems, m_nrDungeonsCleared);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(m_startMoney, m_startMember, m_shopLevel, m_shopNrItems, m_nrDungeonsCleared);
        }

    protected:
        void SaveChanges();

        int m_startMoney;
        int m_startMember;
        int m_shopLevel;
        int m_shopNrItems;
        int m_nrDungeonsCleared;

    private:
};

#endif // PERSISTENTPROGRESS_H
