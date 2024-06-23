## Descripción



## Cómo compilarlo

1. Abre el enlace "" para redirigirte al programa en repl.it.
2. Inicia sesión en caso de que no esté iniciada.
3. En caso de que te aparezca, selecciona la opción "Fork & RUN", en caso de que no te aparezca pase al siguiente paso.
4. Oprime el botón "Run" para compilar y ejecutar el programa.

## Funcionalidades

### Funcionando correctamente:
* **Mostrar recetas**: Muestra recetas según uno de los siguientes criteros
1. Tipo de plato: Se muestran las recetas de un tipo de plato en específico seleccionado por el usuario
2. Tipo de dieta: Se muestran las recetas de un tipo de dieta en específico seleccionado por el usuario
3. Todas las recetas: Se muestran todas las recetas disponibles
* **Buscar por ingredientes**: Muestra recetas según ingrediente(s) registrado(s) por el usuario, para que las recetas sean mostradas contener estrictamente todos los ingredientes que sean ingresados
1. Por (1) ingrediente: Se muestran todas las recetas que contengan el ingrediente ingresado
2. Por (2) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresado
3. Por (3) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresados
4. Por (4) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresados
5. Por (5) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresados
* **Buscar recetas posibles**: Muestra recetas posibles dependiendo los ingredientes que ingrese el usuario, este debe ingresar 5, las recetas que se muestren coinciden en por lo menos 3 ingredientes.
* **Mostrar recetas favoritas**: Muestra las recetas favoritas agregadas anteriormente por el usuario, ya que al momento que se realiza cualquier tipo de búsqueda, se le consulta al usuario si desea agregar una receta a su lista de favoritas.
Si existen recetas en la lista, el usuario tendrá la opción de eliminar las que desee.
* **Mostrar historial**: Muestra ...
El usuario tendra la opción de eliminar ... del historial, también podrá ver la lista de los que eliminó-
* **omitir ingredientes**:  Al momento de realizar una búsqueda de cualquier tipo  primero se le preguntará al usuario si desea omitir algún ingrediente, así si el usuario desea evitar recetas con ciertos ingredientes, usará esta opción.

### Problemas conocidos:
* 

### A mejorar:
* Mejorar la legibilidad.
* Implementar mayor modularización del programa.

## Ejemplo de uso

### Paso 1: Seleccionar búsqueda deseada

````
========================================
                Recetario               
========================================
1) Mostrar recetas
2) Buscar por ingredientes
3) Buscar recetas posibles
4) Mostrar recetas favoritas
5) Mostrar historial
6) Salir

Ingrese su opción: "1"
````
#### El usuario visualiza el menú principal y selecciona la opción que desee

### Paso 2: Mostrar recetas

````
Mostrar recetas según:
-----------------------

1. Tipo de plato
2. Tipo de dieta
3. Todas las recetas
4. Volver al menú principal

Ingrese su opción: "1"
````
#### El programa muestra el submenú de la opción seleccionada, el usuario deseará hacia donde continuar.

### Paso 3: Tipo de plato
````
Platos disponibles:

1) Bebida
2) Plato principal
3) Aperitivo
4) Acompañamiento
5) Postre
6) Sopa
7) Desayuno

RECUERDA: primera letra en mayuscula
Ingrese el tipo de plato deseado: "Desayuno"

````
#### El programa muestra el siguiente menú y las posibles opciones, el usuario escoge que opción desea.

### Paso 4: Tipo de plato: "Desayuno"

````
Recetas disponibles para el plato deseado:

1. Receta: Omelette de Queso
    Tipo de plato: Desayuno
    Ingredientes: Huevo, Queso, Leche, Sal, Pimienta
    Dietas: Vegetariano, Ovo-vegetariano, Omnívoro
    Preparacion: Bate los huevos con leche, sal y pimienta, vierte en una sartén caliente, añade el queso rallado y cocina hasta que el huevo esté cuajado

