#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    MAIN_TITLE,
    GAME_PLAY,
    ANIMATION
} GAMESTATE;

typedef enum {
    GAME_KAISHI,
    TURN_KAISHI,
    CARD_SELECT,
    USE_CARD,
    PLAYER_ANIM,
    SHOW_MESSAGES,
    ENEMY_TURN,
    ENEMY_ANIM,
    WIN_CHECK,
    LOSE_CHECK,
    CALC_SPOILS,
    BATTLE_END
} BATTLESTATE;

typedef enum {
    CT_ATTACK,
    CT_SHIELD,
    CT_HEAL
} CARDTYPE;

typedef enum {
    ANIM_ATTACK,
    ANIM_SHIELD,
    ANIM_HEAL,
    ANIM_ENEMY_ATTACK,
    ANIM_ENEMY_SHIELD,
    ANIM_ENEMY_HEAL
} ANIMTYPE;

typedef enum {
    SHURIKEN = 0U,  // Low cost damage
    KATANA   = 1U,  // High cost big damage
    HASAMI   = 2U,  // Higher cost bigger damage
    HIKOUKI  = 3U,  // Free cost, small damage
    SHATSU   = 4U,  // Low cost shield
    KABUTO   = 5U,  // High cost shield
    HAATO    = 6U,  // Heal
    EMPTY    = 7U
} CARDFACE;

typedef enum {
    P1  = 0U,
    CPU = 1U
} PLAYERNAME;

// extern BOOLS bools;
extern GAMESTATE gamestate;
extern ANIMTYPE animtype;
extern BATTLESTATE battlestate;
extern CARDTYPE cardtype;
extern CARDFACE cardface;
extern PLAYERNAME playername;
 
#endif