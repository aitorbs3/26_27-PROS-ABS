# Actividades 4-7: Procesos en C

## Problemas encontrados y soluciones

Durante la realización de las actividades 4, 5, 6 y 7 surgieron algunas dificultades relacionadas principalmente con el funcionamiento de `fork()` y la creación de procesos.

### Actividad 4

Uno de los problemas fue comprender que, al utilizar `fork()`, el programa continúa ejecutándose tanto en el proceso padre como en el proceso hijo.

Para solucionarlo, se utilizó el valor devuelto por `fork()` para diferenciar ambos procesos.

También se tuvo en cuenta que el orden en el que aparecen los mensajes de los hijos puede variar, ya que los procesos se ejecutan de forma independiente.

### Actividad 5

La principal dificultad fue conseguir que los procesos formasen una cadena, de manera que cada proceso crease únicamente al siguiente hijo.

Para solucionarlo, se controló mediante `fork()` qué proceso debía continuar creando nuevos procesos y se utilizó `wait()` para controlar la finalización de los procesos.

### Actividad 6

El problema principal fue conseguir la estructura solicitada: el proceso padre debía crear dos hijos y únicamente el segundo hijo debía crear un tercer proceso.

Se solucionó diferenciando correctamente los procesos mediante el valor devuelto por `fork()`, haciendo que solamente el segundo hijo ejecutase el segundo `fork()`.

### Actividad 7

La dificultad principal fue comprender qué ocurre con las variables después de utilizar `fork()`.

Se comprobó que el padre y el hijo trabajan con copias independientes de la variable. Por ello, partiendo de `valor = 6`, el padre puede sumar 5 y obtener 11, mientras que el hijo puede restar 5 y obtener 1, sin modificar el valor del otro proceso.

### Conclusión

Las dificultades encontradas se resolvieron comprendiendo el funcionamiento de `fork()`, diferenciando correctamente el proceso padre y el hijo mediante su valor de retorno y utilizando `wait()` cuando era necesario para controlar la finalización de los procesos.