2. Receta: Pancakes
    Tipo de plato: Desayuno
    Ingredientes: Harina, Leche, Huevo, Azúcar, Mantequilla
    Dietas: Vegetariano, Ovo-vegetariano, Flexitariano, Omnívoro
    Preparacion: Mezcla la harina con leche, huevo y azúcar, vierte pequeñas porciones en una sartén con mantequilla derretida y cocina hasta que aparezcan burbujas, voltea y cocina hasta dorar


Deseas agregar una de estas recetas a tu lista de favoritas? (S/N):
"S"
````
#### El usuario desea buscar por tipo de plato, especificamente de "Desayuno", el programa ha mostrado los platos disponibles según este tipo, ahora el programa consulta si desea agregar recetas a su lista de favoritas.

### Paso 5: Agregar a lista de favoritos

````
Ingrese el nombre de la receta que desea agregar a tu lista de favoritas:

"Pancakes"
````
#### El usuario seleccionó agregar listas a favoritos e ingresa la opción que desea.

### Paso 6: Seguir agregando o no a la lista de favoritos

````
Receta agregada correctamente a tu lista de favoritas!!!

¿Deseas agregar otra receta a tu lista de favoritas? (S/N):
"N"
¿Desea buscar recetas de otro plato? (S/N): N
Presione una tecla para continuar...
````
#### El programa añadió exitosamente la receta a la lista de favoritos. El usuario ya no desea seguir añadiendo recetas a su lista.

### Paso 7: Nueva Búsqueda

````
Mostrar recetas según:
-----------------------

1. Tipo de plato
2. Tipo de dieta
3. Todas las recetas
4. Volver al menú principal

Ingrese su opción: 2
````
#### El programa ha regresado al menú anterior, ahora el usuario realizará una nueva búsqueda.

### Paso 8: Tipo de dieta 

````
Dietas disponibles:

1) Vegetariano
2) Lacto-vegetariano
3) Omnívoro
4) Flexitariano
5) Vegano
6) Ovo-vegetariano
7) Pescetariano


Ingrese la dieta deseada: Vegano
````
#### El programa muestra el siguiente menú y las posibles opciones, el usuario escoge que opción desea.

### Paso 9: Tipo de dieta: "Vegano"

````
Recetas disponibles para el plato deseado:

...
...


Deseas agregar una de estas recetas a tu lista de favoritas? (S/N):
"S"
````
#### El usuario desea buscar por tipo de dieta, especificamente de "Vegano", el programa ha mostrado los platos disponibles según este tipo, ahora el programa consulta si desea agregar recetas a su lista de favoritas.

### Paso 10: Agregar a lista de favoritos

````
Ingrese el nombre de la receta que desea agregar a tu lista de favoritas:

"..."
````
#### El usuario seleccionó agregar listas a favoritos e ingresa la opción que desea.

### Paso 11: Seguir agregando o no a la lista de favoritos

````
Receta agregada correctamente a tu lista de favoritas!!!

¿Deseas agregar otra receta a tu lista de favoritas? (S/N):
"N"
¿Desea buscar recetas de otro plato? (S/N): N
Presione una tecla para continuar...
````
#### El programa añadió exitosamente la receta a la lista de favoritos. El usuario ya no desea seguir añadiendo recetas a su lista.

### Paso 12: Regreso

````
Mostrar recetas según:
-----------------------

1. Tipo de plato
2. Tipo de dieta
3. Todas las recetas
4. Volver al menú principal

Ingrese su opción: 4
````
#### El programa ha regresado al menú anterior, ahora el usuario realizará una nueva búsqueda, pero de otro tipo.

### Paso 13: Seleccionar nueva búsqueda deseada

````
========================================
                Recetario               
========================================
1) Mostrar recetas
2) Buscar por ingredientes
3) Buscar recetas posibles
4) Mostrar recetas favoritas
5) Mostrar historial
6) Salir

Ingrese su opción: "2"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee