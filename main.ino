#include <Arduino.h>

// Constantes de los pines
const int rele1 = 3;
const int rele2 = 4;
const int rele3 = 5;
const int rele4 = 6;
const int rele5 = 7;

int mi_boton0=13;
int EstadoAnterior_Boton=0;
int EstadoPresente_boton=0;
int contador=0;

const int trigger1 = 8;
const int echo1 = 9;
const int trigger2 = 10;
const int echo2 = 11;

// Constantes para los rangos de color
const int blanco_min = 495;
const int blanco_max = 515;
const int amarillo_min = 538;
const int amarillo_max = 548;
const int azul_min = 620;
const int azul_max = 648;
const int morado_min = 700;
const int morado_max = 715;
const int negro_min = 770;
const int negro_max = 800;

// Variables para controlar los relés
bool rele1_encendido = false;
bool rele2_encendido = false;
bool rele3_encendido = false;
bool rele4_encendido = false;
bool rele5_encendido = false;
unsigned long rele1_tiempo_encendido = 0;
unsigned long rele2_tiempo_encendido = 0;
unsigned long rele3_tiempo_encendido = 0;
unsigned long rele4_tiempo_encendido = 0;
unsigned long rele5_tiempo_encendido = 0;

const unsigned long rele1_encendido_duracion = 5500; // Duración en milisegundos
const unsigned long rele2_encendido_duracion = 3500; // Duración en milisegundos

const unsigned long rele3_encendido_duracion = 2500; // Duración en milisegundos
const unsigned long rele4_encendido_duracion = 4500; // Duración en milisegundos
const unsigned long rele5_encendido_duracion = 4000; // Duración en milisegundos


unsigned long tiempo_caudal =0;

volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor = 2;    //Sensor conectado en el pin 2
float factor_conversion=4.82; //para convertir de frecuencia a caudal

float frecuencia;

//---Función que se ejecuta en interrupción---------------
void ContarPulsos ()
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
} 

//---Función para obtener frecuencia de los pulsos--------

float caudal_L_m;
void caudal(){
  
  caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m

  //-----Enviamos por el puerto serie---------------
 //Serial.print ("FrecuenciaPulsos: "); 
  //Serial.print (frecuencia,0); 
  //Serial.print ("Hz\tCaudal: "); 
  //Serial.print (caudal_L_m,3);
  //Serial.print(","); 
  //Serial.println (" L/m\t");
}

// Función para medir la distancia con el sensor ultrasónico
float medirDistancia(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  float duracion = pulseIn(echoPin, HIGH);
  float distancia = duracion * 0.034 / 2;
  
  return distancia;
}

void encenderRele(int relePin) {
  digitalWrite(relePin, LOW);
}

void apagarRele(int relePin) {
  digitalWrite(relePin, HIGH);
}

void setup() {
  // Configurar pines de salida para relés
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT);

  pinMode(mi_boton0,INPUT);

  // Configurar pines de ultrasonido
  pinMode(trigger1, OUTPUT);
 pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
  
  apagarRele(rele1);
  apagarRele(rele2);
  apagarRele(rele3);
  apagarRele(rele4);
  apagarRele(rele5);

  pinMode(PinSensor, INPUT); 
  attachInterrupt(0,ContarPulsos,RISING); //(Interrupcion 0(Pin2),funcion,Flanco de subida)

  // Iniciar comunicación serial
  Serial.begin(115200);
}


