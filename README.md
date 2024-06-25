## Descripción



## Cómo compilarlo

1. Abre el enlace "" para redirigirte al programa en repl.it.
2. Inicia sesión en caso de que no esté iniciada.
3. En caso de que te aparezca, selecciona la opción "Fork & RUN", en caso de que no te aparezca pase al siguiente paso.
4. Oprime el botón "Run" para compilar y ejecutar el programa.

## Funcionalidades

### Funcionando correctamente:
* **Ver todas las recetas**: Muestra recetas según uno de los siguientes criteros
1. Tipo de plato: Se muestran las recetas de un tipo de plato en específico seleccionado por el usuario
2. Tipo de dieta: Se muestran las recetas de un tipo de dieta en específico seleccionado por el usuario
3. Todas las recetas: Se muestran todas las recetas disponibles
* **Buscar recetas por ingredientes**: Muestra recetas según ingrediente(s) registrado(s) por el usuario, para que las recetas sean mostradas contener estrictamente todos los ingredientes que sean ingresados
1. Por (1) ingrediente: Se muestran todas las recetas que contengan el ingrediente ingresado
2. Por (2) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresado
3. Por (3) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresados
4. Por (4) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresados
5. Por (5) ingredientes: Se muestran todas las recetas que contengan los ingrediente ingresados
* **Buscar recetas sugeridas**: Muestra recetas posibles dependiendo los ingredientes que ingrese el usuario, este debe ingresar 5, las recetas que se muestren coinciden en por lo menos 3 ingredientes.
* **Recetas favoritas**: Muestra las recetas favoritas agregadas anteriormente por el usuario, ya que al momento que se realiza cualquier tipo de búsqueda, se le consulta al usuario si desea agregar una receta a su lista de favoritas.
Si existen recetas en la lista, el usuario tendrá la opción de eliminar las que desee.
* **Historial de búsquedas**: Muestra ...
El usuario tendra la opción de eliminar ... del historial, también podrá ver la lista de los que eliminó-
* **omitir ingredientes**:  Al momento de realizar una búsqueda de cualquier tipo  primero se le preguntará al usuario si desea omitir algún ingrediente, así si el usuario desea evitar recetas con ciertos ingredientes, usará esta opción.

### Problemas conocidos:
* Funciones con mismo objetivo por ejemplo; "arreglar cadena" y "trim"
* Acciones repetitivas dentro de las funciones
### A mejorar:
* Mejorar la legibilidad.
* Implementar mayor modularización del programa.
  
## Ejemplo de uso

### Paso 1: Seleccionar búsqueda deseada

````
========================================
                 Recetario                
========================================
1. Ver todas las recetas
2. Buscar recetas por ingredientes
3. Buscar recetas sugeridas
4. Recetas favoritas
5. Historial de búsquedas
6. Salir del recetario

Ingrese su opción: 
"1"
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

Ingrese su opción: 
"1"
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
Ingrese el tipo de plato deseado:
"Desayuno"

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
¿Desea buscar recetas de otro plato? (S/N):
"N"
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

Ingrese su opción: 
"2"
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


Ingrese la dieta deseada: "Vegano"
````
#### El programa muestra el siguiente menú y las posibles opciones, el usuario escoge que opción desea.

### Paso 9: Tipo de dieta: Vegano

````
Recetas disponibles para el plato deseado: Vegano

RECETAS Vegano:

1. Receta: Bruschetta
    Tipo de plato: Aperitivo
    Ingredientes: Pan, Tomate, Albahaca, Ajo, Aceite de oliva
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Tosta las rebanadas de pan, frota con ajo, agrega tomate picado, albahaca y un chorrito de aceite de oliva

2. Receta: Ensalada de Frutas
    Tipo de plato: Postre
    Ingredientes: Fresas, Plátano, Manzana, Uvas, Jugo de naranja
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Corta las frutas en trozos, mezcla en un bol y rocía con jugo de naranja

3. Receta: Ensalada de Quinoa
    Tipo de plato: Acompañamiento
    Ingredientes: Quinoa, Pepino, Tomate, Cebolla, Limón
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Cocina la quinoa según las instrucciones del paquete, mezcla con pepino, tomate y cebolla picados, y adereza con jugo de limón

4. Receta: Espaguetis Aglio e Olio
    Tipo de plato: Plato principal
    Ingredientes: Espaguetis, Ajo, Aceite de oliva, Guindilla, Perejil
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Cocina los espaguetis, mientras tanto, sofríe ajo y guindilla en aceite de oliva, mezcla con los espaguetis cocidos y añade perejil picado

5. Receta: Falafel
    Tipo de plato: Aperitivo
    Ingredientes: Garbanzos, Ajo, Cebolla, Cilantro, Comino
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Tritura los garbanzos con ajo, cebolla, cilantro y comino, forma bolitas y fríelas hasta que estén doradas

