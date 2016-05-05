#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

void Object_destroy(void *self)
{
    Object *obj = self;

    if(obj) {
        if(obj->description) free(obj->description);
        free(obj);
    }
}

void Object_describe(void *self)
{
    Object *obj = self;
    printf("%s.\n", obj->description);
}

int Object_init(void *self)
{
    //retorno 1 pra saber se criou o objeto
    return 1;
}

void *Object_move(void *self, Direction direction)
{
    printf("você não pode ir a essa direção.\n");
    return NULL;
}

int Object_attack(void *self, int damage)
{
    printf("você não pode atacar isso\n");
    return 0;
}


void Object_get(void *self, char *item) { 

    printf("você não pode pegar isso;\n");
 
}

void *Object_new(size_t size, Object proto, char *description)
{
    // setup the default
    if(!proto.init) proto.init = Object_init;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.move) proto.move = Object_move;
    //    if(!proto.get) proto.get = Object_get;
    
    // truque: faz um calloc e na hora de derreferenciar ele faz um cast automatico!!!
    Object *el = calloc(1, size);
    *el = proto;

    el->description = strdup(description);

    //  verifica se ou a função da classe Object abstrata ou a nova implementada tem como retorno 
    //  da função init o valor 1
    if(!el->init(el)) {
        // se entrar aqui ou é pau de alocação ou a função init esta mal escrita
        el->destroy(el);
        return NULL;
    } else {
        // finalmente criado e inicializando um object  
        // a função retorna ponteiro pra void mas na verdade é um Object!
        return el;
    }
}
