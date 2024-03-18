	This is my first personal project, I have created a C program that edits photo. bmp.h contains the functions that reades from a bmp photo and writes to one, converting the photo to a triple pointer that holds the values of the pixels in the RBG format. Imagine processing.c contains the functions that do as followed :
	flip_horizontal - flips the image	
	rotate left - rotates the image to the left
	crop - crops the image
	extend - extends the image with a border
	paste - pastes another image on the current one
	apply_filter - a filter is a two-dimensional matrix of size (filter_size x filter_size) that defines how each pixel is modified based on its value and the values of its neighbors. Each neighbouring pixel will be multiplied by the value of the filter matrix. The resulting pixel will be the sum of all 
	the modified neighbouring pixels. I have also limited the values. If the new
	R > 255 then it will be limited to 255. Same for R < 0 limited at 0.

	Interactive.c
	It is an interactive c program that can load and store images and filters. You can type commands in the cli
	and the program will run the functions.

e	Exit
l	N M path	Load 
s	index path	Save
ah	index	Apply Horizontal Flip 
ar	index	Apply Rotate
ac	index x y w h	Apply Crop 
ae	index rows cols R G B	Apply Extend
ap	index_dst index_src x y	Apply Paste
cf	size [list of values]	Create filter 
af	index_img index_filter	Apply filter 
df	index_filter	Delete filter
di	index_img	Delete image 

Example of interactive.c:
l 768 1024 ./cat.bmp
l 768 1024 ./dog.bmp
ah 0
ac 1 300 300 200 100
cf 3 0 1 0 1 1 1 0 1 0
af 1 0
ap 0 1 300 300
s 0 ./output.bmp
df 0
di 0
di 0
e

Theses program loads 2 photos. Applies a horizontal flip on cat.bmp (indexed 0) (ah 0). Crops dog.bmp(ac). Creates a filter (3x3 matrix). Applies that filter
on image dog.bmp. Applies a paste on cat.bmp from dog.bmp. Then saves the new image cat.bmp to output.bmp. We then deleate the filters and images and exit.