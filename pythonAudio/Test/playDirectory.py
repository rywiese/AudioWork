import sys
sys.path.append('/usr/local/lib/python2.7/site-packages')
import pyaudio
import wave
import os

NUMFRAMES = 1024

pie = pyaudio.PyAudio()

dirName = sys.argv[1]
dirlist = os.listdir(dirName)
for inFileName in dirlist:
    inFileName = ('%s/%s' % (dirName, inFileName))
    
    waveFile = wave.open(inFileName, 'r')
    
    chip = pie.open(rate = waveFile.getframerate(),
                      channels = waveFile.getnchannels(),
                      format = pie.get_format_from_width(waveFile.getsampwidth()),
                      output = True,
                      output_device_index = 2)
    
    frames = waveFile.readframes(NUMFRAMES)
    while(len(frames) > 0):
        chip.write(frames)
        frames = waveFile.readframes(NUMFRAMES)
    
    waveFile.close()

chip.stop_stream()
chip.close()
pie.terminate()
