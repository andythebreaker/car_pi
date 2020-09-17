import obd
import time
import requests
#from bs4 import BeautifulSoup
import urllib

obd.logger.setLevel(obd.logging.DEBUG)

#helper function to determine which ports are available for writing
ports = obd.scan_serial()       # return list of valid USB or RF ports
print(ports)                    # ports = ['COM6', 'COM7',....,'COM10']

connection = obd.Async(portstr=ports[-1],fast=False, timeout=30) # auto-connects to USB or RF port

#a callback func that prints every new value to the console
#RPM
def new_rpm(r):
    print("RPM: "+str(r.value.magnitude))
    
    file = open("OBDdata.txt","w")
    file.write(str(r.value.magnitude))
    file.close()
    
    print("\t")    
    result = "user=Willy&RPM="+str(r.value.magnitude)+"&SPEED=0"
    requests.get("http://luffy.ee.ncku.edu.tw:10087/anything?"+result)
    

#SPEED
def new_speed(r):
    print("SPEED: "+str(r.value.magnitude))

    file = open("OBDdata.txt","w")
    file.write("SPEED: "+str(r.value.magnitude))
    file.close()
    
    print("\t")

print("連接成功，即將watch...")

#keep track of the car's data
connection.watch(obd.commands.RPM,callback = new_rpm)
connection.watch(obd.commands.SPEED,callback = new_speed)

print("即將開始...")
connection.start()

#the callback will now be fired upon receipt of new values
time.sleep(30)
print("即將結束...")
connection.stop()
