#ifndef _objeto_h
#define _objeto_h

typedef struct { 

	char *descricao;

	int (*iniciar)(void *abstrato);
	void (*sobre)(void *abstrato); 

}Objeto;


int objeto_iniciar(void *abstrato);
void objeto_sobre (void *abstrato);

void *objeto_criar(size_t tam,Objeto obj,char *descricao);

//#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
//#define _(N) proto.N

#endif



