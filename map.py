# -*- coding: utf-8 -*-
"""
Created on Mon Jun  7 16:57:09 2021

@author: dinaa
"""

import gmplot
import gmaps
import pandas as pd
import serial
from serial import Serial
import sys

readings = []
longitude_list = []
latitude_list = []

# Serial connection to Tiva C board
try:
    ser = serial.Serial('/dev/ttyACM0',115200)
    #ser = serial.Serial("COM10", 115700)
except:
    print("Unable to open serial port")
    
#The following code will read the serial 
while True:
    try:
        line = ser.readline()
        print(line)
        readings.append(line)
    except:
        print ("Unable to read from device")
        sys.exit(0)
        
# Formatting the readings: from string to int
    
for i in range(len(readings)):
    readings[i] = int(i)
    
# Storing the readings in Lists 
    
latitude_list.append(readings[0])
longitude_list.append(readings[1])
date = readings[3]

for i in range(3, len(readings)):
    if(i%3==0):
        latitude_list.append(readings[i])
        longitude_list.append(readings[i+1])
    

# Mapping Code

apikey = "AIzaSyAyU5txJ86b25-_l0DW-IldSKGGYqQJn3M"
latitude_list = [ 30.3358376, 30.307977, 30.3216419 ]
longitude_list = [ 77.8701919, 78.048457, 78.0413095 ]

gmap3 = gmplot.GoogleMapPlotter(30.0634725239,
                                31.27879477537, 13) # faculty location
  

gmap3.scatter(latitude_list, longitude_list, '#FF0000',
                                size = 40, marker = True)
  
# Drawing Trajectory
gmap3.plot(latitude_list, longitude_list,
                   color = 'cornflowerblue')
# Saving the map  
gmap3.draw(r"G:\aaaaaaa\Uni\Third Year\Second Term\google_map_2.html")
