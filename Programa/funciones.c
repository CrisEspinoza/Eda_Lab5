#include <stdio.h>
#include "struct.h"
#include <string.h>
#include <stdlib.h>
#include <locale.h>

Nodo* cargar(char nombre[])
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen (nombre, "r"); // Estamos abriendo el archivo en modo lectura

    Nodo* listaPersonas = NULL;
    int cantidadDePeronas;
    fscanf(archivo, "%d", &cantidadDePeronas);

    char *primerNombre;
    primerNombre = (char*)calloc(100,sizeof(char));
    char *segundoNombre;
    segundoNombre = (char*)calloc(100,sizeof(char));
    char *primerApellido;
    primerApellido = (char*)calloc(100,sizeof(char));
    char *segundoApellido;
    segundoApellido = (char*)calloc(100,sizeof(char));
    char *parte1;
    parte1 = (char*)calloc(20,sizeof(char));
    char *parte2;
    parte2 = (char*)calloc(20,sizeof(char));
    char *parte3;
    parte3 = (char*)calloc(20,sizeof(char));
    char *parte4;
    parte4 = (char*)calloc(20,sizeof(char));
    char *numero;
    numero = (char*)calloc(100,sizeof(char));

    struct Informacion* auxNodo;
    int contador = 0 ;

    while (!feof(archivo)) 
    {
        fscanf(archivo, "%s %s %s %s %s %s %s %s",primerNombre,segundoNombre,primerApellido,segundoApellido,parte1,parte2,parte3,parte4);
        numero = strcat(strcat(parte1,parte2),strcat(parte3,parte4));
        auxNodo = crearInformacion(primerNombre,segundoNombre,primerApellido,segundoApellido,numero); // Creamos un nuevo nodo con lo caputrado desde el archivo
        listaPersonas = agregarNodo(listaPersonas,auxNodo);
    }
    fclose(archivo); // Cerramos el archivo
    return listaPersonas;
}

// Funcion que se encarga de mostrar a cada una de las personas que slicitan buscar.
void mostrarPersonasBuscadas(Lista *lista)
{
	int j;
    // For  que muestra moviendose segun el largo de la lista, con el fin de msotrar a cada una de las personas a buscar
    for (j = 0; j < lista->largo-1; j++)
    {
        printf("%s ", lista->nodo[j].info->primerNombre);
        printf("%s ", lista->nodo[j].info->segundoNombre);
        printf("%s ", lista->nodo[j].info->primerApellido);
        printf("%s ", lista->nodo[j].info->segundoApellido);
        printf("El numero es: %s ", lista->nodo[j].info->numero);   
        printf("%s ", lista->nodo[j].info->nombreCompleto);
        printf("\n");
    }   
}

Lista* cargarNombresBuscados(char nombre[])
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen (nombre, "r"); // Estamos abriendo el archivo en modo lectura

    int cantidadDePeronas;
    fscanf(archivo, "%d", &cantidadDePeronas);

    char *primerNombre;
    primerNombre = (char*)calloc(100,sizeof(char));
    char *segundoNombre;
    segundoNombre = (char*)calloc(100,sizeof(char));
    char *primerApellido;
    primerApellido = (char*)calloc(100,sizeof(char));
    char *segundoApellido;
    segundoApellido = (char*)calloc(100,sizeof(char));

    struct Nodo* auxNodo = crearNodo();
    int contador = 0 ;
    Lista* listaPersonas = crearLista();

    while (!feof(archivo)) 
    {
        fscanf(archivo, "%s %s %s %s",primerNombre,segundoNombre,primerApellido,segundoApellido);
        auxNodo->info = crearInformacion(primerNombre,segundoNombre,primerApellido,segundoApellido,""); // Creamos un nuevo nodo con lo caputrado desde el archivo
        agregarNodoLista(listaPersonas,auxNodo);
        contador++;
    }
    fclose(archivo); // Cerramos el archivo
 
    return listaPersonas;
}

Lista* crearLista() // Creamos la lista nueva 
{
    Lista* lista = (Lista*)malloc(sizeof(Lista)); // Pedimos memoria para la nueva lista 
    lista->nodo = NULL;
    lista->largo = 0 ; // El largo de la lista es igual a "0".
    return lista; // Se retorna la lista creada
}

