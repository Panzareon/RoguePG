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
        void SetStartMoney(int value);
        void SetStartMember(int value);
        void SetShopLevel(int value);
        void SetShopNrItems(int value);

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(m_startMoney, m_startMember, m_shopLevel, m_shopNrItems);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(m_startMoney, m_startMember, m_shopLevel, m_shopNrItems);
        }

    protected:
        void SaveChanges();

        int m_startMoney;
        int m_startMember;
        int m_shopLevel;
        int m_shopNrItems;

    private:
};

#endif // PERSISTENTPROGRESS_H
