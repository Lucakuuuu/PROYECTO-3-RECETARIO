#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/stack.h"
#include "TDAs/map.h"

// PARA ELIMINAR GITs INGRESAR CÓDIGO EN Shell: " git reset --hard HEAD~1 "

// **************************************** VARIABLES DINAMICAS (STRUCTs) **************************************** //

// Estructura para almacenar la información de una receta
typedef struct {
  char nombre_receta[30]; // Nombre de la receta
  List *lista_ingredientes; // Lista de ingredientes
  char tipo_de_plato[15]; // Si es acompañamiento, postre, plato principal, etc
  List *lista_dietas; // Si es vegana, vegetariana, omnivora, etc.
  char preparacion[2000]; // Pasos a seguir para preparar la receta
} receta;

typedef struct {
  char dieta[50]; 
  List *recetas;
} recetasxdieta;

typedef struct {
    char tipo_busqueda[50];
    List *ingredientes;
    char categoria[20];
} datosHistorial;

//***************************************************************************************************************************** //

// **************************************** FUNCIONES DE FUNCIONES PRINCIPALES **************************************** //

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

// Función para pasar una cadena a minúsculas
void Capitalizar(char *cadena) {
    char *actual = cadena;
    while (*actual){
      if (*actual == ' '  && *actual == cadena[0]) memmove(actual, actual + 1, strlen(actual));
      if(*actual == cadena[0]) *actual = toupper(*actual);
      actual++;
    }
}

// Función para quitar el espacio inicial de una cadena
char *espacioInicial(char *cadena) {
    int longitud = strlen(cadena); // Obtener la longitud de la cadena
    char *cadenaCopia = (char *)malloc((longitud + 1) * sizeof(char)); // Asignar memoria y quitar el espacio inicial
    if (cadenaCopia == NULL) { // Si la reserva de memoria no fue exitosa
        printf("Error al asignar memoria.\n"); 
        exit(1); // Salir del programa con código de error
    }
    strcpy(cadenaCopia, cadena); // Copiar la cadena original a la copia
    return cadenaCopia; // Retornar la copia
}

// Función para copiar una lista
void copiarLista(List *listaCopia, List *listaOriginal) {
    if (listaOriginal == NULL) return;
    List *actual = list_first(listaCopia);
    while (actual != NULL) {
        list_pushBack(listaOriginal, actual);
        actual = list_next(listaCopia);
    }
}

// Función para llenar el mapa de platos
void rellenar_tipo_plato(Map *mapa_tipo, receta *receta){
    MapPair *par = map_search(mapa_tipo, receta->tipo_de_plato);
    if (par == NULL)
    {
        List *lista_recetas = list_create();
        list_pushBack(lista_recetas, receta);
        map_insert(mapa_tipo, receta->tipo_de_plato, lista_recetas);    
    }
    else
    {
        List *lista_recetas = par->value;
        list_pushBack(lista_recetas, receta);  
    }
}

// Función para llenar el mapa de ingredientes
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

int comparar_listas(List *lista1, List *lista2, int ingr){
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
  if (count == ingr) return 1;
  return 0;
}

int buscar_en_listas(List *lista1, List *lista2){
    if (lista1 == NULL || lista2 == NULL)
    {
        printf("una de las listas está vacía.\n");
        exit(EXIT_FAILURE);
    }
    char *aux1 = list_first(lista1);
    char *aux2 = list_first(lista2);

    while (aux1 != NULL)
    {
        while (aux2 != NULL)
        {
            if (strcmp(aux1, aux2) == 0) return 0;
            aux2 = list_next(lista2);
        }
        aux1 = list_next(lista1);
        aux2 = list_first(lista2);
    }
    return 1;
}

