# -*- coding: utf-8 -*-
"""
Created on Wed Nov 13 18:55:03 2019

@author: root
"""

import smbus
import time

bus = smbus.SMBus(1)  # '/dev/i2c-1'
i2c_addr = 0x08

#byte_data = bus.read_byte(i2c_addr)               # Perform SMBus Read Byte transaction.
#byte_data = bus.read_byte_data(i2c_addr, 0x00)    # (addr, cmd), Perform SMBus Read Byte Data transaction.
#word_data = bus.read_word_data(i2c_addr, 0x01)    # (addr, cmd), Perform SMBus Read Word Data transaction.

bus.write_i2c_block_data(i2c_addr, 0, [0x61,128])
time.sleep(.500)
bus.write_i2c_block_data(i2c_addr, 0, [0x76,5])
#write_byte(i2c_addr, 0xff)                    # Perform SMBus Write Byte transaction.
#bus.write_byte_data(i2c_addr, 0x10, 0xff)         # (addr, cmd, val), Perform SMBus Write Byte Data transaction.
#bus.write_word_data(i2c_addr, 0x11, 0x1234)       # (addr, cmd, val), Perform SMBus Write Word Data transaction.

#v : 0x76
#a : 0x61