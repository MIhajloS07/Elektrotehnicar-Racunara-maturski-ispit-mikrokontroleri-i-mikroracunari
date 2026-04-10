// Dodajemo standardnu biblioteku za rad sa step motorima
#include <Stepper.h>
#include <TimerOne.h>

// Pinovi ULN2003 kontrolera (kako je kontroler povezan sa mikrokontrolerom)
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

// Broj koraka po jednom obrtaju motora
const int KoraciPoObr = 2048;  // (na osnovu specifikacija step motora)

// Kreiranje i inicijalizacija Stepper objekta mojStpMot sa datim pinovima
Stepper mojStpMot(KoraciPoObr, IN1, IN3, IN2, IN4);
const int PinTastera = 2;                  // pin na koji je povezan taster
const int PinPotenciometra = A0;           // pin potenciometra
const unsigned long timerPeriod = 500000;  // perioda tajmera u ms -> 0.5s
int ADVrednost;                            // vrednost na analognom ulazu (rezultat AD konverzije)
volatile boolean ukljucen = false;         // stanje motora: da li je ukljucen ili nije
const int minRazmak = 2, maxRazmak = 10;   // minimalni i maksimalni razmak u ms

void TasterISR() {
  // servisna rutina prekida (ISR), koja se izvrsava
  // svaki put kada se detektuje pritisak tastera na pinu PinTastera
  ukljucen = !ukljucen;  // menjamo vrednost globalne promenljive ukljucen
}

void TimerISR() {
  // Ispis brzine step motora u procentima
  Serial.print("Brzina: ");
  if (ukljucen) {
    ADVrednost = analogRead(PinPotenciometra);        //uzima se vrednost sa analognog ulaza...
    Serial.print(map(ADVrednost, 0, 1023, 20, 100));  // mapiranje vrednosti sa potenciometra u procente brzine -> 20-100%)
  } else {
    Serial.print(0);
  }
  Serial.println("%");
}

void setup() {
  // inicijalizacija ulaznog pina sa internim Pull-Up otpornikom
  pinMode(PinTastera, INPUT_PULLUP);
  // Aktiviranje interapta na pinu PinTastera, sa prek rutinom TasterISR
  attachInterrupt(digitalPinToInterrupt(PinTastera), TasterISR, FALLING);
  // Inicijalizacija serijske komunikacije sa racunarom na 9600 bps
  Serial.begin(9600);
  Timer1.initialize(timerPeriod);
  Timer1.attachInterrupt(TimerISR);
}

void loop() {
  if (ukljucen) {
    mojStpMot.step(1);  // motor pravi jedan korak
    delay(map(ADVrednost, 0, 1023, maxRazmak, minRazmak));
  }
}