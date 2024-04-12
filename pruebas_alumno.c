#include "pa2m.h"
#include "src/lista.h"

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

void lista_crear_crea_una_lista_vacia() 
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crear lista.");
	pa2m_afirmar(lista_vacia(lista), "Se crea lista vacia.");
}

void lista_insertar_insierta_un_elemento_al_final()
{
	lista_t *lista = lista_crear();
	int elemento_1 = 1;
	int elemento_2 = 2;

	lista = lista_insertar(lista, &elemento_1);
	lista = lista_insertar(lista, &elemento_2);

	pa2m_afirmar(lista != NULL && *(int*)lista->nodo_inicio->elemento == elemento_1 , "Se puede insertar un elemento en la lista vacía.");
	pa2m_afirmar(*(int*)lista->nodo_final->elemento == elemento_2, "Se puede insertar un elemento en una lista no vacía.");
	pa2m_afirmar((int*)lista->nodo_final->siguiente == NULL, "El ultimo nodo apunta a NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "Se actualiza el tamaño de la lista.");

}

void lista_insertar_en_posicion_inserta_elementos() 
{
	lista_t *lista = lista_crear();
	int elemento_1 = 1;
	int elemento_2 = 2;
	int elemento_3 = 3;
	int elemento_4 = 4;
	int elemento_5 = 5;


	lista = lista_insertar(lista, &elemento_1);
	lista = lista_insertar(lista, &elemento_2);
	lista = lista_insertar(lista, &elemento_1);
	lista = lista_insertar(lista, &elemento_2);


	lista_insertar_en_posicion(lista, &elemento_3, 0);
	lista_insertar_en_posicion(lista, &elemento_4, 1);
	lista_insertar_en_posicion(lista, &elemento_5, 10);


	pa2m_afirmar(lista != NULL && *(int*)lista->nodo_inicio->elemento == elemento_3, "Se inserta un elemento indicando posición 0.");
	pa2m_afirmar(*(int*)lista->nodo_inicio->siguiente->elemento == elemento_4, "Se inserta un elemento indicando posición 1");
	pa2m_afirmar(*(int*)lista->nodo_final->elemento == elemento_5, "Se inserta un elemento al final al indicar una posición  del medio");

}

















int main()
{
	pa2m_nuevo_grupo("\nCreación lista vacía");
	lista_crear_crea_una_lista_vacia();

	pa2m_nuevo_grupo("\nInserción de elementos al final");
	lista_insertar_insierta_un_elemento_al_final();
	pa2m_nuevo_grupo("\nInserción de elementos en cualquier posicion");

	lista_insertar_en_posicion_inserta_elementos();
	

	return pa2m_mostrar_reporte();
}
