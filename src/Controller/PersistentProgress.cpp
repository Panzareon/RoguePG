#include "Controller/PersistentProgress.h"
#include "Controller/GameController.h"

PersistentProgress::PersistentProgress()
{
    //ctor
    m_startMoney = 0;
    m_startMember = 1;
    m_shopLevel = 1;
    m_shopNrItems = 1;
    m_nrDungeonsCleared = 0;
}

PersistentProgress::~PersistentProgress()
{
    //dtor
}

int PersistentProgress::GetStartMoney()
{
    return m_startMoney;
}

int PersistentProgress::GetStartMember()
{
    return m_startMember;
}

int PersistentProgress::GetShopLevel()
{
    return m_shopLevel;
}

int PersistentProgress::GetShopNrItems()
{
    return m_shopNrItems;
}

int PersistentProgress::GetNrDungeonsCleared()
{
    return m_nrDungeonsCleared;
}

void PersistentProgress::SetStartMoney(int value)
{
    m_startMoney = value;
    SaveChanges();
}

void PersistentProgress::AddStartMoney(int value)
{
    SetStartMoney(m_startMoney + value);
}

void PersistentProgress::SetStartMember(int value)
{
    m_startMember = value;
    SaveChanges();
}

void PersistentProgress::AddStartMember(int value)
{
    SetStartMember(m_startMember + value);
}

void PersistentProgress::SetShopLevel(int value)
{
    m_shopLevel = value;
    SaveChanges();
}

void PersistentProgress::AddShopLevel(int value)
{
    SetShopLevel(m_shopLevel + value);
}

void PersistentProgress::SetShopNrItems(int value)
{
    m_shopNrItems = value;
    SaveChanges();
}

void PersistentProgress::AddShopNrItems(int value)
{
    SetShopNrItems(m_shopNrItems + value);
}

void PersistentProgress::ClearedDungeon(int id)
{
    if(id > m_nrDungeonsCleared)
    {
        m_nrDungeonsCleared = id;
        SaveChanges();
    }
}

void PersistentProgress::SaveChanges()
{
    GameController::getInstance()->SaveProgress();
}
