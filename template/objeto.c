#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "objeto.h"


int objeto_iniciar(void *abstrato) { 

	return 1;

}


void objeto_sobre (void *abstrato) { 

	Objeto *obj = abstrato;
	printf("%s.\n",obj->descricao);
}


void *objeto_criar(size_t tam,Objeto obj,char *descricao) { 

	
	if (!obj.iniciar) 
		obj.iniciar = objeto_iniciar; 
	if (!obj.sobre) 
		obj.sobre = objeto_sobre;
	Objeto *instancia = calloc(1,tam);
	*instancia = obj;

	instancia->descricao = strdup(descricao);

	return instancia;

}


void humano_sobre(void *abstrato) { 

	Objeto *obj = abstrato;
	printf("%s.\n",obj->descricao);

}

void cachorro_sobre(void *abstrato) { 

	Objeto *obj = abstrato;
	printf("%s.\n",obj->descricao);

}

Objeto humanoObjeto = {
   
    .sobre = humano_sobre
    
};

Objeto cachorroObjeto = {
   
    .sobre = cachorro_sobre
    
};



int main () { 

	Objeto *humano;
	humano = objeto_criar(sizeof(humano),humanoObjeto,"sou humano!"); 

	Objeto *cachorro;
	cachorro = objeto_criar(sizeof(cachorro),cachorroObjeto,"sou um cachorro!");

	humano->sobre(humano);
	cachorro->sobre(cachorro);
	
	return 0;

}