// Función para imprimir una lista
void mostrarLista(List *lista){
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

// Función para imprimir una receta
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

void menu_secundario() {
    printf("\nMostrar recetas según:\n");
    printf("-----------------------\n\n");
    printf("1. Tipo de plato\n");
    printf("2. Tipo de dieta\n");
    printf("3. Todas las recetas\n");
    printf("4. Volver al menú principal\n\n");
}

void omitir_ingredientes(List *lista){
    char ingrediente_actual[20];
    int ingr = 0;
    int i = 0;
    
    printf("\nIngrese la cantidad de ingredientes que quiere omitir: \n");
    scanf("%d", &ingr);

    if (ingr == 0)
    {
        printf("No se omitirá ningún ingrediente\n");
        return;
    }
    
    printf("\nRECUERDE: todo en minúsculas, con tilde y pulse enter para agregar el siguiente ingrediente\n");	
    printf("Inserte los ingredientes que no desea en las recetas: \n");
    getchar();
    
    while (i < ingr)
    {
        scanf("%19[^\n]", ingrediente_actual);
        getchar();
        Capitalizar(ingrediente_actual);
        trim(ingrediente_actual);
        list_pushBack(lista, espacioInicial(ingrediente_actual));
        i++;
    }
}

int comparar_listas_posibles(List *lista1, List *lista2, List *ingredientes_faltantes){
    if (lista1 == NULL || lista2 == NULL) {
        printf("Una de las listas está vacía.\n");
        exit(EXIT_FAILURE);
    }

  char *aux1 = list_first(lista1);
  int count = 0;
  int posicion = 0;
  int marcar[5] = {0};
  while (aux1 != NULL) 
  {
    char *aux2 = list_first(lista2);
    while (aux2 != NULL) 
    {
      if (strcmp(aux1, aux2) == 0) 
      {
        count++;
        marcar[posicion] = 1;
        break;  // Romper el bucle interno si hay coincidencia para este elemento de lista1
      }
      aux2 = list_next(lista2);  // Avanzar al siguiente elemento de lista2
    }
    aux1 = list_next(lista1);  // Avanzar al siguiente elemento de lista1
    posicion++;
   }

  if (count >= 3) 
  {
      char *ingrediente = list_first(lista1);
      for(int i = 0; i < 5; i++)
      {
          if(marcar[i] == 0) list_pushBack(ingredientes_faltantes, ingrediente);
           ingrediente = list_next(lista1);
      }
      return 1;
  }
  return 0;
}

bool filtro_receta_repetida(List *lista_favoritas, char *nombre_receta){
    List *actual = list_first(lista_favoritas);
    while (actual != NULL){
        receta *Receta = (receta *) actual;
        if (strcmp(Receta->nombre_receta, nombre_receta) == 0) return true;
        actual = list_next(lista_favoritas);
    }
    return false;
}

void eliminar_receta(List *lista_favoritas, Stack *historial) {

    char opcion_receta[50];
    int bandera = 1;
    char opcion;

    printf("Ingrese el nombre de la receta que desea eliminar de tu lista de favoritas\n");
    scanf("%49[^\n]", opcion_receta);

    // Obtén el primer nodo de la lista de favoritas
    List *aux = list_first(lista_favoritas);

    // Itera sobre la lista de favoritas
    while (aux != NULL) {
        receta *Receta = (receta *) aux;
        // Compara el nombre de la receta actual con el nombre de la receta a eliminar
        if (strcmp(Receta->nombre_receta, opcion_receta) == 0) {
            stack_push(historial, Receta);
            list_popCurrent(lista_favoritas);
            printf("Receta eliminada correctamente de tu lista de favoritas!!!\n");
            bandera = 0; break;
        }
        // Avanza al siguiente nodo
        aux = list_next(lista_favoritas);
    }
    if(bandera == 1) printf("Lo sentimos, no se encontró ninguna receta con ese nombre\n");
    printf("\n¿Deseas eliminar otra receta de tu lista de favoritas? (S/N)\n"); getchar();
    scanf("%c", &opcion); getchar();
    if(opcion == 's' || opcion == 'S') eliminar_receta(lista_favoritas, historial);
}

void agregar_receta_favorita(List *lista_favoritas, Map *recetas_ordenadas){
    char opcion_receta[50], opcion;
    printf("\nIngrese el nombre de la receta que desea agregar a tu lista de favoritas:\n");
    getchar();
    scanf("%49[^\n]", opcion_receta);
    MapPair *par = map_search(recetas_ordenadas, opcion_receta);
    if(par == NULL)
    {
        printf("No se encontró ninguna receta con ese nombre\n");
        printf("Asegurate de escribir el nombre correctamente (Primera letra en mayuscula y con los tildes correspondientes)\n\n");
    }
    else
    {
        if(filtro_receta_repetida(lista_favoritas, opcion_receta) == false)
        {
            list_pushFront(lista_favoritas, par->key);
            printf("Receta agregada correctamente a tu lista de favoritas!!!\n\n");
            printf("¿Deseas agregar otra receta a tu lista de favoritas? (S/N):\n"); getchar();
            scanf("%c", &opcion);
            if(opcion == 's' || opcion == 'S') agregar_receta_favorita(lista_favoritas, recetas_ordenadas);
        }
        else printf("\nYa tienes esa receta en tu lista de favoritas\n");
    }
}

void actualizar_lista_favoritas(List *lista_favoritas, Map *recetas_ordenadas, int funcion){
    char opcion;
    printf("\nDeseas agregar una de estas recetas a tu lista de favoritas? (S/N):\n");
    if(funcion == 1) getchar();
    scanf("%c", &opcion);
    if(opcion == 's' || opcion == 'S') agregar_receta_favorita(lista_favoritas, recetas_ordenadas);
}

void agregar_al_historial(Stack *historial, char *tipo_busqueda, List *lista_ingredientes, char *categoria){
    datosHistorial *datos = (datosHistorial *) malloc(sizeof(datosHistorial));
    strcpy(datos->tipo_busqueda, tipo_busqueda);
    copiarLista(datos->ingredientes, lista_ingredientes);
    strcpy(datos->categoria, categoria);
    stack_push(historial, datos);
}

//***************************************************************************************************************************** //

// **************************************** FUNCIONES SECUNDARIAS DEL PROGRAMA **************************************** //

// Función para buscar por plato
void buscar_por_plato(Map *mapa_platos, Stack *historial, List *lista_favoritas, Map *recetas_ordenadas){
    printf("\nPlatos disponibles:\n\n"); // Imprimir los platos disponibles
    MapPair *pair = map_first(mapa_platos); // Obtener el primer par del mapa de platos
    unsigned short contador = 1; // Contador para enumerar los platos
    while (pair != NULL) // Mientras haya pares en el mapa de platos
    {
        printf("%hu) %s\n", contador, (char *)pair->key); contador++; // Imprimir el número del plato y su nombre
        pair = map_next(mapa_platos); // Obtener el siguiente par del mapa de platos
    } 
    printf("\n");

    char opcion_plato[20];
    contador = 1;
    printf("RECUERDA: primera letra en mayuscula\n");
    printf("Ingrese el tipo de plato deseado: ");
    getchar();
    scanf("%19[^\n]", opcion_plato); // Lee la dieta
    agregar_al_historial(historial, "Por Tipo de Plato", NULL, opcion_plato); 
    MapPair *plato = map_search(mapa_platos, opcion_plato);
    
    if(plato == NULL){
        printf("\nNo se encontraron recetas para el tipo de plato ingresado\n");
        char opcion;
        printf("¿Desea buscar recetas de otro plato? (S/N): "); getchar();
        scanf("%c", &opcion);
        if(opcion == 's' || opcion == 'S'){
            limpiarPantalla();
            buscar_por_plato(mapa_platos, historial, lista_favoritas, recetas_ordenadas);
        }
        return;
    }

    List *recetas = plato->value;
    contador = 1;

    receta *actual = list_first(recetas);
    while (actual != NULL)
    {
        if(contador == 1) printf("\nRecetas disponibles para el plato deseado:\n\n");
        imprimir(actual, contador);
        contador++;
        actual = list_next(recetas);
    }
    actualizar_lista_favoritas(lista_favoritas, recetas_ordenadas, 1);
    char opcion;
    printf("¿Desea buscar recetas de otro plato? (S/N): "); getchar();
    scanf("%c", &opcion);
    if(opcion == 's' || opcion == 'S'){
        limpiarPantalla();
        buscar_por_plato(mapa_platos, historial, lista_favoritas, recetas_ordenadas);
    }
}

// Función para buscar por dieta
void buscarDieta(Map *tipo_dieta, Stack *historial, Map *recetas_ordenadas, List *lista_favoritas) {
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
    agregar_al_historial(historial, "Por Tipo de Dieta", NULL, opcionDieta); 
    // Itera sobre el mapa para buscar recetas de la dieta especificada
    pair = map_search(tipo_dieta, opcionDieta);
    if(pair == NULL){
        printf("No se encontraron recetas para la dieta ingresada\n\n");
        char opcion;
        printf("¿Desea buscar recetas de otro dieta? (S/N): "); getchar();
        scanf("%c", &opcion);
        printf("\n");
        if(opcion == 's' || opcion == 'S'){
            limpiarPantalla();
            buscarDieta(tipo_dieta, historial, recetas_ordenadas, lista_favoritas);
        }
        return;
    }
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
        actualizar_lista_favoritas(lista_favoritas, recetas_ordenadas, 1);
    }
    char opcion;
    printf("¿Desea buscar recetas de otro dieta? (S/N): "); getchar();
    scanf("%c", &opcion);
    if(opcion == 's' || opcion == 'S'){
        limpiarPantalla();
        buscarDieta(tipo_dieta, historial, recetas_ordenadas, lista_favoritas);
    }
}

