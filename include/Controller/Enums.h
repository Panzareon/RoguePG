#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

namespace BattleEnums
{
    enum class Target{OwnTeamEntity, EnemyTeamEntity, OwnTeam, EnemyTeam, Self, None, All, Passive, OwnTeamRandomEntity, EnemyTeamRandomEntity, COUNT};
    enum class AttackType{Physical, Fire, Water, Earth, Air, COUNT};
    enum class EffectType{Damage, Heal, Debuff, Buff, BuffDefense, BuffOffense, BuffMagic, DebuffDefense, DebuffOffense, DebuffMagic, Passive, COUNT};
    enum class Attribute{MaxHp, MaxMp, Strength, Int, Defense, MagicDefense, Speed, COUNT};
}

namespace Enums
{
    enum class Direction {North, East, South, West};
    enum class EnemyTypes {EnemyBoss, EnemyChest, EnemyDefault};
    enum class GenerationType {Cave, Dungeon, ConnectedCaves};
}
#endif // ENUMS_H_INCLUDED
