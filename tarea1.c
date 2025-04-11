#include "list.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
  int id;
  char descripcion[100];
  int prioridad; //1 = Baja, 2 = Media, 3 = Alta
  time_t timestamp;
} Ticket;

typedef struct Node {
  Ticket *data;
  struct Node *next;
} Node;


// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("Sistema de gestión de tickets de soporte técnico");
  puts("========================================");

  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a ticket");
  puts("3) Mostrar lista tickets pendientes");
  puts("4) Atender al siguiente ticket");
  puts("5) Buscar ticket por ID");
  puts("6) Salir");
}

int existe_id(List *alto, List *medio, List *bajo, int id){
  Ticket *actual = list_first(bajo);
  while(actual != NULL){
    if(actual->id == id) return 1;
    actual = list_next(bajo);
  }
  actual = list_first(medio);
  while(actual != NULL){
    if(actual->id == id) return 1;
    actual = list_next(medio);
  }
  actual = list_first(alto);
  while(actual != NULL){
    if(actual->id == id) return 1;
    actual = list_next(alto);
  }
  return 0;
}

void registrar_ticket(List *alto, List *medio, List *bajo) {
  puts("Registrar nuevo ticket");
  Ticket *nuevo = (Ticket *)malloc(sizeof(Ticket)); //se crea un nuevo Ticket
  printf("Ingrese ID:\n");
  scanf("%d", &nuevo->id); //se ingresa el ID del ticket 
  getchar();
  if(existe_id(alto, medio, bajo, nuevo->id)){
    printf("ID ya fue registrado.");
    return;
  }
  printf("Ingrese descripción de problema:\n");
  scanf(" %99[^\n]", nuevo->descripcion); //se lee la descripción del problema hasta el salto de linea
  getchar();
  nuevo->timestamp = time(NULL); // Hora actual
  list_pushBack(bajo, nuevo); //se ingresa el ticket a la lista de prioridad baja(1) por defecto
}

void cambiar_prioridad(Ticket *actual, int nueva_prioridad, List *origen, List *destino){
  actual->prioridad = nueva_prioridad;
  actual->timestamp = time(NULL);
  list_popCurrent(origen);
  list_pushBack(destino, actual);
  printf("Prioridad reasignada correctamente.\n");
}

void asignar_prioridad(List *alto, List *medio, List *bajo){
  int nueva_prioridad;
  int id;
  printf("Ingrese ID de ticket para asignar prioridad:\n");
  scanf("%d", &id);
  Ticket *actual = list_first(bajo);
  while(actual != NULL){
    if(actual->id == id){
      printf("Ingrese nueva prioridad:\n");
      scanf("%d", &nueva_prioridad); //se ingresa la nueva prioridad que se le quiere asignar al ticket (1(Baja), 2(Media), 3(Alta))
      if (nueva_prioridad < 2 || nueva_prioridad > 3){
        printf("Número ingresado no válido o prioridad nueva igual a la actual.\n");
        return;
      }
      if(nueva_prioridad == 2) cambiar_prioridad(actual, nueva_prioridad, bajo, medio);
      else cambiar_prioridad(actual, nueva_prioridad, bajo, alto);
      return;
    }
    actual = list_next(bajo); //"actual" recorre toda la lista de prioridad baja hasta encontrar el ticket con el ID ingresado
  }
//si no se encuentra el ticket en la lista "Bajo", se repite el mismo proceso buscando en las otras dos listas y reasignando el ticket si corresponde.
//esto permite reasignar prioridad de un ticket independiente de si su prioridad ya fue asignada.
  actual = list_first(medio);
  while(actual != NULL){
    if(actual->id == id){
      printf("Ingrese nueva prioridad:\n");
      scanf("%d", &nueva_prioridad); //se ingresa la nueva prioridad que se le quiere asignar al ticket (1(Baja), 2(Media), 3(Alta))
      if (nueva_prioridad < 1 || nueva_prioridad > 3 || nueva_prioridad == 2){
        printf("Número ingresado no válido o prioridad nueva igual a la actual.\n");
        return;
      }
      if(nueva_prioridad == 1) cambiar_prioridad(actual, nueva_prioridad, medio, bajo);
      else cambiar_prioridad(actual, nueva_prioridad, medio, alto);
      return;
    }
    actual = list_next(medio);
  }
  actual = list_first(alto);
  while(actual != NULL){
    if(actual->id == id){
      printf("Ingrese nueva prioridad:\n");
      scanf("%d", &nueva_prioridad); //se ingresa la nueva prioridad que se le quiere asignar al ticket (1(Baja), 2(Media), 3(Alta))
      if (nueva_prioridad < 1 || nueva_prioridad > 2){
        printf("Número ingresado no válido o prioridad nueva igual a la actual.\n");
        return;
      }
      if(nueva_prioridad == 2) cambiar_prioridad(actual, nueva_prioridad, alto, medio);
      else cambiar_prioridad(actual, nueva_prioridad, alto, bajo);
      return;
    }
    actual = list_next(alto);
  }
  printf("Ticket de ID %d no encontrado en la lista de tickets.\n", id);
}