void mostrar_todas_las_recetas(Map *recetas_ordenadas, Stack *historial, List *recetas_favoritas) {
    MapPair *pair = map_first(recetas_ordenadas);
    printf("\n");
    int contador = 0;
    while (pair != NULL) {
        receta *receta_actual = pair->value;
        contador++;
        imprimir(receta_actual, contador);
        pair = map_next(recetas_ordenadas);
    }
    actualizar_lista_favoritas(recetas_favoritas, recetas_ordenadas, 1);
}

void menu_omitir_ingredientes(){
    printf("Desea omitir algun ingrediente en las recetas?\n");
    printf("Ingrese su respuesta (S/N): \n");
}

void menu_ingredientes(){
  printf("Cuantos ingredientes quiere en la receta:\n");
  printf("-----------------------\n\n");
  printf("1. Por un ingrediente\n");
  printf("2. Por dos ingredientes\n");
  printf("3. Por tres ingredientes\n");
  printf("4. Por cuatro ingredientes\n");
  printf("5. Por cinco ingredientes\n");
}

void mostrar_opciones_historial(){
    printf("1) Mostrar historial de recetas buscadas\n");
    printf("2) Mostrar historial de recetas eliminadas de favoritos\n");
    printf("3) Regresar al menú principal\n\n");
}

