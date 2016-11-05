#include "AnimationFactory.h"
#include "AnimationPartSprite.h"

AnimationFactory::AnimationFactory()
{
    //ctor
}

AnimationFactory::~AnimationFactory()
{
    //dtor
}

AnimationFactory::AnimationList AnimationFactory::GetAnimationTypeFor(std::set<BattleEnums::AttackType>* att, std::set<BattleEnums::EffectType>* eff)
{
    //TODO: return Animation according to Attack and Effect Type
    return Fireball;
}


Animation* AnimationFactory::GetAnimation(AnimationList anim, Entity* target)
{
    //start the Animation at the position of the given Entity
    sf::FloatRect t = target->GetNode()->getTransform().transformRect(target->GetBattleSprite()->getLocalBounds());
    Animation* ret = GetAnimation(anim, t);
    if(ret == nullptr)
    {
        //anim is not for target of a position
        std::vector<Entity*> entities;
        entities.push_back(target);
        ret = GetAnimation(anim, &entities);
    }
    return ret;
}

Animation* AnimationFactory::GetAnimation(AnimationList anim, std::vector<Entity* >* targets)
{
    switch(anim)
    {
    default:
        //start the animation in the middle of all given Entities
        sf::FloatRect target;
        target.width = 0.0f;
        target.height = 0.0f;
        target.left = 0.0f;
        target.top = 0.0f;
        for(auto it = targets->begin(); it != targets->end(); it++)
        {
            sf::FloatRect t = (*it)->GetNode()->getTransform().transformRect((*it)->GetBattleSprite()->getLocalBounds());
            target.left += t.left + t.width / 2;
            target.top += t.top + t.height / 2;
        }
        target.left /= targets->size();
        target.top /= targets->size();
        return GetAnimation(anim, target);
    }
}

Animation* AnimationFactory::GetAnimation(AnimationList anim, sf::FloatRect startPos)
{
    //play the animation at a given Position
    sf::Transform startTransform;
    startTransform.translate(startPos.left, startPos.top);
    Animation* ret;
    switch(anim)
    {
    case Fireball:
        {
            ret = new Animation(0.2f);
            AnimationPartSprite* part = new AnimationPartSprite(TextureList::FireballAnimation);
            sf::FloatRect spriteBounds = part->GetSprite()->getLocalBounds();
            startTransform.translate((startPos.width - spriteBounds.width) / 2, (startPos.height - spriteBounds.height) / 2);
            part->SetTiming(0.0f, 0.2f);
            part->SetStartTransform(startTransform);
            part->SetScaling(3.0f);
            ret->AddStep(part);
            return ret;
        }
        break;
    default:
        return nullptr;
    }

}
