# Dispensador-de-bebidas
Prototipo capaz de servir cinco bebidas diferentes; la selección se hace al presentar una tarjeta de color frente a un detector LED blanco + LDR. Un Arduino Uno procesa la lectura, abre la electroválvula adecuada el tiempo justo para llenar un vaso de 7 oz y remite en serie los datos a una interfaz LabVIEW que permite supervisar niveles, caudal y temperatura en tiempo real.

## Hardware

| Subsistema             | Componentes clave                                                | Imagen sugerida                              |
| ---------------------- | ---------------------------------------------------------------- | -------------------------------------------- |
| **Detección de color** | LED blanco, LDR y divisor de voltaje encapsulados                | ![image](https://github.com/user-attachments/assets/bbef1be0-bf9e-4d08-b940-5b1988194311)|
| **Tarjetas**           | Negro, Morado, Azul, Amarillo, Blanco                            | ![image](https://github.com/user-attachments/assets/8f66669c-9439-4a26-8561-1daaf1ef9b55)|
| **Control de flujo**   | 5 × Electroválvulas 12 V + relés FL-3FFF-S-Z                     |![image](https://github.com/user-attachments/assets/9f16b3df-d9a1-47f7-a5bf-120f31a06f1e)|
| **Medición de caudal** | Caudalímetro YF-S201 (sensor Hall)                               | ![image](https://github.com/user-attachments/assets/ea19edd3-01a6-4afb-9628-2a447ff55b52)|
| **Medición de nivel**  | Sensores ultrasónicos analógicos US-016 en dos tanques (0 – 3 L) | ![image](https://github.com/user-attachments/assets/b3fc1f85-84a7-4d69-a06a-8b3a81905df9)|
| **Temperatura**        | Termocupla tipo K + controlador Omron TC4S                       | ![image](https://github.com/user-attachments/assets/e924deb3-26c2-4866-83e9-a24b19101165)|
| **Estructura**         | Bastidor de madera, tanques elevados, mangueras estancas         | ![image](https://github.com/user-attachments/assets/c8368047-95f5-4694-bde6-15934d8f5c7e)|



