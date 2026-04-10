import RPi.GPIO as GPIO
from time import sleep

# definisanje pinova i pocetnog duty cycle-a
uvecaj = 5
smanji = 6
ledr = 17
ledy = 27
ledg = 22   
duty=0 # diode ne svetle -> pocetni polozaj

# postavljanje pinova i modula
GPIO.setmode(GPIO.BCM) 
GPIO.setup(ledr, GPIO.OUT)
GPIO.setup(ledy, GPIO.OUT)
GPIO.setup(ledg, GPIO.OUT)
GPIO.setup(uvecaj, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(smanji, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# funkcija koja se poziva kada se pritisne dugme za povecanje intenziteta svetla
def uvecajCallback(uvecaj):
    global duty # koristimo globalnu promenljivu da bismo mogli da je menjamo unutar funkcije
    if duty < 100:
        duty += 10
    else:
        duty = 100
        print("Ne moze vise od 100% duty cycle-a")
    print(f"Duty cycle: {duty}%")
        
# funkcija koja se poziva kada se pritisne dugme za smanjenje intenziteta svetla
def smanjiCallback(smanji):
    global duty # koristimo globalnu promenljivu da bismo mogli da je menjamo unutar funkcije
    if duty > 0:
        duty -= 10
    else:
        duty = 0
        print("Ne moze manje od 0% duty cycle-a")
    print(f"Duty cycle: {duty}%")
        
# dodavanje detekcije pritiska na dugmadima
GPIO.add_event_detect(uvecaj, GPIO.FALLING, callback=uvecajCallback, bouncetime=300)
GPIO.add_event_detect(smanji, GPIO.FALLING, callback=smanjiCallback, bouncetime=300)

# inicijalizacija PWM-a za LED diode
pwmLEDr = GPIO.PWM(ledr, 1000)
pwmLEDy = GPIO.PWM(ledy, 1000)
pwmLEDg = GPIO.PWM(ledg, 1000)
pwmLEDr.start(0)
pwmLEDy.start(0)
pwmLEDg.start(0)

try:
    while True:
        # azuriranje duty cycle-a za sve LED diode
        pwmLEDr.ChangeDutyCycle(duty)
        pwmLEDy.ChangeDutyCycle(0)
        pwmLEDg.ChangeDutyCycle(0)
        sleep(0.3) # kratko cekanje pre ponovnog azuriranja
        pwmLEDr.ChangeDutyCycle(0)
        pwmLEDy.ChangeDutyCycle(duty)
        pwmLEDg.ChangeDutyCycle(0)
        sleep(0.3) # kratko cekanje pre ponovnog azuriranja
        pwmLEDr.ChangeDutyCycle(0)
        pwmLEDy.ChangeDutyCycle(0)
        pwmLEDg.ChangeDutyCycle(duty)
        sleep(0.3) # kratko cekanje pre ponovnog azuriranja
except KeyboardInterrupt:
    # prekid programa na Ctrl+C
    print("Prekid rada programa")
    GPIO.cleanup()