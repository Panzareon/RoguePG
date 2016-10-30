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

Animation* AnimationFactory::GetAnimation(AnimationList anim, EntityNode* target)
{

    Animation* ret;
    switch(anim)
    {
    case Fireball:
        ret = new Animation(0.3f);
        AnimationPartSprite* part = new AnimationPartSprite(TextureList::FireballAnimation);
        part->SetTiming(0.0f, 0.3f);
        part->SetStartTransform(target->getTransform().scale(2.0f, 2.0f));
        part->SetScaling(3.0f);
        ret->AddStep(part);
        break;
    }

    return ret;
}
