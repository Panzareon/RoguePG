#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

namespace BattleEnums
{
    enum Target{TargetOwnTeamEntity, TargetEnemyTeamEntity, TargetOwnTeam, TargetEnemyTeam, TargetSelf, TargetNone, TargetAll, TARGET_END};
    enum AttackType{AttackTypePhysical, AttackTypeFire, AttackTypeWater, AttackTypeEarth, AttackTypeAir, ATTACK_TYPE_END};
    enum EffectType{EffectTypeDamage, EffectTypeHeal, EffectTypeDebuff, EffectTypeBuff, EffectTypeBuffDefense, EffectTypeBuffOffense, EffectTypeBuffMagic, EffectTypeDebuffDefense, EffectTypeDebuffOffense, EffectTypeDebuffMagic, EFFECT_TYPE_END};
    enum Attribute{AttributeMaxHp, AttributeMaxMp, AttributeStrength, AttributeInt, AttributeDefense, AttributeMagicDefense, AttributeSpeed, ATTRIBUTE_END};
}

namespace Enums
{
    enum Direction {North, East, South, West};
}
#endif // ENUMS_H_INCLUDED