Lista* agregarNodoLista(Lista* lista , Nodo* aux)
{
    if(lista->largo == 0)
    {
        lista->nodo = (Nodo*)malloc(sizeof(Nodo));
        lista->nodo[0] = *aux;
    }
    else
    {
        lista->nodo = (Nodo*)realloc(lista->nodo, (lista->largo + 1) * sizeof (Nodo)); // Pedimos mas memoria para el arreglo creado
        lista->nodo[lista->largo] = *aux; // Agregamos el nodo que se desea agregar, luego de haber solicitado memoria
    }
    lista->largo++; // aumnetamos el largo de la lista de arreglos
    return lista;
}

Informacion* crearInformacion(char *primerNombre, char *segundoNombre, char *primerApellido,
 char *segundoApellido, char *numero)
{
    Informacion* nuevoNodo = (Informacion*)malloc(sizeof(Informacion)); // Pedimos memoria para el nuevo nodo declarado   
    
    char *nombreCompleto;
    nombreCompleto = (char*)calloc(100,sizeof(char));

    if (nuevoNodo != NULL)
    {
        //Copiamos cada una de las caracteristicas que recibimos como parametro al nuevo nodo creado
        strcpy(nuevoNodo->primerNombre,primerNombre);
        strcpy(nuevoNodo->segundoNombre,segundoNombre);
        strcpy(nuevoNodo->primerApellido,primerApellido);
        strcpy(nuevoNodo->segundoApellido,segundoApellido);
        strcpy(nuevoNodo->numero,numero);
        nombreCompleto = strcat(strcat(primerNombre,segundoNombre),strcat(primerApellido,segundoApellido));
        strcpy(nuevoNodo->nombreCompleto,nombreCompleto);
        nuevoNodo->bandera = 0;        
        nuevoNodo->altura = 0;
    }
    return nuevoNodo; // Se retorna el nuevo nodo creado
}

Lista* personasBuscadas(Nodo* listaPersonas, Lista* listaPersonasABuscar, int contador, Lista* auxLista)
{
    if (listaPersonas != NULL)
    {
        //Realizamos las comparaciones correspondientes mediante la persona que estamos buscando
        if (strcmp(listaPersonas->info->primerNombre,listaPersonasABuscar->nodo[contador].info->primerNombre) == 0 &&
            strcmp(listaPersonas->info->segundoNombre,listaPersonasABuscar->nodo[contador].info->segundoNombre) == 0 &&
            strcmp(listaPersonas->info->primerApellido,listaPersonasABuscar->nodo[contador].info->primerApellido) == 0 &&
            strcmp(listaPersonas->info->segundoApellido,listaPersonasABuscar->nodo[contador].info->segundoApellido) == 0 )
        {
            auxLista = agregarNodoLista(auxLista,listaPersonas);
        }

        // Hacemos una bifurcacion para verificar hacia donde avanzamos en el arbol avl
        if (mayor(listaPersonas->info,listaPersonasABuscar->nodo[contador].info) == 1)
        {
            personasBuscadas(listaPersonas->hijoDerecho,listaPersonasABuscar,contador,auxLista);
        }
        else
        {
            personasBuscadas(listaPersonas->hijoIzquierdo,listaPersonasABuscar,contador,auxLista);
        }        
    }
    return auxLista;
}

Lista* arreglarLista(Lista* lista, Lista* listaPersonas, int largoLista)
{
     //Declaramos cada una de las variables
    char *numero;
    numero = (char*)calloc(100,sizeof(char));
    int i,j;

    for (i = 0; i < largoLista; i++)
    {
        for (j = 0; j < lista->largo; j++)
        {             
            //Hacemos una comparación para verificar si es el primer numero encontrado o otro, con el fin de agregarlo al archivo
             //con un " - ". 
            if (strcmp(listaPersonas->nodo[i].info->nombreCompleto,lista->nodo[j].info->nombreCompleto) == 0 &&
                listaPersonas->nodo[i].info->bandera == 1)
            {
                numero = strcat( strcat(numero," - ") ,lista->nodo[j].info->numero );
            }

            if (strcmp(listaPersonas->nodo[i].info->nombreCompleto,lista->nodo[j].info->nombreCompleto) == 0 && 
                listaPersonas->nodo[i].info->bandera == 0)
            {
                listaPersonas->nodo[i].info->bandera = 1;
                numero = strcat(numero,lista->nodo[j].info->numero);
            }        
        }
        //Realizamos el reemplazo en el numero y volvemoa a pedir memoria para el siguiente numero
        strcpy(listaPersonas->nodo[i].info->numero,numero);
        numero = (char*)calloc(100,sizeof(char));
    }
    return listaPersonas; // Retornamos la lista con los numeros actualizados
}

