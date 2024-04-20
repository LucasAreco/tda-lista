#include "pa2m.h"
#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
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
	nodo_t *corriente;
	lista_t *lista;
};

int comparador_numeros(void *elemento_1, void *elemento_2)
{
	if (!elemento_1 || !elemento_2) {
		return -1;
	}

	if (*(int *)elemento_1 == *(int *)elemento_2) {
		return 0;
	}

	return -1;
}

void lista_crear_crea_una_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crear lista válida.");
	pa2m_afirmar(lista_vacia(lista) == true, "Se crea lista vacia.");
	pa2m_afirmar(lista->nodo_inicio == NULL,
		     "Al crear una lista, el nodo inicial es NULL.");
	pa2m_afirmar(lista->nodo_final == NULL,
		     "Al crear una lista, el nodo final es NULL.");

	lista_destruir(lista);
}

void lista_insertar_insierta_un_elemento_al_final()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;

	pa2m_afirmar(lista_insertar(NULL, elemento_3) == NULL,
		     "Insertar al final de una lista nula devuelve NULL.");

	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(
		lista->nodo_inicio->elemento == elemento_1,
		"Se puede insertar un elemento en una lista vacía y su posición es correcta");
	pa2m_afirmar(
		lista->nodo_final->elemento == elemento_3,
		"Se puede insertar un elemento en una lista no vacía y su posición es correcta.");
	lista_insertar(lista, false);
	pa2m_afirmar(lista->nodo_final->elemento == false,
		     "Se puede insertar al final un false.");
	lista_insertar(lista, NULL);
	pa2m_afirmar(lista->nodo_final->elemento == NULL,
		     "Se puede insertar al final un NULL.");
	pa2m_afirmar(lista->nodo_final->siguiente == NULL,
		     "El ultimo nodo apunta a NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "Se actualiza el tamaño de la lista.");

	lista_destruir(lista);
}

void lista_insertar_en_posicion_inserta_elemento_en_posicion()
{
	lista_t *lista = lista_crear();

	int numero_3 = 3;
	int numero_4 = 4;
	int numero_5 = 5;
	int numero_7 = 7;
	char caracter_x = 'x';

	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;
	void *elemento_5 = &numero_5;
	void *elemento_7 = &numero_7;
	void *elemento_x = &caracter_x;

	pa2m_afirmar(
		lista_insertar_en_posicion(NULL, elemento_3, 20) == NULL,
		"Insertar en un cualquier posición de una lista nula devuelve NULL.");

	lista_insertar_en_posicion(lista, elemento_3, 0);

	pa2m_afirmar(
		lista->nodo_inicio->elemento == elemento_3,
		"Inserta un elemento al inicio de una lista vacía y la posición es correcta.");

	lista_insertar_en_posicion(lista, elemento_4, 1);
	lista_insertar_en_posicion(lista, elemento_5, 2);

	pa2m_afirmar(
		lista->nodo_inicio->elemento == elemento_3 &&
			lista->nodo_inicio->siguiente->elemento == elemento_4 &&
			lista->nodo_final->elemento == elemento_5,
		"Inserta varios elementos y todas las posiciones son correctas.");

	lista_insertar_en_posicion(lista, elemento_x, 1);
	pa2m_afirmar(
		lista->nodo_inicio->siguiente->elemento == elemento_x,
		"Inserta un elemento en cualquier posición de una lista no vacía y la posición es correcta.");

	lista_insertar_en_posicion(lista, elemento_7, 10);
	pa2m_afirmar(
		lista->nodo_final->elemento == elemento_7,
		"Al pasar una posición mayor al tamaño, se agrega el elemento al final de una lista por defecto.");

	lista_insertar_en_posicion(lista, elemento_7, 90);
	pa2m_afirmar(lista->nodo_final->elemento == elemento_7,
		     "Inserta elemento repetido en una lista correctamente.");

	lista_insertar_en_posicion(lista, NULL, 1);
	pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == NULL,
		     "Inserta un elemento nulo en una lista válida.");

	pa2m_afirmar(lista->nodo_final->siguiente == NULL,
		     "El último nodo apunta a NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 7,
		     "Se actualiza el tamaño de una lista correctamente.");

	lista_destruir(lista);
}

