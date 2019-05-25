import RPi.GPIO as GPIO
import time
pin=17
GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, False)
while True:
    try:
        GPIO.output(pin, True)
        time. Sleep(0.5)
        GPIO.output(pin, False)
        time.sleep(0.5)
    except KeyboardInterrupt:
            GPIO.cleanup()
            exit()