int mayor(Informacion* aux, Informacion* aux1 )
{
    //Declaramos las variables a utilizar 
    int largoMinimo;

    //Verificamos si alguno de los ombres ta nulo, para devolver el largo de la otra palabra
    if (aux == NULL)
    {
        return 0;
    }

    if (aux1 == NULL)
    {
        return 1;
    }

    //Verificamos cual de las palabras es mas larga y devolvemos la contraria 
    if (strlen(aux->nombreCompleto) > strlen(aux1->nombreCompleto) )
    {
        //Devolvemos la palabra de menor largo
        largoMinimo = strlen(aux1->nombreCompleto);
    }
    else
    {
          //Devolvemos la palabra de menor largo
        largoMinimo = strlen(aux->nombreCompleto);
    }

    int i ;

    for (i = 0 ; i < largoMinimo ; i++)
    {
        //Vamos verificando caracter a caracter cual es mayor que el otro, para poder tener el orden alfabeticamente dentor del arbol
        if (aux->nombreCompleto[i] > aux1->nombreCompleto[i])
        {
            return 1;
        }

        if (aux1->nombreCompleto[i] > aux->nombreCompleto[i])
        {
            return 0;
        }
    }
    return 0; //Retornamos 0, si ninguna de las anteriores opciones se cumple 
}

Nodo* agregarNodo(Nodo *arbol, Informacion* dato)
{
    //Verificamos si el arbol esta nulo
    if(arbol == NULL)
    {
        arbol = crearNodo();        
        arbol->info = dato;
        arbol->largo++;
        //Equilibramos para asegurar que el arbol se mantenga totalmente equilibrado, luego de agregar un neuvo nodo
        arbol = equilibrar(arbol);
        return arbol; //Retornamos el nuevo arbol, recalcar que esta equilibrado
    }

    else
    {
        if(mayor(arbol->info, dato) == 1)
        {
            //Agremos el nodo , luego actualizamos las alturas de dicho arbol, para finalmente equilibrar el arbol, con el fin de 
            //mantener el arbol de una forma que sea arbol avl
            arbol->hijoDerecho = agregarNodo(arbol->hijoDerecho, dato);
            arbol = actualizarAltura(arbol);
            arbol = equilibrar(arbol);
            return arbol;
        }

        else
        {
            //Agremos el nodo , luego actualizamos las alturas de dicho arbol, para finalmente equilibrar el arbol, con el fin de 
            //mantener el arbol de una forma que sea arbol avl
            arbol->hijoIzquierdo = agregarNodo(arbol->hijoIzquierdo, dato);
            arbol = actualizarAltura(arbol);
            arbol = equilibrar(arbol); 
            return arbol;
        }
    }    
}

Nodo* crearNodo() // Creamos la lista nueva 
{
    Nodo* nodo = malloc(sizeof *nodo); // Pedimos memoria para la nueva nodo 
    if (nodo != NULL)
    {
        nodo->info = (Informacion*)malloc(sizeof(Informacion));
        nodo->hijoDerecho = NULL;
        nodo->hijoIzquierdo = NULL;
        nodo->largo = 0 ;
    } 
    return nodo; // Se retorna la lista creada
}

void inordenPedido(Nodo *arbol)
{
    //Realizamos la funcion que muestra al arbol ordenado alfabeticamene mostrando cada una de sus caracteristicas
    if(arbol != NULL)
    {
        inordenPedido(arbol->hijoDerecho);      
        
        printf("El nombre completo de la persona es: %s \n", arbol->info->nombreCompleto);
        printf("La altura del nodo actual es: %d \n", arbol->info->altura);

        if (arbol->hijoDerecho != NULL)
        {
            printf("El nombre completo del hijo derecho del nodo actual es: %s \n", arbol->hijoDerecho->info->nombreCompleto);
        }
        else
        {
            printf("El nombre completo del hijo derecho del nodo actual es: NULL \n");
        }

        if (arbol->hijoIzquierdo != NULL)
        {
            printf("El nombre completo del hijo izquierda del nodo actual es: %s \n", arbol->hijoIzquierdo->info->nombreCompleto);
        }
        else
        {
            printf("El nombre completo del hijo izquierdo del nodo actual es: NULL \n");
        }

        printf("\n");

        inordenPedido(arbol->hijoIzquierdo);
    }
}

