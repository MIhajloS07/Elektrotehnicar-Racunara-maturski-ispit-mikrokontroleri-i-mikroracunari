#include <Stepper.h>  // standardna biblioteka za rad sa step motorima

// Pinovi ULN2003 kontrolera (kako je kontroler povezan sa mikrokontrolerom)
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

// Broj koraka po jednom obrtaju motora
const int KoraciPoObr = 2048;  // (na osnovu specifikacija step motora)

// Kreiranje i inicijalizacija Stepper objekta mojStpMot sa datim pinovima
Stepper mojStpMot(KoraciPoObr, IN1, IN3, IN2, IN4);

const int PinTastera = 2;            // pin na koji je povezan taster
const int PinPotenciometra = A0;     // pin potenciometra
int ADVrednost;                      // vrednost na analognom ulazu (rezultat AD konverzije)
volatile boolean pritisnut = false;  // stanje tastera: da li je pritisnut ili nije

void TasterISR() {
  // servisna rutina prekida (ISR), koja se izvrsava
  // svaki put kada se detektuje pritisak tastera na pinu PinTastera
  pritisnut = true;  // menjamo vrednost globalne promenljive pritisnut
}


void setup() {
  // inicijalizacija ulaznog pina sa internim Pull-Up otpornikom
  pinMode(PinTastera, INPUT_PULLUP);
  // Aktiviranje interapta na pinu PinTastera, sa prek rutinom TasterISR
  attachInterrupt(digitalPinToInterrupt(PinTastera), TasterISR, FALLING);
  // Inicijalizacija serijske komunikacije sa racunarom na 9600 bps
  Serial.begin(9600);
  // Podešavanje brzine step motora na 15 obrtaja u minuti (maks brzina ovog motora)
  mojStpMot.setSpeed(15);
}

void loop() {
  if (pritisnut) {                                              // Ako je taster pritisnut
    ADVrednost = analogRead(PinPotenciometra);                  //uzima se vrednost sa analognog ulaza...
    int tezinaProizvoda = map(ADVrednost, 205, 818, 185, 215);  // mapiranje vrednosti za dobijanje tezine proizvoda u gramima
    Serial.print("Masa proizvoda: ");
    Serial.print(tezinaProizvoda); 
    Serial.println(" g");
    if (tezinaProizvoda < 196 || tezinaProizvoda > 204) {
      Serial.println("NEISPRAVAN");
      mojStpMot.step(100);  // motor pravi 100 koraka u smeru kazaljke na satu
      delay(1000);
      mojStpMot.step(-100);  // motor pravi 100 koraka u smeru suprotnom od kazaljke na satu -> pocetni polozaj
    } else {
      Serial.println("ISPRAVAN");
      mojStpMot.step(-100);  // motor pravi 100 koraka u smeru kazaljke na satu
      delay(1000);
      mojStpMot.step(100);  // motor pravi 100 koraka u smeru suprotnom od kazaljke na satu -> pocetni polozaj    
    }
    pritisnut = false;  // resetuje se logicka promenljiva
  }
}