

/*
 * Codificado por Rubens Hubner Junior PY2 RHJ ID DMR:7245251
 * 
 * Este codigo comanda o modulo SI5351 com o arduino nano via protocolo I2C
 * A frequencia de saida do modulo SI5351 deve ser 4 vezes a frequencia desejada pois serah divida por 4 
 * para obter a quadratura.
 * O Arduino nano recebe a informacao da frequencia desejada atraves da porta serial ou do encoder
 * Os paramentros sao visualizados no display LCD
 * Tem 08 saidas (0 5V) para usar na selecao de filtros conforme a faixa.
 * Tem uma entrada para acionamento do PTT e a uma saida logica TTL para comutacao RX/TX.
 * 
 */

#include <Wire.h>                          // Comunicacao I2C com o SI5351
#include "si5351.h"                        // Si5351 library
#include <LiquidCrystal_I2C.h>             // LCD library

#define encoder0PinA  2
#define encoder0PinB  3
#define tunestep   A2

unsigned long time_now = 0;// Tempo decorrido do programa ligado em milissegundos
unsigned long time1 = 0;
unsigned long time2 = 0;


static const uint32_t bandStart = 3000000;     // Inicio da banda em HF (HZ)
static const uint32_t bandEnd =   30000000;    // Fim da banda HF (HZ)
static const uint32_t pll_min =   600000000;     //Frequencia minima do PLL (HZ)
static const uint32_t pll_max =   900000000;     //Frequencia maxima do PLL (HZ)

int faixa = 1;

const int f1 = 4;
const int f2 = 5;
const int f3 = 6;
const int f4 = 7;
const int f5 = 8;
const int f6 = 9;
const int f7 = 10;
const int f8 = 11;
const int ptt_out = 12;


volatile uint32_t oldfreq = 0;
volatile uint32_t freq = 7000000 ;
volatile uint32_t freqX4 = 28000000 ; // Frequencia multiplicada por 4 para usar o divisor
volatile uint32_t freqStep = 1000 ;// Frequencia do Step em HZ


volatile int lastEncoded = 0;

const int lcdColumns = 16;
const int lcdRows = 2;

Si5351 si5351;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

//================Leitura da porta serial=========================

