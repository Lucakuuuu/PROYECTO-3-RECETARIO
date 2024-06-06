#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/map.h"

// PARA ELIMINAR GITs INGRESAR CÓDIGO EN Shell: " git reset --hard HEAD~1 "

void cargar_recetas(Map *recetas_ordenadas, Map *tipo_de_plato, Map *tipo_dieta)
{
  FILE *archivo = fopen("beta - Hoja 1 (3).csv", "r"); // Abrimos el archivo en modo lectura

  if (archivo == NULL){ // Si no se pudo abrir el archivo
      perror("Error al abrir el archivo"); // Informa si el archivo no puede abrirse
      return; // Retorna de la función
  }

  char **campos;
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) 
  { // Lee cada línea del archivo CSV hasta el final
    receta *receta_nueva = (receta*)malloc(sizeof(receta));
    // borrarComillas(campos[1]);
    strcpy(receta_nueva->nombre_receta, campos[0]);
    // Leer los ingredientes
    //receta_nueva->lista_ingredientes = list_create();
    //List* aux = list_create();
    strcpy(receta_nueva->tipo_de_plato, campos[2]);
    strcpy(receta_nueva->preparacion, campos[4]);

    // Aquí solo se está insertando en el mapa recetas_ordenadas
    map_insert(recetas_ordenadas, receta_nueva->nombre_receta, receta_nueva);

  }

  fclose(archivo); // Cierra el archivo después de leer todas las líneas

}

void mostrar_todas_las_recetas(Map *recetas_ordenadas){
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

void mostrar_recetas(Map *recetas_ordenadas)
{
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

void mostrarMenuPrincipal() 
{
  limpiarPantalla();
  puts("========================================");
  puts("                Recetario               ");
  puts("========================================");

  puts("1) Mostrar recetas"); //esto lleva a un mini menú donde se pregunta por el tipo de dieta y la categoria de receta que se busca
  puts("2) Buscar por ingredientes");
  puts("3) Buscar recetas posibles");
  puts("4) Salir\n");
}


int main() 
{
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