This is an attempt to make pdf creation an easy, fast and language agnostic process.

It has 3 functions:

1) Create a pdf file from a text command file.

2) Create a pdf from a pdf template and a text command file.

3) (Optional) Convert a "simple" xlsx file to pdf (support basic xlsx features for big pdf reports)

Ideal for server applications that need to generate pdf reports very frequently.

Supports many commands for any basic (or rich especially with the help of images) 
pdf report with many more to be added and uppon requests or contributions.

*It also has a command for automatic qr-code image in a pdf page from a string input.


Many thanks to these libs authors:

https://github.com/galkahana/PDF-Writer
https://github.com/RaymiiOrg/cpp-qr-to-png
https://www.libxl.com/ (paid for the xlsx --> pdf create function)

without them, this project could not be possible,
and https://certusonline.com for sponsoring it.



Creates one thread per input page... so have that in mind (possible to make that optional or dynamic).

See the main.cpp example for usage (very simple).


Compile:

Create a 'build' folder inside libs\PDF-Writer-master
and then inside it run: cmake .. && make
and then go to the root folder and run the compilation command (Linux).
Then run: ./main 

Will to add cmake support fo the whole project...


Compile:

make

Run:

./main


Input Commands Format:


#Variable Symbol: ^
e.g.:
V, QRVAR, https://google.com
Q, 10, 10, 100, 1.0, ^QRVAR

# Set Variable
V, Name, StringValue

# Line
L, fromX, fromY, toX, toY, lineWidth, lineColor, lineOpacity

# Image with Base64 data input
I, X, Y, scaleX, scaleY, imageOpacity, imageType, base64ImageDataBytes

# Image with file path data input
IF, X, Y, scaleX, scaleY, imageOpacity, imageType, imageFilePath

# QRCodeImage from string
Q, X, Y, size, imageOpacity, string

# Rectangle
R, left, bottom, width, height, reactangleColor, rectangleOpacity, fill

# Circle
C, centerX, centerY, radius, circleColor, circleOpacity, fill

# Polygon
Z, polygonColor, polygonOpacity, fill, p1X, p1Y, ...

# Hyperlink
S, lowerLeftX, lowerLeftY, upperRightX, upperRightY, hyperlink

# (Bold or Barcode or Plain Text) Simple text line
('B' or 'C' or nothing)T, startX, startY, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Justified(or Right Aligned) text line
('B' or 'C' or nothing)A, (startX or '#'), startY, endX, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Highlighted text line
('B' or 'C' or nothing)H, startX, startY, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# (Bold or Barcode or Plain Text) Highlighted-Justified(or Right Aligned) text line
('B' or 'C' or nothing)W, (startX or '#'), startY, endX, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# (Bold or Barcode or Plain Text) Simple text line with hyperlink
('B' or 'C' or nothing)TS"hyperlink", startX, startY, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Justified(or Right Aligned) text line with hyperlink
('B' or 'C' or nothing)AS"hyperlink", (startX or '#'), startY, endX, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Highlighted text line with hyperlink
('B' or 'C' or nothing)HS"hyperlink", startX, startY, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# (Bold or Barcode or Plain Text) Highlighted-Justified(or Right Aligned) text line with hyperlink
('B' or 'C' or nothing)WS"hyperlink", (startX or '#'), startY, endX, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# (Bold or Barcode or Plain Text) Underlined text line
('B' or 'C' or nothing)TU, startX, startY, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Justified(or Right Aligned)-Underlined text line
('B' or 'C' or nothing)AU, (startX or '#'), startY, endX, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Highlighted-Underlined text line
('B' or 'C' or nothing)HU, startX, startY, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# (Bold or Barcode or Plain Text) Highlighted-Justified(or Right Aligned)-Underlined text line
('B' or 'C' or nothing)WU, (startX or '#'), startY, endX, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# (Bold or Barcode or Plain Text) Underlined text line with hyperlink
('B' or 'C' or nothing)TUS"hyperlink", startX, startY, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Justified(or Right Aligned)-Underlined text line with hyperlink
('B' or 'C' or nothing)AUS"hyperlink", (startX or '#'), startY, endX, fontSize, textColor, textOpacity, text

# (Bold or Barcode or Plain Text) Highlighted-Underlined text line with hyperlink
('B' or 'C' or nothing)HUS"hyperlink", startX, startY, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# (Bold or Barcode or Plain Text) Highlighted-Justified(or Right Aligned)-Underlined text line with hyperlink
('B' or 'C' or nothing)WUS"hyperlink", (startX or '#'), startY, endX, fontSize, textColor, textOpacity, highlightColor, highlihtOpacity, text

# Paragraph
P, lines, bold, underlined, fontsize, textColor, textOpacity, (highlightColor or 'FFFFFF'), (highlightOpacity or 0), (startX or '-'), startY, alignment, (endX or '-'), ySpacing, excludeLastLine
line1
line2
...
lineN

# Plain Texts (Faster)
PT, textLines, bold, fontSize, textColor, textOpacity
start1X, start1Y, text1
start2X, start2Y, text2
...
startNX, startNY, textN

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Examples:

"H, 5, 790, 25, 0358FF, 1, FFFF00, 1, VEHICLE E-TICKET"
"T, 335, 785, 12, 0358FF, 1, ΔΟΥ ΠΛΟΙΩΝ ΠΕΙΡΑΙΑ, ΑΦΜ: 997595200"
"BA,#,1160,840,12,0129A6,1,PIREAUS, 176 74 - ΑΘΗΝΑ"
"L, 5, 775, 590,775,2,000000, 0.5",
"I, 5, 675, 0.9, 0.9, 1,JPG, /9j/4AA..."
"I, 5, 675, 0.9, 0.9, 1,PNG, OQwd990..."
"R, 5, 790, 215, 20, FF0000, 1, Y"
"R, 5, 790, 215, 20, FF0000, 1, N"
"C, 100, 100.5, 50.5, FF0000, 0.5, Y"
"P, 00FF00, 1, N, 1, 1, 2, 2, 3, 3"
