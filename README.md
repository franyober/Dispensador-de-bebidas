# Dispensador-de-bebidas
Prototipo capaz de servir cinco bebidas diferentes; la selección se hace al presentar una tarjeta de color frente a un detector LED blanco + LDR. Un Arduino Uno procesa la lectura, abre la electroválvula adecuada el tiempo justo para llenar un vaso de 7 oz y remite en serie los datos a una interfaz LabVIEW que permite supervisar niveles, caudal y temperatura en tiempo real.

## Hardware

| Subsistema             | Componentes clave                                                | Imagen sugerida                              |
| ---------------------- | ---------------------------------------------------------------- | -------------------------------------------- |
| **Detección de color** | LED blanco, LDR y divisor de voltaje encapsulados                | ![image](https://github.com/user-attachments/assets/bbef1be0-bf9e-4d08-b940-5b1988194311)|
| **Tarjetas**           | Negro, Morado, Azul, Amarillo, Blanco                            | ![image](https://github.com/user-attachments/assets/8f66669c-9439-4a26-8561-1daaf1ef9b55)|
| **Control de flujo**   | 5 × Electroválvulas 12 V                                         |![image](https://github.com/user-attachments/assets/9f16b3df-d9a1-47f7-a5bf-120f31a06f1e)|
| **Control de flujo**   | 5 × relés FL-3FFF-S-Z                                            |![image](https://github.com/user-attachments/assets/e24d7aff-3cfb-45d5-9b6e-df278ac745cc)|
| **Medición de caudal** | Caudalímetro YF-S201 (sensor Hall)                               | ![image](https://github.com/user-attachments/assets/ea19edd3-01a6-4afb-9628-2a447ff55b52)|
| **Medición de nivel**  | Sensores ultrasónicos analógicos US-016 en dos tanques (0 – 3 L) | ![image](https://github.com/user-attachments/assets/b3fc1f85-84a7-4d69-a06a-8b3a81905df9)|
| **Temperatura**        | Controlador Omron TC4S                                           | ![image](https://github.com/user-attachments/assets/e924deb3-26c2-4866-83e9-a24b19101165)|
| **Temperatura**        | Termocupla tipo K2M                                              | ![image](https://github.com/user-attachments/assets/7a23945f-3ac0-45ee-9c5b-96566fa8fd84)|
| **Estructura**         | Estructura de madera general                                     | ![image](https://github.com/user-attachments/assets/c8368047-95f5-4694-bde6-15934d8f5c7e)|


## Interfaz LabView

![image](https://github.com/user-attachments/assets/15f23f33-df97-43dd-95c2-3c1db115a722)


## Flujo de operación

* Inserción de tarjeta: el valor ADC se compara con ventanas pre-calibradas (Blanco 495-515, Amarillo 538-548, Azul 620-648, Morado 700-715, Negro 770-800). 

* Confirmación con botón; el Arduino activa el relé asignado y abre la válvula entre 2 500 ms y 5 500 ms según la bebida. 

* Usando interrupciones se cuentan los pulsos del YF-S201; caudal (L/min) = frecuencia / 4.82, factor obtenido por calibración. 

* Cada segundo se transmiten los campos X<caudal> F<nivel2> Y<nivel1> A<ADC> Q<flag> a LabVIEW, que actualiza gráficas y medidores en vivo. 

* Dos hilos lógicos independientes garantizan que el muestreo de sensores no se vea afectado por los retardos del llenado.
