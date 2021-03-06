#include "BattleAnimation/AnimationFactory.h"
#include "BattleAnimation/AnimationPartSprite.h"
#include "BattleAnimation/AnimationPartText.h"
#include "Controller/SoundController.h"

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
    //return Animation according to Attack and Effect Type
    if(att->size() > 0)
    {
        switch(*att->begin())
        {
        case BattleEnums::AttackType::Fire:
            return AnimationList::Fireball;
        case BattleEnums::AttackType::Earth:
            return AnimationList::Earth;
        case BattleEnums::AttackType::Water:
            return AnimationList::Water;
        case BattleEnums::AttackType::Air:
            return AnimationList::Air;
        case BattleEnums::AttackType::Physical:
            return AnimationList::Sword;
        }
    }
    //Default return is Fireball
    return AnimationList::Fireball;
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

Animation* AnimationFactory::GetAnimation(AnimationList anim, sf::FloatRect startPos)
{
    //play the animation at a given Position
    sf::Transform startTransform;
    startTransform.translate(startPos.left, startPos.top);
    Animation* ret;
    switch(anim)
    {
    case AnimationList::Fireball:
        {
            ret = new Animation(0.2f);
            AnimationPartSprite* part = new AnimationPartSprite(TextureList::TextureFiles::FireballAnimation);
            sf::FloatRect spriteBounds = part->GetSprite()->getLocalBounds();
            startTransform.translate((startPos.width - spriteBounds.width) / 2, (startPos.height - spriteBounds.height) / 2);
            part->SetTiming(0.0f, 0.2f);
            part->SetStartTransform(startTransform);
            part->SetScaling(3.0f);
            ret->AddStep(part);
            SoundController::GetInstance()->PlaySound(SoundController::Fire);
            return ret;
        }
        break;
    case AnimationList::Water:
        {
            float yMovement = 50.0f;
            ret = new Animation(0.2f);
            AnimationPartSprite* part = new AnimationPartSprite(TextureList::TextureFiles::WaterAnimation);
            sf::FloatRect spriteBounds = part->GetSprite()->getLocalBounds();
            startTransform.translate((startPos.width - spriteBounds.width) / 2, (startPos.height - spriteBounds.height) / 2 - yMovement);
            part->SetTiming(0.0f, 0.2f);
            part->SetStartTransform(startTransform);
            part->SetTranslation(0.0f, yMovement);
            ret->AddStep(part);
            SoundController::GetInstance()->PlaySound(SoundController::Water);
            return ret;
        }
    case AnimationList::Earth:
        {
            float yMovement = 75.0f;
            ret = new Animation(0.2f);
            AnimationPartSprite* part = new AnimationPartSprite(TextureList::TextureFiles::EarthAnimation);
            sf::FloatRect spriteBounds = part->GetSprite()->getLocalBounds();
            startTransform.translate((startPos.width - spriteBounds.width) / 2, (startPos.height - spriteBounds.height) / 2 - yMovement);
            part->SetTiming(0.0f, 0.2f);
            part->SetStartTransform(startTransform);
            part->SetTranslation(0.0f, yMovement);
            ret->AddStep(part);
            SoundController::GetInstance()->PlaySound(SoundController::Earth);
            return ret;
        }
    case AnimationList::Air:
        {
            float xMovement = -30.0f;
            ret = new Animation(0.2f);
            AnimationPartSprite* part = new AnimationPartSprite(TextureList::TextureFiles::AirAnimation);
            sf::FloatRect spriteBounds = part->GetSprite()->getLocalBounds();
            startTransform.translate((startPos.width - spriteBounds.width) / 2 - xMovement, (startPos.height - spriteBounds.height) / 2);
            part->SetTiming(0.0f, 0.2f);
            part->SetStartTransform(startTransform);
            part->SetTranslation(xMovement, 0.0f);
            ret->AddStep(part);
            SoundController::GetInstance()->PlaySound(SoundController::Wind);
            return ret;
        }
    case AnimationList::Sword:
        {
            float yMovement = 75.0f;
            ret = new Animation(0.2f);
            AnimationPartSprite* part = new AnimationPartSprite(TextureList::TextureFiles::SwordAnimation);
            sf::FloatRect spriteBounds = part->GetSprite()->getLocalBounds();
            startTransform.translate((startPos.width - spriteBounds.width) / 2, (startPos.height - spriteBounds.height) / 2 - yMovement);
            part->SetTiming(0.0f, 0.2f);
            part->SetStartTransform(startTransform);
            part->SetTranslation(0.0f, yMovement);
            ret->AddStep(part);
            SoundController::GetInstance()->PlaySound(SoundController::Hit);
            return ret;
        }
    default:
        return nullptr;
    }

}

Animation* AnimationFactory::GetTextAnimation(Entity* target, std::string text, sf::Color color, float xTranslate, float yTranslate )
{
    if(target->GetNode() == nullptr)
    {
        //If there is no Node, animation can not be displayed
        return nullptr;
    }
    sf::FloatRect startPos = target->GetNode()->getGlobalBoundingBox();
    sf::Transform startTransform;
    startTransform.translate(startPos.left + xTranslate, startPos.top + yTranslate);
    Animation* ret;
    ret = new Animation(0.2f);
    AnimationPartText* part = new AnimationPartText(text, color, 12);
    sf::FloatRect bounds = part->GetText()->getLocalBounds();
    startTransform.translate((startPos.width - bounds.width) / 2, - bounds.height / 2);
    part->SetTiming(0.0f, 0.2f);
    part->SetStartTransform(startTransform);
    part->SetTranslation(-3.0f, - 10.0f);
    part->SetScaling(1.5f);
    ret->AddStep(part);
    return ret;
}
