from PIL import Image

im = Image.open('data/lena.jpg')
im.show()
cropImage = im.crop((100, 100, 350, 350))
cropImage.show()
cropImage.save('data/lena-crop.jpg')





