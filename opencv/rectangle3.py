import numpy as np
import cv2

img = np.zeros(shape=(512,512,3), dtype=np.uint8) + 255
#img = np.full((512,512,3),(0,0,255), dtype=np.uint8) 


x1, x2 = 100, 400
y1, y2 = 100, 400

cv2.rectangle(img, (x1, y1), (x2, y2), (0, 0, 255),-1)

px1 = 250, 40
py1 = 250, 450

cv2.line(img, px1,py1, (255,0,0), 2)

px2 = 40, 250
py2 = 450, 250

cv2.line(img, px2, py2, (255, 0, 0), 2)

imgRect1 = (x1, y1, x2-x1, y2-y1)
imgRect2 = (x1, y1, x2-x1, y2-y1)

retval1, rpt1, rpt2 = cv2.clipLine(imgRect1, px1, py1)
retval2, rpt3, rpt4 = cv2.clipLine(imgRect2, px2, py2)

if retval1:
    cv2.circle(img, rpt1, radius=5, color=(0, 0, 0), thickness=-1)
    cv2.circle(img, rpt2, radius=5, color=(0, 0, 0), thickness=-1)

if retval2:
    cv2.circle(img, rpt3, radius=5, color=(0, 0, 0), thickness=-1)
    cv2.circle(img, rpt4, radius=5, color=(0, 0, 0), thickness=-1)

cv2.imshow('img', img)
cv2.waitKey()
cv2.destroyAllWindows()
