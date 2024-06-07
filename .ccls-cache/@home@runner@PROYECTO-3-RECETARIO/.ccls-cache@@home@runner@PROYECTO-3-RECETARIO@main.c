#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/map.h"

// PARA ELIMINAR GITs INGRESAR CÓDIGO EN Shell: " git reset --hard HEAD~1 "

typedef struct receta{
  char nombre_receta[30]; 
  List *lista_ingredientes; // Lista de ingredientes
  char tipo_de_plato[15]; //acompañamiento, postre, plato principal, etc
  List *lista_dietas; //si es vegana, vegetariana, omnivora, etc.
  char preparacion[2000]; //pasos a seguir para preparar la receta
} receta;

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

// Función para recortar espacios en blanco al inicio y final de una cadena
char *trim(char *cadena) {
  // Punteros para el inicio y final de la cadena recortada
  char *inicio, *fin;

  // Elimina espacios en blanco al inicio de la cadena
  inicio = cadena;
  while (*inicio == ' ') {
    inicio++;
  }

  // Si la cadena está vacía después de eliminar espacios al inicio, retorna la cadena vacía
  if (*inicio == '\0') {
    return "";
  }

  // Elimina espacios en blanco al final de la cadena
  fin = inicio + strlen(inicio) - 1;
  while (*fin == ' ') {
    fin--;
  }

  *(fin + 1) = '\0'; // Agrega un terminador de cadena al final recortado

  // Retorna la cadena recortada
  return inicio;
}

// Función para copiar los elementos de una lista a otra lista
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

//Función para las recetas y los datos
void imprimir(receta *receta, int contador){
  printf("%d. Receta: %s\n", contador, receta->nombre_receta); 
  printf("Tipo de plato: %s\n", receta->tipo_de_plato);
<<<<<<< HEAD
  printf("Ingredientes: "); mostrarLista(receta->lista_ingredientes);
  printf("Dietas: "); mostrarLista(receta->lista_dietas);
=======
  printf("Ingredientes: "); 
  mostrarLista(receta->lista_ingredientes);
  printf("Dietas: "); 
  mostrarLista(receta->lista_dietas);
>>>>>>> 3403473afece02b4bed39a1d81488509ab187f72
  printf("Preparacion: %s\n", receta->preparacion);
  printf("\n");
}

void arreglar_cadena(char *cadena){
  // Elimina las comillas dobles si están presentes (")")
  if (cadena[0] == '"') {
    memmove(cadena, cadena + 1, strlen(cadena));
      cadena[strlen(cadena) - 1] = '\0';
  }
  // Elimina las comillas simples si están presentes (')")
  if (cadena[0] == '\'') {
    memmove(cadena, cadena + 1, strlen(cadena));
    cadena[strlen(cadena) - 1] = '\0';
  }
  // Elimina espacios en blanco al inicio y final del género
  cadena = trim(cadena);
}

