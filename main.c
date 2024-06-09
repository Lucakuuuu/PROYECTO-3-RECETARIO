#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/map.h"

// PARA ELIMINAR GITs INGRESAR CÓDIGO EN Shell: " git reset --hard HEAD~1 "

typedef struct{
  char nombre_receta[30]; 
  List *lista_ingredientes; // Lista de ingredientes
  char tipo_de_plato[15]; //acompañamiento, postre, plato principal, etc
  List *lista_dietas; //si es vegana, vegetariana, omnivora, etc.
  char preparacion[2000]; //pasos a seguir para preparar la receta
} receta;

typedef struct
{
  char dieta[50];
  List *recetas;
} recetasxdieta;

typedef struct{
  char plato[50];
  List *recetas;
} platosxdieta;

int is_equal_str(void *key1, void *key2) {return strcmp((char *)key1, (char *)key2) == 0;}

int is_equal_int(void *key1, void *key2) {return *(int *)key1 == *(int *)key2; }

// Función para reservar espacio inicial para una cadena
char *espacioInicial(char *cadena) {
    int longitud = strlen(cadena);
    char *cadenaCopia = (char *)malloc((longitud + 1) * sizeof(char));
    if (cadenaCopia == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    strcpy(cadenaCopia, cadena);
    return cadenaCopia;
}

// Función para recortar espacios en blanco al inicio y final de una cadena
char *trim(char *cadena) {
    char *inicio, *fin;

    // Elimina espacios en blanco al inicio de la cadena
    inicio = cadena;
    while (*inicio == ' ') {
        inicio++;
    }

    // Si la cadena está vacía después de eliminar espacios al inicio, retorna la cadena vacía
    if (*inicio == '\0') {
        return inicio;
    }

    // Elimina espacios en blanco al final de la cadena
    fin = inicio + strlen(inicio) - 1;
    while (fin > inicio && *fin == ' ') {
        fin--;
    }

    *(fin + 1) = '\0'; // Agrega un terminador de cadena al final recortado
    return inicio;
}

// Función para eliminar comillas y espacios en blanco al inicio y al final de la cadena
void arreglar_cadena(char *cadena) {
    while (1) {
        int cambio = 0;

        // Elimina las comillas dobles si están presentes (")
        if (cadena[0] == '"' && cadena[strlen(cadena) - 1] == '"') {
            memmove(cadena, cadena + 1, strlen(cadena));
            cadena[strlen(cadena) - 1] = '\0';
            cambio = 1;
        }

        // Elimina las comillas simples si están presentes (')
        if (cadena[0] == '\'' && cadena[strlen(cadena) - 1] == '\'') {
            memmove(cadena, cadena + 1, strlen(cadena));
            cadena[strlen(cadena) - 1] = '\0';
            cambio = 1;
        }

        // Recorta espacios en blanco al inicio y final de la cadena
        char *recortada = trim(cadena);
        if (recortada != cadena) {
            memmove(cadena, recortada, strlen(recortada) + 1);
            cambio = 1;
        }

        if (!cambio) {
            break;
        }
    }
}

void aMinusculas(char *cadena) {
    // Inicializamos el puntero actual
    char *actual = cadena;

    // Mientras haya caracteres en la cadena
    while (*actual) {
        // Convertir a minúscula si es una letra mayúscula (excepto las tildadas)
        if (*actual >= 'A' && *actual <= 'Z' && !((*actual >= (char)128 && *actual <= (char)165) || (*actual >= (char)192 && *actual <= (char)221))) {
            *actual = *actual + 32;
        }
        if (*actual == ' '  && *actual == cadena[0]) 
        {
            memmove(actual, actual + 1, strlen(actual));
        }

        actual++;
    }
}

void copiarLista(List *listaCopia, List *listaOriginal) {
    if (listaOriginal == NULL) {
        printf("La lista original está vacía.\n");
        return;
    }
    List *actual = list_first(listaCopia);
    while (actual != NULL) {
        list_pushBack(listaOriginal, actual);
        actual = list_next(listaCopia);
    }
}

void mostrarLista(List *lista) {
    if (lista == NULL) {
        printf("La lista está vacía.\n");
        return;
    }
    List *actual = list_first(lista);
    printf("%s", (char *)actual);
    actual = list_next(lista);
    while (actual != NULL) {
        printf(", %s", (char *)actual);
        actual = list_next(lista);
    }
    printf("\n");
}

void imprimir(receta *receta, int contador) {
    printf("%d. Receta: %s\n", contador, receta->nombre_receta);
    printf("    Tipo de plato: %s\n", receta->tipo_de_plato);
    printf("    Ingredientes: ");
    mostrarLista(receta->lista_ingredientes);
    printf("    Dietas: ");
    mostrarLista(receta->lista_dietas);
    printf("    Preparacion: %s\n", receta->preparacion);
    printf("\n");
}

void rellenar_mapa_de_ingredientes(Map *mapa_ingredientes, receta *receta) {
  List *lista_ingredientes = receta->lista_ingredientes;
  char *aux = list_first(lista_ingredientes);

  while (aux != NULL) {
    MapPair *par = map_search(mapa_ingredientes, aux);

    // If the ingredient is not present in the map, create a new list
    if (par == NULL) {
      List *lista_recetas = list_create();
      list_pushBack(lista_recetas, receta);
      map_insert(mapa_ingredientes, aux, lista_recetas);
    } else { // If the ingredient is present, add the recipe to its list
      List *lista_recetas = par->value;
      list_pushBack(lista_recetas, receta);
    }

    aux = list_next(lista_ingredientes);
  }
}

void cargar_recetas(Map *recetas_ordenadas, Map *tipo_de_plato, Map *tipo_dieta, Map *mapa_ingredientes) {
    FILE *archivo = fopen("Ingredientes/Ingredientes.csv", "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');
    List *aux = list_create();

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        receta *receta_nueva = (receta*)malloc(sizeof(receta));
        strcpy(receta_nueva->nombre_receta, campos[0]);
        receta_nueva->lista_ingredientes = list_create();

        if (strcmp(campos[1], "") != 0) {
            char *ingredienteActual = strtok(campos[1], ",");
            while (ingredienteActual != NULL) {
                arreglar_cadena(ingredienteActual);
                list_pushBack(aux, espacioInicial(ingredienteActual));
                ingredienteActual = strtok(NULL, ",");
            }
            copiarLista(aux, receta_nueva->lista_ingredientes);
            list_clean(aux);
        }
        strcpy(receta_nueva->tipo_de_plato, campos[2]);
        receta_nueva->lista_dietas = list_create();

        if (strcmp(campos[3], "") != 0) {
            char *dietaActual = strtok(campos[3], ",");
            while (dietaActual != NULL) {
                arreglar_cadena(dietaActual);
                if (strlen(dietaActual) > 0) {
                    list_pushBack(aux, espacioInicial(dietaActual));
                    MapPair *estaDieta = map_search(tipo_dieta, espacioInicial(dietaActual));
                    if (estaDieta == NULL) {
                        recetasxdieta *nuevadieta = (recetasxdieta *)malloc(sizeof(recetasxdieta));
                        nuevadieta->recetas = list_create();
                        map_insert(tipo_dieta, espacioInicial(dietaActual), nuevadieta);
                        list_pushBack(nuevadieta->recetas, receta_nueva);
                    } else {
                        recetasxdieta *Dpair = estaDieta->value;
                        list_pushBack(Dpair->recetas, receta_nueva);
                    }
                }
                dietaActual = strtok(NULL, ",");
            }
            copiarLista(aux, receta_nueva->lista_dietas);
            list_clean(aux);
        }
        strcpy(receta_nueva->preparacion, campos[4]);
        map_insert(recetas_ordenadas, receta_nueva->nombre_receta, receta_nueva);
        rellenar_mapa_de_ingredientes(mapa_ingredientes, receta_nueva);
    }
    fclose(archivo);
}

void mostrar_todas_las_recetas(Map *recetas_ordenadas) {
    MapPair *pair = map_first(recetas_ordenadas);
    printf("\n");
    int contador = 0;
    while (pair != NULL) {
        receta *receta_actual = pair->value;
        contador++;
        imprimir(receta_actual, contador);
        pair = map_next(recetas_ordenadas);
    }
}

void menu_secundario() {
    printf("\nMostrar recetas según:\n");
    printf("-----------------------\n\n");
    printf("1. Tipo de plato\n");
    printf("2. Tipo de dieta\n");
    printf("3. Todas las recetas\n");
    printf("4. Volver al menú principal\n\n");
}

void buscarDieta(Map *tipo_dieta) {
    printf("\nDietas disponibles:\n\n");
    MapPair *pair = map_first(tipo_dieta);
    unsigned short contador = 1;
    while (pair != NULL) {
        recetasxdieta *dieta = (recetasxdieta *)pair->value;
        printf("%hu) %s\n", contador, (char *)pair->key); contador++;
        pair = map_next(tipo_dieta);
    } 
    printf("\n");

    char opcionDieta[50];
    contador = 1;

    printf("\nIngrese la dieta deseada: ");
    scanf("%s", opcionDieta); // Lee la dieta
    // Itera sobre el mapa para buscar recetas de la dieta especificada
    pair = map_search(tipo_dieta, opcionDieta);
    if (pair != NULL) {
        recetasxdieta *dietaP = pair->value;
        receta *receta_actual = list_first(dietaP->recetas);
        while (receta_actual != NULL) {
            if (contador == 1) 
                printf("\nRECETAS %s:\n\n", opcionDieta);
            imprimir(receta_actual, contador);
            contador++;
            receta_actual = list_next(dietaP->recetas);
        }
    }
    if (contador == 1) 
        printf("No se encontraron recetas %s\n", opcionDieta);
}

void mostrar_recetas(Map *recetas_ordenadas, Map *tipo_dieta) {
    char opcion;
    do {
        limpiarPantalla();
        menu_secundario();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
        switch (opcion) {
        case '1':
            // buscarPlato();
            break;
        case '2':
            buscarDieta(tipo_dieta);
            break;
        case '3':
            mostrar_todas_las_recetas(recetas_ordenadas);
            break;
        case '4':
            printf("Volviendo...\n");
            return;
        default:
            puts("Opción no válida. Por favor, intente de nuevo.");
        }
        presioneTeclaParaContinuar();
    } while (opcion != '4');
}

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("                Recetario               ");
    puts("========================================");

    puts("1) Mostrar recetas");
    puts("2) Buscar por ingredientes");
    puts("3) Buscar recetas posibles");
    puts("4) Salir\n");
}

