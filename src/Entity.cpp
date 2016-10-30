#include "Entity.h"
#include "AIRandom.h"
#include "SceneManagerBattle.h"
#include <math.h>
#include <map>
#include "TextureList.h"

Entity::Entity()
{
    //ctor
    m_controllTypeAtm = Entity::ControllAI;
    m_teamId = -1;

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
}

Entity::~Entity()
{
    //dtor
    if(m_AI != 0)
        delete m_AI;
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
        delete iter->second;
    delete m_battleSprite;
}
void Entity::AttackEntity(Entity* target)
{
    //TODO: play Attack animation
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
    Attack att(attack, isPhysical);
    AttackEntity(target, &att);
}

void Entity::AttackEntity(Entity* target, Attack* attack)
{
    for(auto iter = m_passiveEffects.begin(); iter != m_passiveEffects.end(); iter++)
    {
        iter->second->AttackEntity(attack, target, this);
    }
    target->GetHit(attack, this);
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
    float dmg = attack->m_dmg / std::sqrt(defense);
    //add resistance or weakness to Attack type
    for(auto it = attack->m_type.begin(); it != attack->m_type.end(); it++)
    {
        dmg *= GetResistanceFor(*it);
    }
    m_hp -= dmg;
    //TODO: play get hit animation
    if(m_hp <= 0)
    {
        m_hp = 0;
        Died();
    }
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
    m_skills.push_back(*skill);
}

void Entity::AddPassiveEffect(IPassiveEffect* eff)
{
    m_passiveEffects.insert(std::pair<int, IPassiveEffect*>(eff->GetActivationPriority(), eff));
    eff->OnEffectStart();
}

void Entity::RemovePassiveEffect(IPassiveEffect* eff)
{
    for(auto it = m_passiveEffects.begin(); it != m_passiveEffects.end();)
    {
        if(it->second == eff)
        {
            delete it->second;
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
        m_hp = attr;
    }
}

void Entity::InitAllAttributes(int maxHp, int strength, int intelligence, int defense, int magicDefense)
{
    InitAttribute(BattleEnums::AttributeMaxHp, maxHp);
    InitAttribute(BattleEnums::AttributeStrength, strength);
    InitAttribute(BattleEnums::AttributeInt, intelligence);
    InitAttribute(BattleEnums::AttributeDefense, defense);
    InitAttribute(BattleEnums::AttributeMagicDefense, magicDefense);
}

void Entity::PassTime(float Time)
{
    m_toNextAttack -= Time * GetAttribute(BattleEnums::AttributeSpeed);
}

void Entity::FinishedTurn()
{
    m_toNextAttack += 1.0f;
    auto iter = m_passiveEffects.begin();
    while(iter != m_passiveEffects.end())
    {
        iter->second->OnTurn();
        if(iter->second->IsStillActive())
            iter++;
        else
        {
            delete iter->second;
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
std::vector<Skill>* Entity::GetSkillList()
{
    return &m_skills;
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
    Texture* tex = TextureList::getTexture(newSprite);
    m_battleSprite->setTexture(*tex);
    m_numberSprites = tex->GetNumberAnimationSteps();
}

int Entity::GetNumberSprites()
{
    return m_numberSprites;
}

int Entity::GetTeamId()
{
    return m_teamId;
}

void Entity::SetTeamId(int id)
{
    m_teamId = id;
}

