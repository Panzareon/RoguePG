#ifndef ANIMATIONFACTORY_H
#define ANIMATIONFACTORY_H

#include "Animation.h"
#include "SceneGraph/EntityNode.h"

class AnimationFactory
{
    public:
        enum class AnimationList{
            Fireball,
            Water,
            Earth,
            Air,
            Sword
        };
        AnimationFactory();
        virtual ~AnimationFactory();
        static AnimationList GetAnimationTypeFor(std::set<BattleEnums::AttackType>* att, std::set<BattleEnums::EffectType>* eff);

        static Animation* GetAnimation(AnimationList anim, Entity* target);
        static Animation* GetAnimation(AnimationList anim, std::vector<Entity* >* targets);
        static Animation* GetAnimation(AnimationList anim, sf::FloatRect startPos);

        static Animation* GetTextAnimation(Entity* target, std::string text, sf::Color color, float xTranslate = 0.0f, float yTranslate = 0.0f);

    protected:

    private:
};

#endif // ANIMATIONFACTORY_H
