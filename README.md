## Descripción

Esta aplicación permite gestionar recetas de cocina, ofreciendo funcionalidades como la visualización de recetas según el tipo de plato o dieta seleccionados por el usuario. También permite buscar recetas por ingredientes específicos, asegurando que las recetas mostradas contengan estrictamente todos los ingredientes ingresados. Además, cuenta con una función para sugerir recetas basadas en al menos tres de los cinco ingredientes proporcionados por el usuario. Los usuarios pueden agregar recetas a su lista de favoritas y gestionarlas, así como consultar su historial de búsquedas y recetas eliminadas de favoritos. Adicionalmente, se ofrece la opción de omitir ingredientes no deseados al realizar cualquier tipo de búsqueda.

## Cómo compilarlo

1. Abre el enlace "" para redirigirte al programa en replit.
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
* **Historial de búsquedas**: Muestra todas las búsquedas realizadas por el usuario anteriormente.
También, el usuario tendra la opción de ver su historial de recetas eliminadas de su lista de favoritas.
* **Omitir ingredientes**:  Al momento de realizar una búsqueda de cualquier tipo  primero se le preguntará al usuario si desea omitir algún ingrediente, así si el usuario desea evitar recetas con ciertos ingredientes, usará esta opción.

### Problemas conocidos:
* Funciones con mismo objetivo por ejemplo; "arreglar cadena" y "trim"
* Acciones repetitivas dentro de las funciones
* Posibles problema con el uso de recursividad al momento de limpiar el buffer

### A mejorar:
* Mejorar la legibilidad.
* Implementar mayor modularización del programa.
* Implementar recursividad en todas las funciones
* Manejo de ingresos erróneos por parte del usuario
  
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

### Paso 2: Mostrar recetas tipo de plato

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

### Paso 3: Omitir ingredientes

````
Desea omitir algun ingrediente en las recetas?
Ingrese su respuesta (S/N): 
"N"
````
#### El programa pregunta al usuario si desea omitir ingredientes, es decir, si desea que se omitan las recetas que contengan los ingredientes que ingrese el usuario.

### Paso 4: Elección del tipo de plato
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
#### El usuario no seleccionó omitir ingredeintes, por lo tanto programa muestra el siguiente menú y las posibles opciones, el usuario escoge que opción desea.

### Paso 5: Tipo de plato: "Desayuno"

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

### Paso 6: Agregar a lista de favoritos

````
Ingrese el nombre de la receta que desea agregar a tu lista de favoritas:

"Pancakes"
````
#### El usuario seleccionó agregara a lista de favoritas e ingresa la opción que desea.

### Paso 7: Seguir agregando o no a la lista de favoritos

````
Receta agregada correctamente a tu lista de favoritas!!!

¿Deseas agregar otra receta a tu lista de favoritas? (S/N):
"N"
¿Desea buscar recetas de otro plato? (S/N):
"N"
Presione una tecla para continuar...
````
#### El programa añadió exitosamente la receta a la lista de favoritos. El usuario ya no desea seguir añadiendo recetas a su lista.

### Paso 8: Nueva Búsqueda, por tipo de dieta

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

### Paso 9: Omitir ingredientes

````
Desea omitir algun ingrediente en las recetas?
Ingrese su respuesta (S/N): 
"S"

Ingrese la cantidad de ingredientes que quiere omitir: 
"2"

RECUERDE: Primera letra en mayúscula, con tildes correspondientes y pulse enter para agregar el siguiente ingrediente
Inserte los ingredientes que no desea en las recetas: 
"huevo"
"leche"
````
#### El usuario ha deseado buscar por tipo de dieta, ahora el programa pregunta si desea omitir ingredientes

### Paso 10: Elección del tipo de dieta

````
Dietas disponibles:

1) Vegetariano
2) Lacto-vegetariano
3) Omnívoro
4) Flexitariano
5) Vegano
6) Ovo-vegetariano
7) Pescetariano


Ingrese la dieta deseada:
"Vegano"
````
#### EL usuario ha omitido sus ingredientes, ahora el programa muestra el siguiente menú y las posibles opciones, el usuario escoge que opción desea.

### Paso 11: Tipo de dieta: Vegano

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

### Paso 12: Agregar a lista de favoritos

