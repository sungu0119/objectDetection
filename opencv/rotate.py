from PIL import Image

im = Image.open('data/lena.jpg')

# 크기를 600x600 으로
img2 = im.resize((600, 600))
img2.save('lena-1000.jpg')

# 90도 회전
img3 = im.rotate(90)
img3.save('lena-rotate.jpg')

im.show()
img2.show()
img3.show()
