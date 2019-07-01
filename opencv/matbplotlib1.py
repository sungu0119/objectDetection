import cv2

from matplotlib import pyplot as plt

imageFile = './data/lena.jpg'
# BGR포맷으로 읽어서 img 객체에 저장한다.
img = cv2.imread(imageFile)

# cv2.IMREAD_COLOR
# X, Y축을 표시하지 않는다.
plt.axis('off')

#plt.imshow(imgBGR)
#plt.show()
# plot에 그리기 위해서는 RGB순서의 포맷이어야 한다.

imgRGB = cv2.cvtColor(imgBGR,cv2.COLOR_BGR2RGB)
plt.imshow(imgRGB) # plot에 imgRGB를 그리고
plt.show( )
