# Practica 01

**Punto 1**

Implementar un programa que haga parpadear el led de la placa NUCLEO-F446RE LD2.
El led debe permanecer encendido 200 ms con duty cycle 50%.

```	 
HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	 HAL_Delay(200);
```
**Punto 2**

Utilizar el pulsador (B1) para controlar el tiempo de encendido.  Cada vez que se presiona el pulsador el tiempo de encendido debe alternar entre 200 ms y 500 ms.


```	  
if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 0)
	  {
		  HAL_Delay(200);
		  up_time = (up_time == 200) ? 500 : 200;
	  }

 	 HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
 	 HAL_Delay(up_time);
```

**Algunas preguntas para pensar el ejercicio**

 `¿De qué serviría usar un array de “tiempos” en el programa? ¿Qué pasa con nuestro programa si nos piden agregar/sacar/cambiar un tiempo de encendido?`

 ```
    Podríamos tener una series de valores predefinidos y cada vez que se quiera aumentar o disminuir el tiempo simplemente recorreriamos el array. Esto tiene otro tipo de ventajas como:
        - Mayor orden y legibilidad de nuestro código, por ejemplo no tener una variable para cada tiempo que vatamos a user y si queremos hacer un cambio de tiempo simplemente cambiamos el array y no alteraria la logica del promgrama
 ```

 `¿Cómo responde el programa a las pulsaciones, hay falsos positivos o pulsaciones no detectadas?`

 ```
    Si hay pulsaciones que no son detectadas y tambien flasos positivos en los siguientes casos en esta implementación:
        - Si se pulsa el botón rapidamente puede un pulsación no ser detectada.
        - Si se pulsa el botón en un momento no oportuno tambien ingnora la pulsación
    
    Para que este comportamiento sea corregido sería usar el antirrebote y leer un estado del botón o cierto flanco como una pulsación valida pero esto generaría un DELAY bloquente y basicamente estariamos en un lectura por polling según lo visto en clase de Protocolos de comunicación 
```
 `¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar el led? ¿Qué diferencia hay entre estas alternativas?`

 ```
    Opción 1: Hace que se el comportamiento del LED de mas legible, a diferencia de la opción 2 que, el comportamiento del led se verá afectado después de que este se apaque o se enciend haciendo confuso su funcionamiento y aparte si el tiempo es muy largo puede que existan pulsaciones y no sean leidas.

    Opción 2: Nos aseguramos que la lectura del pulsador ocurra en un tiempo controlado. A diferencia de la opción 1 que pueden haber pulsaciones no leidas o falsos positivos.


    Si el tiempo es controlado el mejor momento para leer sería la opción 2.
 ```

 `¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido del led fuera sensiblemente más grande, 2 segundos por ejemplo? ¿Y si fuera  sensiblemente más chico, 50 ms por ejemplo?`

 ```
    Si, si es mucho más largo o más chico la opción sería la 1.
    Como mencioné antes si el tiempo es más grande no habrán pulsaciones que no se tomarán en cuenta. Si es muy pequeño el tiempo no se que estado del botón pueda leer.
 ```
