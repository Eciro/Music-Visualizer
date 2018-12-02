import matplotlib.pyplot as plt
from scipy.io import wavfile as wav
from scipy.fftpack import fft
import numpy as np
import sys

music = sys.argv[1]
rate, data = wav.read(music)
fft_out = fft(data, 16)
real = fft_out.real

bins = len(real)//16

file = open("fft.txt","w")

nums = [b[0] for b in real]

for i in range(len(nums)):
    file.write(str(nums[i]))
    if(i < len(nums)-1):
        file.write(', ')

file.close()