from PIL import Image
# Take two images for blending them together
image1 = Image.open("./data/apple.jpg")
image2 = Image.open("./data/orange.jpg")

# Make sure images got an alpha channel
image5 = image1.convert("RGBA")
image6 = image2.convert("RGBA")

# alpha-blend the images with varying values of alpha
alphaBlended1 = Image.blend(image5, image6, alpha=.4)
alphaBlended2 = Image.blend(image5, image6, alpha=.6)

# Display the alpha-blended images
alphaBlended1.show()
alphaBlended2.show()
