import cv2
import numpy as np

src = cv2.imread("data/captin.jpg", cv2.IMREAD_COLOR)
#b, g, r = cv2.split(src)

#height, width, channel = src.shape
#gray = np.full((height, width, 1),80, dtype=np.uint8)
#zero = np.zeros((height, width, 1), dtype=np.uint8)
#white = np.full((height, width, 1), 255, dtype=np.uint8)
hsv = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)
lower_red = cv2.inRange(hsv, (0,100,100), (50,255,255))
upper_red = cv2.inRange(hsv, (150,100,100), (180,255,255))
added_red = cv2.addWeighted(lower_red, 1.0, upper_red, 1.0, 0.0)

red = cv2.bitwise_and(hsv, hsv, mask = added_red)
red = cv2.cvtColor(red, cv2.COLOR_HSV2BGR)

b,g,r = cv2.split(red)

src2 = cv2.imread("data/captin.jpg", cv2.IMREAD_GRAYSCALE)
mix = cv2.merge((src2, src2, r))


cv2.imshow("red", red)
cv2.imshow("mix", mix)
cv2.imshow("src", src)

cv2.waitKey(0)
cv2.destroyAllWindows()
