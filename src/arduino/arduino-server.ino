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
    Um simples robô que recebe solicitações dos tipos Get e Set para 
    modificar ou consultar valores de pinos do Arduino ou de um vetor
    de inteiros.
*/

void setup () { 
  Serial.begin(9600);

}