void lista_quitar_quita_elementos_al_final()
{
	lista_t *lista = lista_crear();

	char letra_1 = 'A';
	char letra_2 = 'L';
	char letra_3 = 'G';
	char letra_4 = 'O';

	void *elemento_1 = &letra_1;
	void *elemento_2 = &letra_2;
	void *elemento_3 = &letra_3;
	void *elemento_4 = &letra_4;

	pa2m_afirmar(lista_quitar(NULL) == NULL,
		     "Quitar al final en una lista nula devuelve NULL.");
	pa2m_afirmar(lista_quitar(lista) == NULL,
		     "Quitar al final en una lista vacía devuelve NULL.");

	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);
	lista_insertar(lista, elemento_4);

	pa2m_afirmar(lista_quitar(lista) == elemento_4,
		     "Quita el único elemento de una lista no vacía.");

	lista_insertar(lista, NULL);
	pa2m_afirmar(lista->nodo_final->elemento == NULL,
		     "Quita un elemento nulo de la lista.");

	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "Al quitar, reduce el tamaño de una lista.");
	pa2m_afirmar(lista->nodo_final->siguiente == NULL,
		     "El ultimo nodo apunta a NULL.");

	lista_destruir(lista);
}

void lista_quitar_en_posicion_quita_elemento_en_posicion()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(
		lista_quitar_de_posicion(NULL, 1) == NULL,
		"Quitar en cualquier posición de una lista nula devuelve NULL.");
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 4) == NULL,
		"Quitar en cualquier posición de una lista vacía devuelve NULL.");

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

	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 2) == elemento_2,
		"Quita de cualquier posición un elemento en una lista no vacía.");
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 902) == elemento_3,
		"Al pasar una posición mayor al tamaño, se quita el elemento al final de una lista por defecto.");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == elemento_0 &&
			     lista_quitar_de_posicion(lista, 1) == elemento_1,
		     "Quita varios elementos de una lista.");

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);

	lista_insertar_en_posicion(lista, NULL, 2);
	pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == NULL,
		     "Quita un elemento nulo de la lista.");

	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "Al quitar, reduce el tamaño de una lista.");
	pa2m_afirmar(lista->nodo_final->siguiente == NULL,
		     "El ultimo nodo apunta a NULL.");

	lista_destruir(lista);
}

void lista_elemento_en_posicion_obtiene_elemento_de_la_posicion_indicada()
{
	lista_t *lista = lista_crear();

	char letra_1 = 'A';
	char letra_2 = 'L';
	char letra_3 = 'G';
	char letra_4 = 'O';

	void *elemento_1 = &letra_1;
	void *elemento_2 = &letra_2;
	void *elemento_3 = &letra_3;
	void *elemento_4 = &letra_4;

	pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL,
		     "Obtener elemento de una lista nula, devuelve NULL.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "Obtener elemento de una lista vacía, devuelve NULL");

	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);
	lista_insertar(lista, elemento_4);

	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == elemento_2,
		"Al indicarle una posición válida, devuelve correctamente el elemento de esa posición.");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 10) == NULL,
		"Al indicarle una posicion invalida en una lista válida, develve NULL");

	lista_destruir(lista);
}

void lista_buscar_elemento_busca_segun_condicion_dada()
{
	lista_t *lista = lista_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	int numero_4 = 4;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;

	pa2m_afirmar(lista_buscar_elemento(NULL, comparador_numeros,
					   elemento_1) == NULL,
		     "Buscar en una lista nula, devuelve NULL.");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_numeros,
					   elemento_2) == NULL,
		     "Buscar en una lista vacía, devuelve NULL.");
	pa2m_afirmar(lista_buscar_elemento(lista, NULL, elemento_4) == NULL,
		     "Buscar con un comparador nulo, devuelve NULL.");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_numeros, NULL) ==
			     NULL,
		     "Buscar con un contexto nulo, devuelve NULL.");

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(
		lista_buscar_elemento(lista, comparador_numeros, elemento_3) ==
			elemento_3,
		"Devuelve correctamente el elemento buscado de acuerdo al contexto.");
	pa2m_afirmar(
		lista_buscar_elemento(lista, comparador_numeros, elemento_4) ==
			NULL,
		"Buscar un elemento que no existe en la lista, devuelve NULL.");

	lista_destruir(lista);
}

