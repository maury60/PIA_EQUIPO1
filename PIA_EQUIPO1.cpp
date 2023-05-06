#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//****************          FUNCIONES PARA LA PILA          ********************

// Definicion de la estructura Nodo
struct NodoP {
    int dato;
    struct NodoP *siguiente;
};

// Funcion para agregar un nuevo elemento a la pila
void push(struct NodoP **top, int dato) {
    struct NodoP *nuevoNodo = (struct NodoP *) malloc(sizeof(struct NodoP));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = *top;
    *top = nuevoNodo;
}

// Funcion para quitar el ultimo elemento de la pila
int pop(struct NodoP **top) {
    int dato = -1;
    if (*top == NULL) {
        printf("La pila esta vacia\n");
    } else {
        struct NodoP *temp = *top;
        *top = (*top)->siguiente;
        dato = temp->dato;
        free(temp);
    }
    return dato;
}



// Funcion para mostrar los elementos de la pila
void mostrarPila(struct NodoP *top) {
    printf("Pila: ");
    while (top != NULL) {
        printf("%d ", top->dato);
        top = top->siguiente;
    }
    printf("\n");
}
//******************************************************************************************************


//***************************       FUNCIONES PARA LA COLA           ***********************************
#define DEFAULT_QUEUE_SIZE 10

struct Queue {
    int *items;
    int front;
    int rear;
    int size;
};

typedef struct Queue queue_t;

