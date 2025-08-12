# ITC (Image To Cdraw canvas)
this program was made to transform any type of image into a Cdraw canvas of any size (if your RAM supports it)

## how to use
there are 4 variables in the program's code:

```py
c_width = 50
img_p = "sample.jpg"
author = "unknown"
output = "out/sample.cdc"
```

`c_width` defines the width of the output canvas  
`img_p` defines the image path  
`author` defines the author's name (you or the maker of the image)  
`output` defines the path where the canvas will be put onto

change those to your liking, run the program, and before you know it, it's done

## how to view

compile & open Cdraw, but set the `-fl` parameter to the size of the file + 1, so if your file is 3000 bytes big,
set the `-fl` parameter to 3001  
like this:

```sh
./main -fl 3001
```

**IMPORTANT: if your file is any smaller than 2047 bytes you don't need the `-fl` parameter**

then view the canvas like you would view any other canvas (press 2 on the main menu and insert the path to the canvas)

## other

sample image from [wikipedia](https://en.wikipedia.org/wiki/List_of_monochrome_and_RGB_color_formats)