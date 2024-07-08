

#include <Wire.h>                          // Comunicacao I2C com o SI5351
#include "si5351.h"                        // Si5351 library
#include <LiquidCrystal_I2C.h>             // LCD library


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
      String arg = command.substring(command.indexOf(',') + 1); //(Mensagem do Hardware SDR ex:  FREQ,7000000)
      freq = arg.toInt();
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
  lcd.init();
  lcd.backlight();

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
  lcd.print("Faixa:");
  lcd.setCursor(7 , 1);
  lcd.print(faixa); // faixa

}

//================Ajusta a frequencia do modulo SI5351===========================
void SendFrequency()
{
  freqX4 = freq * 4; // Saida do VFO que serah dividida por 4 para formar a quadratura
  setFaixa(); // Ajusta os filtros conforme a faixa de frequencia ( f1 a f8 )
  
  si5351.set_freq_manual(freqX4 * 100ULL, pll_max * 100ULL, SI5351_CLK0); // *100ULL para converter HZ em 0.01 HZ
  showDisplay();
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

}
//=============================loop()=================
void loop() {

  leSerial();

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

  delay(1);

}
