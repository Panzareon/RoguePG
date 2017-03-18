#include "Controller/MathHelper.h"

#include "Controller/GameController.h"

MathHelper* MathHelper::m_instance = nullptr;

MathHelper::MathHelper()
{
    //ctor
    m_randomGenerator = GameController::getInstance()->GetRandomGenerator();
}

MathHelper::~MathHelper()
{
    //dtor
}

int MathHelper::GetRandomInt(int max, int min, bool gauss)
{
    if(gauss)
    {
        std::normal_distribution<float> distribution((max + min)/2.0f, (max - min)/ 4.0f);
        float retval = distribution(*m_randomGenerator);
        int ret = std::round(retval);
        if(ret < min)
            return min;
        if(ret > max)
            return max;
        return ret;
    }
    else
    {
        return rand()%(max - min + 1) + min;
    }
}

MathHelper* MathHelper::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new MathHelper();
    return m_instance;
}