void lista_tamanio_devuelve_cantidad_de_elemento_de_la_lista()
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

	pa2m_afirmar(lista_tamanio(NULL) == 0,
		     "El tamaño de una lista nula es 0.");
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "El tamaño de una lista vacía es 0.");

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "Devuelve correctamente el tamaño de una lista no vacía.");

	lista_destruir(lista);
}

void lista_vacia_devuelve_si_tiene_elementos_o_no_la_lista()
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

	pa2m_afirmar(lista_vacia(NULL) == true,
		     "Verifica que la lista nula este vacía.");
	pa2m_afirmar(lista_vacia(lista) == true,
		     "Verifica que la lista vacía este vacía.");

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(lista_vacia(lista) == false,
		     "Verifica que la lista con elementos no este vacía.");

	lista_destruir(lista);
}

void lista_primer_y_ultimo_elemento()
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

	pa2m_afirmar(lista_primero(NULL) == NULL,
		     "El primer elemento de una lista nula es nulo.");
	pa2m_afirmar(lista_primero(lista) == NULL,
		     "El primero elemento de una lista vacía es nulo.");
	pa2m_afirmar(lista_ultimo(NULL) == NULL,
		     "El último elemento de una lista nula es nulo.");
	pa2m_afirmar(lista_ultimo(lista) == NULL,
		     "El último elemento de una lista vacía es nulo.");

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);

	pa2m_afirmar(
		lista_primero(lista) == elemento_0,
		"Obtiene el primer elemento de una lista no vacía correctamente.");
	pa2m_afirmar(
		lista_ultimo(lista) == elemento_3,
		"Obtiene el úlitmo elemento de una lista no vacía correctamente.");

	lista_destruir(lista);
}

bool es_menor(void *elemento_1, void *elemento_2)
{
	return *(int *)elemento_1 < *(int *)elemento_2;
}

bool es_mayor(void *elemento_1, void *elemento_2)
{
	return *(int *)elemento_1 > *(int *)elemento_2;
}

void iterador_interno_itera_internamente_sobre_lista()
{
	lista_t *lista = lista_crear();

	int numero_x = 100;
	int numero_y = 10;
	int numero_z = 3;
	int numero_p = 203;
	int numero_k = 2;

	void *elemento_0 = &numero_x;
	void *elemento_1 = &numero_y;
	void *elemento_2 = &numero_z;
	void *elemento_3 = &numero_p;
	void *elemento_4 = &numero_k;

	int numero_de_corte = 200;
	int numero_sin_corte = 1;

	pa2m_afirmar(lista_con_cada_elemento(NULL, es_menor,
					     &numero_de_corte) == 0,
		     "Iterar sobre una lista nula devuelve 0.");
	pa2m_afirmar(lista_con_cada_elemento(lista, es_menor,
					     &numero_de_corte) == 0,
		     "Iterar sobre una lista vacía devuelve 0.");

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);
	lista_insertar(lista, elemento_4);

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &numero_de_corte) ==
			     0,
		     "Iterar sobre una lista con función nula devuelve 0.");
	pa2m_afirmar(lista_con_cada_elemento(lista, es_menor, NULL) == 0,
		     "Iterar sobre una lista con contexto nulo devuelve 0.");
	pa2m_afirmar(
		lista_con_cada_elemento(lista, es_menor, &numero_de_corte) == 4,
		"Recorre la lista hasta que encuentre un elemento que coincida y devuelve los cantidad de elementos iterados.");
	pa2m_afirmar(lista_con_cada_elemento(lista, es_mayor,
					     &numero_sin_corte) == 5,
		     "Recorre la lista en su totalidad.");

	lista_destruir(lista);
}

