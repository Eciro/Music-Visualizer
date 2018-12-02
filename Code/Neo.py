import matplotlib.pyplot as plt
from scipy.io import wavfile as wav
from scipy.fftpack import fft
import numpy as np
import sys

# music = sys.argv[1]

music = 'solo.wav'
rate, data = wav.read(music)
data = np.max(data, 1)

sample_rate = 4
step = rate/sample_rate

fft_dims = 2**10

length = len(data)
total_steps = np.ceil(length/step)

fft_data = np.zeros((total_steps, fft_dims))

for t in np.arange(total_steps):
    fft_out = fft(data[t*step:], fft_dims).real
    fft_data[t,:] = fft_out

np.savetxt("fft.csv", fft_data, delimiter=",")