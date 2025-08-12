from PIL import Image
import time
import sys

#config
c_width = 50
img_p = "sample.jpg"
author = "unknown"
output = "out/sample.cdc"


#don't mess
img = Image.open(img_p).convert("RGB")
resized = img.resize((c_width, int(img.height * (c_width / img.width))))
result = "CDC;"

for y in range(resized.height):
  for x in range(resized.width):
    pix = resized.getpixel((x, y))
    pix2 = (pix[0] >= 128, pix[1] >= 128, pix[2] >= 128)
    result += str(pix2[2] * 4 + pix2[1] * 2 + pix2[0])
  if y < resized.height - 1:
    result += "."
  print("size of file: {} bytes ({} kilobytes)".format(len(result), round(len(result) / 1000, 2)), end="\r")
result += ";"
result += author.replace(";", "_")
result += ";"
result += str(int(time.time()))
print("size of file: {} bytes ({} kilobytes)".format(len(result), round(len(result) / 1000, 2)))

with open(output, "w") as f:
  f.write(result)

print("done")