void mostrar_historial_busquedas(Stack *historial){
    printf("\nBienvenido al historial!!!\n");
    printf("Aqui podras ver todas las busquedas que realizaste\n\n");
    Stack *pila_aux = stack_create();
    if(stack_top(historial) == NULL) printf("No haz realizado ninguna busqueda\n");  
    else
    {
        printf("Estas son todas tus búsquedas:\n\n");
        printf("-----------------------------\n");
        datosHistorial *datos = (datosHistorial *)stack_top(historial);
        while ((datos = (datosHistorial *)stack_pop(historial)) != NULL) {
            printf("Tipo de busqueda: %s\n", datos->tipo_busqueda);
            if (datos->ingredientes != NULL) {
                printf("Categoría: %s\n", datos->categoria);
            } else {
                printf("Ingredientes ingresados:");
                mostrarLista(datos->ingredientes);
            }
            printf("\n");
            stack_push(pila_aux, datos);
        }
        // Revertir el orden de la pila
        while ((datos = (datosHistorial *)stack_pop(pila_aux)) != NULL) {
            stack_push(historial, datos);
        }
    }
}

void devolver_recetas_eliminadas(Stack *aux, Stack *historial){

    receta* dato = (receta*) stack_top(aux);
    while((dato = (receta *) stack_pop(historial)) != NULL){
        stack_push(historial, dato);
        dato = (receta*) stack_pop(aux);
    }
}

void mostrar_historial_eliminados(Stack *historial){

    Stack* aux = stack_create();
    int contador = 1;
    
    printf("\nBienvenido al historial de recetas eliminadas de favoritos!!!\n");
    printf("Aquí podras ver todas las recetas eliminadas\n\n");
    if(stack_top(historial) == NULL) printf("No haz realizado ninguna eliminación\n");
    else{
        receta *datos = (receta *) stack_top(historial);
        while((datos = (receta *) stack_pop(historial)) != NULL){
            imprimir(datos, contador);
            contador++;
            stack_push(aux, datos);
        }
    }
    devolver_recetas_eliminadas(aux, historial);
}

//***************************************************************************************************************************** //

// **************************************** FUNCIONES PRINCIPALES DEL PROGRAMA **************************************** //

