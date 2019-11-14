# -*- coding: utf-8 -*-


import odroid_wiringpi as wpi

OUTPUT = 1
PIN_TO_PWM = 0

wpi.wiringPiSetup()
wpi.pinMode(PIN_TO_PWM,OUTPUT)
wpi.softPwmCreate(PIN_TO_PWM,0,10) # Setup PWM using Pin, Initial Value and Range parameters
wpi.softPwmWrite(PIN_TO_PWM,0)
#
#for time in range(0,4):
#    for brightness in range(0,10): # Going from 0 to 100 will give us full off to full on
#        wpi.softPwmWrite(PIN_TO_PWM,brightness) # Change PWM duty cycle
#        wpi.delay(100) # Delay for 0.2 seconds
#        print(brightness)
#    for brightness in reversed(range(0,10)):
#        wpi.softPwmWrite(PIN_TO_PWM,brightness)
#        wpi.delay(100)
#        print(brightness)