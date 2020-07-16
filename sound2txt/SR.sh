#!/bin/bash
arecord test.wav -f S16_LE -r 44100 -d 5
python speech_wav.py
