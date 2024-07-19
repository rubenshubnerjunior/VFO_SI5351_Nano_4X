


/******************************************************************************
 Este codigo recebe mensagem com o protocolo I2C  e envia na porta serial para monitoracao
 em algum terminal.
 Esta embarcado em um arduino Nano e eh usado para debugar o programa do cat11.ino porque
 a porta serial do arduino que trabalha com o cat11.ino estah sendo usada para receber mensagens
 do HDSDR via Omni-rig para controle do VFO.
******************************************************************************/

// Inclusão da biblioteca
#include <Wire.h> // Biblioteca nativa do core Arduino

// Variáveis globais
const int myAddress = 0x08; // armazena o endereço deste dispositivo (slave)

void setup() {
  Serial.begin(115200);  // Configura a taxa de transferência em bits por
  //                        segundo (baud rate) para transmissão serial.
  Serial.println();

  Wire.begin(myAddress); // inicia o dispositivo com o endereço definido anteriormente
  Wire.onReceive(receiveEvent); //registra o evento de recebimento de mensagem
  Serial.println("Software do arduino MEGA");
}

void loop() {}

void receiveEvent(int howMany) {
  String message = readString();
  Serial.print(message); // imprime a mensagem recebida
}

String readString() {
  String retorno;  
  while (Wire.available()) { // Enquanto houver bytes disponíveis para leitura, ...
    char c = Wire.read(); // recebe o byte como caractere
    retorno += c;
  }
  return retorno;
}+
