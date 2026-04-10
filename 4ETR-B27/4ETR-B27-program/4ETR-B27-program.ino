const int PinCrveneDiode = 12;      // pin crvene diode
const int PinZvucnika = 8;          // pin zvučnika
const int PinPIRSenzora = 2;        // pin PIR senzora
volatile unsigned short brojPokretanja = 0;  // Brojac za broj pokretanja
volatile bool alarm;                

void AlarmISR() {
  alarm = true;
  ++brojPokretanja;
}

void setup() {
  // Inicijalizacija pinova
  pinMode(PinCrveneDiode, OUTPUT);
  pinMode(PinZvucnika, OUTPUT);
  pinMode(PinPIRSenzora, INPUT);
  attachInterrupt(digitalPinToInterrupt(PinPIRSenzora), AlarmISR, RISING);
  // Početne vrednosti izlaznih pinova
  digitalWrite(PinCrveneDiode, LOW);
  Serial.begin(9600);
}

void loop() {
  if (alarm) {    
    alarm = false;
    Serial.print("Upozorenje | broj pokretanja aktivacije: ");
    Serial.println(brojPokretanja);
    digitalWrite(PinCrveneDiode, HIGH);
    for (int i = 0; i < 15; i++) {
      tone(PinZvucnika, 2100);
      delay(100);
      tone(PinZvucnika, 2200);
      delay(100);
      tone(PinZvucnika, 2300);
    } 
    digitalWrite(PinCrveneDiode, LOW);
    noTone(PinZvucnika);
  } else {
    Serial.println("BEZBEDNO!");  
  }
}