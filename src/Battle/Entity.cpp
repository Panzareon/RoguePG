#include "Battle/Entity.h"
#include "AI/AIRandom.h"
#include "SceneManager/SceneManagerBattle.h"
#include <math.h>
#include <map>
#include "SceneGraph/TextureList.h"
#include "BattleAnimation/AnimationFactory.h"
#include "Controller/GameController.h"
#include "PassiveSkill.h"

Entity::Entity(int exp)
{
    //ctor
    m_controllTypeAtm = Entity::ControllAI;
    m_teamId = -1;
    m_lastAttackWasEffective = false;

    m_AI = new AIRandom(this);
    //Setting attribute values to default: 0
    for(int i = 0; i < BattleEnums::ATTRIBUTE_END; i++)
    {
        m_attributes.insert(std::pair<BattleEnums::Attribute, int>((BattleEnums::Attribute)i, 0));
    }
    //Setting default resistances to 1
    for(int i = 0; i < BattleEnums::ATTACK_TYPE_END; i++)
    {
        m_resistances.insert(std::pair<BattleEnums::AttackType, float>((BattleEnums::AttackType)i, 1.0f));
    }

    m_battleSprite = new sf::Sprite();
    SetBattleSprite(TextureList::DefaultBattleSprite);

    m_toNextAttack = 1.0f;

    m_name = "Entity";

    m_giveExp = exp;

    m_useHpInsteadOfMp = false;
}

Entity::~Entity()
{
    //dtor
    if(m_AI != 0)
        delete m_AI;
    delete m_battleSprite;
}

void Entity::AttackWasEffective()
{
    m_lastAttackWasEffective = true;
}

void Entity::AttackEntity(Entity* target)
{
    //TODO: play actual Attack animation (get from Weapon)
    Animation* newAnim = AnimationFactory::GetAnimation(AnimationFactory::Sword, target);
    GameController::getInstance()->GetActiveSceneManager()->AddAnimation(newAnim);
    //TODO: maybe change base Attack dmg
    int attack = 1;
    bool isPhysical = IsAttackPhysical();
    if(isPhysical)
    {
        attack *= GetAttribute(BattleEnums::AttributeStrength);
    }
    else
    {
        attack *= GetAttribute(BattleEnums::AttributeInt);
    }
    Attack att(attack, isPhysical, target);
    //TODO: Get Attack Type from weapon
    att.m_type.insert(BattleEnums::AttackTypePhysical);
    AttackEntity(target, &att);
}

void Entity::AttackEntity(Entity* target, Attack* attack)
{
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        iter->second->AttackEntity(attack, this);
    }
    attack->m_target->GetHit(attack, this);
}

void Entity::GetHit(Attack* attack, Entity* attacker)
{
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        iter->second->GetAttacked(attack, this, attacker);
    }
    //TODO: maybe other dmg calculation?
    float defense;
    if(attack->m_physical)
    {
        defense = GetAttribute(BattleEnums::AttributeDefense);
    }
    else
    {
        defense = GetAttribute(BattleEnums::AttributeMagicDefense);
    }
    float baseDmg = attack->m_dmg / std::sqrt(defense);
    float dmg = baseDmg;
    //add resistance or weakness to Attack type
    for(auto it = attack->m_type.begin(); it != attack->m_type.end(); it++)
    {
        dmg /= GetResistanceFor(*it);
    }

    sf::Color color = sf::Color::Black;
    if(dmg > baseDmg * 1.001f)
    {
        //effective Attack
        color = sf::Color::Red;
        attacker->AttackWasEffective();
    }
    else if(dmg < baseDmg * 0.999f)
    {
        //resisted Attack
        color = sf::Color::Blue;
    }
    int finalDmg = dmg;
    if(finalDmg < 1)
        finalDmg = 1;
    Animation * newAnim = AnimationFactory::GetTextAnimation(this, std::to_string(finalDmg), color);
    GameController::getInstance()->GetActiveSceneManager()->AddAnimation(newAnim);

    m_hp -= finalDmg;
    //TODO: play get hit animation
    if(m_hp <= 0)
    {
        m_hp = 0;
        Died();
    }
}

