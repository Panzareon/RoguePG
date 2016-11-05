#ifndef ANIMATIONFACTORY_H
#define ANIMATIONFACTORY_H

#include "Animation.h"
#include "EntityNode.h"

class AnimationFactory
{
    public:
        enum AnimationList{
            Fireball
        };
        AnimationFactory();
        virtual ~AnimationFactory();
        static AnimationList GetAnimationTypeFor(std::set<BattleEnums::AttackType>* att, std::set<BattleEnums::EffectType>* eff);

        static Animation* GetAnimation(AnimationList anim, Entity* target);
        static Animation* GetAnimation(AnimationList anim, std::vector<Entity* >* targets);
        static Animation* GetAnimation(AnimationList anim, sf::FloatRect startPos);

    protected:

    private:
};

#endif // ANIMATIONFACTORY_H