````
Ingrese el nombre de la receta que desea agregar a tu lista de favoritas:

"Guacamole"
````
#### El usuario seleccionó agregar listas a favoritos e ingresa la opción que desea.

### Paso 13: Seguir agregando o no a la lista de favoritos

````
Receta agregada correctamente a tu lista de favoritas!!!

¿Deseas agregar otra receta a tu lista de favoritas? (S/N):
"N"
¿Desea buscar recetas de otro plato? (S/N): 
"N"
Presione una tecla para continuar...
````
#### El programa añadió exitosamente la receta a la lista de favoritos. El usuario ya no desea seguir añadiendo recetas a su lista.

### Paso 14: Regreso

````
Mostrar recetas según:
-----------------------

1. Tipo de plato
2. Tipo de dieta
3. Todas las recetas
4. Volver al menú principal

Ingrese su opción: 
"4"
Volviendo...
Presione una tecla para continuar...
````
#### El programa ha regresado al menú anterior, ahora el usuario seleccionará su opción siguiente

### Paso 15: Seleccionar nueva búsqueda deseada, por ingredientes

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

### Paso 16: Omitir ingredientes

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
#### El programa consulta si el usuario desea omitir algun ingrediente, el usuario selecciona su preferencia.

### Paso 17: Búsqueda por ingredientes (2)

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

### Paso 18: Búsqueda por 2 ingredientes: "arroz" y "leche"

````
1. Receta: Arroz con Leche
    Tipo de plato: Postre
    Ingredientes: Arroz, Leche, Azúcar, Canela, Vainilla
    Dietas: Vegetariano, Lacto-vegetariano, Omnívoro
    Preparacion: Cocina el arroz en leche con azúcar, canela y vainilla a fuego lento hasta que esté cremoso

Deseas agregar una de estas recetas a tu lista de favoritas? (S/N):
"N"
¿Desea buscar recetas con otros ingredientes? (S/N): 
"N"
Presione una tecla para continuar...
````
#### El programa muestra las recetas solicitadas y consulta al usuario si desea agregar alguna receta a la lista de favoritos

### Paso 19: Seleccionar nueva búsqueda deseada, buscar recetas sugeridas

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

Desea omitir algun ingrediente en las recetas?
Ingrese su respuesta (S/N): 
"N"
````
#### El usuario visualiza nuevamente el menú principal y selecciona la opción que desee


### Paso 20: Elección de ingredientes para la búsqueda

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

### Paso 21: Recetas con los ingredientes ingresados

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

### Paso 22: Agregar a lista de favoritos

````
Ingrese el nombre de la receta que desea agregar a tu lista de favoritas:

"Omelette de Queso"
````
#### El usuario seleccionó agregar listas a favoritos e ingresa la opción que desea.

### Paso 23: Seguir agregando o no a la lista de favoritos

````
Receta agregada correctamente a tu lista de favoritas!!!

¿Deseas agregar otra receta a tu lista de favoritas? (S/N):
"N"
¿Deseas realizar otra búsqueda? (S/N):
"N"
Presione una tecla para continuar...
````
#### El programa añadió exitosamente la receta a la lista de favoritos. El usuario ya no desea seguir añadiendo recetas a su lista, por lo tanto regresará al menú principal

### Paso 24: Seleccionar una nueva opción, recetas favoritas 

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
#### El usuario visualiza nuevamente el menú principal y selecciona una nueva opción

### Paso 25: Recetas favoritas

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

### Paso 26: Eliminar recetas de favoritas

````
Ingrese el nombre de la receta que desea eliminar de tu lista de favoritas
"Pancakes"

Receta eliminada correctamente de tu lista de favoritas!!!

¿Deseas eliminar otra receta de tu lista de favoritas? (S/N)
"N"
````
#### El usuario eliminó correctamente una recetas de su lista de favoritas. Por ahora el usuario no desea seguir eliminando, por lo tanto, regresará al menú principal.

### Paso 27: Corroboración historial

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

### Paso 28: Visualización ista de favoritas actualizadas
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

¿Deseas eliminar alguna de tus recetas favoritas? (S/N)
"N"
````
#### El usuario desea ver su lista actualizada para comprobar que estuviera todo en orden

