# Arduino RC Car con NRF24L01 y SoftPWM
Este proyecto implementa el sistema de control para un vehículo a control remoto utilizando comunicación por radiofrecuencia y modulación por ancho de pulso por software (SoftPWM). El sistema permite el movimiento multidireccional, rotación sobre el eje y la activación de un actuador externo.
## Descripción general
* Comunicación Inalámbrica: Utiliza la banda de 2.4GHz mediante el módulo nRF24L01.
* Configuración de Radio: Opera en el canal 80 con una tasa de datos de 250KBPS y nivel de potencia bajo (RF24_PA_LOW).
* Control de Motores: Implementado mediante SoftPWM en los pines 2, 3, 4 y 5.
* Seguridad (Fail-safe): El sistema incluye una rutina de reinicio de datos que se activa si no se recibe señal durante más de 1000 milisegundos, deteniendo el vehículo por seguridad.

