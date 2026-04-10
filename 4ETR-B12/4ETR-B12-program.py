import time
import RPi.GPIO as GPIO
import Adafruit_CharLCD as LCD
import random 

# Postavljanje GPIO pinova
GPIO.setmode(GPIO.BCM)

# Definisanje pinova i promenljivih
taster = 6
lcd_rs = 22
lcd_en = 17
lcd_d4 = 25
lcd_d5 = 24
lcd_d6 = 23
lcd_d7 = 18
lcd_backlight = 2
lcd_columns = 16
lcd_rows = 2
redni_broj = 0
baci = False

# Inicijalizacija LCD displeja
lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7, lcd_columns, lcd_rows, lcd_backlight)
GPIO.setup(taster, GPIO.IN, pull_up_down=GPIO.PUD_UP)  

# Funkcija koja se poziva kada se taster pritisne
def baciCallback(taster):
    global baci
    baci = True
    lcd.clear()
    
# Postavljanje prekidaca na tasteru
GPIO.add_event_detect(taster, GPIO.FALLING, callback=baciCallback, bouncetime=300)
lcd.clear()
lcd.show_cursor(False)

try:
    # Prikaz dobrodoslice poruke i pomeranje teksta
    lcd.message("Dobro dosli")
    for _ in range(6):
        time.sleep(0.5) # pauza od 0.5 sekundi
        lcd.move_right() # desno
    for _ in range(6):
        time.sleep(0.5) # pauza od 0.5 sekundi
        lcd.move_left() # levo
    lcd.clear()
    lcd.message("Baci kocku")
    # Glavna petlja programa
    while True:
        # Provera da li je taster pritisnut
        if baci==True:
            randomBroj = random.randint(1, 6)  # Generisanje random broja od 1 do 6
            redni_broj += 1  # Povecavanje broja za 1
            lcd.clear()
            lcd.message(f"Vas {redni_broj} broj je {randomBroj}")
            if randomBroj == 6:
                lcd.message("\nPonovite bacanje")
            baci = False
            time.sleep(0.5) # Pauza od 0.5 sekundi
except KeyboardInterrupt:
    # Oslobađanje resursa i ciscenje GPIO pinova
    lcd.clear()
    GPIO.cleanup()