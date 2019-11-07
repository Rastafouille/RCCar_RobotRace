#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  5 14:17:46 2019

@author: JS235785
"""

import serial
from math import sqrt
import rospy
from time import sleep
from threading import Lock
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Imu


class RCCar:
    def __init__(self):
        self.sub_pose=rospy.Subscriber("/nunchuk/cmd_vel",Twist,self.cb_cmdvel)
        #le hokuyo
        self.pub_imu=rospy.Publisher("/zumo/imu",Imu,queue_size=10)
        try:
            self.PORT=rospy.get_param('ARDUINO_PORT') 
        except:
            rospy.set_param('ARDUINO_PORT',"/dev/ttyACM0")
            self.PORT=rospy.get_param('ARDUINO_PORT')
        try:
            self.BAUDRATE=rospy.get_param('ARDUINO_BAUDRATE') 
        except:
            rospy.set_param('ARDUINO_BAUDRATE',"9600")
            self.BAUDRATE=rospy.get_param('ARDUINO_BAUDRATE')
        self.TIMEOUT=0.1
        self.lock=Lock()
        self.vitesse =[]
        self.angle=[]
        self.p=Imu()
        self.p.header.stamp = rospy.Time.now()
        self.p.header.frame_id="map"
        
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
       with self.lock:
            #construction et envoie trame consigne
            consigne="~X;"+str(int (cons_vitesse*100))+";"+str(int (cons_angle*100))+";#"
            self.ser.flush()
            sleep(0.001)
            
            try :
                self.ser.write(consigne)
                #rospy.loginfo("Consigne envoyee : "+str(consigne))
            except :
                rospy.loginfo( "envoie trame en rade !")
        
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
