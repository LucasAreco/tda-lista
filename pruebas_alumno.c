#include "pa2m.h"
#include "src/lista.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t *tamanio;
};

struct lista_iterador {
	//y acá?
	int sarasa;
};

int comparador_prueba(void *elemento_1, void *elemento_2) 
{
	if (!elemento_1 || !elemento_2) {
		return -1;
	}

	if (*(int*)elemento_1 == *(int*)elemento_2) {
		return 0;
	}

	return -1;
}

void lista_crear_crea_una_lista_vacia() 
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crear lista.");
	pa2m_afirmar(lista_vacia(lista) == true, "Se crea lista vacia.");
	pa2m_afirmar(lista->nodo_inicio == NULL, "Al crear la lista, el nodo inicial es NULL.");
	pa2m_afirmar(lista->nodo_final == NULL, "Al crear la lista, el nodo final es NULL.");

	lista_destruir(lista);
}

void lista_insertar_insierta_un_elemento_al_final()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;

	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);

	pa2m_afirmar(lista != NULL && lista->nodo_inicio->elemento == elemento_1 , "Se puede insertar un elemento en la lista vacía.");
	pa2m_afirmar(lista->nodo_final->elemento == elemento_2, "Se puede insertar un elemento en una lista no vacía.");
	pa2m_afirmar(lista->nodo_final->siguiente == NULL, "El ultimo nodo apunta a NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "Se actualiza el tamaño de la lista.");

	lista_destruir(lista);
}

void lista_insertar_en_posicion_inserta_elemento_en_posicion() 
{
    lista_t *lista = lista_crear();
    int numero_1 = 1;
    int numero_2 = 2;
    int numero_3 = 3;
    int numero_4 = 4;
    int numero_5 = 5;
    int numero_6 = 6;
    int numero_7 = 7;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;
	void *elemento_5 = &numero_5;
	void *elemento_6 = &numero_6;
	void *elemento_7 = &numero_7;


    lista = lista_insertar(lista, elemento_1);
    lista = lista_insertar(lista, elemento_2);

    lista_insertar_en_posicion(lista, elemento_3, 0);
    lista_insertar_en_posicion(lista, elemento_4, 1); 
    lista_insertar_en_posicion(lista, elemento_5, 3); 
    lista_insertar_en_posicion(lista, elemento_6, 4); 
    lista_insertar_en_posicion(lista, elemento_7, 10); 

    pa2m_afirmar(lista->nodo_inicio->elemento == elemento_3, "Inserta un elemento al inicio de la lista.");
    pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento_4, "Inserta un elemento en la posición 1.");
    pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->siguiente->elemento == elemento_5, "Inserta un elemento en el medio de la lista.");
    pa2m_afirmar(lista->nodo_final->elemento == elemento_7, "Inserta un elemento al final de la lista.");
    pa2m_afirmar(lista->nodo_final->siguiente == NULL, "El último nodo apunta a NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 7, "Aumenta correctamente el tamaño de la lista.");

	lista_destruir(lista);
} 

void lista_quitar_quita_elementos_al_final()
{
	lista_t *lista = lista_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;

	lista_insertar(lista, elemento_0);

	pa2m_afirmar(lista_quitar(lista) == elemento_0, "Se quita el único elemento correctamente.");
	pa2m_afirmar(lista_vacia(lista), "Al quitar el unico elemento, lista queda vacía.");

	lista_insertar(lista, elemento_1); 
	lista_insertar(lista, elemento_2); 
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(lista_quitar(lista) == elemento_3, "Se quita el último elemento correctamente.");
	pa2m_afirmar(lista_ultimo(lista) == elemento_2, "El nuevo ultimo elemento es correcto.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "Reduce tamaño de la lista");
	pa2m_afirmar(lista->nodo_final->siguiente == NULL, "El ultimo nodo apunta a NULL.");

	lista_destruir(lista);
}

void lista_quitar_en_posicion_quita_elemento_en_posicion()
{
	lista_t *lista = lista_crear();


	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1); 
	lista_insertar(lista, elemento_2); 
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == elemento_2, "Se quita el elemento de la posicion dada correctamente.");
	pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento_1, "Anterior al eliminado sigue en lista.");
	pa2m_afirmar(lista_ultimo(lista) == elemento_3, "Se mantiene vinculado el ultimo elemento de la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 3, "Resta tamaño de la lista.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 10) == elemento_3, "Elimina el último elemento si se le pasa una posicion mayor al tamaño.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "Resta tamaño de la lista.");

	lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(lista_primero(lista) == elemento_1, "Quita el primer elemento correctamente.");
	pa2m_afirmar(lista_ultimo(lista) == elemento_1, "Continua vinculado el ultimo elemento a la lista.");

	lista_insertar(lista, elemento_3);
	lista_quitar_de_posicion(lista, 10);
	pa2m_afirmar(lista_ultimo(lista) == elemento_1, "Se mantiene vinculado el ultimo elemento de la lista.");

	lista_destruir(lista);
}

void lista_elemento_en_posicion_devuelve_elemento_segun_posicion_dada() 
{
	lista_t *lista = lista_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1); 
	lista_insertar(lista, elemento_2); 
	lista_insertar(lista, elemento_3);
	
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == elemento_0, "Al indicarle la primera posicion, devuelve correctamente el primer elemento.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == elemento_1, "Al indicarle la segunda posicion, devuelve correctamente el segundo elemento.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 10) == NULL, "Al indicarle una posicion invalida, devuelve NULL.");

	lista_destruir(lista);
}


void lista_buscar_elemento_busca_segun_condicion_dada() {
	lista_t *lista = lista_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1); 
	lista_insertar(lista, elemento_2); 
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(lista_buscar_elemento(lista, comparador_prueba, elemento_1) == elemento_1, "Devuelve correctamente el elemento buscado");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_prueba, elemento_2) == elemento_2, "Devuelve correctamente el elemento buscado");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_prueba, NULL) == NULL, "Al pasar contexto nulo, devuelve NULL");
	pa2m_afirmar(lista_buscar_elemento(NULL, comparador_prueba, elemento_0) == NULL, "Al pasar una lista nula, devuelve NULL");
	pa2m_afirmar(lista_buscar_elemento(lista, NULL, elemento_1) == NULL, "Al pasar una función nula, devuelve NULL"); 

	lista_destruir(lista);
}




int main()
{
	pa2m_nuevo_grupo("\nCreación lista vacía");
	lista_crear_crea_una_lista_vacia();

	pa2m_nuevo_grupo("\nInserción de elementos al final");
	lista_insertar_insierta_un_elemento_al_final();

	pa2m_nuevo_grupo("\nInserción de elementos en posicion especifica");
	lista_insertar_en_posicion_inserta_elemento_en_posicion();
	
	pa2m_nuevo_grupo("\nQuita de elemento al final.");
	lista_quitar_quita_elementos_al_final();

	pa2m_nuevo_grupo("\nQuita de elementos en posicion especifica");
	lista_quitar_en_posicion_quita_elemento_en_posicion();

	pa2m_nuevo_grupo("\nObtencion elemento segun posición.");
	lista_elemento_en_posicion_devuelve_elemento_segun_posicion_dada();

	pa2m_nuevo_grupo("\nObtencion elemento segun condicion.");
	lista_buscar_elemento_busca_segun_condicion_dada();

	return pa2m_mostrar_reporte();
}
