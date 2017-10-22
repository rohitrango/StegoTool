# Steganography Tool 

## Introduction 
This program is an example to show how files can be hidden inside an image by modifying the pixel data. In this mini steganography tool, bitmap images are used and text files are hidden in it. Other file types may give unexpected results.

To use this tool, simply press the number keys corresponding to the list items shown in the menu.

To encode/decode, enter the name of the bmp image when prompted, then press the desired number key according to the list items. In case the file to be hidden is too large, or the file doesn't exist, errors are thrown up on the screen (enough error management has been done).

In the folder named "files", some .bin files are present. These contain plain text of what has to be displayed on the screen corresponding to different menus. A cpp file "fileWriter.cpp" has been written and used to write the .bin files. This file has no involvement in the Steganography tool.

Please do not relocate the folder named "files" or DO NOT DELETE anything in it (except the fileWriter.cpp if you wish).

Some test image files are given as well. Please feel free to choose your own BMP FILES ONLY and .txt files for hiding. Please ensure that these files are kept in the same directory as that of the executable before running the file.

Entering wrong password in the encoding procedures can give garbage text files. So do remember to enter the correct password.

## Building
#### Windows
1. Install MinGW32 and MSYS
2. Open the Mingw32 shell
3. Navigate to the project root
2. Use the following command - <code>make</code>

Run with the command - <code>stego.exe</code>

#### Ubuntu
1. Install g++ with - <code>sudo apt-get install g++</code>
2. Navigate to the project root
3. Use the following command - <code>make</code>

Run with the command - <code>./stego.out</code>

## Credits-

Made by Nilesh Gupta -

1. bitmap_n.cpp
2. bitmap.h
3. (Searched articles for algorithms for encoding/decoding)

Made by Rohit Kumar Jena -

1. bitmap_r.cpp
2. UI.cpp
3. UI.h
4. All the .bin files, fileWriter.cpp , and this README file.

The encode/decode test algorithm (in bitmap_n.cpp) was used as a framework for development of other encode/decode algorithms.

Thank you.

Made by-
Nilesh Gupta (Roll 150050059)
Rohit Kumar Jena (Roll 150050061)
