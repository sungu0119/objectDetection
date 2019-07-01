import cv2
import numpy as np

src = cv2.imread("data/lena.jpg", cv2.IMREAD_COLOR)
b, g, r = cv2.split(src)

height, width, channel = src.shape
zero = np.zeros((height, width, 1), dtype = np.uint8)

zzr = cv2.merge((zero, zero, r))
cv2.imshow("zzr", zzr);

cv2.waitKey(0)
cv2.destroyAllWindows()
