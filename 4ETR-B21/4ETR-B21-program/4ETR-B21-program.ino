#include <TimerOne.h>

const int PinGrejaca = 12;      // pin crvene diode
const int PinVentilatora = 11;  // pin zelene diode
const int PinSenzoraTemp = A0;  // pin potenciometra

volatile int ADVrednost;                 // vrednost na analognom ulazu (rezultat AD konverzije)
volatile float Napon, temperatura;       // Napon koji se računa na osnovu ADVrednosti i temperatura

int statusGrejaca = LOW, statusVentilatora = LOW;
const unsigned long TimerPeriod = 200000;

void TimerISR(){
  ADVrednost = analogRead(PinSenzoraTemp);  //uzima se vrednost sa analognog ulaza...
  Napon = ADVrednost * (5.0 / 1023);        // i na osnovu toga računa se napon
  temperatura = Napon / 0.05 - 10;          // racunanje temperature po datoj formuli
}

void setup() {
  // Inicijalizacija pina grejaca i ventilatora
  pinMode(PinGrejaca, OUTPUT);
  pinMode(PinVentilatora, OUTPUT);
  // Početne vrednosti izlaznih pinova
  digitalWrite(PinGrejaca, LOW);
  digitalWrite(PinVentilatora, LOW);
  // Inicijalizacija serijske komunikacije sa racunarom na 9600 bps
  Serial.begin(9600);
  // Inicijalizacija tajmera 
  Timer1.initialize(TimerPeriod);
  Timer1.attachInterrupt(TimerISR);
}

void loop() {
  // ispis napona i temperature preko serijskog monitora na računaru
  Serial.print("Napon: ");
  Serial.print(Napon);
  Serial.println("V");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  // Logika grejaca
  if (temperatura < 25.0) {
    statusVentilatora = LOW;
    if (temperatura < 20.0) 
      statusGrejaca = HIGH;
  }
  else {
    statusGrejaca = LOW;
    if (temperatura > 30.0) 
      statusVentilatora = HIGH;
  }
  digitalWrite(PinGrejaca, statusGrejaca);
  digitalWrite(PinVentilatora, statusVentilatora);
}