void Entity::Heal(int hp)
{
    if(!IsDead())
    {
        int healAmount = hp;
        m_hp += hp;
        int maxHp = GetAttribute(BattleEnums::AttributeMaxHp);
        if(m_hp > maxHp)
        {
            healAmount -= m_hp - maxHp;
            m_hp = maxHp;
        }
        if(healAmount > 0)
        {
            Animation * newAnim = AnimationFactory::GetTextAnimation(this, std::to_string(healAmount), sf::Color::Green);
            if(newAnim != nullptr)
            {
                GameController::getInstance()->GetActiveSceneManager()->AddAnimation(newAnim);
            }
        }
    }
}
void Entity::RestoreMana(int mp)
{
    m_mp += mp;
    int maxMp = GetAttribute(BattleEnums::AttributeMaxMp);
    if(m_mp > maxMp)
    {
        m_mp = maxMp;
    }
}


int Entity::GetNeededMana(int baseMp)
{
    float fMp = baseMp;
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        fMp = iter->second->GetNeededMP(fMp);
    }
    return fMp;
}

bool Entity::CanCastSkill(Skill* skill)
{
    if(m_useHpInsteadOfMp)
    {
        return GetNeededMana(skill->GetManaUse()) < m_hp;
    }
    else
    {
        return GetNeededMana(skill->GetManaUse()) <= m_mp;
    }
}


bool Entity::UseMp(int mp)
{
    mp = GetNeededMana(mp);
    if(m_useHpInsteadOfMp)
    {
        if(m_hp <= mp)
            return false;
        m_hp -= mp;
    }
    else
    {
        if(m_mp < mp)
            return false;
        m_mp -= mp;
    }
    return true;
}

void Entity::Died()
{
    //TODO: handle death + death animation
}

bool Entity::IsAttackPhysical()
{
    //TODO: Get Type of weapon / Buffs
    return true;
}

bool Entity::IsDead()
{
    return m_hp <= 0;
}

void Entity::AddSkill(Skill* skill)
{
    std::shared_ptr<Skill> sk = std::shared_ptr<Skill>(skill);
    if(skill->GetSkillType() == Skill::Passive)
    {
        AddPassiveEffect(std::static_pointer_cast<PassiveSkill>(sk));
    }
    m_skills.push_back(sk);
}

void Entity::AddSkill(std::shared_ptr<Skill> skill)
{
    if(skill->GetSkillType() == Skill::Passive)
    {
        AddPassiveEffect((PassiveSkill*) skill.get());
    }
    m_skills.push_back(skill);
}

void Entity::AddPassiveEffect(IPassiveEffect* eff)
{
    AddPassiveEffect(std::shared_ptr<IPassiveEffect>(eff));
}

void Entity::AddPassiveEffect(std::shared_ptr<IPassiveEffect> eff)
{
    m_passiveEffects.insert(std::pair<int, std::shared_ptr<IPassiveEffect>>(eff->GetActivationPriority(), eff));
    eff->OnEffectStart();
}

void Entity::RemovePassiveEffect(IPassiveEffect* eff)
{
    for(auto it = m_passiveEffects.begin(); it != m_passiveEffects.end();)
    {
        if(it->second.get() == eff)
        {
            it = m_passiveEffects.erase(it);
        }
        else
        {
            it++;
        }
    }
}

float Entity::GetResistanceFor(BattleEnums::AttackType type)
{
    float atmValue = m_resistances[type];
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        atmValue = iter->second->GetResistance(atmValue, type);
    }
    return atmValue;
}

void Entity::SetResistance(BattleEnums::AttackType type, float value)
{
    m_resistances[type] = value;
}

int Entity::GetAttribute(BattleEnums::Attribute attr)
{
    float atmValue = (float)m_attributes[attr];
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        atmValue = iter->second->GetAttribute(atmValue, attr);
    }
    return (int)atmValue;
}

void Entity::InitAttribute(BattleEnums::Attribute attr, int value)
{
    m_attributes[attr] = value;
    if(attr == BattleEnums::AttributeMaxHp)
    {
        m_hp = value;
    }
    else if(attr == BattleEnums::AttributeMaxMp)
    {
        m_mp = value;
    }
}