void iterador_externo_itera_externamente_sobre_lista()
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

	pa2m_afirmar(lista_iterador_crear(NULL) == NULL,
		     "Crear iterador de una lista nula devuelve NULL.");
	pa2m_afirmar(lista_iterador_crear(lista) == NULL,
		     "Crear iterador de una lista vacía devuelve NULL.");

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1);
	lista_insertar(lista, elemento_2);
	lista_insertar(lista, elemento_3);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL, "Crea iterador con una lista no vacía.");
	pa2m_afirmar(lista_iterador_avanzar(NULL) == false,
		     "Avanzar con un iterador nulo devuelve false.");

	pa2m_afirmar(
		lista_iterador_avanzar(iterador) == true,
		"Avanza con un iterador teniendo elementos para recorrer correctamente.");

	pa2m_afirmar(
		lista_iterador_elemento_actual(NULL) == NULL,
		"Iterar elemento actual de un iterador nulo devuelve NULL.");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == elemento_1,
		"Itera el elemento actual teniendo más elementos que iterar.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false,
		     "Iterador nulo no tiene siguiente.");
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador) == true,
		"Iterador válido tiene siguiente para iterar al no tener más elementos para iterar.");

	lista_iterador_avanzar(iterador);
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == elemento_3,
		"Itera el elemento actual sin tener más elementos que iterar.");
	pa2m_afirmar(
		lista_iterador_avanzar(iterador) == false,
		"Avanzar con un iterador sin tener elementos por recorrer devuelve false.");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void crear_una_pila_crea_una_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL, "Se puede crear una pila válida.");
	pa2m_afirmar(pila_vacia(pila) == true, "Crea una pila vacía.");
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "Al crear una pila, su tope es NULL.");

	pila_destruir(pila);
}

void pila_apilar_apila_elementos()
{
	pila_t *pila = pila_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;

	pa2m_afirmar(pila_apilar(NULL, elemento_0) == NULL,
		     "Apilar en una pila nula devuelve NULL.");
	pila_apilar(pila, elemento_0);
	pa2m_afirmar(pila_tope(pila) == elemento_0,
		     "Apila un elemento en una pila vacía correctamente.");

	pila_apilar(pila, elemento_1);
	pila_apilar(pila, elemento_2);

	pa2m_afirmar(pila_tope(pila) == elemento_2,
		     "Apila un elemento en una pila no vacía correctamente.");
	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "Actualiza tamaño de la pila correctamente");

	pila_destruir(pila);
}

void pila_desapilar_desapila_elementos()
{
	pila_t *pila = pila_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;

	pa2m_afirmar(pila_desapilar(NULL) == NULL,
		     "Desapilar un elemento en una pila nula devuelve NULL.");
	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "Desapilar un elemento en una pila vacía devuelve NULL");

	pila_apilar(pila, elemento_0);
	pila_apilar(pila, elemento_1);
	pila_apilar(pila, elemento_2);

	pila_desapilar(pila);

	pa2m_afirmar(
		pila_tope(pila) == elemento_1,
		"Desapila un elemento en una pila no vacía correctamente.");
	pa2m_afirmar(pila_tamanio(pila) == 2,
		     "Actualiza tamaño de la pila correctamente.");

	pila_destruir(pila);
}

void pila_tamanio_tope_y_vacia()
{
	pila_t *pila = pila_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;

	pa2m_afirmar(pila_tamanio(NULL) == 0,
		     "El tamaño de una pila nula devuelve 0.");
	pa2m_afirmar(pila_tamanio(pila) == 0,
		     "El tamaño de una pila vacía devuelve 0.");

	pa2m_afirmar(pila_tope(NULL) == NULL,
		     "El tope de una pila nula devuelve NULL.");
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "El tope de una pila vacía devuelve NULL.");

	pa2m_afirmar(pila_vacia(NULL) == true,
		     "Verifica que una pila nula este vacía. ");
	pa2m_afirmar(pila_vacia(pila) == true,
		     "Verifica que una pila vacía este vacía.");

	pila_apilar(pila, elemento_0);
	pila_apilar(pila, elemento_1);
	pila_apilar(pila, elemento_2);

	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "Actualiza tamaño de la pila correctamente.");

	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == elemento_1,
		     "Devuelve el elemento del tope luego de desapilar.");

	pila_desapilar(pila);
	pila_desapilar(pila);

	pa2m_afirmar(pila_vacia(pila) == true,
		     "Al desapilar todos los elementos, la pila queda vacía.");

	pila_destruir(pila);
}

void cola_crear_crea_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola != NULL, "Crea cola válida.");
	pa2m_afirmar(cola_vacia(cola) == true, "Crea cola vacía.");
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "Al crear la cola su frente es NULL.");

	cola_destruir(cola);
}

