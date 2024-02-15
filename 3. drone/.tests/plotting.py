import serial
import matplotlib.pyplot as plt
import numpy as np

ser = serial.Serial('COM8')

data_points = []
count = 0

try:
    while count < 1000:
        data = ser.readline().decode().strip()
        data_points.append(data)
        count += 1

except KeyboardInterrupt:
    print("bye bro....")

finally:
    ser.close()

data_points = np.array(data_points)

data_points.sort()

mean_of_data = data_points.mean()

print(mean_of_data)
# print(data_points)


