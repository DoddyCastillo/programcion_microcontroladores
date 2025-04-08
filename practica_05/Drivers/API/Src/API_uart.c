/*
 * API_uart.c
 *
 *  Created on: Apr 3, 2025
 *      Author: doddy
 */


#include "API_uart.h"
#include <string.h>

#define UART_TIMEOUT 100
#define UART_MAX_SIZE 1024

static UART_HandleTypeDef huart2;

static bool_t checkPointer(const uint8_t *ptr);
static bool_t checkSize(uint16_t size);


/**
 * @brief Inicializa la UART2 con parámetros definidos.
 *
 * Configura la UART a 115200 baudios, 8 bits de datos, sin paridad,
 * 1 bit de parada y sin control de flujo.
 *
 * @retval true si la inicialización fue exitosa, false si hubo error.
 */

bool_t uartInit(void)
{
	  huart2.Instance = USART2;
	  huart2.Init.BaudRate = 115200;
	  huart2.Init.WordLength = UART_WORDLENGTH_8B;
	  huart2.Init.StopBits = UART_STOPBITS_1;
	  huart2.Init.Parity = UART_PARITY_NONE;
	  huart2.Init.Mode = UART_MODE_TX_RX;
	  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	  if (HAL_UART_Init(&huart2) != HAL_OK)
	  {
		  return false;
	  }

	  else
	  {
		  const char *msg = "Uart inicializada a 115200, 8N1\r\n";

		  HAL_UART_Transmit(&huart2, (uint8_t *) msg , strlen(msg), HAL_MAX_DELAY);

		  return true;
	  }

	  return false;

}

/**
 * @brief Envía un string completo por UART hasta el carácter nulo '\0'.
 *
 * @param pstring Puntero al string a enviar.
 */

void uartSendString(uint8_t * pstring)
{
    if (!checkPointer(pstring)) return;

    uint16_t length = strlen((char*)pstring);

    if (!checkSize(length)) return;

    HAL_UART_Transmit(&huart2, pstring, length, UART_TIMEOUT);
}

/**
 * @brief Envía una cantidad específica de bytes por UART.
 *
 * @param pstring Puntero al buffer que contiene los datos.
 * @param size Cantidad de bytes a enviar.
 */

void uartSendStringSize(uint8_t * pstring, uint16_t size)
{
    if (!checkPointer(pstring) || !checkSize(size)) return;

    HAL_UART_Transmit(&huart2, pstring, size, UART_TIMEOUT);
}

/**
 * @brief Recibe una cantidad fija de bytes desde UART.
 *
 * Función bloqueante que espera hasta recibir 'size' bytes.
 *
 * @param pstring Puntero al buffer de destino.
 * @param size Cantidad de bytes a recibir.
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
	if (!checkPointer(pstring) || !checkSize(size)) return;

	HAL_UART_Receive(&huart2, pstring, size, UART_TIMEOUT);
}

/**
 * @brief Verifica si un puntero es válido (no NULL).
 *
 * @param ptr Puntero a verificar.
 * @return true si es válido, false si es NULL.
 */

static bool_t checkPointer(const uint8_t *ptr)
{
	return (ptr != NULL);
}

/**
 * @brief Verifica si un tamaño es válido (rango razonable).
 *
 * @param size Tamaño a verificar.
 * @return true si está en el rango permitido, false si no.
 */
static bool_t checkSize(uint16_t size)
{
	return (size > 0 && size <= UART_MAX_SIZE);
}