6. Receta: Gazpacho
    Tipo de plato: Sopa
    Ingredientes: Tomate, Pepino, Pimiento, Ajo, Aceite de oliva
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Licua todos los ingredientes hasta obtener una mezcla homogénea, refrigera y sirve frío

7. Receta: Guacamole
    Tipo de plato: Aperitivo
    Ingredientes: Aguacate, Tomate, Cebolla, Cilantro, Limón
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Machaca los aguacates, mezcla con tomate, cebolla, cilantro picados y jugo de limón, sazona al gusto

8. Receta: Hummus
    Tipo de plato: Aperitivo
    Ingredientes: Garbanzos, Tahini, Limón, Ajo, Aceite de oliva
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Tritura los garbanzos con tahini, jugo de limón, ajo y aceite de oliva hasta obtener una pasta suave

9. Receta: Ratatouille
    Tipo de plato: Plato principal
    Ingredientes: Berenjena, Calabacín, Pimiento rojo, Tomate, Cebolla
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Corta todas las verduras en rodajas, coloca en un molde alternando, rocía con aceite de oliva y hornea a 180°C durante 45 minutos

10. Receta: Wok de Verduras
    Tipo de plato: Plato principal
    Ingredientes: Brócoli, Zanahoria, Pimiento, Champiñones, Salsa de soja
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Saltea todas las verduras en un wok con un poco de aceite, añade salsa de soja y cocina hasta que estén tiernas

11. Receta: Brócoli al Vapor con Ajo
    Tipo de plato: Acompañamiento
    Ingredientes: Brócoli, Ajo, Aceite de oliva, Sal, Pimienta
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Cocina el brócoli al vapor, saltea el ajo en aceite de oliva, mezcla con el brócoli, sazona con sal y pimienta

Deseas agregar una de estas recetas a tu lista de favoritas? (S/N):
"S"
````
#### El usuario desea buscar por tipo de dieta, especificamente de "Vegano", el programa ha mostrado los platos disponibles según este tipo, ahora el programa consulta si desea agregar recetas a su lista de favoritas.

### Paso 10: Agregar a lista de favoritos

````
Ingrese el nombre de la receta que desea agregar a tu lista de favoritas:

"Guacamole"
````
#### El usuario seleccionó agregar listas a favoritos e ingresa la opción que desea.

### Paso 11: Seguir agregando o no a la lista de favoritos

````
Receta agregada correctamente a tu lista de favoritas!!!

¿Deseas agregar otra receta a tu lista de favoritas? (S/N):
"N"
¿Desea buscar recetas de otro plato? (S/N): 
"N"
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

Ingrese su opción: 
"4"
````
#### El programa ha regresado al menú anterior, ahora el usuario realizará una nueva búsqueda, pero de otro tipo.

### Paso 13: Seleccionar nueva búsqueda deseada

````
========================================
                 Recetario                
========================================
1. Ver todas las recetas
2. Buscar recetas por ingredientes
3. Buscar recetas sugeridas
4. Recetas favoritas
5. Historial de búsquedas
6. Salir del recetario

Ingrese su opción: 
"2"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee

### Paso 14: Omitir ingredientes

````
Desea omitir algun ingrediente en las recetas?
Ingrese su respuesta (S/N): 
"S"

Ingrese la cantidad de ingredientes que quiere omitir: 
"1"

RECUERDE: todo en minúsculas, con tilde y pulse enter para agregar el siguiente ingrediente
Inserte los ingredientes que no desea en las recetas: 
"ajo"

````
#### El programa consulta si el usuario desea omitir algun ingrediente, el usuario selecciona su elección.

### Paso 15: Búsqueda por ingredientes

````
Cuantos ingredientes quiere en la receta:
-----------------------
1. Por un ingrediente
2. Por dos ingredientes
3. Por tres ingredientes
4. Por cuatro ingredientes
5. Por cinco ingredientes

Ingrese una opcion valida: 
"2"

RECUERDE: todo en minúsculas y con tilde
Inserte los ingredientes: 
"arroz"
"leche"

````
#### El programa muestra el menú de búsqueda y las opciones para el usuario

### Paso 16: Búsqueda por 2 ingredientes: "arroz" y "leche"

````
.... recetas posibles

Deseas agregar una de estas recetas a tu lista de favoritas? (S/N):
"N"
Presione una tecla para continuar...
````
#### El programa muestra las recetas solicitadas y consulta al usuario si desea agregar alguna receta a la lista de favoritos

### Paso 17: Seleccionar nueva búsqueda deseada

````
========================================
                 Recetario                
========================================
1. Ver todas las recetas
2. Buscar recetas por ingredientes
3. Buscar recetas sugeridas
4. Recetas favoritas
5. Historial de búsquedas
6. Salir del recetario

Ingrese su opción: "3"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee

### Paso 18: Elección de ingredientes para la búsqueda