int aux_caudal=1;
int aux_boton=0;
int botonlab=0;
void loop() {
  if (aux_caudal==1){
  NumPulsos = 0;   //Ponemos a 0 el número de puls>=1000o{
  interrupts();   //Habilitamos las interrupciones
  aux_caudal=0;
  }
  if (millis() - tiempo_caudal>=1000){
    noInterrupts(); //Desabilitamos las interrupciones
    frecuencia=NumPulsos; //Hz(pulsos por segundo)
    tiempo_caudal=millis();
    aux_caudal=1;
  }
  
  caudal();
  // Medir la distancia con el primer sensor ultrasónico
  //float distancia1 = 0;//medirDistancia(trigger1, echo1);
  int distancia1 = analogRead(A0);
  int distancia2 = analogRead(A1);

  // Medir la distancia con el segundo sensor ultrasónico
  //float distancia2 = 0;// medirDistancia(trigger2, echo2);



  int caudal_mL_m = caudal_L_m*1000;
  int nivel1 = map(distancia1,93,87,2212,3000);
  int nivel2 = map(distancia2,87,63,2245,3000);


   EstadoPresente_boton = digitalRead(mi_boton0);
    if(!EstadoPresente_boton && EstadoAnterior_Boton)
        {
        contador++;
        aux_boton=1;
        }
    EstadoAnterior_Boton = EstadoPresente_boton; 

  // Leer el valor del pin analógico A0 para detectar el color
  int valorAnalogico = analogRead(A5);
  //Serial.println(valorAnalogico);
  Serial.print("X");
  Serial.print(caudal_mL_m);
  Serial.print("X F");
  Serial.print(nivel2);
  Serial.print("F Y");
  Serial.print(nivel1);
  Serial.print("Y A");
  Serial.print(valorAnalogico);
  Serial.print("A Q");
  Serial.print(botonlab);
  Serial.println("Q");
delay(100);



  if(aux_boton==1){
    botonlab=1;
      // Comprobar los rangos de color y activar el relé correspondiente
      if (valorAnalogico >= blanco_min && valorAnalogico <= blanco_max && !rele1_encendido) {
       // Serial.println("Tarjeta blanca detectada.");
        encenderRele(rele1);
        rele1_encendido = true;
        rele1_tiempo_encendido = millis();
      } else if (valorAnalogico >= amarillo_min && valorAnalogico <= amarillo_max && !rele2_encendido) {
        //Serial.println("Tarjeta amarilla detectada.");
        encenderRele(rele2);
        rele2_encendido = true;
        rele2_tiempo_encendido = millis();
      } else if (valorAnalogico >= azul_min && valorAnalogico <= azul_max && !rele3_encendido) {
        //Serial.println("Tarjeta azul detectada.");
        encenderRele(rele3);
        rele3_encendido = true;
        rele3_tiempo_encendido = millis();
      } else if (valorAnalogico >= morado_min && valorAnalogico <= morado_max && !rele4_encendido) {
        //Serial.println("Tarjeta morada detectada.");
        encenderRele(rele4);
        rele4_encendido = true;
        rele4_tiempo_encendido = millis();
      } else if (valorAnalogico >= negro_min && valorAnalogico <= negro_max && !rele5_encendido) {
        //Serial.println("Tarjeta negra detectada.");
        encenderRele(rele5);
        rele5_encendido = true;
        rele5_tiempo_encendido = millis();
      }
      aux_boton=0;
  } 
  // Apagar los relés después de la duración establecida
  if (rele1_encendido && millis() - rele1_tiempo_encendido >= rele1_encendido_duracion) {
    apagarRele(rele1);
    rele1_encendido = false;
    botonlab=0;
  }
  if (rele2_encendido && millis() - rele2_tiempo_encendido >= rele2_encendido_duracion) {
    apagarRele(rele2);
    rele2_encendido = false;
    botonlab=0;
  }
  if (rele3_encendido && millis() - rele3_tiempo_encendido >= rele3_encendido_duracion) {
    apagarRele(rele3);
    rele3_encendido = false;
    botonlab=0;
  }
  if (rele4_encendido && millis() - rele4_tiempo_encendido >= rele4_encendido_duracion) {
    apagarRele(rele4);
    rele4_encendido = false;
    botonlab=0;
  }
  if (rele5_encendido && millis() - rele5_tiempo_encendido >= rele5_encendido_duracion) {
    apagarRele(rele5);
    rele5_encendido = false;
    botonlab=0;
  }
}

