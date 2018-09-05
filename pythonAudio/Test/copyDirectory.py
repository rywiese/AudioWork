import sys
sys.path.append('/usr/local/lib/python2.7/site-packages')
import pyaudio
import wave
import os

NUMFRAMES = 1024

pie = pyaudio.PyAudio()