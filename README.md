## Maturski ispit – Elektrotehničar računara

Ovaj repozitorijum sadrži moja rešenja zadataka sa maturskog ispita iz oblasti mikrokontrolera i mikroračunara, u okviru obrazovnog profila Elektrotehničar računara.

## Opis rada

Tokom realizacije zadataka korišćene su dve platforme:

#### `Arduino Uno` – za rad sa mikrokontrolerima i upravljanje elektronskim komponentama na nižem nivou
#### `Raspberry Pi` – kao mikroračunarska platforma za složenije zadatke i rad u Python okruženju

Zadaci obuhvataju rad sa digitalnim i analognim signalima, upravljanje perifernim uređajima, kao i implementaciju interaktivnih sistema.

| Tehnologija / Koncept | Opis |
|------------------------|------|
| C/C++ (Arduino okruženje) | Programiranje mikrokontrolera i rad sa hardverom na nižem nivou |
| Python | Programski jezik korišćen na Raspberry Pi platformi |
| RPi.GPIO | Biblioteka za upravljanje GPIO pinovima na Raspberry Pi uređaju |
| Adafruit_CharLCD | Biblioteka za upravljanje 16x2 LCD displejom |
| PWM (Pulse Width Modulation) | Tehnika za kontrolu intenziteta signala, npr. jačine LED dioda |
| Interrupt mehanizmi | Obrada događaja u realnom vremenu (npr. pritisak tastera) |

<div align="center" style="display:flex; justify-content:center; align-items:center; gap:100px;">

  <img src="https://github.com/user-attachments/assets/b5b6e470-c552-4ab7-93b5-4e5bc66ac89e" width="120" />

  <img src="https://github.com/user-attachments/assets/57ff7806-668b-4677-b14d-1982901809a3" width="100" />

</div>

## Razvojna okruženja

Za rad sa Raspberry Pi uređajem korišćeno je Thonny razvojno okruženje na `Raspberry Pi OS` sistemu. Thonny omogućava jednostavno pisanje, pokretanje i testiranje Python programa direktno na uređaju.

Za rad sa Arduino Uno platformom korišćeno je `Arduino IDE` okruženje, koje se koristi za pisanje i učitavanje C/C++ programa na mikrokontroler.


#### U okviru projekta realizovani su različiti praktični primeri:

- Upravljanje LED diodama i aktuatorima pomoću mikrokontrolera
- Kontrola intenziteta svetlosti korišćenjem PWM-a
- Očitavanje ulaza (tasteri, potenciometri)
- Komunikacija sa LCD displejem (16x2)
- Simulacija realnih scenarija (npr. sistem za proveru ispravnosti proizvoda, bacanje kocke)

#### Napomena

Prikazana rešenja predstavljaju jedno od mogućih implementacionih rešenja zadatih problema. Tokom izrade, fokus je bio na:

- modularnosti i čitljivosti koda
- pravilnoj upotrebi programskih struktura
- primeni dobrih praksi u embedded programiranju
- proširenju funkcionalnosti u odnosu na osnovne zahteve zadataka

Ovaj repozitorijum može poslužiti kao referenca i pomoć drugim učenicima prilikom savladavanja gradiva iz oblasti mikrokontrolera i mikroračunara i pripreme za maturski ispit.

## Autor

Mihajlo Stoiljković

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)




