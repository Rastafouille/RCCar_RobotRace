# -*- coding: utf-8 -*-
"""
Created on Wed Nov 13 10:32:50 2019

@author: JS235785
"""

#https://forum.odroid.com/viewtopic.php?t=27732
#sudo apt-get install wiringpi


import odroid_wiringpi as wpi
#

#pin_base = 65
#i2c_addr = 0x08
#pins = [65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80]
#
#wpi.wiringPiSetup()
#wpi.mcp23017Setup(pin_base,i2c_addr)
#
#for pin in pins:
#	wpi.pinMode(pin,1)
#	wpi.digitalWrite(pin,1)
##	wiringpi.delay(1000)
##	wiringpi.digitalWrite(pin,0)
#

#import wiringpi2 as wpi

i2c_dev = "/dev/i2c-1"
i2c_addr = 0x08

wpi.wiringPiSetup()
i2c_fd = wpi.wiringPiI2CSetupInterface(i2c_dev, i2c_addr)

#wpi.wiringPiI2CRead(i2c_fd)                      # Simple device read. Some devices present data when you read them without having to do any register transactions.
wpi.wiringPiI2CWrite(i2c_fd, [0x54, 0x6f, 0x4f, 0x6e, 0x54] )         # Simple device write. Some devices accept data this way without needing to access any internal registers.
print("ok")
#wpi.wiringPiI2CReadReg8(i2c_fd, 0x00)            # These read an 8-bit value from the device register(0x00) indicated.
#wpi.wiringPiI2CWriteReg16(i2c_fd, 0x10, 0x14)  # These write an 16-bit data value into the device register(0x10) indicated.





#v : 0x76
#a : 0x61
