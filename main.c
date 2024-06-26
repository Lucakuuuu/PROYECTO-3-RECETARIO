#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/stack.h"
#include "TDAs/map.h"
#include <unistd.h>

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

// Estructura para mapa de dietas
typedef struct { 
  char dieta[50]; // Tipo de dieta
  List *recetas; // Lista de recetas
} recetasxdieta;

// Estructura para almacenar acciones para el historial
typedef struct {
    char tipo_busqueda[50]; // búsqueda realizada (por ingrediente, por dieta, etc.)
    List *ingredientes; // Lista de ingredientes buscados (en caso que se busque por ingredientes)
    char categoria[20]; // categoría de la receta (tipo de plato o dieta)
} datosHistorial;

//********************************************************************************************************************* //

// **************************************** FUNCIONES DE FUNCIONES PRINCIPALES **************************************** //

// Función para recortar espacios en blanco al inicio y final de una cadena
char *trim(char *cadena) {
    char *inicio, *fin; // Punteros cadena

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
    char *actual = cadena; // Puntero cadena
    while (*actual){ // Recorremos la cadena
      if (*actual == ' '  && *actual == cadena[0]) memmove(actual, actual + 1, strlen(actual)); // Elimina espacios en blanco al inicio de la cadena
      if(*actual == cadena[0]) *actual = toupper(*actual); // Pasa la primera letra a mayúscula
      actual++; // Avanzar al siguiente caracter
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
void copiarLista(List *listaOriginal, List *listaCopia) {
    if (listaOriginal == NULL) return; // Si la lista original está vacía, retorna
    list_clean(listaCopia); // Limpia la lista de destino
    char *actual = list_first(listaOriginal); // Obtiene el primer elemento de la lista original
    while (actual != NULL) { // Mientras haya elementos en la lista original
        list_pushBack(listaCopia, actual); // Agrega el elemento a la lista de destino
        actual = list_next(listaOriginal); // Obtiene el siguiente elemento de la lista original
    }
}

// Función para llenar el mapa de platos
void rellenar_tipo_plato(Map *mapa_tipo, receta *receta){
    MapPair *par = map_search(mapa_tipo, receta->tipo_de_plato); // Busca el par clave-valor en el mapa
    if (par == NULL) // Si no se encuentra el par clave-valor en el mapa
    {
        List *lista_recetas = list_create(); // Crea una nueva lista de recetas
        list_pushBack(lista_recetas, receta); // Agrega la receta a la lista de recetas
        map_insert(mapa_tipo, receta->tipo_de_plato, lista_recetas); // Inserta el par clave-valor(lista) en el mapa  
    }
    else // Si se encuentra la clave en el mapa
    {
        List *lista_recetas = par->value; // Obtiene la lista de recetas asociada a la clave
        list_pushBack(lista_recetas, receta);  // Agrega la receta a la lista de recetas asociada a esa clave
    }
}

// Función para llenar el mapa de ingredientes
void rellenar_mapa_de_ingredientes(Map *mapa_ingredientes, receta *receta) {
  List *lista_ingredientes = receta->lista_ingredientes; // Obtiene la lista de ingredientes de la receta
  char *aux = list_first(lista_ingredientes); // Obtiene el primer ingrediente de la lista

  while (aux != NULL) { // Mientras haya ingredientes en la lista
    MapPair *par = map_search(mapa_ingredientes, aux); // Busca el la clave en el mapa

    if (par == NULL) { // Si no se encuentra el par clave-valor en el mapa
      List *lista_recetas = list_create(); // Crea una nueva lista de recetas
      list_pushBack(lista_recetas, receta); // Agrega la receta a la lista de recetas
      map_insert(mapa_ingredientes, aux, lista_recetas); // Inserta la clave y el valor (lista) en el mapa
    } 
    else { // Si se encuentra el par clave-valor en el mapa
      List *lista_recetas = par->value; // Obtiene la lista de recetas asociada a la clave
      list_pushBack(lista_recetas, receta); // Agrega la receta a la lista de recetas asociada a esa clave
    }

    aux = list_next(lista_ingredientes); // Obtiene el siguiente ingrediente de la lista 
  }
}

// Función para comparar 2 listas que contienen cadenas
int comparar_listas(List *lista1, List *lista2, int ingr){
    
    if (lista1 == NULL || lista2 == NULL) // Si una de las listas está vacía
    {
    printf("una de las listas está vacía.\n");
    exit(EXIT_FAILURE); // Se hace exit
    }
    
    char *aux1 = list_first(lista1); // Obtiene la primera cadena de la lista1
    char *aux2 = list_first(lista2); // Obtiene la primera cadena de la lista2
    int count = 0; // Contador de coincidencias
    
    while (aux1 != NULL) // Se recorre la lista1
    {
        while (aux2 != NULL) // Se recorre la lista2
        {
          if (strcmp(aux1, aux2) == 0) // Si las cadenas son iguales
          {
            count++; // Incrementa el contador de coincidencias
            break; // Sale del bucle interno
          }
          aux2 = list_next(lista2); // Obtiene la siguiente cadena de la lista2
        }
        aux1 = list_next(lista1); // Obtiene la siguiente cadena de la lista1
        aux2 = list_first(lista2); // Vuelve a la primera cadena de la lista 2
    }
    
    if (count == ingr) return 1; // Si se encontraron todas las coincidencias, retorna verdadero
    return 0; // Si no se encuentra todas las coincidencias, retorna falso
}

// Función para verificar si hay coincidencias entre 2 listas
int buscar_en_listas(List *lista1, List *lista2){
    if (lista1 == NULL || lista2 == NULL) // Si una de las listas está vacía
    {
        printf("una de las listas está vacía.\n");
        exit(EXIT_FAILURE); // Se hace exit
    }
    char *aux1 = list_first(lista1); // Obtiene la primera cadena de la lista1
    char *aux2 = list_first(lista2); // Obtiene la primera cadena de la lista2

    while (aux1 != NULL) // Se recorre la lista1
    {
        while (aux2 != NULL) // Se recorre la lista2
        {
            if (strcmp(aux1, aux2) == 0) return 0; // Si las cadenas son iguales, retorna falso
            aux2 = list_next(lista2); // Obtiene la siguiente cadena de la lista2
        }
        aux1 = list_next(lista1); // Obtiene la siguiente cadena de la lista1
        aux2 = list_first(lista2); // Vuelve a la primera cadena de la lista 2
    }
    return 1; // Si no se encuentra ninguna coincidencia, retorna verdadero
}

// Función para imprimir una lista
void mostrarLista(List *lista){
    if (lista == NULL) { // Si la lista está vacía
        printf("La lista está vacía.\n");
        return; // Retorna 
    }
    List *actual = list_first(lista); // Obtiene el primer elemento de la lista
    printf("%s", (char *)actual); // Imprime el primer elemento de la lista
    actual = list_next(lista); // Obtiene el siguiente elemento de la lista
    
    while (actual != NULL) { // Se recorre la lista
        printf(", %s", (char *)actual); // Imprime el elemento actual de la lista
        actual = list_next(lista); // Obtiene el siguiente elemento de la lista
    }
    printf("\n"); // Imprime un salto de línea
}

// Función para imprimir una receta
void imprimir(receta *receta, int contador) {
    printf("\033[1;36m%d.\033[0m Receta: %s\n", contador, receta->nombre_receta); //Imprime el número de la receta y el nombre de la receta
    printf("    Tipo de plato: %s\n", receta->tipo_de_plato); // Imprime el tipo de plato de la receta
    printf("    Ingredientes: "); // Imprime el texto "Ingredientes: "
    mostrarLista(receta->lista_ingredientes); // Imprime la lista de ingredientes de la receta
    printf("    Dietas: "); // Imprime el texto "Dietas: "
    mostrarLista(receta->lista_dietas); // Imprime la lista de dietas de la receta
    printf("    Preparacion: %s\n", receta->preparacion); // Imprime la preparación de la receta
    printf("\n"); // Imprime un salto de línea
}

// Función para mostrar menú secundario
void menu_secundario() {
    printf("Mostrar recetas según:\n"); 
    printf("\033[1;36m=======================\033[0m\n");
    printf("\033[1;36m1.\033[0m Tipo de plato\n");
    printf("\033[1;36m2.\033[0m Tipo de dieta\n");
    printf("\033[1;36m3.\033[0m Todas las recetas\n");
    printf("\033[1;36m4.\033[0m Volver al menú principal\n\n"); 
}

// Función para mostrar menú de pregunta si omitir ingredientes
void menu_omitir_ingredientes(){
    printf("Desea omitir algun ingrediente en las recetas?\n");
    printf("Ingrese su respuesta (S/N): \n");
}

// Función para omitir ingredientes
void omitir_ingredientes(List *lista){
    char ingrediente_actual[20]; // Variable para almacenar el ingrediente a omitir
    int ingr = 0; // Variable para contar los ingredientes omitidos
    int i = 0; // Variable para contar los ingredientes de la lista
    
    printf("\nIngrese la cantidad de ingredientes que quiere omitir: \n");
    scanf("%d", &ingr); // Lee la cantidad de ingredientes a omitir
    if (ingr == 0) // Si no se ingresan ingredientes a omitir
    {
        printf("No se omitirá ningún ingrediente\n");
        return; // Retorna y continúa el proceso común
    }
    printf("\nRECUERDE: Primera letra en mayúscula, con tildes correspondientes y pulse enter para agregar el siguiente ingrediente\n");	
    printf("Inserte los ingredientes que no desea en las recetas: \n");
    getchar(); // Limpia el buffer de entrada 

    while (i < ingr) // Mientras no se hayan ingresado todos los ingredientes a omitir
    {
        scanf("%19[^\n]", ingrediente_actual); // Lee el ingrediente actual
        getchar(); // Limpia el buffer de entrada
        Capitalizar(ingrediente_actual); // Capitaliza el ingrediente actual
        trim(ingrediente_actual); // Elimina espacios en blanco al inicio y final del ingrediente actual
        list_pushBack(lista, espacioInicial(ingrediente_actual)); // Agrega el ingrediente actual a la lista de omitidos
        i++; // Incrementa el contador de ingredientes omitidos
    }
}

// Función para comparar 2 listas de ingredientes, debe tener por lo menos 3 coincidencias
int comparar_listas_posibles(List *lista1, List *lista2, List *ingredientes_faltantes){
    if (lista1 == NULL || lista2 == NULL) { // Si una de las listas está vacía
        printf("Una de las listas está vacía.\n");
        exit(EXIT_FAILURE); // Se hace exit
    }

  char *aux1 = list_first(lista1); // Obtiene la primera cadena de la lista1
  int count = 0; // Contador de coincidencias
  int posicion = 0; // Variable para almacenar la posición del arreglo
  int marcar[5] = {0}; // Arreglo para marcar las coincidencias encontradas
    
  while (aux1 != NULL) // Se recorre la lista1
  {
    char *aux2 = list_first(lista2); // Obtiene la primera cadena de la lista2
    while (aux2 != NULL) // Se recorre la lista2
    {
      if (strcmp(aux1, aux2) == 0) // Si las cadenas son iguales (hay coincidencia)
      {
        count++; // Incrementa el contador de coincidencias
        marcar[posicion] = 1; // Marca la coincidencia encontrada
        break;  // Romper el bucle interno 
      }
      aux2 = list_next(lista2);  // Avanzar al siguiente elemento de lista2
    }
    aux1 = list_next(lista1);  // Avanzar al siguiente elemento de lista1
    posicion++; // Incrementa la posición del arreglo
   }

  if (count >= 3) // Si se encontraron al menos 3 coincidencias
  {
      char *ingrediente = list_first(lista1); // Obtiene la primera cadena de la lista1
      for(int i = 0; i < 5; i++) // Recorre el arreglo de coincidencias
      {
          if(marcar[i] == 0) list_pushBack(ingredientes_faltantes, ingrediente); // Si el ingrediente no es coincidente, se agrega a la lista de ingredientes faltantes
           ingrediente = list_next(lista1); // Avanza al siguiente ingrediente en la lista1
      }
      return 1; // Retorna verdadero
  }
  return 0; // En caso que no se hayan encontrado 3 coincidencias, retorna falso
}

// Función para verificar si hay recetas repetidas en la lista de favoritas
bool filtro_receta_repetida(List *lista_favoritas, char *nombre_receta){
    List *actual = list_first(lista_favoritas); // Obtiene el primer elemento de la lista
    while (actual != NULL){ // Mientras haya elementos en la lista
        receta *Receta = (receta *) actual; // Obtiene la receta actual
        if (strcmp(Receta->nombre_receta, nombre_receta) == 0) return true; // Si la receta actual es igual a la receta buscada, retorna verdadero
        actual = list_next(lista_favoritas); // Avanza a la siguiente receta en la lista
    }
    return false; // Si no se encontró la receta, retorna falso
}

// Función para eliminar una receta de la lista de recetas favoritas
void eliminar_receta(List *lista_favoritas, Stack *historial) {

    char opcion_receta[50]; // Variable para almacenar el nombre de la receta a eliminar
    int bandera = 1; // Bandera para controlar el bucle (true)
    char opcion; // Variable para almacenar la opción del usuario

    printf("Ingrese el nombre de la receta que desea eliminar de tu lista de favoritas\n");
    scanf("%49[^\n]", opcion_receta); // Lee el nombre de la receta a eliminar

    List *aux = list_first(lista_favoritas); // Obtiene el primer elemento de la lista

    while (aux != NULL) { // Se recorre la lista
        receta *Receta = (receta *) aux; // Obtiene la receta actual
        if (strcmp(Receta->nombre_receta, opcion_receta) == 0) { // Si la receta actual es igual a la receta buscada
            stack_push(historial, Receta); // Agrega la receta a la pila de historial de eliminadas
            list_popCurrent(lista_favoritas); // Elimina la receta de la lista de favoritas
            printf("Receta eliminada correctamente de tu lista de favoritas!!!\n");
            bandera = 0; break; // Cambia la bandera a false y sale del bucle
        }
        aux = list_next(lista_favoritas); // Avanza al siguiente elemento de la lista
    }
    
    if(bandera == 1) printf("Lo sentimos, no se encontró ninguna receta con ese nombre\n"); // Si no se encontró la receta
    printf("\n¿Deseas eliminar otra receta de tu lista de favoritas? (S/N)\n"); getchar(); // Pregunta si desea eliminar otra receta
    scanf("%c", &opcion); getchar(); // Lee la opción del usuario
    if(opcion == 's' || opcion == 'S') eliminar_receta(lista_favoritas, historial); // Si desea eliminar otra receta, vuelve a llamar a la función
}

// Función para agregar una receta a la lista de recetas favoritas
void agregar_receta_favorita(List *lista_favoritas, Map *recetas_ordenadas){
    char opcion_receta[50], opcion; // Variables para almacenar el nombre de la receta a agregar y la opción del usuario
    printf("\nIngrese el nombre de la receta que desea agregar a tu lista de favoritas:\n");
    getchar(); // Limpia el buffer de entrada
    scanf("%49[^\n]", opcion_receta); // Lee el nombre de la receta a agregar
    MapPair *par = map_search(recetas_ordenadas, opcion_receta); // Busca la receta en el mapa de recetas 
    if(par == NULL) // Si no se encontró la receta
    {
        printf("No se encontró ninguna receta con ese nombre\n");
        printf("Asegurate de escribir el nombre correctamente (Primera letra en mayuscula y con los tildes correspondientes)\n\n");
    }
    else // Si se encontró la receta
    {
        if(filtro_receta_repetida(lista_favoritas, opcion_receta) == false) // Si la receta no está en la lista de favoritas
        {
            list_pushFront(lista_favoritas, par->key); // Agrega la receta a la lista de favoritas
            printf("Receta agregada correctamente a tu lista de favoritas!!!\n\n");
            printf("¿Deseas agregar otra receta a tu lista de favoritas? (S/N):\n"); getchar(); 
            // Limpia el buffer y consulta si desea agregar otra receta
            scanf("%c", &opcion); // Lee la opción del usuario
            if(opcion == 's' || opcion == 'S') agregar_receta_favorita(lista_favoritas, recetas_ordenadas);
            // Si la opción es afirmativa, se vuelve a llamar a la función para agregar otra receta
        }
        else printf("\nYa tienes esa receta en tu lista de favoritas\n"); 
        // Si la receta ya está en la lista de favoritas, se muestra un mensaje de error
    }
}

// Función para actualizar la lista de recetas favoritas
void actualizar_lista_favoritas(List *lista_favoritas, Map *recetas_ordenadas, int funcion){
    char opcion; // Variable para almacenar la opción del usuario
    printf("\nDeseas agregar una de estas recetas a tu lista de favoritas? (S/N):\n");
    if(funcion == 1) getchar(); // Si es la primera función, se limpia el buffer de entrada
    scanf("%c", &opcion); // Lee la opción del usuario
    if(opcion == 's' || opcion == 'S') agregar_receta_favorita(lista_favoritas, recetas_ordenadas);
    // Si el usuario selecciona que si, se llama a la función para agregar una receta a la lista de favoritas
}

// Función para agregar datos al historial
void agregar_al_historial(Stack *historial, char *tipo_busqueda, List *lista_ingredientes, char *categoria){
    datosHistorial *datos = (datosHistorial *) malloc(sizeof(datosHistorial)); // Se reserva memoria para los nuevos datos
    datos->ingredientes = list_create(); // Se crea una nueva lista para los ingredientes
    strcpy(datos->tipo_busqueda, tipo_busqueda); // Se copia el tipo de búsqueda en el campo tipo_busqueda
    copiarLista(lista_ingredientes, datos->ingredientes); // Se copia la lista de ingredientes en el campo ingredientes
    strcpy(datos->categoria, categoria); // Se copia la categoría en el campo categoria
    stack_push(historial, datos); // Se agrega el nuevo dato al tope del historial
}

// Función para imprimir gato fachero
void printCatASCII() {
    printf("⠀⠀⠀⠀⠀⣴⠉⡙⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠤⣚⡯⠴⢬⣱⡀⠀\n");
    printf("⠀⠀⠀⠀⢰⡇⣷⡌⢲⣄⡑⢢⡀⠀⠀⠀⠀⠀⢠⠾⢋⠔⣨⣴⣿⣷⡌⠇⡇⠀\n");
    printf("⠀⠀⠀⠀⢸⢹⣿⣿⣄⢻⣿⣷⣝⠷⢤⣤⣤⡶⢋⣴⣑⠟⠿⠿⠿⣿⣿⡀⡇⠀\n");
    printf("⠀⠀⠀⠀⢸⢸⣿⡄⢁⣸⣿⣋⣥⣶⣶⣶⣶⣶⣶⣿⣿⣶⣟⡁⠚⣿⣿⡇⡇⠀\n");
    printf("⢀⣠⡤⠤⠾⡘⠋⢀⣘⠋⠉⠉⠉⠉⢭⣭⣭⣭⣍⠉⢩⣭⠉⠉⠂⠙⠛⠃⣇⡀\n");
    printf("⠏⠀⠀⢿⣿⣷⡀⠀⢿⡄⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣆⠀⢿⣇⠀⠀⠀⠀⠀⠀⠈⢱\n");
    printf("⣦⠀⠀⠈⢿⣿⣧⠀⠘⣿⠀⠀⠀⡀⠀⠀⠘⣿⣿⣿⣿⡆⠀⢻⡆⠀⠀⠀⠀⠀⠀⢸\n");
    printf("⢻⡄⠀⠀⠘⠛⠉⠂⠀⠙⠁⠀⣼⣧⠀⠀⠀⠈⠀⠀⠈⠙⠀⠘⠓⠀⠀⠀⠀⠀⢀⡟\n");
    printf("⠀⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣏⠀\n");
    printf("⠀⠀⠛⢶⢰⣶⢢⣤⣤⣄⠲⣶⠖⠀⣙⣀⠀⠀⠀⠤⢤⣀⣀⡀⣀⣠⣾⠟⡌⠀\n");
    printf("⠀⠀⠀⠘⢄⠃⣿⣿⣿⣿⠗⠀⠾⢿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⠸⠟⣡⣤⡳⢦\n");
    printf("⠀⠀⠀⠀⠀⢻⡆⣙⡿⢷⣾⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⡿⠟⢡⣴⣾⣿⣿⣿⣦\n");
    printf("⠀⠀⠀⠀⠀⡼⢁⡟⣫⣶⣍⡙⠛⠛⠛⠛⠛⣽⡖⣉⣠⣶⣶⣌⠛⢿⣿⣿⣿⣿\n");
    printf("⠀⠀⠀⢀⠔⢡⢎⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠹⣿⣿⣿\n");
    printf("⠀⢠⠖⢁⣴⡿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢹⣿⣿\n\n");
}


//***************************************************************************************************************************** //

// **************************************** FUNCIONES SECUNDARIAS DEL PROGRAMA **************************************** //


// Función para buscar por plato
void buscar_por_plato(Map *mapa_platos, Stack *historial, List *lista_favoritas, Map *recetas_ordenadas){
    
    limpiarPantalla(); // Limpia la pantalla
    char respuesta; // Variable para almacenar la respuesta del usuario
    List *omitidos = list_create(); // Lista para almacenar los ingredientes omitidos
    menu_omitir_ingredientes(); // Muestra el menú de ingredientes omitidos
    getchar(); // Limpia el buffer de entrada
    scanf("%c", &respuesta); // Lee la respuesta del usuario
    getchar(); // Limpia el buffer
    if (respuesta == 'S' || respuesta == 's') // Si el usuario desea omitir ingredientes
    {
        omitir_ingredientes(omitidos); // Llama a la función para omitir ingredientes
    }
    
    printf("Tipos de platos disponibles:\n"); // Imprimir los platos disponibles
    printf("\033[1;36m===========================\033[0m\n\n");
    MapPair *pair = map_first(mapa_platos); // Obtener el primer par del mapa de platos
    unsigned short contador = 1; // Contador para enumerar los platos
    
    while (pair != NULL) // Mientras haya pares en el mapa de platos
    {
        printf("\033[1;36m%hu)\033[0m %s\n", contador, (char *)pair->key);  // Imprimir el número de plato y su nombre
        contador++; // Imprimir el número del plato y su nombre
        pair = map_next(mapa_platos); // Obtener el siguiente par del mapa de platos
    } 
    printf("\033[1;36m8)\033[0m Volver\n"); // Imprimir la opción de volver
    printf("\n"); // Imprimir una línea en blanco

    char opcion_plato[20]; // Variable para almacenar la opción del usuario
    contador = 1; // Reiniciar el contador
    printf("RECUERDA: primera letra en mayuscula \n"); // Imprimir la instrucción para escribir el nombre del plato
    printf("Ingrese el tipo de plato deseado: "); // Pedir al usuario que ingrese el tipo de plato
    scanf("%19[^\n]", opcion_plato);  // Leer la opción del usuario
    if(strcmp(opcion_plato, "8") == 0 || strcmp(opcion_plato, "Volver") == 0) return; // Si el usuario elige volver, se retorna
    agregar_al_historial(historial, "Por Tipo de Plato", NULL, opcion_plato); // Agregar los datos al historial
    MapPair *plato = map_search(mapa_platos, opcion_plato); // Buscar el plato en el mapa de platos
    
    if(plato == NULL){ // Si no se encuentra el plato
        printf("\nNo se encontraron recetas para el tipo de plato ingresado\n"); // Imprimir un mensaje de error
        char opcion; // Variable para almacenar la opción del usuario
        printf("¿Desea buscar recetas de otro plato? (S/N): "); getchar(); // Preguntar si desea buscar otro plato y limpia el buffer
        scanf("%c", &opcion); // Leer la opción del usuario
        if(opcion == 's' || opcion == 'S'){ // Si el usuario desea buscar otro plato
            limpiarPantalla(); // Limpiar la pantalla
            buscar_por_plato(mapa_platos, historial, lista_favoritas, recetas_ordenadas); // Se reutiliza la función recursivamente
        }
        return; // Si ya no desea seguir la búsqueda se retorna
    }

    List *recetas = plato->value; // Obtener la lista de recetas asociadas al plato
    contador = 1; // Reiniciar el contador
    limpiarPantalla(); // Limpiar la pantalla
    receta *actual = list_first(recetas); // Obtener el primer elemento de la lista de recetas
    while (actual != NULL) // Recorremos las lista de recetas
    {
        if(contador == 1) printf("Recetas disponibles para el plato deseado:\n\n"); // Imprimir el encabezado de las recetas
        if (omitidos != NULL) // Si hay ingredientes omitidos
        {
            if (buscar_en_listas(omitidos , actual->lista_ingredientes) == 0) // Si hay un ingrediente omitido en la receta actual
            {
                actual = list_next(recetas); // Avanzar a la siguiente receta
                continue; // Salta a la siguiente iteración
            }
        }
        imprimir(actual, contador); // Imprimir la receta actual
        contador++; // Incrementar el contador
        actual = list_next(recetas); // Avanzar a la siguiente receta
    }
    
    actualizar_lista_favoritas(lista_favoritas, recetas_ordenadas, 1); // Consulta si desea agregar una receta a la lista de favoritas
    list_clean(omitidos); // Limpia la lista de ingredientes omitidos
    char opcion; // Variable para almacenar la opción del usuario
    printf("¿Desea buscar recetas de otro plato? (S/N): "); getchar(); // Preguntar si desea buscar otro plato y limpia el buffer
    scanf("%c", &opcion); // Leer la opción del usuario
    if(opcion == 's' || opcion == 'S'){ // Si el usuario desea buscar otro plato
        limpiarPantalla(); // Limpiar la pantalla
        buscar_por_plato(mapa_platos, historial, lista_favoritas, recetas_ordenadas); // Se reutiliza la función recursivamente
    }
}

// Función para buscar por dieta
void buscarDieta(Map *tipo_dieta, Stack *historial, Map *recetas_ordenadas, List *lista_favoritas) {
    limpiarPantalla(); // Limpiar la pantalla
    char respuesta; // Variable para almacenar la respuesta del usuario
    List *omitidos = list_create(); // Crear una lista para almacenar los ingredientes omitidos
    menu_omitir_ingredientes(); // Mostrar el menú de ingredientes omitidos
    getchar(); // Limpiar el buffer de entrada
    scanf("%c", &respuesta); // Leer la respuesta del usuario
    getchar(); // Limpia el buffer
    if (respuesta == 'S' || respuesta == 's') // Si la respuesta es afirmativa
    {
        omitir_ingredientes(omitidos); // Llamar a la función para omitir ingredientes
    }
    printf("Dietas disponibles:\n");
    printf("\033[1;36m===================\033[0m\n\n");
    MapPair *pair = map_first(tipo_dieta); // Obtener el primer par del mapa de dietas
    unsigned short contador = 1; // Contador para enumerar las dietas
    while (pair != NULL) { // Mientras haya pares en el mapa de dietas
        recetasxdieta *dieta = (recetasxdieta *)pair->value; // Obtener el valor del par
        printf("\033[1;36m%hu)\033[0m %s\n", contador, (char *)pair->key); // Imprimir el número de la dieta y su nombre
        contador++; // Incrementar el contador
        pair = map_next(tipo_dieta); // Obtener el siguiente par del mapa de dietas
    }
    printf("\033[1;36m8)\033[0m Volver\n");
    printf("\n");

    char opcionDieta[50]; // Variable para almacenar la opción de la dieta
    contador = 1; // Inicializar el contador

    printf("RECUERDA: primera letra en mayuscula y si quieres regresar al menú, escribe 'Volver'\n");
    printf("Ingrese la dieta deseada: ");
    scanf("%s", opcionDieta); // Lee la dieta
    if(strcmp(opcionDieta, "8") == 0 || strcmp(opcionDieta, "Volver") == 0) return; 
    // Si la opción es "Volver", regresar al menú principal
    
    agregar_al_historial(historial, "Por Tipo de Dieta", NULL, opcionDieta); // Agregar los datos al historial
    
    pair = map_search(tipo_dieta, opcionDieta); // Se busca la dieta en el mapa
    if(pair == NULL){ // Si no se encuentra la dieta
        printf("No se encontraron recetas para la dieta ingresada\n\n");
        char opcion; // Variable para almacenar la opción del usuario
        printf("¿Desea buscar recetas de otro dieta? (S/N): "); getchar(); // Limpia el buffer
        scanf("%c", &opcion); // Leer la opción del usuario
        printf("\n");
        if(opcion == 's' || opcion == 'S'){ // Si la opción es afirmativa
            limpiarPantalla(); // Limpiar la pantalla
            buscarDieta(tipo_dieta, historial, recetas_ordenadas, lista_favoritas); // Volver a buscar por dieta
        }
        return; // Si la opción es negativa, regresa al menú principal
    }
    limpiarPantalla();
    if (pair != NULL) { // Si se encuentra la dieta en el mapa
        recetasxdieta *dietaP = pair->value; // Obtener el valor del par
        receta *receta_actual = list_first(dietaP->recetas); // Obtener la primera receta de la dieta
        while (receta_actual != NULL) { // Mientras haya recetas en la lista de recetas de la dieta
            if (contador == 1) // Si es la primera receta de la dieta
                printf("RECETAS %s:\n\n", opcionDieta); // Imprimir el nombre de la dieta
            if (omitidos != NULL){
                if (buscar_en_listas(omitidos , receta_actual->lista_ingredientes) == 0){
                    receta_actual = list_next(dietaP->recetas);
                    continue;
                }
            }
            imprimir(receta_actual, contador); // Imprimir la receta
            contador++; // Incrementar el contador
            receta_actual = list_next(dietaP->recetas); // Obtener la siguiente receta de la lista 
        }
        actualizar_lista_favoritas(lista_favoritas, recetas_ordenadas, 1); 
        // Se hace la pregunta de si se desea agregar la receta a la lista de favoritas
    }
    list_clean(omitidos);
    char opcion; // Variable para almacenar la opción del usuario
    printf("¿Desea buscar recetas de otro dieta? (S/N): "); getchar(); // Limpia el buffer
    scanf("%c", &opcion); // Leer la opción del usuario
    if(opcion == 's' || opcion == 'S'){ // Si la opción es afirmativa
        limpiarPantalla(); // Limpiar la pantalla
        buscarDieta(tipo_dieta, historial, recetas_ordenadas, lista_favoritas); // Se regresa a buscar por dieta
    }
}

// Función para mostrar todas las recetas
void mostrar_todas_las_recetas(Map *recetas_ordenadas, Stack *historial, List *recetas_favoritas) {
    char respuesta; // Variable para almacenar la respuesta del usuario
    List *omitidos = list_create(); // Crear una lista para almacenar los ingredientes omitidos
    menu_omitir_ingredientes(); // Muestra el menú de pregunta para omitir ingredientes
    getchar(); // Limpiar el buffer de entrada
    scanf("%c", &respuesta); // Leer la respuesta del usuario
    getchar(); // Limpia el buffer
    printf("\n");
    if (respuesta == 'S' || respuesta == 's') // Si la respuesta es afirmativa
    {
        omitir_ingredientes(omitidos); // Llamar a la función para omitir ingredientes
    }
    limpiarPantalla();
    printf("Todas las recetas disponibles:\n\n");
    MapPair *pair = map_first(recetas_ordenadas); // Obtener el primer par del mapa de recetas ordenadas
    int contador = 0; // Inicializar el contador en 0
    while (pair != NULL) { // Mientras haya pares en el mapa de recetas
        receta *receta_actual = pair->value; // Obtener el valor del par
        if (omitidos != NULL) // Si hay ingredientes omitidos
        {
            if (buscar_en_listas(omitidos , receta_actual->lista_ingredientes) == 0) // Si hay un ingrediente omitido en la receta actual
            {
                pair = map_next(recetas_ordenadas); // Avanzar al siguiente par del mapa
                continue; // Salta a la siguiente iteración
                }
        }
        contador++; // Incrementar el contador
        imprimir(receta_actual, contador); // Imprimir la receta
        pair = map_next(recetas_ordenadas); // Obtener el siguiente par del mapa de recetas
    }
    list_clean(omitidos); // Limpiar la lista de ingredientes omitidos
    actualizar_lista_favoritas(recetas_favoritas, recetas_ordenadas, 1);
    // Se hace la pregunta de si se desea agregar la receta a la lista de favoritas
}

// Función para mostra menú de búsqueda por ingredientes
void menu_ingredientes(){
  printf("¿Por cuantos ingredientes quiere búscar la receta?:\n");
    printf("\033[1;36m==================================================\033[0m\n\n");
    printf("\033[1;36m1.\033[0m Por un ingrediente\n");
    printf("\033[1;36m2.\033[0m Por dos ingredientes\n");
    printf("\033[1;36m3.\033[0m Por tres ingredientes\n");
    printf("\033[1;36m4.\033[0m Por cuatro ingredientes\n");
    printf("\033[1;36m5.\033[0m Por cinco ingredientes\n");

}

// Función para mostrar menú del historial
void mostrar_opciones_historial(){
    printf("1) Mostrar historial de recetas buscadas\n");
    printf("2) Mostrar historial de recetas eliminadas de favoritos\n");
    printf("3) Regresar al menú principal\n\n");
}

// Función para mostrar el historial de búsquedas
void mostrar_historial_busquedas(Stack *historial){
    printf("\nBienvenido al historial!!!\n");
    printf("Aqui podras ver todas las busquedas que realizaste\n\n");
    Stack *pila_aux = stack_create(); // Crear una pila auxiliar para almacenar los datos
    if(stack_top(historial) == NULL) printf("No haz realizado ninguna busqueda\n");
    // Si el historial está vacío, mostrar un mensaje
        
    else // Si el historial no está vacío
    {
        printf("Estas son todas tus búsquedas:\n\n");
        printf("-----------------------------\n");
        datosHistorial *datos = (datosHistorial *)stack_top(historial); // Obtener el último dato del historial
        while ((datos = (datosHistorial *)stack_pop(historial)) != NULL) { // Mientras haya datos en el historial
            printf("Tipo de busqueda: %s\n", datos->tipo_busqueda); // Imprimir el tipo de búsqueda
            if (strcmp(datos->categoria, "Todas") != 0) { // Si la categoría no es "Todas"
                printf("Categoría: %s\n", datos->categoria); // Imprime la categoría
            } else { // Si la categoría es "Todas"
                printf("Ingredientes ingresados: ");
                mostrarLista(datos->ingredientes); // Imprime los ingredientes ingresados
            }
            printf("\n"); // Imprimir un salto de línea
            stack_push(pila_aux, datos); // Agregar los datos al historial auxiliar
        }
        
        // Revertir el orden de la pila
        while ((datos = (datosHistorial *)stack_pop(pila_aux)) != NULL) { // Mientras haya datos en la pila auxiliar
            stack_push(historial, datos); // Agregar los datos al historial
        }
    }
}

//Función para devolver las recetas eliminadas temporalmente
void devolver_recetas_eliminadas(Stack *aux, Stack *historial){
    receta* dato = (receta*) stack_top(aux); // Obtener el último dato del auxiliar
    while((dato = (receta *) stack_pop(historial)) != NULL){ // Mientras haya datos en el historial
        stack_push(historial, dato); // Agregar los datos al historial
        dato = (receta*) stack_pop(aux); // Obtiene el siguiente dato del auxiliar
    }
}

// Función para mostrar el historial de recetas eliminadas de favoritos
void mostrar_historial_eliminados(Stack *historial){

    Stack* aux = stack_create(); // Crear una pila auxiliar para almacenar los datos
    int contador = 1; // Indice para enumerar los datos

    //Se imprimen mensajes de bienvenida
    printf("\nBienvenido al historial de recetas eliminadas de favoritos!!!\n");
    printf("Aquí podras ver todas las recetas eliminadas\n\n");
    
    // Si el historial está vacío, no se reliza ninguna acción y se imprime un mensaje
    if(stack_top(historial) == NULL) printf("No haz realizado ninguna eliminación\n");
    
    else{ // Si el historial no está vacío
        receta *datos = (receta *) stack_top(historial); // Obtener el último dato del historial
        while((datos = (receta *) stack_pop(historial)) != NULL){ // Mientras haya datos en el historial
            imprimir(datos, contador); // Imprimir la receta
            contador++; // Incrementar el contador
            stack_push(aux, datos); // Agregar los datos al auxiliar
        }
    }
    devolver_recetas_eliminadas(aux, historial); // Devolver las recetas eliminadas al historial original
}

//***************************************************************************************************************************** //


// **************************************** FUNCIONES PRINCIPALES DEL PROGRAMA **************************************** //

// Función para mostrar la animación de cargando
void mostrarAnimacionCargando() {
    printCatASCII();
    const int totalDuration = 5; // Duración total en segundos
    const int interval = 500000; // Intervalo en microsegundos (0.5 segundos)

    for (int i = 0; i < totalDuration * 2; i++) { // 2 iteraciones por segundo
        printf("Cargando");
        for (int j = 0; j <= i % 3; j++) {
            printf(".");
        }
        fflush(stdout); // Asegura que el punto se imprima inmediatamente
        usleep(interval); // Espera 0.5 segundos
        printf("\r"); // Retorno de carro para sobreescribir la línea
        fflush(stdout);
        printf("           "); // Espacios en blanco para borrar la línea anterior
        printf("\r"); // Retorno de carro para sobreescribir la línea
        fflush(stdout);
    }
}

// Función para comparar por nombre
int is_equal_str(void *key1, void *key2) {return strcmp((char *)key1, (char *)key2) == 0;} 

// Función para comparar por valor
int is_equal_int(void *key1, void *key2) {return *(int *)key1 == *(int *)key2;}

// Función para cargar las recetas
void cargar_recetas(Map *recetas_ordenadas, Map *tipo_de_plato, Map *tipo_dieta, Map *mapa_ingredientes) {
    
    FILE *archivo = fopen("Ingredientes/Ingredientes.csv", "r"); // Abrir el archivo de ingredientes
    
    if (archivo == NULL) { // Si no se pudo abrir el archivo
        perror("Error al abrir el archivo");
        return; // Salir de la función
    }

    char **campos; // Arreglo de punteros a cadenas para almacenar los campos
    campos = leer_linea_csv(archivo, ','); // Leer la primera línea del archivo CSV
    List *aux = list_create(); // Crear una lista auxiliar para almacenar los ingredientes

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) { // Leer cada línea del archivo CSV
        receta *receta_nueva = (receta*)malloc(sizeof(receta)); // Crear una nueva receta
        strcpy(receta_nueva->nombre_receta, campos[0]); // Copiar el nombre de la receta
        receta_nueva->lista_ingredientes = list_create(); // Crear una nueva lista de ingredientes

        if (strcmp(campos[1], "") != 0) { // Lee todos los ingredientes de la receta
            char *ingredienteActual = strtok(campos[1], ","); // Obtener el primer ingrediente
            while (ingredienteActual != NULL) { // Mientras haya ingredientes
                arreglar_cadena(ingredienteActual); // Arreglar la cadena
                Capitalizar(ingredienteActual); // Capitalizar la cadena
                list_pushBack(aux, espacioInicial(ingredienteActual)); // Agregar el ingrediente a la lista
                ingredienteActual = strtok(NULL, ","); // Obtiene el siguiente ingrediente
            }
            // Una vez hecha la lectura se traspasa la lista de ingredientes a la receta actual
            copiarLista(aux, receta_nueva->lista_ingredientes);
            list_clean(aux); // Limpiar la lista auxiliar
        }
        strcpy(receta_nueva->tipo_de_plato, campos[2]); // Leer el tipo de plato
        receta_nueva->lista_dietas = list_create(); // Crear una nueva lista de dietas

        if (strcmp(campos[3], "") != 0) { // Lee todas las dietas de la receta
            char *dietaActual = strtok(campos[3], ","); // Obtener la primera dieta
            while (dietaActual != NULL) { // Mientras haya dietas
                arreglar_cadena(dietaActual); // Arreglar la cadena
                if (strlen(dietaActual) > 0) { // Si la dieta no está vacía
                    list_pushBack(aux, espacioInicial(dietaActual)); // Agregar la dieta a la lista
                    MapPair *estaDieta = map_search(tipo_dieta, espacioInicial(dietaActual)); // Buscar la dieta en el mapa de dietas
                    if (estaDieta == NULL) { // Si no se encuentra la dieta en el mapa
                        recetasxdieta *nuevadieta = (recetasxdieta *)malloc(sizeof(recetasxdieta)); // Crear una nueva dieta
                        nuevadieta->recetas = list_create(); // Crear una nueva lista de recetas
                        map_insert(tipo_dieta, espacioInicial(dietaActual), nuevadieta); // Inserta la dieta en el mapa de dietas
                        list_pushBack(nuevadieta->recetas, receta_nueva); // Agregar la receta a la lista de recetas de la dieta
                    } else { // Si se encuentra la dieta en el mapa
                        recetasxdieta *Dpair = estaDieta->value; // Obtener el valor de la dieta (receta)
                        list_pushBack(Dpair->recetas, receta_nueva); // Agrega la receta a la lista de recetas de la dieta
                    }
                }
                dietaActual = strtok(NULL, ","); // Obtiene la siguiente dieta
            }
            copiarLista(aux, receta_nueva->lista_dietas); // Copiar la lista de dietas a la receta actual
            list_clean(aux); // Limpiar la lista auxiliar
        }
        strcpy(receta_nueva->preparacion, campos[4]); // Leer la preparación de la receta
        map_insert(recetas_ordenadas, receta_nueva->nombre_receta, receta_nueva); // Insertar la receta en el mapa de recetas ordenadas
        rellenar_tipo_plato(tipo_de_plato, receta_nueva); // Rellenar el mapa de tipo de plato
        rellenar_mapa_de_ingredientes(mapa_ingredientes, receta_nueva); // Rellenar el mapa de ingredientes
    }
    fclose(archivo); // Cerrar el archivo
}

// Función imagen 1 gato 
void printCatFrame1() {
    printf("\n                ▄▀▄     ▄▀▄ \n");
    printf("               ▄█░░▀▀▀▀▀░░█▄ \n");
    printf("           ▄▄  █░░░░░░░░░░░█  ▄▄  \n");
    printf("          █▄▄█ █░░▀░░┬░░▀░░█ █▄▄█\n");
    printf("===========================================\n");
}

// Función imagen 2 gato
void printCatFrame2() {
    printf("\n       MIAU     ▄▀▄     ▄▀▄ \n");
    printf("           ▄▄  ▄█░░▀▀▀▀▀░░█▄ \n");
    printf("          ████ █░░░░░░░░░░░█  ▄▄  \n");
    printf("          █  █ █░░▀░░┬░░▀░░█ █▄▄█\n");
    printf("===========================================\n");
}

// Función imagen 3 gato
void printCatFrame3() {
    printf("\n                ▄▀▄     ▄▀▄ \n");
    printf("               ▄█░░▀▀▀▀▀░░█▄ \n");
    printf("           ▄▄  █░░░░░░░░░░░█  ▄▄  \n");
    printf("          █▄▄█ █░░▀░░┬░░▀░░█ █▄▄█\n");
    printf("===========================================\n");
}

// Funcion para mostrar menú principal
void mostrarMenuPrincipal(){
    limpiarPantalla();
    printf("\n                ▄▀▄     ▄▀▄ \n");
    printf("               ▄█░░▀▀▀▀▀░░█▄ \n");
    printf("           ▄▄  █░░░░░░░░░░░█  ▄▄  \n");
    printf("          █▄▄█ █░░▀░░┬░░▀░░█ █▄▄█\n");
    printf("\033[1;36m===========================================\033[0m\n");
    printf("                 Recetario                \n");
    printf("\033[1;36m===========================================\033[0m\n");
    printf("\033[1;36m1.\033[0m Ver todas las recetas\n");
    printf("\033[1;36m2.\033[0m Buscar recetas por ingredientes\n");
    printf("\033[1;36m3.\033[0m Buscar recetas sugeridas\n");
    printf("\033[1;36m4.\033[0m Recetas favoritas\n");
    printf("\033[1;36m5.\033[0m Historial de búsquedas\n");
    printf("\033[1;36m6.\033[0m Salir del recetario\n");
    printf("\n");
}

// Función para casos del sub menú 1 (Ver todas las recetas)  
void mostrar_recetas(Map *recetas_ordenadas, Map *tipo_dieta, Map *tipo_de_plato , List *lista_favoritos, Stack *historial) {
    char opcion; // Variable para almacenar la opción seleccionada por el usuario
    do {
        limpiarPantalla(); // Limpiar la pantalla
        menu_secundario(); // Mostrar el submenú
        printf("Ingrese su opción: "); // Solicitar al usuario que ingrese una opción
        scanf(" %c", &opcion); // Leer la opción ingresada por el usuario
        switch (opcion) { // Casos posibles
        case '1': // Caso 1: búsqueda por plato
            buscar_por_plato(tipo_de_plato, historial, lista_favoritos, recetas_ordenadas); // Se llama la función correspondiente
            break; // Salir del caso 1
        case '2': // Caso 2: búsqueda por ingredientes
            buscarDieta(tipo_dieta, historial, recetas_ordenadas, lista_favoritos); // Se llama la función correspondiente
            break; // Salir del caso 2
        case '3': // Caso 3: mostrar todas las recetas
            mostrar_todas_las_recetas(recetas_ordenadas, historial, lista_favoritos); // Se llama la función correspondiente
            break; // Salir del caso 3
        case '4': // Caso 4: volver al menú principal
            printf("Volviendo...\n");
            return; // Retornar 
        default: // Caso por defecto: opción inválida
            puts("Opción no válida. Por favor, intente de nuevo.");
        }
        presioneTeclaParaContinuar();
    } while (opcion != '4'); // Repetir el bucle mientras la opción no sea '4' (volver al menú principal)
}

// Función para buscar por ingredientes
void buscar_por_ingredientes(Map *mapa_ingredientes, Stack *historial, List *lista_favoritos, Map *recetas_ordenadas) {
    int ingr = 0;
    char respuesta;
    List *omitidos = list_create();

    limpiarPantalla();
    menu_omitir_ingredientes();
    getchar(); // Limpiar el buffer
    scanf("%c", &respuesta);
    getchar(); // Limpiar el buffer

    if (respuesta == 'S' || respuesta == 's') {
        omitir_ingredientes(omitidos);
        getchar(); // Limpiar el buffer después de omitir_ingredientes
    }

    printf("\n");
    menu_ingredientes();
    printf("\nIngrese una opción válida: \n");
    scanf("%d", &ingr);
    getchar(); // Limpiar el buffer

    printf("\n[RECUERDE: la primera letra en mayúscula y con los tildes correspondientes]\n");
    printf("Inserte los ingredientes: \n");

    List *ingredientes = list_create();
    char ingrediente_actual[20];
    int i = 0;

    while (i < ingr) {
        scanf("%19[^\n]", ingrediente_actual);
        getchar(); // Limpiar el buffer
        Capitalizar(ingrediente_actual);
        trim(ingrediente_actual);
        list_pushBack(ingredientes, espacioInicial(ingrediente_actual));
        i++;
    }

    printf("\n");
    mostrarLista(ingredientes);
    agregar_al_historial(historial, " Ingredientes", ingredientes, "Todas");

    List *recetas_encontradas = list_create();
    MapPair *par = map_search(mapa_ingredientes, ingrediente_actual);

    if (par == NULL) {
        printf("No se encontraron recetas con esos ingredientes\n");
        list_clean(omitidos); // Limpiar lista de omitidos
        return;
    }

    List *lista_recetas = par->value;
    receta *aux = list_first(lista_recetas);
    int contador = 1;

    while (aux != NULL) {
        if (comparar_listas(aux->lista_ingredientes, ingredientes, ingr) == 1) {
            if (omitidos != NULL && buscar_en_listas(omitidos, aux->lista_ingredientes) == 0) {
                aux = list_next(lista_recetas);
                continue;
            }
            imprimir(aux, contador);
            list_pushBack(recetas_encontradas, aux);
            contador++;
        }
        aux = list_next(lista_recetas);
    }

    actualizar_lista_favoritas(lista_favoritos, recetas_ordenadas, 0);
    list_clean(omitidos); // Limpiar lista de omitidos

    printf("¿Desea buscar recetas con otros ingredientes? (S/N): ");
    getchar(); // Limpiar el buffer
    scanf("%c", &respuesta);
    getchar(); // Limpiar el buffer

    if (respuesta == 's' || respuesta == 'S') {
        // Llamar recursivamente con los mismos parámetros
        buscar_por_ingredientes(mapa_ingredientes, historial, lista_favoritos, recetas_ordenadas);
    }
}

// Función para buscar recetas posibles con tus ingredientes
void buscar_recetas_posibles(Map *recetas_ordenadas, Stack *historial, List *lista_favoritos){
  limpiarPantalla(); // Limpia la pantalla
  char respuesta; // Variable para almacenar la respuesta del usuario
  List *omitidos = list_create(); // Lista para almacenar las recetas omitidas
  menu_omitir_ingredientes(); // Muestra el menú de omitir ingredientes
  getchar(); // Limpia el buffer
  scanf("%c", &respuesta); // Lee la respuesta del usuario
  getchar(); // Limpia el buffer
  
  if (respuesta == 'S' || respuesta == 's')  // Si la respuesta es afirmativa
      omitir_ingredientes(omitidos); // Llama a la función para omitir ingredientes
    
  printf("\n[RECUERDE: la primera letra en mayúscula y con los tildes correspondientes]\n");
  printf("Inserte los ingredientes: \n");

  List *ingredientes = list_create(); // Lista para almacenar los ingredientes ingresados
  char ingrediente_actual[20]; // Variable para almacenar el ingrediente actual
  int i = 0; // Variable para recorrer los ingredientes ingresados

  while (i < 5)
  {
      scanf("%19[^\n]", ingrediente_actual); // Lee el ingrediente ingresado por el usuario
      getchar(); // Limpia el buffer
      Capitalizar(ingrediente_actual); // Capitaliza el ingrediente
      trim(ingrediente_actual); // Arregla la cadena del ingrediente
      list_pushBack(ingredientes, espacioInicial(ingrediente_actual)); // Agrega el ingrediente a la lista
      i++;
  }
  printf("\n"); // Imprime un salto de línea 
  agregar_al_historial(historial, "Recetas Posibles", ingredientes, "Todas");
  // Agrega al historial la acción realizada
  MapPair *pair = map_first(recetas_ordenadas); // Obtiene el primer par del mapa de recetas 
  int contador = 1; // Indice para mostrar las recetas
  while (pair != NULL) // Mientras haya pares en el mapa
  {
    receta *receta_actual = pair->value; // Obtiene la receta actual
    List *ingredientes_faltantes = list_create(); // Lista para almacenar los ingredientes faltantes
    if(comparar_listas_posibles( receta_actual->lista_ingredientes, ingredientes, ingredientes_faltantes) == 1)
    { //si la receta actual cumple los requisitos 
      if (omitidos != NULL) // Si hay ingredientes omitidos
      {
        if (buscar_en_listas(omitidos , receta_actual->lista_ingredientes) == 0) // Si el ingrediente no está en la lista de omitidos
        {
            pair = map_next(recetas_ordenadas); // Sigue al siguiente par del mapa
            continue; // Salta a la siguiente iteración
        }
      }
      imprimir(receta_actual, contador); // Imprime la receta actual
      printf("Ingredientes faltantes: "); // Imprime el mensaje de ingredientes faltantes
      mostrarLista(ingredientes_faltantes); // Imprime la lista de ingredientes faltantes
      printf("\n"); // Imprime un salto de línea
      contador++; // Incrementa el indice
    }
    pair = map_next(recetas_ordenadas); // Obtiene el siguiente par del mapa
  }
  if (contador == 1) printf("No se encontraron recetas posibles\n"); // Si no se encontraron recetas posibles
  else // Si se encontraron recetas posibles
    actualizar_lista_favoritas(lista_favoritos, recetas_ordenadas, 0); // Pregunta al usuario si desea añadir a favoritas
    
    list_clean(omitidos); // Limpia la lista de ingredientes omitidos
    char recursiva; // Variable para almacenar la respuesta del usuario
    printf("¿Deseas realizar otra búsqueda? (S/N): \n"); // Pregunta al usuario si desea realizar otra búsqueda
    scanf("%c", &recursiva); // Lee la respuesta del usuario
    if (recursiva == 'S' || recursiva == 's')  // Si la respuesta es afirmativa
        buscar_recetas_posibles(recetas_ordenadas, historial,lista_favoritos); // Llama a la función recursivamente
    else return; // Si la respuesta es negativa, termina la función
}

// Función para mostrar recetas favoritas
void mostrar_recetas_favoritas(List *lista_favoritas, Stack *historial){
    limpiarPantalla(); // Limpia la pantalla
    // Imprime mensajes de inicio
    printf("Veamos cuales son las recetas que más te gustaron!!!\n\n");
    printf("Lista de recetas favoritas:\n");
    printf("---------------------------\n\n");
    
    if (list_first(lista_favoritas) == NULL) // Si la lista está vacía
    {
        // Imprime mensaje de aviso
        printf("Oh, no! Aún no tienes recetas favoritas.\n"); 
        printf("Recuerda que siempre puedes agregar recetas a tu lista de favoritos.\n\n");
        return; // Retorna
    }

    else // Si la lista de favortios no está vacía
    {
        int contador = 1; // Indice de la lista de favoritos
        receta *aux = list_first(lista_favoritas); // Obtiene la primera receta de la lista de favoritos
        while (aux != NULL){ // Recorre la lista de favoritas
            imprimir(aux, contador); // Imprime la receta actual
            contador++; // Incrementa el indice
            aux = list_next(lista_favoritas); // Obtiene la siguiente receta de la lista
        }
    }

    // Pregunta al usuario si desea eliminar una receta de la lista de favoritos
    printf("¿Deseas eliminar alguna de tus recetas favoritas? (S/N)\n"); getchar(); // Limpia el buffer
    char opcion; // Variable para almacenar la opción seleccionada por el usuario
    scanf("%c", &opcion); getchar(); // Lee la opción ingresada por el usuario y limpia el buffer
    if(opcion == 's' || opcion == 'S') // Si la opción es afirmativa
        eliminar_receta(lista_favoritas, historial); // Llama a la función para eliminar una receta de la lista de favoritos
}

// Función para mostrar opciones del submenú 5 (Historial de búsquedas)
void Historial(Stack *historial_busquedas, Stack *historial_eliminados){
    limpiarPantalla(); // Limpia la pantalla
    printf("Menú historial\n"); 
    printf("--------------\n\n");
    mostrar_opciones_historial(); // Muestra las opciones del historial
    char opcion; // Variable para almacenar la opción seleccionada por el usuario
    printf("Ingrese su opción:\n"); getchar(); // Solicita la opción al usuario y limpia el buffer
    scanf("%c", &opcion); getchar(); // Lee la opción ingresada por el usuario y limpia el buffer
    switch (opcion){ // Casos posibles
        case '1': // Caso 1: mostrar historial de búsquedas
            mostrar_historial_busquedas(historial_busquedas);
            break; // Salir del caso 1
        case '2': // Caso 2: mostrar historial de recetas eliminadas
            mostrar_historial_eliminados(historial_eliminados);
            break; // Salir del caso 2
        case '3': // Caso 3: volver al menú principal
            limpiarPantalla(); // Limpia la pantalla
            return; // Retorna
        default: // Caso por defecto: opción inválida
            puts("Opción no válida. Por favor, intente de nuevo.");
    }
}

//***************************************************************************************************************************** //


// **************************************** FUNCIÓN MAIN **************************************** 

int main() {
    mostrarAnimacionCargando();
    limpiarPantalla();
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
        for (int i = 0; i < 1; i++) {   //animacion
            limpiarPantalla();
            printCatFrame1();
            sleep(1);  // Pausa de 1 segundo

            limpiarPantalla();
            printCatFrame2();
            sleep(1);  // Pausa de 1 segundo

            limpiarPantalla();
            printCatFrame3();
            sleep(1);  // Pausa de 1 segundo
        }
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
