#include <API_debounce.h>

/**
 * @brief Estados posibles de la máquina de estados para el anti-rebote.
 */
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

static debounceState_t debounceState;
static bool_t key_pressed_flag = false;

static delay_t led_delay;
static tick_t debounceDelay = 100;
static const tick_t debounceDelayRange[] = {100, 500};


/**
 * @brief Inicializa la máquina de estados del anti-rebote.
 * @retval None
 */
void debounceFSM_init()
{
    debounceState = BUTTON_UP;
    if (debounceDelay > 0) {
        delayInit(&led_delay, debounceDelay);
    }
}

/**
 * @brief Actualiza la máquina de estados del anti-rebote para un botón específico.
 *
 * Esta función implementa una MEF (Máquina de Estados Finitos) para gestionar el
 * anti-rebote de un botón. Detecta flancos descendentes válidos (cuando el botón
 * se presiona)
 * y envia los mensajes mediante uart cuando detecta flanco descendente o ascendente
 * @param GPIOx Puerto GPIO al que está conectado el botón.
 * @param GPIO_Pin Pin específico del botón.
 *
*/
void debounceFSM_update(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if (GPIOx == NULL || GPIO_Pin == 0) return;

	switch(debounceState)
	{
		case BUTTON_UP:
			if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
			{
				debounceState = BUTTON_FALLING;
				delayInit(&led_delay, debounceDelay);
			}
			break;

		case BUTTON_FALLING:
			if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
			{
				debounceState = BUTTON_DOWN;
				key_pressed_flag = true;
				delayInit(&led_delay, debounceDelay);
				uartSendString((uint8_t*)"\033[33m");
				uartSendString((uint8_t*)"Flanco descendente detectado \r\n");
				uartSendString((uint8_t*)"\033[0m");

			}
			else
			{
				debounceState = BUTTON_UP;
			}
			break;

		case BUTTON_DOWN:
			if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
			{
				debounceState = BUTTON_RAISING;
				delayInit(&led_delay, debounceDelay);
			}
			break;

		case BUTTON_RAISING:
			if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
			{
				debounceState = BUTTON_UP;
				delayInit(&led_delay, debounceDelay);
				uartSendString((uint8_t*)"\033[34m");
				uartSendString((uint8_t*)"Flanco ascendente detectado \r\n");
				uartSendString((uint8_t*)"\033[0m");
			}
			else
			{
				debounceState = BUTTON_DOWN;
			}
			break;

		default:
			debounceFSM_init();
			break;

	}
}

/**
 * @brief Controla el parpadeo de un LED con cambio de frecuencia mediante un botón.
 * @param GPIOx Puerto GPIO del LED.
 * @param GPIO_Pin Pin GPIO del LED.
 */

void toggle_led(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{

	if (GPIOx == NULL || GPIO_Pin == 0) return;

    if (delayRead(&led_delay)) {
        HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
    }

    if (readKey()) {
  	  debounceDelay = (debounceDelay == 100) ? debounceDelayRange[1] : debounceDelayRange[0];
        delayWrite(&led_delay, debounceDelay);
    }
}

/**
 * @brief Indica si se detectó una pulsación válida del botón (flanco descendente).
 *
 * @return `true` si el botón fue presionado (una sola vez), `false` si no.
 */

bool_t readKey(void) {

    if (key_pressed_flag) {
        key_pressed_flag = false;
        return true;
    }
    return false;
}