void menu_ingredientes()
{
  printf("Cuantos ingredientes quiere en la receta:\n");
  printf("-----------------------\n\n");
  printf("1. Por un ingrediente\n");
  printf("2. Por dos ingredientes\n");
  printf("3. Por tres ingredientes\n");
  printf("4. Por cuatro ingredientes\n");
  printf("5. Por cinco ingredientes\n");
}

int comparar_listas(List *lista1, List *lista2, int ingr)
{
  if (lista1 == NULL || lista2 == NULL)
  {
    printf("una de las listas está vacía.\n");
    exit(EXIT_FAILURE);
  }

  char *aux1 = list_first(lista1);
  char *aux2 = list_first(lista2);
  int count = 0;

  while (aux1 != NULL)
  {
    while (aux2 != NULL)
    {
      if (strcmp(aux1, aux2) == 0)
      {
        count++;
        break;
      }

      aux2 = list_next(lista2);
    }
    aux1 = list_next(lista1);
    aux2 = list_first(lista2);
  }

  if (count == ingr)
    return 1;
  return 0;
}

void buscar_por_ingredientes(Map *mapa_ingredientes)
{
  limpiarPantalla();
  menu_ingredientes();
  int ingr = 0;
  printf("\nIngrese una opcion valida: \n");
  scanf("%d", &ingr);

  printf("\nRECUERDE: todo en minúsculas y con tilde\n");	
  printf("Inserte los ingredientes: \n");
  getchar();

  List *ingredientes = list_create();
  char ingrediente_actual[20];
  int i = 0;


  while (i < ingr)
  {
      scanf("%19[^\n]", ingrediente_actual);
      getchar();
      aMinusculas(ingrediente_actual);
      trim(ingrediente_actual);
      list_pushBack(ingredientes, espacioInicial(ingrediente_actual));
      i++;
  }

  MapPair *par = map_search(mapa_ingredientes, ingrediente_actual);
    if(par == NULL) {
        printf("No se encontraron recetas con esos ingredientes\n");
        return;
    }
    List *lista_recetas = par->value;
    receta *aux = list_first(lista_recetas);
    int contador = 1;
    while (aux != NULL) 
    {
      if (comparar_listas(aux->lista_ingredientes, ingredientes, ingr) == 1)
      {
        imprimir(aux, contador);
        contador++;
      }
      aux = list_next(lista_recetas);
    }
  map_clean(mapa_ingredientes);
}

int main() {
    char opcion;
    Map *recetas_ordenadas = map_create(is_equal_str);
    Map *tipo_de_plato = map_create(is_equal_str);
    Map *tipo_dieta = map_create(is_equal_str);
    Map *mapa_ingredientes = map_create(is_equal_str);

    do {
        mostrarMenuPrincipal();
        cargar_recetas(recetas_ordenadas, tipo_de_plato, tipo_dieta, mapa_ingredientes);
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
        switch (opcion) {
        case '1':
            mostrar_recetas(recetas_ordenadas, tipo_dieta);
            break;
        case '2':
            buscar_por_ingredientes(mapa_ingredientes);
            break;
        case '3':
            // buscarXRecetas(recetas_ordenadas);
            break;
        case '4':
            puts("Saliendo del recetario...");
            break;
        default:
            puts("Opción no válida. Por favor, intente de nuevo.");
        }
        presioneTeclaParaContinuar();
    } while (opcion != '4');
    return 0;
}