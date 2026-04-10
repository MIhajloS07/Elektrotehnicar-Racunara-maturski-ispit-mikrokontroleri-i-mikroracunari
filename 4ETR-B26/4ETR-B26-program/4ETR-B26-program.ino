// Dodajemo biblioteku za rad sa LCD displejem
#include <LiquidCrystal.h>

// Pinovi LCD displeja
const int RSPin = 10;
const int EnablePin = 11;
const int D4Pin = 4;
const int D5Pin = 5;
const int D6Pin = 6;
const int D7Pin = 7;

// Kreiranje i inicijalizacija LiquidCrystal objekta
LiquidCrystal lcd(RSPin, EnablePin, D4Pin, D5Pin, D6Pin, D7Pin);

const int PinTastera = 2;            // pin na koji je povezan taster
volatile boolean Pritisnut = false;  // da li je taster pritisnut?
unsigned short brojBacanja = 0;      // redni broj bacanja (brojac)
int randomBroj;                      // slucajni broj koji se generise svakim pritiskom na dugme

// servisna rutina prekida, koja se izvrsava
// svaki put kada se detektuje pritisak tastera na pinu PinTastera
void TasterISR() {
  // menjamo vrednost globalne promenljive Pritisnut u true
  Pritisnut = true;
}


void setup() {
  // Inicijalizacije veličine displeja (širina, visina)
  lcd.begin(16, 2);
  // inicijalizacija ulaznog pina (dugmeta)
  pinMode(PinTastera, INPUT);
  // Aktiviramo interrupt na pinu PinTastera, sa prekidnom rutinom TasterISR
  attachInterrupt(digitalPinToInterrupt(PinTastera), TasterISR, FALLING);
  // ispis pozdravne poruke
  lcd.print("Dobro dosli");
  for (int i = 0; i < 6; i++){
    delay(500);
    lcd.scrollDisplayRight();
  }
  for (int i = 0; i < 6; i++){
    delay(500);
    lcd.scrollDisplayLeft();
  }
  delay(500);
  lcd.clear();
  lcd.print("Baci kocku");
}

void loop() {
  if (Pritisnut) {        //ako je taster pritisnut
    ++brojBacanja;
    randomBroj = random(1, 7); // nasumicna vrednost izmedju 1 i 6
    lcd.clear();          // briše se sadržaj displeja
    lcd.print("Vas "); 
    lcd.print(brojBacanja); 
    lcd.print(" broj je ");
    lcd.print(randomBroj);
    if (randomBroj == 6) {
      lcd.setCursor(0, 1);
      lcd.print("Ponovite bacanje");
    }
    Pritisnut = false;    // čaka se sledeći pritisak (ako ga ima)
  }
}