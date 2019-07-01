import cv2
from matplotlib import pyplot as plt

def on_press(event):
    print('you pressed', event.button, int(event.xdata), int(event.ydata))

fig = plt.figure()
cid = fig.canvas.mpl_connect('button_press_event', on_press)

imageFile = './data/lena.jpg'
imgGray = cv2.imread(imageFile, cv2.IMREAD_GRAYSCALE)
plt.axis('off')

plt.imshow(imgGray, cmap = "gray", interpolation='bicubic')
plt.show()