void leSerial()
{
  if (Serial.available())
  {
    String command = Serial.readString();
    Serial.print("Info da Serial:");
    Serial.println(command);
    command.toUpperCase();

    if (command.startsWith("FREQ"))
    {
      String arg = command.substring(command.indexOf(',') + 1); //(Mensagem do Software SDR ex:  FREQ,7000000)
      freq = arg.toInt(); // Frequencia em Hz
      Serial.println((long int)freq);
    }
  }
}
//===========Ajusta a faixa conforme a frequencia================================
void setFaixa()
{
  if (freq >= 3000000 && freq < 6000000)
  {
    faixa = 1;
    digitalWrite(f1, HIGH);
    digitalWrite(f2, LOW);
    digitalWrite(f3, LOW);
    digitalWrite(f4, LOW);
    digitalWrite(f5, LOW);
    digitalWrite(f6, LOW);
    digitalWrite(f7, LOW);
    digitalWrite(f8, LOW);
  }
  if (freq >= 6000000 && freq < 9000000)
  {
    faixa = 2;
    digitalWrite(f1, LOW);
    digitalWrite(f2, HIGH);
    digitalWrite(f3, LOW);
    digitalWrite(f4, LOW);
    digitalWrite(f5, LOW);
    digitalWrite(f6, LOW);
    digitalWrite(f7, LOW);
    digitalWrite(f8, LOW);
  }
  if (freq >= 9000000 && freq < 12000000)
  {
    faixa = 3;
    digitalWrite(f1, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(f3, HIGH);
    digitalWrite(f4, LOW);
    digitalWrite(f5, LOW);
    digitalWrite(f6, LOW);
    digitalWrite(f7, LOW);
    digitalWrite(f8, LOW);
  }
  if (freq >= 12000000 && freq < 18000000)
  {
    faixa = 4;
    digitalWrite(f1, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(f3, LOW);
    digitalWrite(f4, HIGH);
    digitalWrite(f5, LOW);
    digitalWrite(f6, LOW);
    digitalWrite(f7, LOW);
    digitalWrite(f8, LOW);
  }
  if (freq >= 18000000 && freq < 21000000)
  {
    faixa = 5;
    digitalWrite(f1, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(f3, LOW);
    digitalWrite(f4, LOW);
    digitalWrite(f5, HIGH);
    digitalWrite(f6, LOW);
    digitalWrite(f7, LOW);
    digitalWrite(f8, LOW);
  }
  if (freq >= 21000000 && freq < 24000000)
  {
    faixa = 6;
    digitalWrite(f1, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(f3, LOW);
    digitalWrite(f4, LOW);
    digitalWrite(f5, LOW);
    digitalWrite(f6, HIGH);
    digitalWrite(f7, LOW);
    digitalWrite(f8, LOW);
  }
  if (freq >= 24000000 && freq < 27000000)
  {
    faixa = 7;
    digitalWrite(f1, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(f3, LOW);
    digitalWrite(f4, LOW);
    digitalWrite(f5, LOW);
    digitalWrite(f6, LOW);
    digitalWrite(f7, HIGH);
    digitalWrite(f8, LOW);
  }
  if (freq >= 27000000 && freq < 31000000)
  {
    faixa = 8;
    digitalWrite(f1, LOW);
    digitalWrite(f2, LOW);
    digitalWrite(f3, LOW);
    digitalWrite(f4, LOW);
    digitalWrite(f5, LOW);
    digitalWrite(f6, LOW);
    digitalWrite(f7, LOW);
    digitalWrite(f8, HIGH);
  }

}

//==================Mostrar no Display===============
void showDisplay()
{
  

  lcd.setCursor(0, 0);
  lcd.print("                "); // Apaga a linha superior
  lcd.setCursor(0, 0);
  lcd.print(freq / 1000); // frequencia em KHZ
  lcd.setCursor(6, 0);
  lcd.print("Khz");
  lcd.setCursor(11, 0);
  lcd.print("OUT");


  lcd.setCursor(0, 1);
  lcd.print("                "); // Apaga a linha inferior
  lcd.setCursor(0, 1);
  lcd.print("FX:");
  lcd.setCursor(3 , 1);
  lcd.print(faixa); // faixa

  lcd.setCursor(5, 1);
  lcd.print("STP:");
  lcd.setCursor(9 , 1);
  lcd.print(freqStep / 1000); // Frequencia do Step

  lcd.setCursor(13, 1);
  lcd.print("Khz");

}

//================Ajusta a frequencia do modulo SI5351===========================
void SendFrequency()
{
  freqX4 = freq * 4; // Saida do VFO que serah dividida por 4 para formar a quadratura
  setFaixa(); // Ajusta os filtros conforme a faixa de frequencia ( f1 a f8 )
  showDisplay();
  si5351.set_freq_manual(freqX4 * 100ULL, pll_max * 100ULL, SI5351_CLK0); // *100ULL para converter HZ em 0.01 HZ

}

//====================Interrupcao do Encoder=========================
void serviceEncoderInterrupt()
{
  int signalA = digitalRead(encoder0PinA); //Leitura do pino canal A
  int signalB = digitalRead(encoder0PinB); //Leitura do pino canal B

  int encoded = (signalB << 1) | signalA;  // Converte valores dois pinos em um unico numero
  int sum  = (lastEncoded << 2) | encoded; // Adiciona ao valor previo ( antes da nova posicao do Encoder )

  if (sum == 0b0111 || sum == 0b1110 || sum == 0b1000 || sum == 0b0001)// Encoder sentido Horario (Codigo gray)
  {
    if (freq < bandEnd && (time_now - time2) > 10)// Freq. menor que o fim da banda e aguarda tempo para atender nova interrupcao
    {
      freq = freq + freqStep; // Incrementa frequencia conforme Step selecionado
      time2 = time_now;// Remove a diferenca entre as variaveis para reiniciar a temporizacao
    }
  }
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)// Encoder sentido AntiHorario (Codigo gray)
  {
    if (freq > bandStart && (time_now - time2) > 10 )// Freq. maior que o inicio da banda e e aguarda tempo para atender nova interrupcao
    {
      freq = freq - freqStep; // Decrementa a frequencia conforme Step selecionado
      time2 = time_now;// Remove a diferenca entre as variaveis para reiniciar a temporizacao
    }
  }
  lastEncoded = encoded; // Guarda o valor para a proxima alteracao
}

//=================Ajuste do Step================================

void setStep()
{
  if (freqStep == 1000)
  {
    freqStep = 10000; // Step de 10 Khz
    showDisplay();
    Serial.println(freqStep);
    return;
  }
  if (freqStep == 10000)
  {
    freqStep = 100000; // Step de 100 Khz
    showDisplay();
    return;
  }
  if (freqStep == 100000)
  {
    freqStep = 1000000; // Step de 1000 Khz
    showDisplay();
    return;
  }
  if (freqStep == 1000000)
  {
    freqStep = 1000; // Step de 1000 Khz
    showDisplay();
    return;
  }

}

//=================================setup()======================
void setup() {

  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  if (si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0)) // Cristal 25 MHZ
  {
    Serial.println("SI5351 encontrado");
  }
  else
  {
    Serial.println("SI5351 Nao encontrado");
  }

  si5351.output_enable(SI5351_CLK0, 1);
  si5351.output_enable(SI5351_CLK1, 0);
  si5351.output_enable(SI5351_CLK2, 0);
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA);
  si5351.update_status();

  pinMode(f1, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(f3, OUTPUT);
  pinMode(f4, OUTPUT);
  pinMode(f5, OUTPUT);
  pinMode(f6, OUTPUT);
  pinMode(f7, OUTPUT);
  pinMode(f8, OUTPUT);
  pinMode(ptt_out, OUTPUT);

  digitalWrite(f1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(f3, LOW);
  digitalWrite(f4, LOW);
  digitalWrite(f5, LOW);
  digitalWrite(f6, LOW);
  digitalWrite(f7, LOW);
  digitalWrite(f8, LOW);
  digitalWrite(ptt_out, LOW);

  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(tunestep, INPUT);

  attachInterrupt(0, serviceEncoderInterrupt, CHANGE);
  attachInterrupt(1, serviceEncoderInterrupt, CHANGE);
}
//=============================loop()=================
void loop() {

  time_now = millis();
  if (time1 > time_now) time1 = time_now; // Overflow da variavel time_now
  if (time2 > time_now) time2 = time_now; // Overflow da variavel time_now

  leSerial();

  if (digitalRead(tunestep) == LOW && (time_now - time1) > 500 ) // Botao do encoder clicado
  {
    setStep(); // Ajusta a frequencia do Step que o encoder irah aplicar
    time1 = time_now;
  }

  if (freq != oldfreq)
  {
    if (freq <= bandEnd && freq >= bandStart) // A frequencia esta dentro da banda (3MHZ a 30MHZ)
    {
      SendFrequency();
      oldfreq = freq;
    }
    else
    {
      Serial.println("Frequencia fora da faixa");
      Serial.println("Mantendo o valor anterior");
      freq = oldfreq;
    }

  }


}
