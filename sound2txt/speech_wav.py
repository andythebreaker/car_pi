#coding:utf8
import speech_recognition as sr
#import serial
import time
#COM_PORT='/dev/ttyUSB0'
#BAUD_RATES = 9600
#ser = serial.Serial(COM_PORT, BAUD_RATES)

# obtain path to "english.wav" in the same folder as this script
from os import path
AUDIO_FILE = path.join(path.dirname(path.realpath(__file__)), "~/car_pi/sound2txt/test.wav")
# AUDIO_FILE = path.join(path.dirname(path.realpath(__file__)), "french.aiff")
# AUDIO_FILE = path.join(path.dirname(path.realpath(__file__)), "chinese.flac")

# use the audio file as the audio source
r = sr.Recognizer()
with sr.AudioFile(AUDIO_FILE) as source:
    audio = r.record(source)  # read the entire audio file

# recognize speech using Google Speech Recognition
try:
    # for testing purposes, we're just using the default API key
    # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
    # instead of `r.recognize_google(audio)`
    anwser = r.recognize_google(audio, language="zh-TW")
    print("Google Speech Recognition thinks you said " + anwser)
#    if (anwser == (u"關燈")) :
#         print("transfer the instruction to pi")
#         while True:
#                ser.write(1)
except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))
