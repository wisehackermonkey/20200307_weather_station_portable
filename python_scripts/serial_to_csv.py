try:
    import serial
    import re 
    # %%

    from time import sleep
    from datetime import datetime
    import serial, platform, json, os, csv, pathlib
    import serial.tools.list_ports
    import pathlib
    # add "export PHONE_NUMBER='<phone_number>'" to bashrc

    def num_there(s):
        return any(i.isdigit() for i in s)
    
    CSV_PATH = pathlib.Path.cwd() /"temp_data_v1.csv"
    CSV_PATH = str(CSV_PATH)

    PLATFORM = platform.system()

    try:
        if PLATFORM == "Windows":
            COM_PORT = ""
            for p in list(serial.tools.list_ports.comports()):
                if "Arduino" in p.description:
                    COM_PORT = str(p.device)
        elif PLATFORM == 'Linux':
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

                    # throw away any lines that don't have numbers and ","
                    # regex explanation 
                    # https://regex101.com/r/yK6oF4/1
                    if re.match('^[0-9,.]*$', raw_temp):
                        split_row = raw_temp.split(",")# second value in array is the temp

                        if len(split_row) > 1:
                            print(split_row)

                            #write temp values to a file
                            with open(CSV_PATH,"a+") as f:
                                writer = csv.writer(f,delimiter=",")
                                row = [datetime.now().strftime("%Y%m%d %H:%M:%S")]
                                row.extend(split_row)
                                writer.writerow(row)
        except KeyboardInterrupt:
            print("Closing program...")
    except serial.serialutil.SerialException:
        print("I'm having trouble connecting to the Arduino")
        print("Try plugging the arduino in to the computers usb port")

except Exception as e:
    print("\n\n\n")

    print(e)
    print(""" 
----------------------
Error!! 
----------------------
Pyserial is not installed on your computer: 
please install pyserial by typing the fallowing:

>pip install pyserial
(or) 
>conda install pyserial
----------------------
    """)
