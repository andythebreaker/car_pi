#coding:utf8
import speech_recognition as sr
#import serial
import time
import os
#COM_PORT='/dev/ttyUSB0'
#BAUD_RATES = 9600
#ser = serial.Serial(COM_PORT, BAUD_RATES)

# obtain path to "english.wav" in the same folder as this script
from os import path
def Chineseize(num):
       dict = {1:"一", 2:"二", 3:"三", 4: "四", 5:"五", 6:"六", 7:"七", 8:"八", 9:"九", 0:"零"}
       num = int(num)

       if num==0:
            num="零"
       elif num==10:
            num = "十"
       else:
             ch_num = ""+num   #int to str

             if len(ch_num)==1:
                   num = dict[num]
             elif len(ch_num)==2:
                   num = dict[int(ch_num[1])]+"十"+dict[ch_num[0])]
             elif len(ch_num)==3:
                   num = dict[int(ch_num[2])]+"百"+dict[int(ch_num[1])]+"十"+dict[ch_num[0])]
             elif len(ch_num)==4:
                   num = dict[int(ch_num[3])]+"千"+dict[int(ch_num[2])]+"百"+dict[int(ch_num[1])]+"十"+dict[ch_num[0])]
             elif len(ch_num)==5:
                    num = dict[int(ch_num[4])]+"萬"+dict[int(ch_num[3])]+"千"+dict[int(ch_num[2])]+"百"+dict[int(ch_num[1])]+"十"+dict[ch_num[0])]

        if num[len(num)-1]=="零":
                num[len(num)-1] = ""
        for i=0:len(num)-3:
                if num[i]=="零":
                       num[i+1]=""

        print(num)
return num
os.system("arecord test.wav -f S16_LE -r 44100 -d 5")

AUDIO_FILE = path.join(path.dirname(path.realpath(__file__)), "test.wav")
# AUDIO_FILE = path.join(path.dirname(path.realpath(__file__)), "french.aiff")
# AUDIO_FILE = path.join(path.dirname(path.realpath(__file__)), "chinese.flac")

# use the audio file as the audio source
r = sr.Recognizer()
with sr.AudioFile(AUDIO_FILE) as source:
    audio = r.record(source)  # read the entire audio file

# recognize speech using Google Speech Recognition
try:
    print("Google Speech Recognition thinks you said:")
    str = r.recognize_google(audio, language="zh-TW")
    print(str)

    file=open("OBDdata.txt","r")
    OBDdata = file.read()
    OBDdata = Chineseize(OBDdata)
    result = ""

    for i=0:len(str)-3:
        if str[i:i+2] == "轉速" || str[i:i+2] == "引擎":
            result = "現在的引擎轉速是 "+OBDdata+"每分"
            break
        elif str[i:i+2] == "車速" || str[i:i+2] == "速度"
            result = "現在的行車速度是時速 "+OBDdata+"公里"
            break
    print(result)
    os.system(".~/car_pi/txt2sound/tx.o "+result)
except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))