void inorden(Nodo *arbol)
{
    //Realizamos la funcion que muestra al arbol ordenado alfabeticamene mostrando cada una de sus caracteristicas
    if(arbol != NULL)
    {
        inorden(arbol->hijoDerecho);
        printf("El primer nombre del nodo actual es: %s \n", arbol->info->primerNombre);
        printf("El segundo nombre del nodo actual es: %s \n", arbol->info->segundoNombre);
        printf("El primer apellido del nodo actual es: %s \n", arbol->info->primerApellido);
        printf("El segundo apellido del nodo actual es: %s \n", arbol->info->segundoApellido);
        printf("El numero de la persona actual es: %s \n", arbol->info->numero);        
        printf("El nombre completo de la persona es: %s \n", arbol->info->nombreCompleto);
        printf("La altura del nodo actual es: %d \n", arbol->info->altura);
        printf("\n");
        inorden(arbol->hijoIzquierdo);
    }
}

int largoMenor(Informacion* palabra1, Informacion* palabra2)
{
    //Definimos las variables que vamos a ocupar dentro del codigo
    int largoMinimo = 0;

    //Verificamos los casos bases de las palabras para verificar si alguna es nula
    //
    if ((palabra1->nombreCompleto == NULL) && (palabra2->nombreCompleto != NULL))
    {
        largoMinimo = strlen(palabra2->nombreCompleto);
    }

    else if ((palabra2->nombreCompleto == NULL) && (palabra1->nombreCompleto != NULL))
    {
        largoMinimo = strlen(palabra1->nombreCompleto);
    }

    //En caso contrario hacemos las verifiacciones correspondientes para ver cual de las dos palabras
    //es mas larga, con el fin de devolver el largo de sa palabra 
    else 
    {
        if (strlen(palabra1->nombreCompleto) > strlen(palabra2->nombreCompleto))
        {
            largoMinimo = strlen(palabra2->nombreCompleto);
        }
        else
        {
            largoMinimo = strlen(palabra1->nombreCompleto);
        }
    }

    return largoMinimo; // Retornamos el largo de la palabra mayor.
}

void crearArchivo (Lista* listaPersonas,int largo)
{
    FILE *txt;  // Incialzamos una variable de tipo FILE para poder trabajar con los archivos

    txt = fopen("TelefonosEncontrados.out", "wt"); // Abrimos le archivo en modo escritura y que se cree si no exite el archivo nombrado
	int i;
    for (i = 0 ; i < largo ; i++)
    {
        fprintf(txt,"%s %s %s %s: %s ",listaPersonas->nodo[i].info->primerNombre,listaPersonas->nodo[i].info->segundoNombre,
        listaPersonas->nodo[i].info->primerApellido,listaPersonas->nodo[i].info->segundoApellido,listaPersonas->nodo[i].info->numero); // Se escribe la ruta minima en el archivo
        fprintf(txt,"\n");
    }
    fclose(txt); // Cerramos el archivo
}

int diferenciaAltura(Nodo* arbol)
{
    //Hacemos la diferencia de las alturas de los hijos del arbol o sub-arbol
    int diferencia = altura(arbol->hijoIzquierdo) - altura(arbol->hijoDerecho);
    
	return diferencia; //Retornamos la diferencia del calculo hecho anteriormente
}

int altura(Nodo* arbol)
{
    //Declaramos las variables a utilizar
    int alturaIzquierda, alturaDerecha;

    //Verificamos si el arbol es nulo
	if (arbol == NULL)
	{
		return 0;
	}

    //Colocamos la altura de cada uno de los hijos del arbol, con el fin de llegar a la altura mayor de este
	alturaIzquierda = altura(arbol->hijoIzquierdo);
	alturaDerecha = altura(arbol->hijoDerecho); 

    //Verificamos cual de las dos alturas es mayor, con el fin de retornar la altura mayor + 1, que vendir
    //siendo la altura del padre de los hijos que se esta calculando en el arbol
	if (alturaIzquierda > alturaDerecha)
	{
		return (1 + alturaIzquierda); //Retornamos la altura mayor mas 1
	}

	return (1 + alturaDerecha); //Retornamos la altura mayor mas 1 
}

