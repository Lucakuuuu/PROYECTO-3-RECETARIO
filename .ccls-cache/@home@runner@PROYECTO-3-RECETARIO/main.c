#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/map.h"

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