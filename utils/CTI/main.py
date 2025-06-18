from PIL import Image
import time
import sys

#config
cnv_p = "sample.cdc"
output = "out/sample.bmp"
img_w = 150


#don't mess
with open(cnv_p, "r") as f:
  data = f.read()

canvas = data.split(";")
pixelD = canvas[1].split(".")
w, h = len(pixelD[0]), canvas[1].count(".") + 1

print("width: {}; height: {}".format(w, h))

img = Image.new("RGB", (w, h), color="white")

for y in range(h):
  for x in range(w):
    img.putpixel((x, y), (255 * (int(pixelD[y][x]) & 1 != 0), 255 * (int(pixelD[y][x]) & 2 != 0), 255 * (int(pixelD[y][x]) & 4 != 0)))
    print("progress: {}%".format(round(((x * y) / (w * h)) * 100, 2)), end="\r")

print("\nresizing")
resized = img.resize((img_w, int(img.height * (img_w / img.width))), resample=Image.Resampling.NEAREST)
print("new width: {}; new height: {}".format(img_w, int(img.height * (img_w / img.width))))
print("saving")
resized.save(output)
print("done")