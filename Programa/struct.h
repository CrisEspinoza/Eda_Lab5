// Se importan las cosas que ayudaran al funcionamiento del codigo 
#include <stdio.h>
#include <string.h>
#include <locale.h>

// Definimos las estructuras a ocupar dentro de la aplicacion

typedef struct Informacion
{
	char primerNombre[100];
	char segundoNombre[100];
	char primerApellido[100];
	char segundoApellido[100];
	char nombreCompleto[1000];
	char numero[100];	
	int bandera;
	int altura;
}Informacion;

typedef struct Nodo
{
	Informacion* info;
	struct Nodo* hijoDerecho;
	struct Nodo* hijoIzquierdo;
	int largo;	
}Nodo;

typedef struct Lista
{
	int largo;
	Nodo* nodo;
}Lista;

// Funciones utilizadas dentro del codigo

Nodo* cargar(char nombre[]);
Informacion* crearInformacion(char primerNombre[], char segundoNombre[], char primerApellido[],
char segundoApellido[], char numero[]);
int mayor(Informacion* aux, Informacion* aux1 );
Nodo* agregarNodo(Nodo* arbol, Informacion* dato);
Nodo* crearNodo();
int largoMenor(Informacion* palabra1, Informacion* palabra2);
void inorden(Nodo *arbol);
Lista* cargarNombresBuscados(char nombre[]);
Lista* personasBuscadas(Nodo* listaPersonas, Lista* listaPersonasABuscar, int contador, Lista* auxLista);
Lista* crearLista();
Lista* agregarNodoLista(Lista* lista , Nodo* aux);
void mostrarPersonasBuscadas(Lista *lista);
Lista* arreglarLista(Lista* lista, Lista* listaPersonas, int largoLista);
void crearArchivo (Lista* listaPersonas,int largo);
int diferenciaAltura(Nodo* arbol);
int altura(Nodo* arbol);
Nodo* rotarDerecha(Nodo* arbol);
Nodo* rotarIzquierda(Nodo* arbol);
Nodo* equilibrar(Nodo* arbol);
Nodo* actualizarAltura(Nodo* aux);
int maxAltura(Nodo* aux, Nodo* aux1);
int altura(Nodo* arbol);
void inordenPedido(Nodo *arbol);