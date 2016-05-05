#ifndef _417game_h
#define _417game_h

#include "object.h"

struct Item {

    Object proto;

};

typedef struct Item Item;

int Item_init(void *self);

struct Monster {
    Object proto;
    int hit_points;
    int status; 
    Item *item;

};

typedef struct Monster Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);



struct Player {
    Object proto;
    int hit_points;
    Item *itens;
    int nitens;
    Item *itemAtual;
};  


typedef struct Player Player;
int Player_init(void *self);


struct Room {
    Object proto;
    Monster *bad_guy;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    Item *item;
    int lock;
    int visitada;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);
int Room_open(void *self,void *self2);

struct Map {
    Object proto;
    Room *start;
    Room *location;
    Player *player;
};

typedef struct Map Map;

void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);

#endif