//Funcion que se encarga de hacer una rotacion a la derecha, para poder mantener en un equilibrio el arbol que se esta trabajando
//tener en cuenta que se ocupa un nodo auxiliar para facilitar la toracion que se le hara al arbol en cuestion
Nodo* rotarDerecha(Nodo* arbol)
{
    //Declaramos las variables a utilizar
	Nodo* raiz;

    //Realizamos los cambios correspondientes
	raiz = arbol->hijoIzquierdo;
	arbol->hijoIzquierdo = raiz->hijoDerecho;
	raiz->hijoDerecho = arbol;

    //Actualizamos las alturas de ls nodos que sufrieron modificaciones en el arbol
    arbol = actualizarAltura(arbol);
    raiz = actualizarAltura(raiz);
	
    return raiz; //Retornamos el nuevo arbo, rotado hacia la derecha
}


//Funcion que se encarga de hacer una rotacion a la izquierda, para poder mantener en un equilibrio el arbol que se esta trabajando
//tener en cuenta que se ocupa un nodo auxiliar para facilitar la toracion que se le hara al arbol en cuestion
Nodo* rotarIzquierda(Nodo* arbol)
{
    //Declaramos las variables a utilizar dentro de la funcion
	Nodo* raiz;

    //Haemos los cambios correspondientes, para poder tener una rotacion hacia la izquierda
	raiz = arbol->hijoDerecho;
	arbol->hijoDerecho = raiz->hijoIzquierdo;
	raiz->hijoIzquierdo = arbol;

    //Realizamos las actualizaciones de las alturas de los nodos que sufrieron modificaciones
    arbol = actualizarAltura(arbol);
    raiz = actualizarAltura(raiz);   

	return raiz; //Retornamos el nuevo arbol rotado, con el fin de mantener el arbol equilibrado
}

Nodo* actualizarAltura(Nodo* aux)
{
    //Verificamos si el noso que estamos analizando sea distinto de nulo
    if (aux != NULL)
    {
        //Calculamos las alturas de los hijos del nodo en cuestion, con el fin de devolver la alturta mayor de este
        if (altura(aux->hijoIzquierdo) > altura(aux->hijoDerecho))
        {
            aux->info->altura = altura(aux->hijoIzquierdo); 
        }
        else
        {            
            aux->info->altura = altura(aux->hijoDerecho); 
        }
    }
    return aux; //Retornamos el nuevo nodo con su altura actualizada
}

//Funcion que se encarga de verificar que rotacion se debe hacer en el arbol avl, si es tanto como un rotacion simple hacia la derecha
//, hacia la izquierda, una doble hacia la derecha o una doble hacia la izquierda
Nodo* equilibrar(Nodo* arbol)
{
    //Declaramos cada una de las variables a utilizar dntro de la funcion
	int diferencia = diferenciaAltura(arbol);	

    //Vericamos cuando el arbol no necesita que sea equiibrado 
    if (diferencia == 1 || diferencia == 0)
    {
        arbol = actualizarAltura(arbol);
        return arbol;
    }

    //Realizamos las distintas verificaciones a los casos, para poder tener en cuenta que rotacion se debe aplicar al 
    //arbol en cuestion para poder mantener en arbol en su equiibrio.
    if (diferencia == -2)
    {
        if (diferenciaAltura(arbol->hijoDerecho) > 0)
        {
            arbol->hijoDerecho = rotarDerecha(arbol->hijoDerecho);
        }
        arbol = rotarIzquierda(arbol);
    }
	
	if (diferencia == 2)
	{
		if (diferenciaAltura(arbol->hijoIzquierdo) < 0)
		{
			arbol->hijoIzquierdo = rotarIzquierda(arbol->hijoIzquierdo);
		}
        arbol = rotarDerecha(arbol); 
    }	
    return arbol; //Se retorna el arbol ya equilibrado y actualizdo sus alturas, con el fin de mantener el arbol equilibrado y asi tener un avl
}