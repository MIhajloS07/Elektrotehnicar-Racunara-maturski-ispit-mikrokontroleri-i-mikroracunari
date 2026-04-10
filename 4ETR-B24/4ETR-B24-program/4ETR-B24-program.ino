#include <Servo.h>          // biblioteka za rad sa servo motorom
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
Servo mojServo;                // Kreiranje Servo objekta
const int PinSenzora = A0;     // pin na koji je povezan senzor vlage
const int PinServoMotora = 3;  // pin preko kog servo dobija PWM signal
int vlaznost;                  // celobrojna vrednost očitana sa senzora (0-1023)
unsigned const short donjiPragVlaznosti = 287, gornjiPragVlaznosti = 800;


void setup() {
  lcd.begin(16, 2);                 // Inicijalizacije veličine displeja (širina, visina)
  mojServo.attach(PinServoMotora);  // inicijalizacija servo motora na datom pinu
  mojServo.write(0);                // Pocetni ugao servo motora
}

void loop() {
  lcd.clear(); 
  vlaznost = analogRead(PinSenzora);
  if (vlaznost < donjiPragVlaznosti) { // Ako je zemlja vlazna
    lcd.print("VLAZNA ZEMLJA");           
  } else if (vlaznost > gornjiPragVlaznosti) { // Ako je zemlja suva
    lcd.print("SUVA ZEMLJA!");            
    mojServo.write(30); 
    delay(1000); // 1 sekunda odziv
    mojServo.write(150);
  } else {
    lcd.print("OPTIMALNA ZEMLJA");    
  }
  // Ispis vlaznosti zemljista u drugom redu LCD-a
  lcd.setCursor(0, 1);
  lcd.print("Vlaznost: ");
  lcd.print(vlaznost);
  delay(3000);  // pauza od 3s 
}