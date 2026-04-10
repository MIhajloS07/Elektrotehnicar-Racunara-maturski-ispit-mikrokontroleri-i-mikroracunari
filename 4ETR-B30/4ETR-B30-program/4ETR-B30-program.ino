const int PinCrvene = 12;  // pin crvene diode
const int PinZelene = 11;  // pin zelene diode
String naredba;            // naredba je string (niz karaktera)
int periodeMs[] = {500, 1000, 1500, 2000}; // niz perioda u ms
int periodaIndex = 0, aktivnaDioda = 100, statusAktivne = HIGH;

void setup() {
  // Inicijalizacija pinova
  pinMode(PinCrvene, OUTPUT);
  pinMode(PinZelene, OUTPUT);
  // Početne vrednosti izlaznih pinova
  digitalWrite(PinCrvene, LOW);
  digitalWrite(PinZelene, LOW);
  // Inicijalizacija serijske komunikacije sa racunarom na 9600 bps
  Serial.begin(9600);
}
void loop() {
  if (Serial.available()) {           // ako na ulazu postoji podatak koji se može pročitati
    naredba = Serial.readString();    // čitamo string
    naredba.trim();                   // sečemo CR i NL sa kraja stringa!!!
    if (naredba == "#CRVENA"){
      Serial.println("Pali se crvena dioda");
      aktivnaDioda = PinCrvene;
    }
    else if (naredba == "#ZELENA") {
      Serial.println("Pali se zelena dioda");
      aktivnaDioda = PinZelene;
    }
    else if (naredba == "#UVECAJ"){
      if (periodaIndex < 3){
        ++periodaIndex;
        Serial.print("Uvecavam periodu na: "); Serial.println(periodeMs[periodaIndex]);
      } else {
        Serial.println("Ovo je maksimalna perioda!");
      }
    }
    else if (naredba == "#SMANJI"){
      if (periodaIndex > 0){
        --periodaIndex;
        Serial.print("Smanjujem periodu na: "); Serial.println(periodeMs[periodaIndex]);
      } else {
        Serial.println("Ovo je minimalna perioda!");
      }
    }
    else {
      Serial.println("Nepoznata naredba");
    }
  }
  if (aktivnaDioda == PinCrvene || aktivnaDioda == PinZelene) {
      digitalWrite(aktivnaDioda, statusAktivne);
      delay(periodeMs[periodaIndex]);
      statusAktivne = !statusAktivne;
  }
}