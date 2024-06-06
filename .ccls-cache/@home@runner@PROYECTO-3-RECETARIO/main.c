#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/extra.h"
#include "TDAs/list.h"
#include "TDAs/map.h"
// jhevfjhSDVJLHSDVh
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