// Funcion para agregar un elemento a la cola
void enqueue(queue_t *q) {
    int item;
    printf("Ingrese el elemento que desea agregar: ");
    scanf("%d", &item);

    if (q->rear == q->size - 1) {
        printf("La cola esta llena\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = item;
        printf("Elemento agregado a la cola: %d\n", item);
    }
}

// Funcion para quitar un elemento de la cola
int dequeue(queue_t *q) {
    int item;
    if (q->front == -1 || q->front > q->rear) {
        printf("La cola esta vacia\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        printf("Elemento removido de la cola: %d\n", item);
    }
    return item;
}

// Funci?n para mostrar los elementos de la cola
void display(queue_t *q) {
    if (q->rear == -1) {
        printf("La cola esta vacia\n");
    } else {
        int i;
        printf("Elementos en la cola: ");
        for (i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

// Funcion para cambiar el tamano de la cola
void resize(queue_t *q) {
    int new_size;
    printf("Ingrese el nuevo tamano de la cola: ");
    scanf("%d", &new_size);

    if (new_size < q->rear - q->front + 1) {
        printf("No se puede reducir el tamano de la cola por debajo del numero actual de elementos\n");
        
    } else {
        q->items = (int *)realloc(q->items, new_size * sizeof(int));
        q->size = new_size;
        printf("Tamano de la cola actualizado a %d\n", new_size);
    }
}
//************************************************************************************************


//*******************************       TABLAS HASH        ***************************************

#define MAX 50 // Tamano maximo de la tabla hash

// Definicion de la estructura nodo
typedef struct nodo {
    char nombre[50]; // Nombre del elemento
    int valor; // Valor del elemento
    struct nodo *sig; // Puntero al siguiente nodo
} Nodo;

// Funcion hash
int funcion_hash(char *clave) {
    int valor = 0;
    for (int i = 0; i < strlen(clave); i++) {
        valor += clave[i];
    }
    return valor % MAX;
}

// Funcion para crear un nodo
Nodo* crear_nodo(char *nombre, int valor) {
    Nodo *nuevo_nodo = (Nodo*) malloc(sizeof(Nodo));
    strcpy(nuevo_nodo->nombre, nombre);
    nuevo_nodo->valor = valor;
    nuevo_nodo->sig = NULL;
    return nuevo_nodo;
}

/* Funcion para insertar un elemento en la tabla hash
void insertar_elemento(Nodo **tabla_hash, char *nombre, int valor) {
    int indice = funcion_hash(nombre); // Obtenemos el indice
    Nodo *nuevo_nodo = crear_nodo(nombre, valor); // Creamos el nuevo nodo
    nuevo_nodo->sig = tabla_hash[indice]; // El nuevo nodo apunta al primer nodo de la lista en esa posicion
    tabla_hash[indice] = nuevo_nodo; // La lista en esa posicion apunta al nuevo nodo
}
*/

void insertar_elemento(Nodo **tabla_hash, char *nombre, int valor) {
    int indice = funcion_hash(nombre); // Obtenemos el indice
    Nodo *nuevo_nodo = crear_nodo(nombre, valor); // Creamos el nuevo nodo
    if (tabla_hash[indice] == NULL) { // Si la lista en esa posicion esta vacia, simplemente insertamos el nuevo nodo
        tabla_hash[indice] = nuevo_nodo;
    } else { // Si la lista en esa posicion no esta vacia, manejamos la colision mediante una lista enlazada
        Nodo *nodo_actual = tabla_hash[indice];
        while (nodo_actual->sig != NULL) {
            nodo_actual = nodo_actual->sig; // Buscamos el final de la lista
        }
        nodo_actual->sig = nuevo_nodo; // Insertamos el nuevo nodo al final de la lista
    }
}

// Funcion para buscar un elemento en la tabla hash
Nodo* buscar_elemento(Nodo **tabla_hash, char *nombre) {
    int indice = funcion_hash(nombre); // Obtenemos el indice
    Nodo *nodo_actual = tabla_hash[indice]; // Empezamos por el primer nodo de la lista en esa posicion
    while (nodo_actual != NULL) {
        if (strcmp(nodo_actual->nombre, nombre) == 0) { // Si encontramos el nodo con ese nombre, lo devolvemos
            return nodo_actual;
        }
        nodo_actual = nodo_actual->sig; // Pasamos al siguiente nodo
    }
    return NULL; // Si no encontramos el nodo con ese nombre, devolvemos NULL
}

// Funci?n para mostrar la tabla hash
void mostrar_tabla(Nodo **tabla_hash) {
    for (int i = 0; i < MAX; i++) {
        printf("Posicion %d: ", i);
        Nodo *nodo_actual = tabla_hash[i]; // Empezamos por el primer nodo de la lista en esa posicion
        while (nodo_actual != NULL) {
            printf("(%s, %d) ", nodo_actual->nombre, nodo_actual->valor);
            nodo_actual = nodo_actual->sig; // Pasamos al siguiente nodo
        }
        printf("\n");
    }
}

//*********************************************************************************************************


//****************************          FUNCION PRINCIPAL               **********************************
int main() {
	//Menu principal
	MenuPrincipal:
	system("cls");
	int num;
	int cant;
	int select;
	printf("Selecciona una opcion:\n1 = PILAS\n2 = COLAS\n3 = TABLAS HASH\n4 = Salir\n");
	scanf("%d",&select);
	switch(select){
		case 1:
			{
				system("cls");
				struct NodoP *top = NULL;
			    
				printf("cuantos datos quiere agregar a la pila?\n");
				scanf("%d",&cant);
				//Loop para agregar los elementos a la pila
				for (int i=0;i<cant;i++){
					printf("\nIngrese un numero a la pila\n");
					scanf("%d",&num);
					push(&top,num);
				}
		
				MenuPilas:
				system("cls");
				printf("Elige una opcion:\n1 = Mostrar Pila\n2 = Eliminar elemento\n3 = Agregar Elemento\n4 = Menu Principal\n");
				scanf("%d",&select);
				switch(select){
			
					case 1:
						{
							// Mostrar los elementos de la pila
							system ("cls");
				    		mostrarPila(top);
				    		system("pause");
				    		goto MenuPilas;
			    		}
					
					case 2:
						{
							// Eliminar un elemento de la pila
							system("cls");
				    		int dato = pop(&top);
				    		printf("Elemento eliminado: %d\n", dato);
				    		system("pause");
				    		goto MenuPilas;
			    		}
			    		
					case 3:
						{
							//agregar elemento	
							printf("Ingresa el elemento: \n");
							scanf("%d", &num);
							push(&top,num);
							goto MenuPilas;
						}
						
					case 4:
						{
							//Volver al menu principal	
							goto MenuPrincipal;
						}
					
					default:
						{
							goto MenuPilas;
						}
				}
			}
			
		case 2:
			{
			
				system("cls");
				queue_t q;
			    q.front = -1;
			    q.rear = -1;
			    q.size = DEFAULT_QUEUE_SIZE;
			    q.items = (int *)malloc(q.size * sizeof(int));
				
				MenuCola:
				system("cls");
			    printf("Elige una opcion:\n1 = Agregar Elemento\n2 = Quitar Elemento\n3 = Mostrar Cola\n4 = Cambiar Tama?o\n5 = Menu Principal\n");
			    scanf("%d", &select);
			    switch(select){
			    	case 1:
			    		{
			    			//Agregar elemento
				    		system("cls");
				    		enqueue(&q);
							system("pause");
							goto MenuCola;
						}
					
					case 2:
						{
							//Quitar elemento
							system("cls");
							dequeue(&q);
							system("pause");
							goto MenuCola;
						}
					
					case 3:
						{
							//Mostrar Cola
							system("cls");
							display(&q);
							system("pause");
							goto MenuCola;
						}
						
					case 4:
						{
							//Cambiar tamano de cola
							system("cls");
							resize(&q);
							system("pause");
							goto MenuCola;
						}
						
					case 5:
						{
							//Ir al Menu Principal
							goto MenuPrincipal;
						}
					
					default:
						goto MenuCola;
				}
			}
		case 3:
			{
				Nodo *tabla_hash[MAX]; // Inicializamos la tabla hash
			    for (int i = 0; i < MAX; i++) {
			        tabla_hash[i] = NULL; // Inicializamos cada lista como vacia
			    }
			    char nombre[50];
			    int valor;
			    MenuTablaHash:
			    system("cls");
				printf("Elige una opcion:\n1 = Agregar elementos a la tabla\n2 = Buscar elementos en la tabla\n3 = Mostrar tabla\n4 = Menu Principal\n");
			    scanf("%d",&select);
			    switch (select){
			    	case 1:
			    		{
			    			system("cls");
			    			// Pedimos al usuario que ingrese los datos
						    printf("Ingrese el nombre y valor del elemento (para salir, ingrese 'salir' como nombre): ");
						    scanf("%s", nombre);
						    while (strcmp(nombre, "salir") != 0) { // Mientras el usuario no ingrese "salir"
						    	printf("\nIngrese el valor del elemento: ");
						        scanf("%d", &valor);
						        insertar_elemento(tabla_hash, nombre, valor); // Insertamos el elemento en la tabla hash
						        printf("Ingrese el nombre y valor del elemento (para salir, ingrese 'salir' como nombre): ");
						        scanf("%s", nombre);
						    }
			    			system("pause");
			    			goto MenuTablaHash;
						}
						
					case 2:
						{
							system("cls");
							// Buscamos un elemento en la tabla hash
						    printf("Ingrese el nombre del elemento a buscar: ");
						    scanf("%s", nombre);
						    Nodo *nodo_buscado = buscar_elemento(tabla_hash, nombre);
						    if (nodo_buscado != NULL) {
						        printf("El valor del elemento %s es %d.\n", nodo_buscado->nombre, nodo_buscado->valor);
						    } else {
						        printf("El elemento no se encontro en la tabla hash.\n");
						    }
							system("pause");
							goto MenuTablaHash;
						}
						
					case 3:
						{
							//Mostramos la tabla
							system("cls");
							mostrar_tabla(tabla_hash);
							system("pause");
							goto MenuTablaHash;
						}
					
					case 4:
						{
							goto MenuPrincipal;
						}
						
					default:
						{
							goto MenuTablaHash;
						}
				}	    
			}
			
		case 4:
			{
				break;
			}
			
		default:
    		{
    			goto MenuPrincipal;
			}
	}
    return 0;
}
