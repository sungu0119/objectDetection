#https://076923.github.io/posts/Python-opencv-17/
import cv2
    
src = cv2.imread("data/lena.jpg", cv2.IMREAD_COLOR)
b, g, r = cv2.split(src)
inversebgr = cv2.merge((r, g, b))
    
cv2.imshow("b", b)
cv2.imshow("g", g)
cv2.imshow("r", r)
cv2.imshow("inverse", inversebgr)
cv2.waitKey(0)
cv2.destroyAllWindows()


