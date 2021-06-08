# -*- coding: utf-8 -*-
"""
Created on Mon Jun  7 16:57:09 2021

@author: dinaa
"""

import gmplot
import pandas as pd
apikey = "AIzaSyAyU5txJ86b25-_l0DW-IldSKGGYqQJn3M"

# Serial connection to Tiva C board
ser = serial.Serial("COM10", 9600)
data = ser.readline(5000).decode('ascii')

real_data = False
centre = [30.3164945, 78.03219179999999] # Add faculty location

# Reading GPS DATA from csv

if real_data:
    df = pd.read_csv(r"\locations.csv") # files that contains gps readings
    latitude_list = df.iloc[:, 0] # selecting first column
    longitude_list =  df.iloc[:, 1] # selecting second column 
    

    
# Sample Code for testing
if not real_data:
    latitude_list = [30.3358376, 30.307977, 30.3216419]
    longitude_list = [77.8701919, 78.048457, 78.0413095]
    #locations = [(30.3358376,77.8701919),(30.307977, 78.048457),(30.3216419,78.0413095)]


# Generating trajectory  
gmap3 = gmplot.GoogleMapPlotter(centre[0],
                                centre[1], 13, apikey = apikey)

gmap3.plot(latitude_list, longitude_list, 
           'blue', edge_width = 2.5)
  
gmap3.draw(r"G:\aaaaaaa\Uni\Third Year\Second Term\google_map_2.html" )

