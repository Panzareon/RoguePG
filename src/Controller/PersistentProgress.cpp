#include "Controller/PersistentProgress.h"
#include "Controller/GameController.h"

PersistentProgress::PersistentProgress()
{
    //ctor
    m_startMoney = 0;
    m_startMember = 1;
    m_shopLevel = 1;
    m_shopNrItems = 1;
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

void PersistentProgress::SetStartMoney(int value)
{
    m_startMoney = value;
    SaveChanges();
}

void PersistentProgress::SetStartMember(int value)
{
    m_startMember = value;
    SaveChanges();
}

void PersistentProgress::SetShopLevel(int value)
{
    m_shopLevel = value;
    SaveChanges();
}

void PersistentProgress::SetShopNrItems(int value)
{
    m_shopNrItems = value;
    SaveChanges();
}

void PersistentProgress::SaveChanges()
{
    GameController::getInstance()->SaveProgress();
}
