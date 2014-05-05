#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "417game.h"



int Player_init(void *self)
{

    Player *player = self;
    player->hit_points = 10;    
    player->nitens = 0;
    return 1;
    
}


void Player_describe(void *self) {

    Player *player = self;
    
    printf("\tNome: %s\n",player->_(description));
    printf("\tHitpoints: %d\n",player->hit_points);
}

      
void Player_get_item(void *mapa) {


    Map *map = mapa;
    Item *item = map->location->item;
    
    int i = map->player->nitens;
    
    if (item) {
        map->player->itens[i] = *item;
        printf("peguei %s\n",map->player->itens[i].proto.description);
        map->player->nitens++;
     }

     free(map->location->item);
     map->location->item = NULL;
}

int Player_jointValidate(void *self,char *item) { 

    
    Player *player = self;

    int i;

    for (i = 0; i < player->nitens; i++) {

        if (strcmp(player->itens[i].proto.description,item) == 0) {
            return 1;
        }

        
    }
    return 0;
}


void Player_joint_roll(void *self) { 

    printf("\tBolando um baseado\n");
    Player *player = self;
    Item *item = player->itens;
    strcpy(item[0].proto.description,"baseado");
    strcpy(item[1].proto.description,"");
    strcpy(item[2].proto.description,"");
}

void Player_describe_list(void *self) { 

    Player *player = self;

    int i;
    for (i=0; i < player->nitens; i++) {
        printf("\titem[%d]: %s\n",i,player->itens[i].proto.description);
    }

}


Object PlayerProto = { 

    .init = Player_init,
    .describe = Player_describe
};


int Item_init(void *self)
{
    return 1;
    
}

Object ItemProto = {
   
    .init = Item_init
    
};