````
[RECUERDE: la primera letra en mayúscula y con los tildes correspondientes]
Inserte los ingredientes: 
"huevo"
"harina"
"sal"
"queso"
"tomate"
````
#### El programa muestra el menú para que el usuario ingrese sus ingredientes

### Paso 19: Elección de ingredientes para la búsqueda

````
1. Receta: Omelette de Queso
    Tipo de plato: Desayuno
    Ingredientes: Huevo, Queso, Leche, Sal, Pimienta
    Dietas: Vegetariano, Ovo-vegetariano, Omnívoro
    Preparacion: Bate los huevos con leche, sal y pimienta, vierte en una sartén caliente, añade el queso rallado y cocina hasta que el huevo esté cuajado

Ingredientes faltantes: Leche, Pimienta

Deseas agregar una de estas recetas a tu lista de favoritas? (S/N):
"S"
````
#### El programa muestra las recetas que coincidan con los requisitos y consulta si el usuario desea agregar alguna receta a favoritos

### Paso 20: Agregar a lista de favoritos

````
Ingrese el nombre de la receta que desea agregar a tu lista de favoritas:

"Omelette de Queso"
````
#### El usuario seleccionó agregar listas a favoritos e ingresa la opción que desea.

### Paso 21: Seguir agregando o no a la lista de favoritos

````
Receta agregada correctamente a tu lista de favoritas!!!

¿Deseas agregar otra receta a tu lista de favoritas? (S/N):
"N"
Presione una tecla para continuar...
````
#### El programa añadió exitosamente la receta a la lista de favoritos. El usuario ya no desea seguir añadiendo recetas a su lista, por lo tanto regresará al menú rin

### Paso 22: Seleccionar una nueva opción 

````
========================================
                 Recetario                
========================================
1. Ver todas las recetas
2. Buscar recetas por ingredientes
3. Buscar recetas sugeridas
4. Recetas favoritas
5. Historial de búsquedas
6. Salir del recetario

Ingrese su opción: 
"4"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee

### Paso 23: Recetas favoritas

````
Veamos cuales son las recetas que más te gustaron!!!

Lista de recetas favoritas:
---------------------------

1. Receta: Omelette de Queso
    Tipo de plato: Desayuno
    Ingredientes: Huevo, Queso, Leche, Sal, Pimienta
    Dietas: Vegetariano, Ovo-vegetariano, Omnívoro
    Preparacion: Bate los huevos con leche, sal y pimienta, vierte en una sartén caliente, añade el queso rallado y cocina hasta que el huevo esté cuajado

2. Receta: Guacamole
    Tipo de plato: Aperitivo
    Ingredientes: Aguacate, Tomate, Cebolla, Cilantro, Limón
    Dietas: Vegano, Vegetariano, Lacto-vegetariano, Ovo-vegetariano, Pescetariano, Flexitariano, Omnívoro
    Preparacion: Machaca los aguacates, mezcla con tomate, cebolla, cilantro picados y jugo de limón, sazona al gusto

3. Receta: Pancakes
    Tipo de plato: Desayuno
    Ingredientes: Harina, Leche, Huevo, Azúcar, Mantequilla
    Dietas: Vegetariano, Ovo-vegetariano, Flexitariano, Omnívoro
    Preparacion: Mezcla la harina con leche, huevo y azúcar, vierte pequeñas porciones en una sartén con mantequilla derretida y cocina hasta que aparezcan burbujas, voltea y cocina hasta dorar

¿Deseas eliminar alguna de tus recetas favoritas? (S/N)
"S"
````
#### El usuario visualiza todas sus recetas favoritas y elige si eliminar alguna de ellas

### Paso 24: Eliminar recetas de favoritas

````
Ingrese el nombre de la receta que desea eliminar de tu lista de favoritas
"Pancakes"

Receta eliminada correctamente de tu lista de favoritas!!!

¿Deseas eliminar otra receta de tu lista de favoritas? (S/N)
"N"
````
#### El usuario eliminó correctamente una recetas de su lista de favoritas. Por ahora el usuario no desea seguir eliminando, por lo tanto, regresará al menú principal.

### Paso 25: Seleccionar una nueva opción 

````
========================================
                 Recetario                
========================================
1. Ver todas las recetas
2. Buscar recetas por ingredientes
3. Buscar recetas sugeridas
4. Recetas favoritas
5. Historial de búsquedas
6. Salir del recetario

Ingrese su opción: 
"5"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee

### Paso 26: Historial

````
Menú historial
--------------

1) Mostrar historial de recetas buscadas
2) Mostrar historial de recetas eliminadas de favoritos
3) Regresar al menú principal

Ingrese su opción:
"1"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee

### Paso 26: Historial

````
Menú historial
--------------

1) Mostrar historial de recetas buscadas
2) Mostrar historial de recetas eliminadas de favoritos
3) Regresar al menú principal

Ingrese su opción:
"1"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee

