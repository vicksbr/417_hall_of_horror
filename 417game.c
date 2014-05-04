#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "417game.h"


int Monster_attack(void *self, int damage)
{
    Monster *monster = self;

    printf("Você atacou %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if(monster->hit_points > 0) {
        printf("Não esta chapado ainda.\n");
        return 0;
    } else {
        printf("chapou!\n");
        return 1;
    }
}

int Monster_init(void *self)
{
    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};


void *Room_move(void *self, Direction direction)
{
    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room->north) {
        printf("Você foi rumo ao norte, para:\n");
        next = room->north;
    } else if(direction == SOUTH && room->south) {
        printf("Você foi rumo ao sul, para\n");
        next = room->south;
    } else if(direction == EAST && room->east) {
        printf("Você foi rumo ao leste, para\n");
        next = room->east;
    } else if(direction == WEST && room->west) {
        printf("Você foi rumo ao oest, para\n");
        next = room->west;
    } else {
        printf("Não pode ir nessa direção.");
        next = NULL;
    }

    if(next) {
        next->_(describe)(next);
    }

    return next;
}


int Room_attack(void *self, int damage)
{
    Room *room = self;
    Monster *monster = room->bad_guy;

    if(monster) {
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("Você não tem quem atacar, anta.\n");
        return 0;
    }
}


Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};


void *Map_move(void *self, Direction direction)
{
    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location, direction);

    if(next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    Map* map = self;
    Room *location = map->location;

    return location->_(attack)(location, damage);
}


int Map_init(void *self)
{
    Map *map = self;

    // make some rooms for a small map
    Room *hall = NEW(Room, "The 417 Hall of Horror");
    Room *modulo1 = NEW(Room, "Modulo 1, você pegou o dixavador");
    Room *arena = NEW(Room, "The arena, com o kchaça");
    Room *modulo2 = NEW(Room, "Modulo2, você tem o baseado agora!");

    // put the bad guy in the arena
    arena->bad_guy = NEW(Monster, "O insaciavel kchaça");

    // setup the map rooms
    hall->north = modulo1;

    modulo1->west = arena;
    modulo1->east = modulo2;
    modulo1->south = hall;

    arena->east = modulo1;
    modulo2->west = modulo1;

    // start the map and the character off in the hall
    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map *game)
{
    printf("\n> ");

    char ch = getchar();
    getchar(); // eat ENTER

    int damage = rand() % 4;

    switch(ch) {
        case 45:
            printf("GG WP.\n");
            return 0;
            break;

        case 'n':
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':

            game->_(attack)(game, damage);
            break;
        case 'l':
            printf("Você pode ir para:\n");
            if(game->location->north) printf("(n)Norte\n");
            if(game->location->south) printf("(s)Sul\n");
            if(game->location->east) printf("(e)Leste\n");
            if(game->location->west) printf("(w)Oeste\n");
            break;

        default:
            printf("ahhmmm?: %d\n", ch);
    }

    return 1;
}

int main(int argc, char *argv[])
{
    // simple way to setup the randomness
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "417 hall of horror");

    printf("Voce entrou no ");
    game->location->_(describe)(game->location);

    while(process_input(game)) {
    }

    return 0;
}
