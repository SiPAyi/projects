import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation
import serial

# Open a serial connection (replace 'COM3' with your actual serial port)
ser = serial.Serial('COM8', 9600)

def rotate_cube(ax, roll, pitch, yaw):
    ax.cla()  # Clear previous frame

    vertices = np.array([[1, 1, 1], [1, -1, 1], [-1, -1, 1], [-1, 1, 1],
                         [1, 1, -1], [1, -1, -1], [-1, -1, -1], [-1, 1, -1]])

    R_roll = np.array([[1, 0, 0],
                       [0, np.cos(roll), -np.sin(roll)],
                       [0, np.sin(roll), np.cos(roll)]])

    R_pitch = np.array([[np.cos(pitch), 0, np.sin(pitch)],
                        [0, 1, 0],
                        [-np.sin(pitch), 0, np.cos(pitch)]])

    R_yaw = np.array([[np.cos(yaw), -np.sin(yaw), 0],
                      [np.sin(yaw), np.cos(yaw), 0],
                      [0, 0, 1]])

    rotated_vertices = vertices.dot(R_yaw).dot(R_pitch).dot(R_roll)

    faces = [[rotated_vertices[j] for j in [0, 1, 2, 3]],
             [rotated_vertices[j] for j in [4, 5, 6, 7]],
             [rotated_vertices[j] for j in [0, 3, 7, 4]],
             [rotated_vertices[j] for j in [1, 2, 6, 5]],
             [rotated_vertices[j] for j in [0, 1, 5, 4]],
             [rotated_vertices[j] for j in [2, 3, 7, 6]]]

    ax.plot_trisurf(rotated_vertices[:, 0], rotated_vertices[:, 1], rotated_vertices[:, 2], triangles=faces, color='blue', alpha=0.6)

    ax.set_xlim([-2, 2])
    ax.set_ylim([-2, 2])
    ax.set_zlim([-2, 2])
    ax.set_xlabel('X-axis')
    ax.set_ylabel('Y-axis')
    ax.set_zlabel('Z-axis')

def update(frame):
    # Read roll, pitch, yaw values from serial port
    roll, pitch, yaw = map(float, ser.readline().decode().strip().split(','))

    # Convert degrees to radians
    roll = np.radians(roll)
    pitch = np.radians(pitch)
    yaw = np.radians(yaw)

    print(roll, pitch, yaw)
    rotate_cube(ax, roll, pitch, yaw)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ani = animation.FuncAnimation(fig, update, interval=50)

plt.show()

# while True:
#     roll, pitch, yaw = map(float, ser.readline().decode().strip().split(','))

#     # Convert degrees to radians
#     roll = np.radians(roll)
#     pitch = np.radians(pitch)
#     yaw = np.radians(yaw)


# Close the serial connection when done
ser.close()