void Entity::InitAllAttributes(int maxHp, int maxMp, int strength, int intelligence, int defense, int magicDefense, int speed)
{
    InitAttribute(BattleEnums::AttributeMaxHp, maxHp);
    InitAttribute(BattleEnums::AttributeMaxMp, maxMp);
    InitAttribute(BattleEnums::AttributeStrength, strength);
    InitAttribute(BattleEnums::AttributeInt, intelligence);
    InitAttribute(BattleEnums::AttributeDefense, defense);
    InitAttribute(BattleEnums::AttributeMagicDefense, magicDefense);
    InitAttribute(BattleEnums::AttributeSpeed, speed);
}

void Entity::PassTime(float Time)
{
    m_toNextAttack -= Time * GetAttribute(BattleEnums::AttributeSpeed);
}

void Entity::StartBattle()
{
    m_toNextAttack = (float)rand()/RAND_MAX;
}

void Entity::StartTurn()
{
    m_lastAttackWasEffective = false;
}

void Entity::FinishedTurn()
{
    if(m_lastAttackWasEffective)
    {
        //reduce Time if last Attack was effective
        m_toNextAttack += 0.75f;
    }
    else
    {
        m_toNextAttack += 1.0f;
    }
    auto iter = m_passiveEffects.begin();
    while(iter != m_passiveEffects.end())
    {
        iter->second->OnTurn(this);
        if(iter->second->IsStillActive())
            iter++;
        else
        {
            iter = m_passiveEffects.erase(iter);
        }
    }
}


float Entity::GetTimeToNextAttack()
{
    return m_toNextAttack / GetAttribute(BattleEnums::AttributeSpeed);
}
Entity::ControllType Entity::GetControllType()
{
    return m_controllTypeAtm;
}
std::vector<std::shared_ptr<Skill>>* Entity::GetSkillList()
{
    return &m_skills;
}

std::multimap<int, std::shared_ptr<IPassiveEffect>>* Entity::GetPassiveEffects()
{
    return &m_passiveEffects;
}


void Entity::CalculateMove(SceneManagerBattle* sm)
{
    //Check if controlled by AI
    if(m_controllTypeAtm == Entity::ControllAI)
    {
        m_AI->UseNextSkill();
        sm->TurnIsFinished();
    }
}

sf::Sprite* Entity::GetBattleSprite()
{
    return m_battleSprite;
}

void Entity::SetBattleSprite(TextureList::TextureFiles newSprite)
{
    m_battleSpriteTexture = newSprite;
    Texture* tex = TextureList::getTexture(newSprite);
    m_battleSprite->setTexture(*tex);
    m_numberSprites = tex->GetNumberAnimationSteps();
}

int Entity::GetNumberSprites()
{
    return m_numberSprites;
}

int Entity::GetHp() const
{
    return m_hp;
}

int Entity::GetMp() const
{
    return m_mp;
}

void Entity::SetHp(int hp)
{
    m_hp = hp;
}

void Entity::SetMp(int mp)
{
    m_mp = mp;
}


float Entity::GetHpPercent()
{
    float maxHp = (float)GetAttribute(BattleEnums::AttributeMaxHp);
    if(maxHp == 0.0f)
        return 0.0f;
    return (float)GetHp() / maxHp;
}

float Entity::GetMpPercent()
{
    float maxMp = (float)GetAttribute(BattleEnums::AttributeMaxMp);
    if(maxMp == 0.0f)
        return 0.0f;
    return (float)GetMp() / maxMp;
}

void Entity::CheckMaxValues()
{
    float maxHp = (float)GetAttribute(BattleEnums::AttributeMaxHp);
    if(maxHp < GetHp())
        m_hp = maxHp;
    float maxMp = (float)GetAttribute(BattleEnums::AttributeMaxMp);
    if(maxMp < GetMp())
        m_mp = maxMp;
}

std::string Entity::GetName()
{
    return m_name;
}

void Entity::SetName(std::string name)
{
    m_name = name;
}

void Entity::SetUseHpInsteadOfMp(bool newValue)
{
    m_useHpInsteadOfMp = newValue;
}

int Entity::GetTeamId()
{
    return m_teamId;
}

void Entity::SetTeamId(int id)
{
    m_teamId = id;
}

void Entity::SetNode(EntityNode* node)
{
    m_node = node;
}

EntityNode* Entity::GetNode()
{
    return m_node;
}


int Entity::GetExpToGive()
{
    return m_giveExp;
}
