#ifndef _417game_h
#define _417game_h

#include "object.h"

struct Monster {
    Object proto;
    int hit_points;
};

typedef struct Monster Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

struct Room {
    Object proto;
    Monster *bad_guy;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Item *item;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);


struct Map {
    Object proto;
    Room *start;
    Room *location;
};

typedef struct Map Map;

void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);


struct Item {

    Object proto;

};

typedef struct Item Item;
int Item_init(void *self);







#endif