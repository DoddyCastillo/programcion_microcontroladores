# Practica 02

**Autor**
Doddy Joel Castillo Caicedo

**Objetivo de la practica**

Realizar la implementación de un retardo no bloqueante

**Punto 1**

En el archivo main.h se encuentra las declaraciones de las funciones, las estructuras de datos y constantes.
Tambien se incluyeron las librerias:
```	 
#include<stdlib.h>
#include <stdbool.h>
```	 
Para hacer uso de tipos de datos:
```
typedef uint32_t tick_t;
typedef bool bool_t;
```
Declaración de la funcion delayInit

```
/**
  * @brief Inicializa la estructua de retardo con la duración incial especificada
  * @param delay_t puntero a la estructura delay_t
  * @param duration Duración del retardo en milisegundos
  * @retval None
  */

void delayInit( delay_t * delay, tick_t duration ){

	if(delay != NULL && duration > 0 )
	{
		delay->duration = duration;
		delay->running = false;
	}
}
```
Declaración de la funcion delayRead
```
/**
  * @brief Lee el estado del retardo (running) y verficia si el tiempo se ha cumplido
  * @param delay_t puntero a la estructura delay_t
  * @retval true si el retardo ha finalizado, false caso contrario
  */

bool_t delayRead( delay_t * delay ){

	if(delay == NULL) return false;

	if(!delay->running)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	if((HAL_GetTick() - delay->startTime) >= delay->duration)
	{
		delay->running = false;
		return true;
	}

	return false;
}
```

Declaración de la funcion delayWrite

```
/**
 * @brief Modifica la duración de un retardo existente
 * @param delay puntero a la estructura delay_t
 * @param duration nueva duración del retardo en milisegundos
 * @retval None
 */

void delayWrite( delay_t * delay, tick_t duration ){
	if(delay != NULL && duration > 0)
	{
		delay->duration = duration;
	}
}

```

**Punto 2**

Uso del retardo no bloqueante, donde LED_TOGGLE_DELAY_MS esta seteado a 100ms
```
	  if(delayRead(&led_delay))
	  {
		  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		  delayWrite(&led_delay, LED_TOGGLE_DELAY_MS);
	  }
```
**Punto 3**

Parpadear el led de la placa con el siguiente patrón:
```
5 veces con período 1 segundo y ciclo de trabajo 50%.
5 veces con período 200 ms y ciclo de trabajo 50%.
5 veces con período 100 ms y ciclo de trabajo 50%. 
```
Utilizar un vector o arreglo para definir el patrón y cambiar los tiempos de parpadeo.

```
    const tick_t blink_patterns[PATTERN_STEPS] = {1000, 200, 100};
    uint8_t pattern_index = 0;
    uint8_t repetition_count = 0;
    bool led_state = false;

    if (delayRead(&led_delay)) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        led_state = !led_state;

        if (!led_state) {
            repetition_count++;

            if (repetition_count >= REPETITIONS_PER_STEP) {
                repetition_count = 0;
                pattern_index++;

                if (pattern_index >= PATTERN_STEPS) {
                    pattern_index = 0;
                }
            }
        }
        delayWrite(&led_delay, blink_patterns[pattern_index] / 2);
    }

```
**Nota**

Al ejecutar el proyecto en la consola aparecerá warning de variables
que han sido declaradas pero no usadas, se debe a que la implementación del punto 3
esta comentada
