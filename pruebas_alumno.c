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

    int numero_3 = 3;
    int numero_4 = 4;
    int numero_5 = 5;
    int numero_6 = 6;
    int numero_7 = 7;

	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;
	void *elemento_5 = &numero_5;
	void *elemento_6 = &numero_6;
	void *elemento_7 = &numero_7;




    lista_insertar_en_posicion(lista, elemento_3, 0);
    lista_insertar_en_posicion(lista, elemento_4, 1); 
    lista_insertar_en_posicion(lista, elemento_5, 3); 
    lista_insertar_en_posicion(lista, elemento_7, 10); 


    pa2m_afirmar(lista->nodo_inicio->elemento == elemento_3, "Inserta un elemento al inicio de la lista.");
    pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento_4, "Inserta un elemento en la posición 1.");
    pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->elemento == elemento_5, "Inserta un elemento en el medio de la lista.");
    lista_insertar_en_posicion(lista, elemento_6, 0); 
	pa2m_afirmar(lista->nodo_inicio->elemento == elemento_6, "Inserta un elemento al inicio de la lista");
    pa2m_afirmar(lista->nodo_final->siguiente == NULL, "El último nodo apunta a NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 5, "Aumenta correctamente el tamaño de la lista.");

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

bool es_mayor(void *elemento_1, void *elemento_2) {
    return *(int*)elemento_1 > *(int*) elemento_2;
}


void iterador_interno_itera_internamente_sobre_lista() 
{
	lista_t *lista = lista_crear();

	int numero_x = 100;
	int numero_y = 10;
	int numero_z = 3;
	int numero_p = 1;
	int numero_k = 2;


	void *elemento_0 = &numero_x;
	void *elemento_1 = &numero_y;
	void *elemento_2 = &numero_z;
	void *elemento_3 = &numero_p;
	void *elemento_4 = &numero_k;


	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1); 
	lista_insertar(lista, elemento_2); 
	lista_insertar(lista, elemento_3);
	lista_insertar(lista, elemento_4);

	int numero_de_corte = 2;
	int numero_de_corte_principio = 120;

	

	pa2m_afirmar(lista_con_cada_elemento(lista, es_mayor, &numero_de_corte) == 3, "Recorre la lista hasta que encuentre un elemento menor a 2.");
	pa2m_afirmar(lista_con_cada_elemento(lista, es_mayor, &numero_de_corte_principio) == 1, "Recorre la lista hasta que encuentre un elemento menor a 120.");
	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &numero_de_corte) == 0, "Al pasar una funcion nula, devuelve 0.");
	pa2m_afirmar(lista_con_cada_elemento(NULL, es_mayor, &numero_de_corte) == 0, "Al pasar una lista nula, devuelve 0.");
	pa2m_afirmar(lista_con_cada_elemento(lista, es_mayor, NULL) == 0, "Al pasar un contexto nulo, devuelve 0.");


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

	lista_insertar(lista, elemento_0);
	lista_insertar(lista, elemento_1); 
	lista_insertar(lista, elemento_2); 
	lista_insertar(lista, elemento_3);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL, "Iterador se crea correctamente");
	pa2m_afirmar(lista_iterador_crear(NULL) == NULL, "Si la lista es nula, no se crea el iterador.");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == elemento_0, "Al crear el iterador se inicializa correctamente con el primer elemento de la lista.");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == true, "Al tener siguiente, el iterador avanza correctamente");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == elemento_1, "Al avanzar, se actualiza correctamente el elemento actual.");

	lista_iterador_avanzar(iterador);
	lista_iterador_avanzar(iterador);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false, "Al ser corriente el ultimo elemento, el iterador no tiene siguiente.");


	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}


void se_implementa_una_pila() 
{
	pila_t *pila = pila_crear(); 

	pa2m_afirmar(pila != NULL, "Se puede crear pila.");
	pa2m_afirmar(pila_vacia(pila) == true, "Se crea pila vacia.");
	pa2m_afirmar(pila_tope(pila) == NULL, "Al crear la pila, el tope es NULL.");

	int numero_1 = 1;
	void *elemento_1 = &numero_1;

	int numero_2 = 2;
	void *elemento_2 = &numero_2;

	int numero_3 = 3;
	void *elemento_3 = &numero_3;

	int numero_4 = 4;
	void *elemento_4 = &numero_4;

	pila_apilar(pila, elemento_1);

	pa2m_afirmar(pila_tope(pila) == elemento_1, "Al apilar un elemento, el tope es el elemento que se apiló.");
	
	pila_apilar(pila, elemento_2);
	pa2m_afirmar(pila_tope(pila) == elemento_2, "Al apilar un elemento, el tope es el elemento que se apiló.");
	pa2m_afirmar(pila_tamanio(pila) == 2, "Se actualiza correctamente el tamaño.");

	pila_apilar(pila, elemento_3);
	pila_apilar(pila, elemento_4);
	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == elemento_3, "Se desapila correctamente el elemento en tope.");

	
	pila_destruir(pila);
}


void se_implementa_una_cola() 
{
	cola_t *cola = cola_crear(); 

	pa2m_afirmar(pila != NULL, "Se puede crear pila.");
	pa2m_afirmar(pila_vacia(pila) == true, "Se crea pila vacia.");
	pa2m_afirmar(pila_tope(pila) == NULL, "Al crear la pila, el tope es NULL.");

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

	pa2m_nuevo_grupo("\nFunciones del iterador interno");
	iterador_interno_itera_internamente_sobre_lista();

	pa2m_nuevo_grupo("\nFunciones del iterador externo");
	iterador_externo_itera_externamente_sobre_lista();

	pa2m_nuevo_grupo("\nFunciones de pila");
	se_implementa_una_pila();

	pa2m_nuevo_grupo("\nFunciones de cola");
	se_implementa_una_cola();


	return pa2m_mostrar_reporte();
}
