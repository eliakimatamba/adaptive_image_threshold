# adaptive_image_threshold

The code creates an image from a ```PPM``` file
The code first opens the input file and reads in the pixel data
Then it creates a new image with width, height, and max values of 255
Next it sets up the memory for that image by allocating space for ```width * height * sizeof(pixel)```
It then copies in 3 bytes of data at a time until there is enough to fill out the entire structure (width * height)
Finally it closes the input file and returns its newly created image to be used elsewhere
The function ```createImage()``` takes two parameters: width and height
It allocates memory for an empty structure called temp which will hold information about this particular instance of creating an image from a PPM file
Then it initializes ```temp->data ```with zeros because we don't need any pixels yet when we are just creating this one instance of our program's output
After that, ```memset()``` is used to clear out all but three bytes of each row so that they can be filled later on with pixel data read from ```fread()```
Finally, ```writePPM()``` writes out some text into our newly created PPM file before closing it off again
The code is a simple example of how to create an image from pixels
The first line declares the pixel structure, which is used to store the color information for each pixel in an image
The next line declares the image structure, which contains all of the information about the dimensions and data type needed to create an image
The last line creates a function that can be used to read PPM images into memory and write them back out as PPM files.
The code is a program that reads an image file, creates two new images from it, and then averages the pixel values of each pixel in the original image
The first line of code declares a variable called fname which is 100 characters long
The second line of code prints out "Enter the name of the file to be read." The third line scans in "fname" as input into this program
This will create an image with dimensions equal to those specified by fname
The fourth line creates an image called img1 with dimensions equal to those specified by fname and assigns it to a variable called img1
Then, on the fifth line, another variable is created and assigned to img2 with dimensions equal to those specified by fname
On lines six through nine, three variables are declared: ```w (the width), h (the height), i (a loop counter), j (another loop counter)```
These variables are used for iterating over every pixel in both images simultaneously so that they can be averaged together later on in this function call using getRpixel(), getGpixel(), and getBpixel().
The code is a function that takes an image as input and outputs the pixels to be displayed
The first line of the code declares the function prototype for ```putRpixel```, which takes three arguments: ```image *img, int x, int y```
The second line of the code declares the function prototype for ```putGpixel```, which also takes three arguments: ```image *img, int x, int y```
The third line of the code declares the function prototype for ```putBpixel```, which also takes three arguments: ```image *img, int x, int y.```
The code starts by creating two arrays, ```img``` and ```img2```
The first array is used to store the image that will be analyzed while the second array stores a copy of the original image
Next, it creates an integer variable called w which represents the width of the image in pixels and h which represents its height in pixels
It then sets i to 0 and j to 0 so that they are both at their respective left-most corners of their respective images
Next, it loops through each pixel on both images using for loops with 50 iterations per loop ```(i < i + 50; j < j + 50)```
For each iteration, it calculates how many times this pixel has been seen during this iteration by adding up all three colors' values from ```getRpixel()```, getGpixel(), and getBpixel()
Then it divides these numbers by ```3 * 50 * 50``` because there are three colors being averaged together for every pixel on each row/column of each image
Finally, after iterating through all pixels on both images once more (for a total of 100 iterations), it prints out some text representing what color was found most often in this block before dividing them into two separate arrays: fname1 for reds and fname2 for greens/
The code will create two files, ```fname1``` and ```fname2```
The first file will contain the pixel values of the red channel in a 50x50 grid, while the second file will contain the pixel values of the green channel in a 50x50 grid.
