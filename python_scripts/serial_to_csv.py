import serial
import time
import csv


# %%
from time import sleep
import serial
import platform
import json
import os
import serial
import serial.tools.list_ports
import pathlib

# add "export PHONE_NUMBER='<phone_number>'" to bashrc

CSV_PATH = pathlib.Path.cwd() /"temp_data_v1.csv"

PLATFORM = platform.system()
if PLATFORM == "Windows":
    COM_PORT = ""
    for p in list(serial.tools.list_ports.comports()):
        if "Arduino" in p.description:
            COM_PORT = str(p.device)
elif pathlib == 'Linux':
    COM_PORT = ""
    for p in list(serial.tools.list_ports.comports()):
        if "Arduino" in p.manufacturer:
            COM_PORT = str(p.device)
else:
   COM_PORT = ""
   for p in serial.tools.list_ports.comports():
      if "usbmodem" in p.device:
         print(p.device)
         COM_PORT = p.device

print("Serial port: " + str(COM_PORT))

try:
    with serial.Serial(COM_PORT,9600) as ser:
        while True:
            raw_temp = ser.readline().decode("utf-8").strip() #decode byte string from arduino and strip return characters
            print(raw_temp)
            split_row = raw_temp.split(":")# second value in array is the temp

            if len(split_row) > 1:
                temp_val = split_row[1]
                print(temp_val)

                #write temp values to a file
                with open(CSV_PATH,"a+") as f:
                    writer = csv.writer(f,delimiter=",")
                    writer.writerow([time.time(),temp_val])
except KeyboardInterrupt:
    print("Closing program...")

