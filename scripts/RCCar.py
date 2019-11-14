#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  5 14:17:46 2019

@author: JS235785
"""

import serial
import rospy
from time import sleep
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Imu

import smbus
import time


#byte_data = bus.read_byte(i2c_addr)               # Perform SMBus Read Byte transaction.
#byte_data = bus.read_byte_data(i2c_addr, 0x00)    # (addr, cmd), Perform SMBus Read Byte Data transaction.
#word_data = bus.read_word_data(i2c_addr, 0x01)    # (addr, cmd), Perform SMBus Read Word Data transaction.

self.bus.write_i2c_block_data(self.i2c_addr, 0, [0x61,128])
time.sleep(.500)
self.bus.write_i2c_block_data(self.i2c_addr, 0, [0x76,5])
#write_byte(i2c_addr, 0xff)                    # Perform SMBus Write Byte transaction.
#bus.write_byte_data(i2c_addr, 0x10, 0xff)         # (addr, cmd, val), Perform SMBus Write Byte Data transaction.
#bus.write_word_data(i2c_addr, 0x11, 0x1234)       # (addr, cmd, val), Perform SMBus Write Word Data transaction.

#v : 0x76
#a : 0x61




class RCCar:
    def __init__(self):
        self.sub_pose=rospy.Subscriber("/nunchuk/cmd_vel",Twist,self.cb_cmdvel)
        #le hokuyo
        self.pub_imu=rospy.Publisher("/zumo/imu",Imu,queue_size=10)
        self.TIMEOUT=0.1
        self.vitesse =[]
        self.angle=[]
        self.p=Imu()
        self.p.header.stamp = rospy.Time.now()
        self.p.header.frame_id="map"
        
        self.bus = smbus.SMBus(1)  # '/dev/i2c-1'
        self.i2c_addr = 0x08
        
        try :
            self.ser = serial.Serial( self.PORT, self.BAUDRATE,timeout=self.TIMEOUT)
            sleep(1)
            rospy.loginfo("connexion serie etablie sur le port "+str(self.PORT))

        except:
            rospy.loginfo("Echec connexion serie")
            
    def __delete__(self):
        self.ser.close()
        print "Connexion fermee"
        
             
    def envoie_consigne(self,cons_vitesse,cons_angle):
        try :        
            self.bus.write_i2c_block_data(self.i2c_addr, 0, [0x61,int(((cons_angle+1)*127.5))])
            sleep(0.005)        
            self.bus.write_i2c_block_data(self.i2c_addr, 0, [0x76,int(((cons_vitesse+1)*127.5))])
        except :
            rospy.loginfo( "envoie trame en rade !")
        #v : 0x76
        #a : 0x61        
        
    def cb_cmdvel(self,msg):
       self.envoie_consigne(msg.linear.x,msg.angular.z)
       #print "callback : ",msg
   
   
if __name__=="__main__":


    print "Starting"
    rospy.init_node("RCCar")
    myRCCar=RCCar()

    while not rospy.is_shutdown():
              myRCCar.recup_trame()
              sleep(0.001)

    rospy.loginfo("Node terminated")
    rospy.delete_param("ARDUINO_BAUDRATE")
    rospy.delete_param("ARDUINO_PORT")
    myZumo.ser.close()
    rospy.loginfo("Connexion fermee")