void mostrar_lista_tickets(List *alto, List *medio, List *bajo) {
  // Mostrar tickets en la cola de espera
  printf("tickets en espera: \n");
  Ticket *actual = list_first(alto);
  if (actual != NULL){
    printf("\nPrioridad alta:\n");
    while(actual != NULL){
      printf("ID: %d. ", actual->id);
      printf("\n");
      actual = list_next(alto);
    }
    printf("\n");
  }
  actual = list_first(medio);
  if (actual != NULL){
    printf("\nPrioridad media:\n");
    while(actual != NULL){
      printf("ID: %d. ", actual->id);
      printf("\n");
      actual = list_next(medio);
    }
    printf("\n");
  }
  actual = list_first(bajo);
  if (actual != NULL){
    printf("\nPrioridad baja:\n");
    while(actual != NULL){
      printf("ID: %d. ", actual->id);
      printf("\n");
      actual = list_next(bajo);
    }
  }
}

void procesar_siguiente(List *alto, List *medio, List *bajo){
  Ticket *actual = list_first(alto);
  if(actual != NULL){
    list_popFront(alto);
    printf("\nAtendiendo ticket de prioridad alta:\n");
  
  }
  else if((actual = list_first(medio)) != NULL){
    list_popFront(medio);
    printf("\nAtendiendo ticket de prioridad media:\n");
  }
  else if((actual = list_first(bajo)) != NULL){
    list_popFront(bajo);
    printf("\nAtendiendo ticket de prioridad baja:\n");
  }
  else{
    printf("No quedan tickets por atender.\n");
    return;
  }
  
  printf("ID: %d\n", actual->id);
  printf("Descripción problema: %s\n", actual->descripcion);
  printf("Hora registro: %s\n\n", ctime(&actual->timestamp));
  free(actual);
}

void buscar_ticket(List *alto, List *medio, List *bajo){
  int id;
  printf("Ingrese ID de ticket deseado:\n");
  scanf("%d", &id);

  Ticket *actual = NULL;
  actual = list_first(alto);
  while(actual != NULL){
    if(actual->id == id){
      printf("ID: %d\n", actual->id);
      printf("Descripción problema: %s\n", actual->descripcion);
      printf("Prioridad ALTA\n");
      printf("Hora registro: %s\n\n", ctime(&actual->timestamp));
      return;
    }
    actual = list_next(alto);
  }
  actual = list_first(medio);
  while(actual != NULL){
    if(actual->id == id){
      printf("ID: %d\n", actual->id);
      printf("Descripción problema: %s\n", actual->descripcion);
      printf("Prioridad MEDIA\n");
      printf("Hora registro: %s\n\n", ctime(&actual->timestamp));
      return;
    }
    actual = list_next(medio);
  }
  actual = list_first(bajo);
  while(actual != NULL){
    if(actual->id == id){
      printf("ID: %d\n", actual->id);
      printf("Descripción problema: %s\n", actual->descripcion);
      printf("Prioridad BAJA\n");
      printf("Hora registro: %s\n\n", ctime(&actual->timestamp));
      return;
    }
    actual = list_next(bajo);
  }
  printf("ID ingresado no está entre los tickets en lista de espera.\n");
}

int main() {
  char opcion;
  List *lista_bajo = list_create(); // lista donde se almacenan todos los tickets al inicio
  List *lista_medio = list_create(); //lista de tickets con nivel de urgencia medio
  List *lista_alto = list_create();  //lista de tickets con nivel de urgencia alto

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el eslistaio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_ticket(lista_alto, lista_medio, lista_bajo);
      break;
    case '2':
      asignar_prioridad(lista_alto, lista_medio, lista_bajo);
      break;
    case '3':
      mostrar_lista_tickets(lista_alto, lista_medio, lista_bajo);
      break;
    case '4':
      // Lógica para atender al siguiente ticket
      procesar_siguiente(lista_alto, lista_medio, lista_bajo);
      break;
    case '5':
      // Lógica para buscar ticket por ID
      buscar_ticket(lista_alto, lista_medio, lista_bajo);
      break;
    case '6':
      puts("Saliendo del sistema de gestión de tickets...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(lista_alto);
  list_clean(lista_medio);
  list_clean(lista_bajo);

  return 0;
}
