#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t tamanio;
};

struct lista_iterador {
	//y acá?
	int sarasa;
};



lista_t *lista_crear()
{
	lista_t *lista = calloc(1,sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}

	return lista;

}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista) {
		return NULL;
	}

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo) {
		return NULL;
	}

	if (lista_vacia(lista)) {
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_final = nuevo_nodo;
	} else {
		lista->nodo_final->siguiente = nuevo_nodo;
		lista->nodo_final = nuevo_nodo;
	}

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;
	(lista->tamanio)++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion) {
    if (!lista) {
        return NULL;
    }

	if (posicion > lista_tamanio(lista)) {
		return lista_insertar(lista, elemento);
	}

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo) {
        return NULL;
    }

    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = NULL;

	if (posicion == 0) {
        nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo; 
    } else {
		nodo_t *nodo_aux = lista->nodo_inicio;
		for (size_t i = 1; i < posicion; i++) {
			nodo_aux = nodo_aux->siguiente;
		}

		nuevo_nodo->siguiente = nodo_aux->siguiente;
		nodo_aux->siguiente = nuevo_nodo;
	}

    (lista->tamanio++);

    return lista;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return NULL;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista) {
		return NULL;
	}

	return lista->nodo_final->elemento;	
}

bool lista_vacia(lista_t *lista)
{
	if (!lista || lista->tamanio == 0) {
		return true;
	}

	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if(lista == NULL) {
		return 0;
	}  

	return lista->tamanio;
}

void lista_destruir(lista_t *lista)
{
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}


































lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
