/*
  Project Name: Simple Arduino Communication Project
  Authors:
      * Filipe Marchesini
      * Thaís Barbosa
  Version: 1.0.0
  Boards Supported:
    * Arduino *
    * NodeMCU
  Dependencies:
    * Bluetooth, 0.22
  Description:
    O código faz a conexão com o arduíno via bluetooth
    e executa funções básicas como ir para frente, ir
    para trás, utilizando as configurações atuais do robô
    (determinadas na penúltima aula 28/06/2017). É possível,
    também, controlar o movimento do arduíno pelo celular.
    
*/

#include <SoftwareSerial.h>

#define ENCODER_DIREITA 2
#define ENCODER_ESQUERDA 3

#define ACELERADOR_DIREITA 5
#define ACELERADOR_ESQUERDA 6

//  Definição das entradas para os motores de cada lado, observem que alguns robôs precisaram ter os pinos trocados devido aos módulos de comunicação que utilizam.
//  Vejam os 4 fios unidos da ponte H que são conectados no Arduino para saberem o padrão do robô que vocês tem em mãos.

#define DIRECAO_DIREITA_1 7   //4
#define DIRECAO_DIREITA_2 8   //7

#define DIRECAO_ESQUERDA_1 9  //8
#define DIRECAO_ESQUERDA_2 10 //9

#define IR_PARA_FRENTE_DIREITA() do { digitalWrite(DIRECAO_DIREITA_1, HIGH); digitalWrite(DIRECAO_DIREITA_2, LOW); } while(false)
#define IR_PARA_FRENTE_ESQUERDA() do { digitalWrite(DIRECAO_ESQUERDA_1, HIGH); digitalWrite(DIRECAO_ESQUERDA_2, LOW); } while(false)
#define IR_PARA_FRENTE() do { IR_PARA_FRENTE_DIREITA(); IR_PARA_FRENTE_ESQUERDA(); } while(false)

#define IR_PARA_TRAS_DIREITA() do { digitalWrite(DIRECAO_DIREITA_1, LOW); digitalWrite(DIRECAO_DIREITA_2, HIGH); } while(false)
#define IR_PARA_TRAS_ESQUERDA() do { digitalWrite(DIRECAO_ESQUERDA_1, LOW); digitalWrite(DIRECAO_ESQUERDA_2, HIGH); } while(false)
#define IR_PARA_TRAS() do { IR_PARA_TRAS_DIREITA(); IR_PARA_TRAS_ESQUERDA(); } while(false)

#define ACELERA_DIREITA(VELOCIDADE) do { pwmDireita = VELOCIDADE; analogWrite(ACELERADOR_DIREITA, VELOCIDADE); } while(false)
#define ACELERA_ESQUERDA(VELOCIDADE) do { pwmEsquerda = VELOCIDADE; analogWrite(ACELERADOR_ESQUERDA, VELOCIDADE); } while(false)
#define ACELERA(VELOCIDADE) do { ACELERA_DIREITA(VELOCIDADE); ACELERA_ESQUERDA(VELOCIDADE); } while(false)

#define FREIO_DIREITA() { ACELERA_DIREITA(0); digitalWrite(DIRECAO_DIREITA_1, LOW); digitalWrite(DIRECAO_DIREITA_2, LOW); } while(false)
#define FREIO_ESQUERDA() { ACELERA_ESQUERDA(0); digitalWrite(DIRECAO_ESQUERDA_1, LOW); digitalWrite(DIRECAO_ESQUERDA_2, LOW); } while(false)
#define FREIO() do { FREIO_DIREITA(); FREIO_ESQUERDA(); } while(false)

// Velocidade armazenada PWM
volatile int pwmDireita = 0;
volatile int pwmEsquerda = 0;

// Numero de passos do Encoder Ótico
volatile int contador_direita = 0;
volatile int contador_esquerda = 0;

// Definir velocidades
int velocidadeDireita  = 50;
int velocidadeEsquerda = 50;

//Definindo pinos conectados ao RX e TX do bluetooth
const int rxpin = 1;
const int txpin = 0;

//Definindo um caractere para ser lido pelo arduíno
char comando = '.';
String motores = "opa opa";

//Conectando...
SoftwareSerial bluetooth(rxpin, txpin);

