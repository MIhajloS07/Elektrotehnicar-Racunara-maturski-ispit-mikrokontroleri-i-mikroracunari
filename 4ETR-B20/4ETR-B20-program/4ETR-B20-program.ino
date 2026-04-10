#include <LiquidCrystal.h>  // biblioteka za rad sa LCD displejem

// Pinovi LCD displeja
const int RSPin = 10;
const int EnablePin = 11;
const int D4Pin = 4;
const int D5Pin = 5;
const int D6Pin = 6;
const int D7Pin = 7;

// Kreiranje i inicijalizacija LiquidCrystal objekta
LiquidCrystal lcd(RSPin, EnablePin, D4Pin, D5Pin, D6Pin, D7Pin);

// Ostali pinovi
const int PinLevogSenzora = 3;
const int PinDesnogSenzora = 2;
const int PinLCrveneDiode = 0;
const int PinDCrveneDiode = 1;
const int PinZeleneDiode = 12;

int LeviSignal = LOW;   // levi senzor nije na liniji
int DesniSignal = LOW;  // desni senzor nije na liniji


void setup() {
  // Inicijalizacije veličine displeja (širina, visina)
  lcd.begin(16, 2);
  // inicijalizacija pinova
  pinMode(PinLCrveneDiode, OUTPUT);
  pinMode(PinDCrveneDiode, OUTPUT);
  pinMode(PinZeleneDiode, OUTPUT);
  pinMode(PinLevogSenzora, INPUT);
  pinMode(PinDesnogSenzora, INPUT);
}

void loop() {
  LeviSignal = digitalRead(PinLevogSenzora);
  DesniSignal = digitalRead(PinDesnogSenzora);
  if (LeviSignal == HIGH && DesniSignal == HIGH) { 
    lcd.clear();                  // briše se sadržaj displeja
    lcd.print("STOJ");    
    // Treptanje crvenih dioda i gasenje zelene diode ako je bila ukljucena
    digitalWrite(PinZeleneDiode, LOW);
    digitalWrite(PinLCrveneDiode, HIGH);
    digitalWrite(PinDCrveneDiode, LOW);
    delay(75);
    digitalWrite(PinLCrveneDiode, LOW);
    digitalWrite(PinDCrveneDiode, HIGH);
    delay(75);
  }
  else if (LeviSignal == HIGH || DesniSignal == HIGH) {
      lcd.clear();                  // briše se sadržaj displeja
      lcd.print("LOS PRAVAC");
      if (LeviSignal == HIGH) {
        digitalWrite(PinLCrveneDiode, HIGH); // pali se odgovarajuća dioda
        digitalWrite(PinDCrveneDiode, LOW);
        digitalWrite(PinZeleneDiode, LOW);
      }
      else if (DesniSignal == HIGH){
        digitalWrite(PinLCrveneDiode, LOW); // pali se odgovarajuća dioda
        digitalWrite(PinDCrveneDiode, HIGH);
        digitalWrite(PinZeleneDiode, LOW);
      }
  }
  else {
    lcd.clear();                  // briše se sadržaj displeja
    lcd.print("DOBAR PRAVAC");  
    digitalWrite(PinLCrveneDiode, LOW); // pali se odgovarajuća dioda
    digitalWrite(PinDCrveneDiode, LOW);
    digitalWrite(PinZeleneDiode, HIGH);
  }

  delay(200);  // čeka se 200ms pre sledećeg očitavanja
}