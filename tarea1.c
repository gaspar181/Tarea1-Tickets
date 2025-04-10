#include "tdas/list.h"
#include "tdas/extra.h"
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

void registrar_ticket(List *lista_bajo) {
  puts("Registrar nuevo ticket");
  Ticket *nuevo = (Ticket *)malloc(sizeof(Ticket)); //se crea un nuevo Ticket
  printf("Ingrese ID:\n");
  scanf("%d", &nuevo->id); //se ingresa el ID del ticket 
  getchar();
  printf("Ingrese descripción de problema:\n");
  scanf(" %[^\n]", nuevo->descripcion); //se lee la descripción del problema hasta el salto de linea
  getchar();
  nuevo->timestamp = time(NULL); // Hora actual
  list_pushBack(lista_bajo, nuevo); //se ingresa el ticket a la lista de prioridad baja(1) por defecto
}

void cambiar_prioridad(Ticket *actual, int nueva_prioridad, List *origen, List *destino){
  actual->prioridad = nueva_prioridad;
  actual->timestamp = time(NULL);
  list_pushBack(destino, actual);
  list_popCurrent(origen);
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
      if (nueva_prioridad < 2 || nueva_prioridad > 3) printf("Número ingresado no válido o prioridad nueva igual a la actual.\n");
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
      if (nueva_prioridad < 1 || nueva_prioridad > 3 || nueva_prioridad == 2) printf("Número ingresado no válido o prioridad nueva igual a la actual.\n");
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
      if (nueva_prioridad < 1 || nueva_prioridad > 2) printf("Número ingresado no válido o prioridad nueva igual a la actual.\n");
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
    printf("\n\nPrioridad alta:\n");
    while(actual != NULL){
      printf("ID: %d. ", actual->id);
      printf("\n");
      actual = list_next(alto);
    }
    printf("\n");
  }
  actual = list_first(medio);
  if (actual != NULL){
    printf("\n\nPrioridad media:\n");
    while(actual != NULL){
      printf("ID: %d. ", actual->id);
      printf("\n");
      actual = list_next(medio);
    }
    printf("\n");
  }
  actual = list_first(bajo);
  if (actual != NULL){
    printf("\n\nPrioridad baja:\n");
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

  struct tm *tm_info = localtime(actual->timestamp);
  int hora = tm_info->tm_hour;
  int min = tm_info->tm_min;
  
  printf("ID: %d\n", actual->id);
  printf("Descripción problema: %s\n", actual->descripcion);
  printf("Hora registro: %02d:%02d\n\n", hora, min);
  free(actual);
}

void buscar_ticket(List *alto, List *medio, List *bajo){
  int id;
  printf("Ingrese ID de ticket deseado:\n");
  scanf("%d", &id);

  Ticket *actual = list_first(alto);
  while(actual != NULL){
    if(actual->id == id){
      struct tm *tm_info = localtime(actual->timestamp);
      int hora = tm_info->tm_hour;
      int min = tm_info->tm_min;
      printf("ID: %d\n", actual->id);
      printf("Descripción problema: %s\n", actual->descripcion);
      printf("Prioridad ALTA\n");
      printf("Hora registro: %02d:%02d\n\n", hora, min);
      return;
    }
    actual = list_next(alto);
  }
  actual = list_first(medio);
  while(actual != NULL){
    if(actual->id == id){
      struct tm *tm_info = localtime(actual->timestamp);
      int hora = tm_info->tm_hour;
      int min = tm_info->tm_min;
      printf("ID: %d\n", actual->id);
      printf("Descripción problema: %s\n", actual->descripcion);
      printf("Prioridad MEDIA\n");
      printf("Hora registro: %02d:%02d\n\n", hora, min);
      return;
    }
    actual = list_next(medio);
  }
  actual = list_first(bajo);
  while(actual != NULL){
    if(actual->id == id){
      struct tm *tm_info = localtime(actual->timestamp);
      int hora = tm_info->tm_hour;
      int min = tm_info->tm_min;
      printf("ID: %d\n", actual->id);
      printf("Descripción problema: %s\n", actual->descripcion);
      printf("Prioridad BAJA\n");
      printf("Hora registro: %02d:%02d\n\n", hora, min);
      return;
    }
    actual = list_next(bajo);
  }
  printf("ID ingresado no está entre los tickets en lista de espera.\n");
}

int main() {
  char opcion;
  List *pac_bajo = list_create(); // lista donde se almacenan todos los tickets al inicio
  List *pac_medio = list_create(); //lista de tickets con nivel de urgencia medio
  List *pac_alto = list_create();  //lista de tickets con nivel de urgencia alto

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_ticket(pac_bajo);
      break;
    case '2':
      asignar_prioridad(pac_alto, pac_medio, pac_bajo);
      break;
    case '3':
      mostrar_lista_tickets(pac_alto, pac_medio, pac_bajo);
      break;
    case '4':
      // Lógica para atender al siguiente ticket
      printf("xxx");
      break;
    case '5':
      // Lógica para mostrar tickets por prioridad
      printf("xxx");
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pac_alto);
  list_clean(pac_medio);
  list_clean(pac_bajo);

  return 0;
}