void cola_encolar_encola_elementos()
{
	cola_t *cola = cola_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;

	pa2m_afirmar(cola_encolar(NULL, elemento_2) == NULL,
		     "Encolar en una cola nula devuelve NULL");
	cola_encolar(cola, elemento_0);
	pa2m_afirmar(cola_frente(cola) == elemento_0,
		     "Encola un elemento en una vacía correctamente.");

	cola_encolar(cola, elemento_1);
	cola_encolar(cola, elemento_2);

	pa2m_afirmar(cola_frente(cola) == elemento_0,
		     "Se mantiene correctamente el frente de la cola.");
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "Actualiza tamaño de la cola correctamente.");

	cola_destruir(cola);
}

void cola_desencolar_desencola_elementos()
{
	cola_t *cola = cola_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;

	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "Desencolar un elemento en una cola nula devuelve NULL.");
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar un elemento en una cola vacía devuelve NULL");

	cola_encolar(cola, elemento_0);
	cola_encolar(cola, elemento_1);
	cola_encolar(cola, elemento_2);

	cola_desencolar(cola);
	cola_desencolar(cola);

	pa2m_afirmar(
		cola_frente(cola) == elemento_2,
		"Desencola un elemento en una cola no vacía correctamente.");
	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "Actualiza tamaño de la cola correctamente.");

	cola_destruir(cola);
}

void cola_tamanio_frente_y_vacia()
{
	cola_t *cola = cola_crear();

	int numero_0 = 0;
	int numero_1 = 1;
	int numero_2 = 2;

	void *elemento_0 = &numero_0;
	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;

	pa2m_afirmar(cola_tamanio(NULL) == 0,
		     "El tamaño de una cola nula devuelve 0.");
	pa2m_afirmar(cola_tamanio(cola) == 0,
		     "El tamaño de una cola vacía devuelve 0.");

	pa2m_afirmar(cola_frente(NULL) == NULL,
		     "El tope de una cola nula devuelve NULL.");
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "El tope de una cola vacía devuelve NULL.");

	pa2m_afirmar(cola_vacia(NULL) == true,
		     "Verifica que una cola nula este vacía. ");
	pa2m_afirmar(cola_vacia(cola) == true,
		     "Verifica que una cola vacía este vacía.");

	cola_encolar(cola, elemento_0);
	cola_encolar(cola, elemento_1);
	cola_encolar(cola, elemento_2);

	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "Actualiza tamaño de la cola correctamente.");

	cola_desencolar(cola);
	pa2m_afirmar(cola_frente(cola) == elemento_1,
		     "Devuelve el elemento del frente luego de desencolar.");

	cola_desencolar(cola);
	cola_desencolar(cola);

	pa2m_afirmar(cola_vacia(cola) == true,
		     "Al desapilar todos los elementos, la cola queda vacía.");

	cola_destruir(cola);
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

	pa2m_nuevo_grupo("\nObtencion elemento según posición.");
	lista_elemento_en_posicion_obtiene_elemento_de_la_posicion_indicada();

	pa2m_nuevo_grupo("\nObtencion elemento según condicion.");
	lista_buscar_elemento_busca_segun_condicion_dada();

	pa2m_nuevo_grupo("\nTamaño de lista y lista vacía");
	lista_tamanio_devuelve_cantidad_de_elemento_de_la_lista();
	lista_vacia_devuelve_si_tiene_elementos_o_no_la_lista();

	pa2m_nuevo_grupo("\nPrimer y último elemento de la lista.");
	lista_primer_y_ultimo_elemento();

	pa2m_nuevo_grupo("\nFunciones del iterador interno");
	iterador_interno_itera_internamente_sobre_lista();

	pa2m_nuevo_grupo("\nFunciones del iterador externo");
	iterador_externo_itera_externamente_sobre_lista();

	pa2m_nuevo_grupo("\nFunciones de pila");
	crear_una_pila_crea_una_pila_vacia();
	pila_apilar_apila_elementos();
	pila_desapilar_desapila_elementos();
	pila_tamanio_tope_y_vacia();

	pa2m_nuevo_grupo("\nFunciones de cola");
	cola_crear_crea_cola_vacia();
	cola_encolar_encola_elementos();
	cola_desencolar_desencola_elementos();
	cola_tamanio_frente_y_vacia();

	return pa2m_mostrar_reporte();
}