<<<<<<< HEAD
void cargar_recetas(Map *recetas_ordenadas, Map *tipo_de_plato, Map *tipo_dieta){
  FILE *archivo = fopen("Ingredientes/Ingredientes.csv", "r"); // Abrimos el archivo en modo lectura

=======
void cargar_recetas(Map *recetas_ordenadas, Map *tipo_de_plato, Map *tipo_dieta)
{
  FILE *archivo = fopen("Ingredientes/beta - Hoja 1 (3).csv", "r"); // Abrimos el archivo en modo lectura
>>>>>>> 3403473afece02b4bed39a1d81488509ab187f72
  if (archivo == NULL){ // Si no se pudo abrir el archivo
      perror("Error al abrir el archivo"); // Informa si el archivo no puede abrirse
      return; // Retorna de la función
  }

  char **campos;
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV
  List *aux = list_create();

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) // Lee cada línea del archivo CSV hasta el final
  {
    receta *receta_nueva = (receta*)malloc(sizeof(receta));
    strcpy(receta_nueva->nombre_receta, campos[0]);
    receta_nueva->lista_ingredientes = list_create(); // Lista para los ingredientes
<<<<<<< HEAD

    // Separación de ingredientes individuales dentro de las comillas
    if (strcmp(campos[1], "") != 0) { // Verifica si el campo de ingredientes no está vacío
      char *ingredienteActual = strtok(campos[1], ","); // Obtiene el primer género

      while (ingredienteActual != NULL) {
        arreglar_cadena(ingredienteActual); // Arregla la cadena para eliminar las comillas dobles)
        list_pushBack(aux, espacioInicial(ingredienteActual)); // Agrega los ingredientes a la lista de ingredientes

=======
    
    // Separación de ingredientes individuales dentro de las comillas
    if (strcmp(campos[1], "") != 0) { // Verifica si el campo de ingredientes no está vacío
      char *ingredienteActual = strtok(campos[1], ","); // Obtiene el primer género

      while (ingredienteActual != NULL) {
        arreglar_cadena(ingredienteActual); // Arregla la cadena para eliminar las comillas dobles)
        list_pushBack(aux, espacioInicial(ingredienteActual)); // Agrega los ingredientes a la lista de ingredientes
        
>>>>>>> 3403473afece02b4bed39a1d81488509ab187f72
        /*
        MapPair *estaingrediente = map_search(mapaingredientes, espacioInicial(ingredienteActual));
        // si no está el género
        if (estaingrediente == NULL) {
          receta *ingrediente = (PelisXingrediente *)malloc(sizeof(PelisXingrediente));
          ingrediente->Peliculas = list_create();
          map_insert(mapaingredientes, espacioInicial(ingredienteActual), ingrediente);
          list_pushBack(ingrediente->Peliculas, peli);
        } else {
          PelisXingrediente *Gpair = estaingrediente->value;
          list_pushBack(Gpair->Peliculas, peli);
        }
        */

        // Obtiene el siguiente ingrediente
        ingredienteActual = strtok(NULL, ",");
      }
      copiarLista(aux, receta_nueva->lista_ingredientes);
      list_clean(aux);
    }
    strcpy(receta_nueva->tipo_de_plato, campos[2]);
    receta_nueva->lista_dietas = list_create();

    // Separación de dietas individuales dentro de las comillas
    if (strcmp(campos[3], "") != 0) { // Verifica si el campo de dietas no está vacío
      char *dietaActual = strtok(campos[3], ","); // Obtiene la primera dieta

      while (dietaActual != NULL) {
        arreglar_cadena(dietaActual); // Arregla la cadena para eliminar las comillas dobles)
        list_pushBack(aux, espacioInicial(dietaActual)); // Agrega las dietas a la lista de ingredientes

        /*
        MapPair *estaingrediente = map_search(mapaingredientes, espacioInicial(ingredienteActual));
        // si no está el género
        if (estaingrediente == NULL) {
          receta *ingrediente = (PelisXingrediente *)malloc(sizeof(PelisXingrediente));
          ingrediente->Peliculas = list_create();
          map_insert(mapaingredientes, espacioInicial(ingredienteActual), ingrediente);
          list_pushBack(ingrediente->Peliculas, peli);
        } else {
          PelisXingrediente *Gpair = estaingrediente->value;
          list_pushBack(Gpair->Peliculas, peli);
<<<<<<< HEAD
          a
=======
>>>>>>> 3403473afece02b4bed39a1d81488509ab187f72
        }
        */

        // Obtiene el siguiente ingrediente
        dietaActual = strtok(NULL, ",");
      }
      copiarLista(aux, receta_nueva->lista_dietas);
      list_clean(aux);
    }
    strcpy(receta_nueva->preparacion, campos[4]);
    // Aquí solo se está insertando en el mapa recetas_ordenadas
    map_insert(recetas_ordenadas, receta_nueva->nombre_receta, receta_nueva);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas
}

void mostrar_todas_las_recetas(Map *recetas_ordenadas)
{
MapPair *pair = map_first(recetas_ordenadas); // Obtenemos el primer par del mapa con todas las recetas
printf("\n"); // Imprimimos un salto de línea
int contador = 0; // Contador para saber el número de recetas
while (pair != NULL) 
  { // Mientras el par no sea nulo
    receta *receta_actual = pair->value; // Tomamos la receta guardada en el valor del par actual
    contador++; // Aumentamos el contador
    imprimir(receta_actual, contador); // Imprimimos los datos de la receta
    pair = map_next(recetas_ordenadas); // Avanza al siguiente par en el mapa
  }
}

void menu_secundario()
{
  printf("\nMostrar recectas según:\n");
  printf("-----------------------\n\n");
  printf("1. Tipo de plato\n");
  printf("2. Tipo de dieta\n");
  printf("3. Todas las recetas\n");
  printf("4. Volver al menú principal\n");
}

void mostrar_recetas(Map *recetas_ordenadas){
  char opcion;
  do 
    {
      limpiarPantalla();
      menu_secundario();
      printf("Ingrese su opción: ");
      scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                             // newline anterior
      switch (opcion) 
      {
      case '1':
          // buscarPlato();
        break;
      case '2':
         // buscarDieta();
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
  return;
}

void mostrarMenuPrincipal(){
  limpiarPantalla();
  puts("========================================");
  puts("                Recetario               ");
  puts("========================================");

  puts("1) Mostrar recetas"); 
  puts("2) Buscar por ingredientes");
  puts("3) Buscar recetas posibles");
  puts("4) Salir\n");
}

int main(){
  char opcion;
  Map *recetas_ordenadas = map_create(is_equal_str); //se puede cambiar por una lista
  Map *tipo_de_plato = map_create(is_equal_str); 
  Map *tipo_dieta = map_create(is_equal_str);

  do 
  {
    mostrarMenuPrincipal();
    cargar_recetas(recetas_ordenadas, tipo_de_plato, tipo_dieta); //estpy printeando para comprobar si se cargaron las recetas
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior
    switch (opcion) 
    {
    case '1':
      mostrar_recetas(recetas_ordenadas);
      break;
    case '2':
       // buscarXIngredientes(recetas_ordenadas);
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