int Monster_attack(void *self, int damage)
{
    Monster *monster = self;

    if (strcmp(monster->_(description),"O insaciavel kchaça") == 0) {
        
        
        printf("Você atacou %s!\n", monster->_(description));
        monster->hit_points -= damage;

        if(monster->hit_points > 0) {
            printf("Não esta chapado ainda.\n");
            return 0;
        } 
        else {
            printf("chapou!\n");
            return 1;
        }
    }

    else {
        printf("nao tem como chapar sem baseado!!\n");
        return 0;
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

int Room_item(void *self) {

    Room *room = self;
    Item *item = room->item;
    if (item) {
        printf("Item na sala: ");
        item->_(describe)(item);
        
        return 1;
    }
    else
        return 0;
}


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
        printf("Você foi rumo ao oeste, para\n");
        next = room->west;
    } else {
        printf("Não pode ir nessa direção.");
        next = NULL;
    }

    if(next) {
        next->_(describe)(next);
        Room_item(next);

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
    } 
    else {
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

    // instancia as salas 
    Room *hall = NEW(Room, "The 417 Hall of Horror");
    Room *arena = NEW(Room, "Calabouço, com o kchaça");
    Room *modulo1 = NEW(Room, "Modulo 1");
    Room *modulo2 = NEW(Room, "Modulo2");
    Room *modulo3 = NEW(Room, "Modulo3");

    //instancia o player

    Player *player = NEW(Player,"vicks, the Hit-Maker");
    map->player = player;
    map->player->itens = (Item*)malloc(5*sizeof(Item));

    //instancia os itens
    Item *dixava = NEW(Item,"dixavador");
    modulo1->item = dixava;

    Item *seda = NEW(Item,"seda");
    modulo2->item = seda;

    Item *maconha = NEW(Item,"maconha");
    modulo3->item = maconha;
    
    // coloca nosso grande amigo cachaça na cena!

    arena->bad_guy = NEW(Monster, "O insaciavel kchaça");

    
    // aponta os endereços das salas
    hall->west = modulo3;
    hall->north = modulo1;

    modulo3->east = hall;

    modulo1->west = arena;
    modulo1->east = modulo2;
    modulo1->south = hall;

    arena->east = modulo1;
    modulo2->west = modulo1;

    // começa o jogo colocando o personagem no hall
    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};


void help () { 

    printf("\n");
    printf("\t Comandos:\n");
    printf("\t\t l: lista os vizinhos\n");
    printf("\t\t i: informações do player\n");
    printf("\t\t k: inventario\n");
    printf("\t\t g: pega um item da sala\n");
    printf("\t\t a: ataca!\n");
    printf("\t\t j: enrola um baseado\n");
}


void Arte_ascii() {

    printf("\n");
    printf("\n");

    printf("=============================================================================\n");
    printf("\n");
    printf("                             d8888  d888  8888888888                         \n");
    printf("          db                d8P888 d8888        d88P            db           \n");
    printf("          88               d8P 888   888       d88P             88           \n");
    printf("   b.     88     .d       d8P  888   888      d88P       b.     88     .d    \n");
    printf("    Yb.   88   .dP       d88   888   888   88888888       Yb.   88   .dP     \n");
    printf("      Yb. 88 .dP         8888888888  888    d88P            Yb. 88 .dP       \n");
    printf("        Yb88dP                 888   888   d88P               Yb88dP         \n");
    printf(" <888888888888888888>          888 888888 d88P         <888888888888888888>  \n");
    printf("\n");
    printf("\n");

    printf("     888    888       d8888   888     888            .d88888b. 8888888888   \n");
    printf("     888    888      d88888   888     888           d88P   Y88b888          \n");
    printf("     888    888     d88P888   888     888           888     888888          \n");
    printf("     8888888888    d88P 888   888     888           888     8888888888      \n");
    printf("     888    888   d88P  888   888     888           888     888888          \n");
    printf("     888    888  d88P   888   888     888           888     888888          \n");
    printf("     888    888 d8888888888   888     888           Y88b. .d88P888          \n");
    printf("     888    888d88P     888   8888888888888888       Y88888PP  888          \n");

    printf("\n");
    printf("\n");

    printf("   888    888 .d88888b. 8888888b. 8888888b.  .d88888b. 8888888b.  .d88888b.  \n");
    printf("   888    888d88P   Y88b888    88b888   Y88bd88P   Y88b888   Y88bd88P   Y88  \n");   
    printf("   888    888888     888888    888888    888888     888888    888888         \n");
    printf("   8888888888888     888888   d88P888   d88P888     888888   d88PY88b.       \n");
    printf("   888    888888     8888888888P  8888888P  888     8888888888P   Y888888b.  \n");   
    printf("   888    888888     888888 T88b  888 T88b  888     888888 T88b        Y888  \n");
    printf("   888    888Y88b. .d88P888  T88b 888  T88b Y88b. .d88P888  T88b 88b. .d888  \n");
    printf("   888    888 Y88888P 88888   T88b888   T888b Y88888P  888   T88bY8888888P   \n");
    printf("\n");
    printf("=============================================================================\n");
    printf("\n");
    printf("\n");


}

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
            if (game->player->itens[0].proto.description && strcmp(game->player->itens[0].proto.description,"baseado") == 0)
                game->_(attack)(game, damage);
            else {
                printf("voce tem que ter um baseado\n"); 
            }
            break;

        case 'g':
            
            if (game->location->item) {
                Player_get_item(game);
            }
            break;
        
        case 'i': 
            game->player->_(describe)(game->player);
            break;
        
        case 'k': 
            Player_describe_list(game->player);
            break;
        
        case 'j':
            if (Player_jointValidate(game->player,"seda") && Player_jointValidate(game->player,"maconha") &  Player_jointValidate(game->player,"dixavador"))
            { 
                Player_joint_roll(game->player);
            }
            else
                printf("voce nao pode bolar um baseado ainda..\n");
            break;
        case 'l':
            printf("Você pode ir para:\n");
            if(game->location->north) printf("(n)Norte\n");
            if(game->location->south) printf("(s)Sul\n");
            if(game->location->east) printf("(e)Leste\n");
            if(game->location->west) printf("(w)Oeste\n");
            break;
        case 'h' :
            help();
            break;
        default:
            printf("ahhmmm?: %d\n", ch);
    }

    return 1;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Map *game = NEW(Map, "417 hall of horror");

    Arte_ascii();
    printf("Voce entrou no ");
    game->location->_(describe)(game->location);

    while(process_input(game)) {
    }

    return 0;
}
