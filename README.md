# <u>Trabajo Práctico 2</u>

Alumno: Franco Daniel Schischlo

Padrón: 100615

Repositorio: https://github.com/gdbien/tp2

## <u>Tabla de contenidos</u>
* [Descripción general](#desc)
* [Diagramas UML](#diag)

## <u>Descripción general</u>

Dado que no había mucha complejidad en este trabajo práctico (ya de por si nos mostraron/proporcionaron una cola bloqueante) el resto se resolvía bastante fácil (hacer el inventario protegido era muy similar a la cola bloqueante, solo que cambiaba la estructura primitiva de base; un map, y la condición por la cual el thread se quedaba esperando) con lo que voy a tratar de hacer mas bien una descripción general explicando como van apareciendo las diversas clases y que se encargan de hacer.

Inicialmente lo primero que se hace en "main.cpp" es procesar el archivo de entrada con la configuración de trabajadores (recolectores y productores) de esto se encarga la clase "WorkerProcessor", esta posee las referencias a las distintas colas bloqueantes separadas por tipo de trabajador, al inventario compartido tanto para los recolectores y productores, y por último al objeto de puntos bloqueante. Se crean las clases puntuales (no abstractas) de cada trabajo (inicializando cada una de ellas con las referencias necesarias) y se insertan en sus respectivas colas. Después se inician (heredan de la clase "Thread") primero todos los productores y luego los recolectores, quedando todos en espera a que se empiecen a llenar las colas de recursos. Cabe aclarar que si bien me hubiese gustado que tanto "WorkerProcessor" como "MapProcessor" tengan solo métodos estáticos, y que se puedan utilizar sin una instancia (dado que no tienen estado) no era óptimo a la hora de modularizar, ya que tenía que pasarle a los distintos métodos de las clases la mayoría de las referencias.

En este momento se llama a "MapProcessor", el cual procesa el archivo del mapa, y realiza el llenado de las colas de recursos, las cuales las van a consumir los recolectores. Es importante aclarar que una vez que "MapProcessor" termina de leer y llenar las colas, debe avisar que termino de procesar utilizando "ProtectedQueue::close() " sobre cada cola bloqueante, para que los recolectores no sigan esperando mas recursos.

Los recolectores (clase "Gatherer") se comportan todos de la misma forma (extraen de a 1 recurso de la cola, y duermen) y si bien se separó por cada profesión (clases; "Farmer", "Lumberjack", y "Miner") todas llaman al método "Gatherer::run()". No sería necesario crear las subclases de "Gatherer", pero por una cuestión de extensibilidad, y de que el código sea mas flexible a cambios, se programó así.

Los productores (clase "Producer") tienen distintos tipos y cantidades de consumo de recursos, es por esto que al ser llamado el método run() de cada uno, se llama al método del padre (Producer::produce()) con los parámetros de cada uno.

Los recolectores van a ir llenando el inventario, y cada vez que inserten un recurso con "ProtectedInventory::increaseResource()" se va a realizar uno "cv.notify_all()" para que los productores que se encuentren esperando luego de querer consumir recursos con "ProtectedInventory::consumeResources()", se despierten, y se verifique si hay suficientes recursos para satisfacer el pedido, si los hay, los consume, duerme (60ms), y incrementa los puntos protegidos. En caso de no haber los suficientes recursos, se queda en estado "wait".

Es importante aclarar, como dije antes, que tanto cuando desde "MapProcessor" se terminan de llenar las colas, como cuando los recolectores terminan de llenar el inventario, se debe realizar el close() de las estructuras, para que los que las consuman no se queden esperando infinitamente mas recursos de los que va a haber.

## <u>Diagramas UML</u>

### <u>Diagramas de clases</u>

***Trabajadores***

<img src="img/Workers" style="zoom:100%;"/>



***MapProcessor***



<img src="img/MapProcessor" style="zoom:100%;"/>

```

```

------

### <u>Diagrama de secuencia</u>

(Ejemplo: Carpintero al querer consumir recursos para generar puntos de beneficio)



<img src="img/Carpenter" style="zoom:100%;"/>




