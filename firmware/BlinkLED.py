#!/usr/bin/python3
import sys
import os
from time import sleep

try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("Error importing RPi.GPIO!  This is probably because you need superuser privileges.  You can achieve this by using 'sudo' to run your script")

PIN_17=17
PIN_18=18
GPIO_Chan_List=[PIN_17,PIN_18]

def writeLED(channel, value):
    GPIO.output (channel, value)
    return

def turnon(color):
   if color == 'red':
      writeLED(PIN_17, GPIO.LOW)
      writeLED(PIN_18, GPIO.HIGH)
   elif color == 'green':
      writeLED(PIN_18, GPIO.LOW)
      writeLED(PIN_17, GPIO.HIGH)
   else:
      turnoff()	
   return

def blink(color1, color2='off'):
   i = 0; 
   for i in range (0, 10):
      turnon(color1)
      sleep(0.5)
      turnon(color2)
      sleep(0.5)
      i+= 1
   return

def blink_pwm(color='green'):
   i = 0;     
   if (color=='green'):
     writeLED(PIN_17, GPIO.HIGH)   
     RESET_LIGHT = -1                  #light up or down the LED
     RESET_DUTY = 100    
   else:
     writeLED(PIN_17, GPIO.LOW)   
     RESET_LIGHT = 1                  #light up or down the LED
     RESET_DUTY = 0    

   duty=RESET_DUTY
   lightup=RESET_LIGHT
   pwm = GPIO.PWM(PIN_18, 1000)   #initialize Pin 18 as PWM control 
   pwm.start(duty)     #start the PWM with to turn OFF the LED.
   i = 0
   while(1):
   #for i in range (0, 100):  #blink 0.5*100 = 50 seconds
      sleep(0.5)
      print ("i=", i)
      if (i%20==0):           #reset light up/down direction every 10 seconds. 
        lightup=RESET_LIGHT
      elif (i%10==0):         #reverse the light up/down direction every 5 seconds. 
        lightup = (-1)*RESET_LIGHT

      duty = duty+lightup*10
      print ("duty=",duty)
      pwm.ChangeDutyCycle(duty) 
      i+= 1  
   pwm.stop()
   return
   
def turnoff():
    writeLED(PIN_18, GPIO.LOW)
    writeLED(PIN_17, GPIO.LOW)
    return

   
def main():  
    global PIN_17
    global PIN_18
    global GPIO_Chan_List

    print ('Start LED blinking')

    if len(sys.argv) != 2:
      print ('usage is blinkLED command')
      print ('''command could be:
           	on, on_green, off, 
           	blink_red,blink_green, blink_mix,
           	blink_pwm or blink_pwm_red''')
      sys.exit(2)
    
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    
    GPIO.setup(GPIO_Chan_List, GPIO.OUT)  #Initialize the Channel List. 

    if sys.argv[1].lower() == 'on':
      print ('Turn on red LED')
      turnon('red')
    elif sys.argv[1].lower() == 'on_green':
      print ('Turn on green LED')
      turnon('green')
    elif sys.argv[1].lower() == 'off':   
      print ('Turn off LED')
      turnoff()
    elif sys.argv[1].lower() == 'blink_red':
      print ('Blink red LED')
      blink('red')
    elif sys.argv[1].lower() == 'blink_green':
      print ('Blink green LED')
      blink('green')
    elif sys.argv[1].lower() == 'blink_mix':
      print ('Blink green/red LED')
      blink('red', 'green')
      turnoff()
    elif sys.argv[1].lower() == 'blink_pwm':
      print ('PWM blink green LED')
      blink_pwm()
      turnoff()    
    elif sys.argv[1].lower() == 'blink_pwm_red':
      print ('PWM blink red LED')
      blink_pwm('red')
      turnoff()    
    else:
      print ('Unrecognized Command')
      print ('''command could be:
           	on, on_green, off, 
           	blink_red,blink_green, blink_mix,
           	blink_pwm or blink_pwm_red''')
   
    print ('End of Code')

	
if __name__ == "__main__":
  main()