void setup() {
  
  // Configuração da Comunicação Bluetooth
  bluetooth.begin(9600);

  // Configuração dos pinos da Ponte H
  pinMode(DIRECAO_DIREITA_1, OUTPUT);
  pinMode(DIRECAO_DIREITA_2, OUTPUT);
  pinMode(DIRECAO_ESQUERDA_1, OUTPUT);
  pinMode(DIRECAO_ESQUERDA_2, OUTPUT);

  // Configuração dos pinos do Encoder Ótico
  pinMode(ENCODER_DIREITA, INPUT_PULLUP);
  pinMode(ENCODER_ESQUERDA, INPUT_PULLUP);

  // Funções de Interrupção de cada um dos Encoders
  attachInterrupt(digitalPinToInterrupt(ENCODER_DIREITA), contadorDireita, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_ESQUERDA), contadorEsquerda, CHANGE); 
}

void loop() {
  
  if(bluetooth.available()) {
    comando = bluetooth.read();
    
  }
  
  //Se o caractere n for recebido, então ir para o norte
  else if (comando == 'n') {

    ACELERA_DIREITA(velocidadeDireita);
    ACELERA_ESQUERDA(velocidadeEsquerda);
    IR_PARA_FRENTE();

    motores = "norte";

  }

  //Sul
  else if (comando == 's') {

    ACELERA_DIREITA(velocidadeDireita);
    ACELERA_ESQUERDA(velocidadeEsquerda);
    IR_PARA_TRAS();

    motores = "sul";
    
  }

  //Nordeste
  else if (comando == 'l') {

    ACELERA_DIREITA(velocidadeDireita);
    IR_PARA_FRENTE_DIREITA();

    motores = "nordeste";
    
    }
     
  //Noroeste
  else if (comando == 'o') {

    ACELERA_ESQUERDA(velocidadeEsquerda);
    IR_PARA_FRENTE_ESQUERDA();

    motores = "noroeste";
    
  }
  
  //Sudeste
  else if (comando == 'h') {

    ACELERA_ESQUERDA(velocidadeEsquerda);
    IR_PARA_TRAS_ESQUERDA();

    motores = "sudeste";
    
  }

  //Sudoeste
  else if (comando == 'j') {

    ACELERA_DIREITA(velocidadeEsquerda);
    IR_PARA_TRAS_DIREITA();

    motores = "sudoeste";
    
  }  
  
  //Freio
  else if (comando == 'f') {
    
    FREIO();
      
    }

  //Acelerar 
  else if (comando == 'a') {
    
    if (motores == "norte") {
          
            velocidadeDireita = velocidadeDireita + 10;
            velocidadeEsquerda = velocidadeEsquerda + 10;
            ACELERA_DIREITA(velocidadeDireita);
            ACELERA_ESQUERDA(velocidadeEsquerda);
            IR_PARA_FRENTE();
               
    } 

    if (motores == "sul") {
          
            velocidadeDireita = velocidadeDireita + 10;
            velocidadeEsquerda = velocidadeEsquerda + 10;
            ACELERA_DIREITA(velocidadeDireita);
            ACELERA_ESQUERDA(velocidadeEsquerda);
            IR_PARA_TRAS();
               
    } 

    

    
    if (motores == "nordeste") {
          
            velocidadeDireita = velocidadeDireita + 10;
            ACELERA_DIREITA(velocidadeDireita);
            IR_PARA_FRENTE_DIREITA();
               
    } 
    
    if (motores == "noroeste") {

            velocidadeEsquerda = velocidadeEsquerda + 10;
            ACELERA_ESQUERDA(velocidadeEsquerda);
            IR_PARA_FRENTE_ESQUERDA();
      
    }

    if (motores == "sudeste") {

            velocidadeEsquerda = velocidadeEsquerda + 10;
            ACELERA_ESQUERDA(velocidadeEsquerda);
            IR_PARA_TRAS_ESQUERDA();
      
    }

    if (motores == "sudoeste") {

            velocidadeEsquerda = velocidadeEsquerda + 10;
            ACELERA_DIREITA(velocidadeEsquerda);
            IR_PARA_TRAS_DIREITA();
      
    }

    

    //Se continuar segurando por 0,5 segundo, ele continua acelerando
    delay(500);
      
    }
      
    
    delay(10);
      
    }

void contadorDireita() {
  contador_direita++;
}

void contadorEsquerda() {
  contador_esquerda++;
}