// Función para comparar por nombre
int is_equal_str(void *key1, void *key2) {return strcmp((char *)key1, (char *)key2) == 0;} 

// Función para comparar por valor
int is_equal_int(void *key1, void *key2) {return *(int *)key1 == *(int *)key2;}

// Función para cargar las recetas
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
                Capitalizar(ingredienteActual);
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
        rellenar_tipo_plato(tipo_de_plato, receta_nueva);
        rellenar_mapa_de_ingredientes(mapa_ingredientes, receta_nueva);
    }
    fclose(archivo);
}

//Funcion para mostrar menú
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("                Recetario               ");
    puts("========================================");

    puts("1) Mostrar recetas");
    puts("2) Buscar por ingredientes");
    puts("3) Buscar recetas posibles");
    puts("4) Mostrar recetas favoritas");
    puts("5) Mostrar historial");
    puts("6) Salir\n");
}

void mostrar_recetas(Map *recetas_ordenadas, Map *tipo_dieta, Map *tipo_de_plato , List *lista_favoritos, Stack *historial) {
    char opcion;
    do {
        limpiarPantalla();
        menu_secundario();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
        switch (opcion) {
        case '1':
            buscar_por_plato(tipo_de_plato, historial, lista_favoritos, recetas_ordenadas);
            break;
        case '2':
            buscarDieta(tipo_dieta, historial, recetas_ordenadas, lista_favoritos); 
            break;
        case '3':
            mostrar_todas_las_recetas(recetas_ordenadas, historial, lista_favoritos);
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

void buscar_por_ingredientes(Map *mapa_ingredientes, Stack *historial, List *lista_favoritos, Map* recetas_ordenadas){
    int ingr = 0;
    char respuesta;
    List *omitidos = list_create();
    limpiarPantalla();
    menu_omitir_ingredientes();
    scanf("%c", &respuesta);
    getchar(); // Limpia el buffer
    if (respuesta == 'S' || respuesta == 's') omitir_ingredientes(omitidos);
    limpiarPantalla();
    menu_ingredientes();
    printf("\nIngrese una opcion valida: \n");
    scanf("%d", &ingr);
    getchar(); // Limpia el buffer
    printf("\nRECUERDE: todo en minúsculas y con tilde\n");	
    printf("Inserte los ingredientes: \n");
    List *ingredientes = list_create();
    if ()
        
    char ingrediente_actual[20];
    int i = 0;
    while (i < ingr)
    {
        scanf("%19[^\n]", ingrediente_actual);
        getchar(); // Limpia el buffer
        Capitalizar(ingrediente_actual);
        trim(ingrediente_actual);
        list_pushBack(ingredientes, espacioInicial(ingrediente_actual));
        i++;
    }
    printf("\n");
    agregar_al_historial(historial, " Ingredientes", ingredientes, NULL);
    List *recetas_encontradas = list_create();
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
        if (omitidos != NULL)
        {
            if (buscar_en_listas(omitidos , aux->lista_ingredientes) == 0)
            {
                aux = list_next(lista_recetas);
                continue;
            }
        }
        imprimir(aux, contador);
        list_pushBack(recetas_encontradas, aux);
        contador++;
      }
      aux = list_next(lista_recetas);
    }
    actualizar_lista_favoritas(lista_favoritos, recetas_ordenadas, 0);  
    if(contador == 1) printf("No se encontraron recetas con esos ingredientes\n");
    list_clean(omitidos);
    map_clean(mapa_ingredientes);
    char opcion;
    printf("¿Desea buscar recetas con otros ingredientes? (S/N): ");
    getchar(); // Limpia el buffer
    scanf("%c", &opcion);
    getchar(); // Limpia el buffer
    if(opcion == 's' || opcion == 'S'){
        limpiarPantalla();
        buscar_por_ingredientes(mapa_ingredientes, historial, lista_favoritos, recetas_ordenadas);
    }
}

void buscar_recetas_posibles(Map *recetas_ordenadas, Stack *historial, List *lista_favoritos){
  limpiarPantalla();
  printf("\n[RECUERDE: la primera letra en mayúscula y con los tildes correspondientes]\n");	
  printf("Inserte los ingredientes: \n");
  getchar();

  List *ingredientes = list_create();
  char ingrediente_actual[20];
  int i = 0;

  while (i < 5)
  {
      scanf("%19[^\n]", ingrediente_actual);
      getchar();
      Capitalizar(ingrediente_actual);
      trim(ingrediente_actual);
      list_pushBack(ingredientes, espacioInicial(ingrediente_actual));
      i++;
  }
  printf("\n");
  agregar_al_historial(historial, "Recetas Posibles", ingredientes, NULL);
  MapPair *pair = map_first(recetas_ordenadas);
  int contador = 1;
  while (pair != NULL)
  {
    receta *receta_actual = pair->value;
    List *ingredientes_faltantes = list_create();
    if(comparar_listas_posibles( receta_actual->lista_ingredientes, ingredientes, ingredientes_faltantes) == 1)
    {
      imprimir(receta_actual, contador);
      printf("Ingredientes faltantes: ");
      mostrarLista(ingredientes_faltantes);
      printf("\n");
      contador++;
    }
    pair = map_next(recetas_ordenadas);
  }

  actualizar_lista_favoritas(lista_favoritos, recetas_ordenadas, 0);
}

void mostrar_recetas_favoritas(List *lista_favoritas, Stack *historial){
    limpiarPantalla();
    printf("Veamos cuales son las recetas que más te gustaron!!!\n\n");
    printf("Lista de recetas favoritas:\n");
    printf("---------------------------\n\n");
    if (list_first(lista_favoritas) == NULL) 
    {
        printf("Oh, no! Aún no tienes recetas favoritas.\n");
        printf("Recuerda que siempre puedes agregar recetas a tu lista de favoritos.\n\n");
        return;
    }

    else
    {
        int contador = 1;
        receta *aux = list_first(lista_favoritas);
        while (aux != NULL){
            imprimir(aux, contador);
            contador++;
            aux = list_next(lista_favoritas);
        }
    }

    printf("¿Deseas eliminar alguna de tus recetas favoritas? (S/N)\n"); getchar();
    char opcion;
    scanf("%c", &opcion); getchar();
    if(opcion == 's' || opcion == 'S') eliminar_receta(lista_favoritas, historial);
}

void Historial(Stack *historial_busquedas, Stack *historial_eliminados){
    limpiarPantalla();
    printf("Menú historial\n");
    printf("--------------\n\n");
    mostrar_opciones_historial();
    char opcion;
    printf("Ingrese su opción:\n"); getchar();
    scanf("%c", &opcion); getchar();
    switch (opcion){
        case '1':
            mostrar_historial_busquedas(historial_busquedas);
            break;
        case '2':
            mostrar_historial_eliminados(historial_eliminados);
            break;
        case '3':
            limpiarPantalla();
            return;
        default:
            puts("Opción no válida. Por favor, intente de nuevo.");
    }
}

//***************************************************************************************************************************** //

// **************************************** FUNCIÓN MAIN **************************************** 

int main() {
    char opcion;
    Map *recetas_ordenadas = map_create(is_equal_str);
    Map *tipo_de_plato = map_create(is_equal_str);
    Map *tipo_dieta = map_create(is_equal_str);
    Map *mapa_ingredientes = map_create(is_equal_str);
    List *lista_favoritos = list_create();
    Stack *historial_busquedas = stack_create();
    Stack *historial_eliminados = stack_create();
    
    cargar_recetas(recetas_ordenadas, tipo_de_plato, tipo_dieta, mapa_ingredientes);
    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
        switch (opcion) {
        case '1':
            mostrar_recetas(recetas_ordenadas, tipo_dieta, tipo_de_plato, lista_favoritos, historial_busquedas);
            break;
        case '2':
            buscar_por_ingredientes(mapa_ingredientes, historial_busquedas, lista_favoritos, recetas_ordenadas);
            break;
        case '3':
            buscar_recetas_posibles(recetas_ordenadas, historial_busquedas, lista_favoritos);
            break;
        case '4':
            mostrar_recetas_favoritas(lista_favoritos, historial_eliminados);
            break;
        case '5':
            Historial(historial_busquedas, historial_eliminados);
            break;
        case '6':
            puts("Saliendo del recetario...");
            break;
        default:
            puts("Opción no válida. Por favor, intente de nuevo.");
            }
        presioneTeclaParaContinuar();
    } while (opcion != '6');
    return 0;
}

//***************************************************************************************************************************** //