### Paso 29: Seleccionar una nueva opción, historial de búsqueda

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

### Paso 30: Elección dentro del submenú del Historial de búsqueda

````
Menú historial
--------------

1) Mostrar historial de recetas buscadas
2) Mostrar historial de recetas eliminadas de favoritos
3) Regresar al menú principal

Ingrese su opción:
"1"
````
#### El usuario visualiza el submenú del historial y selecciona una de sus opciones posibles

### Paso 31: Historial de búsqueda

````
Bienvenido al historial!!!
Aqui podras ver todas las busquedas que realizaste

Estas son todas tus búsquedas:

-----------------------------
Tipo de busqueda: Recetas Posibles
Ingredientes ingresados: Huevo, Harina, Sal, Queso, Tomate

Tipo de busqueda:  Ingredientes
Ingredientes ingresados: Arroz, Leche

Tipo de busqueda: Por Tipo de Dieta
Categoría: Vegano

Tipo de busqueda: Por Tipo de Plato
Categoría: Desayuno

Presione una tecla para continuar...
````
#### El usuario visualiza nuevamente el historial de búsqueda

### Paso 32: Re-elección de Historial 

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
#### El usuario visualiza el menpu principal y selecciona su opción

### Paso 33: elección submenpu del Historial

````
Menú historial
--------------

1) Mostrar historial de recetas buscadas
2) Mostrar historial de recetas eliminadas de favoritos
3) Regresar al menú principal

Ingrese su opción:
"2"
````
#### El usuario seleccionó nuevamente la opción del historial, por lo tanto visualiza el submenú

### Paso 34: Historial de recetas eliminadas de favoritos
````
Bienvenido al historial de recetas eliminadas de favoritos!!!
Aquí podras ver todas las recetas eliminadas

1. Receta: Pancakes
    Tipo de plato: Desayuno
    Ingredientes: Harina, Leche, Huevo, Azúcar, Mantequilla
    Dietas: Vegetariano, Ovo-vegetariano, Flexitariano, Omnívoro
    Preparacion: Mezcla la harina con leche, huevo y azúcar, vierte pequeñas porciones en una sartén con mantequilla derretida y cocina hasta que aparezcan burbujas, voltea y cocina hasta dorar

Presione una tecla para continuar...
````
#### El usuario visualiza nuevamente las recetas eliminadas previamente de su lista de favoritas

### Paso 35: Seleccionar una nueva opción 

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
"6"
````
#### El usuario visualiza nuevamente el menú principal y selecciona su opción

### Paso 36: Saliendo de la aplicación

````
Saliendo del recetario...
Presione una tecla para continuar...
````
#### El usuario desea salir del recetario, por lo tanto seleccionó la ultima opción


Aportes integrantes:

Alexander: 
Implementación de la función “Búsqueda por ingredientes” junto con sus funciones complementarias, implementación de la función general “Omitir ingredientes” junto con sus funciones complementarias, aportó en la implementación y corrección de errores de la lista de favoritos, aportación en la implementación de la función “agregar al historial”,  aportación en las secciones del informe “TDAs” (Mapas), “Implementación”, “Planificación” y parte de “Funcionalidades del programa”.

Eros: 
Creación archivo READ.ME, implementación comentarios dentro del código, asistió en creación de funciones secundarias del programa como; “arreglar cadena”, “copiar lista”, etc. Es participe en la correción general de errores y búsqueda de soluciones.

Constanza: 
Creó el archivo csv el cual contiene todas las recetas usadas en la aplicación, implementó la funciones “capitalizar”, “Buscar por plato”,  “Rellenar tipo plato”, “Agregar receta favorita”, “Mostrar todas las recetas”,  “Actualizar listas favoritas”, “Agregar al historial”, “Buscar recetas posibles”, “Mostrar recetas favoritas”, “Mostrar historial búsquedas” y “Filtro recetas repetidas”.

Lucas: 
Creó la estructura de “recetasxdieta”, implementó funciones de depuración como; “Trim”, “arreglar cadena”, “espacio inicial”, “copiar lista”, “espacio inicial”, “mostrar lista”, contribuyó en la función “mostrar historial”, implementó la función “Buscar por dieta”, corrigió errores del main, ordenó las funciones del código.