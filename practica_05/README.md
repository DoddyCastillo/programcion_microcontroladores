# Practica 05

**Autor**
Doddy Joel Castillo Caicedo

**Objetivo de la practica**

Implementar un módulo de software para utilizar la UART. 

**Punto 1**

Implementar un módulo de software en un archivos fuente API_uart.c con su correspondiente archivo de cabecera API_uart.h
```	
bool_t uartInit();

void uartSendString(uint8_t * pstring);

void uartSendStringSize(uint8_t * pstring, uint16_t size);

void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
```	


**Punto 2**

Implementar un programa que utilice el módulo de uart implementado por ustedes para informar al usuario cuando se producen los flancos ascendentes y descendentes.

```	
“Flanco ascendente/descendente detectado”
```	