from PIL import Image, ImageFilter
    
im = Image.open('data/lena.jpg')
blurImage = im.filter(ImageFilter.BLUR)
blurImage.show()
blurImage.save('data/lena-blur.jpg')
