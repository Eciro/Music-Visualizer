import matplotlib.pyplot as plt
from scipy.io import wavfile as wav
from scipy.fftpack import fft
import numpy as np
#import csv

rate, data = wav.read('solo.wav')
fft_out = fft(data, 16)
real = fft_out.real

bins = len(real)//16

file = open("fft.txt","w")

nums = [b[0] for b in real]

for i in range(len(nums)):
    if(nums[i] > 20 and nums[i] <= 20,000):
        file.write(str(nums[i]))
    if(i < len(nums)-1):
        file.write(', ')

file.close()