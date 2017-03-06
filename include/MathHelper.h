#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <random>

class MathHelper
{
    public:
        virtual ~MathHelper();
        int GetRandomInt(int max, int min, bool gauss = false);


        static MathHelper* GetInstance();
    protected:

    private:
        MathHelper();
        std::default_random_engine* m_randomGenerator;

        static MathHelper* m_instance;
};

#endif // MATHHELPER_H
