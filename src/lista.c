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

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
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

	nodo_t *nodo_actual = lista->nodo_inicio;
	int posicion_actual = 1;


	if (posicion == 0) {
        nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo; 
    } else {
		while (posicion_actual < posicion) {
			nodo_actual = nodo_actual->siguiente;
			posicion_actual++;
		}

		nuevo_nodo->siguiente = nodo_actual->siguiente;
		nodo_actual->siguiente = nuevo_nodo;
	}

	nuevo_nodo->elemento = elemento;
    (lista->tamanio)++;

    return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || lista_vacia(lista))
		return NULL;

	void *elemento_quitado = NULL;
	nodo_t *nodo_actual = lista->nodo_inicio;

	if (lista->nodo_inicio->siguiente == NULL) {
        elemento_quitado = lista->nodo_inicio->elemento;
        free(lista->nodo_inicio);
        (lista->tamanio)--;
        return elemento_quitado;
    }

	while (nodo_actual->siguiente->siguiente != NULL) {
			nodo_actual = nodo_actual->siguiente;
	}
	
	elemento_quitado = nodo_actual->siguiente->elemento;

    free(nodo_actual->siguiente);
    nodo_actual->siguiente = NULL;
    lista->nodo_final = nodo_actual;

	(lista->tamanio)--;

	return elemento_quitado;
}


void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista)) {
        return NULL;
    }

	if (posicion > lista_tamanio(lista)) {
		return lista_quitar(lista);
	}

	void *elemento_quitado = NULL;
	nodo_t *nodo_anterior = lista->nodo_inicio;
	nodo_t *nodo_aux = lista->nodo_inicio;
	size_t posicion_actual = 0;

	if (posicion == 0) {
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		if (lista->nodo_inicio == NULL) {
            lista->nodo_final = NULL; 
        }
		free(nodo_aux);
	} else {
		while (posicion_actual < posicion - 1) {
			nodo_anterior = nodo_anterior->siguiente;
			posicion_actual++;
		}

		nodo_aux = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo_anterior->siguiente->siguiente;

		if (nodo_anterior->siguiente == NULL) {
            lista->nodo_final = nodo_anterior;
        }

		elemento_quitado = nodo_aux->elemento;
		free(nodo_aux);
	}

	(lista->tamanio)--;
	return elemento_quitado;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || posicion > lista_tamanio(lista)) {
		return NULL;
	}

	nodo_t *nodo_actual = lista->nodo_inicio;
	size_t posicion_actual = 0;

	while (posicion_actual < posicion) {
		nodo_actual = nodo_actual->siguiente;
		posicion_actual++;
	}

	return nodo_actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if(!lista || !comparador || !contexto || lista_vacia(lista)) {
		return NULL;
	}

	nodo_t *nodo_actual = lista->nodo_inicio;
	int posicion_actual = 0;

	while (nodo_actual != NULL && posicion_actual < lista_tamanio(lista)) {
		if (comparador(nodo_actual->elemento, contexto) == 0) {
			return nodo_actual->elemento;
		} 
		nodo_actual = nodo_actual->siguiente;
		posicion_actual++;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (!lista || lista_vacia(lista)) {
		return NULL;
	}
	
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista || lista_vacia(lista)) {
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

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *)) 
{
    if (!lista) {
        return;
    }

    nodo_t *nodo_actual = lista->nodo_inicio;
    nodo_t *nodo_aux = NULL;

    while (nodo_actual != NULL) {
        nodo_aux = nodo_actual->siguiente;
        if (funcion != NULL) {
            funcion(nodo_actual->elemento); 
        }
        free(nodo_actual);
        nodo_actual = nodo_aux; 
    }

    free(lista); 
}


void lista_destruir(lista_t *lista)
{
	if (!lista) {
		return;
	}

	lista_destruir_todo(lista, NULL);
	
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
