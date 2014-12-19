Image Processing WWS 2014
=====================================

This Repository contains:

1. Reference Codes ( For all Modules which were covered )
2. Codes written by attendees of the workshop.
(In two folders, **Phase-1 Codes** and **Phase-2 Codes** respectively)
3. Installation Instructions:
  - For Windows Users
  - For Linux/Mac Users
4. Resources:
  - Feature Extraction and Image Processing by Mark Nixon and Alberto Aguado - E-Book
  - IP Workshop Questionnaire
  - Serial Communication Header and Source Files (For Visual Studio)
  - Shell Script to Compile OpenCV Programs (For Linux Users) 

##Mentors
###Phase I
* Abhinav Jain
* Abhinav Aggarwalla
* Shrey Garg
* Arnav Jain

###Phase II
* Abhinav Jain
* Udai Bhardwaj
* Arun Patro

##Topics Covered:
1. Introduction to Images, Channels and Pixels.
2. Basic **C++** - Classes and Objects, Standard Template Library.
3. Introduction to **OpenCV** library and **Visual Studio IDE** ( For Windows Users )
4. Basic Image Input/Output
5. **Grayscale Image** - Basics, Conversion of RGB to Grayscale Image.
6. **Binary Image** - Basics, Conversion from Grayscale using Manual Threshold.
7. **Histogram** - Plotting Histogram for Grayscale Image, Calculating Threshold to convert it to a binary image using Cumulative Frequency method.
8. **Adaptive Thresholding** - Making Binary Image using Local Mean.**
9. **Trackbar** - Implementation in OpenCV, Using trackbar to vary threshold for conversion from grayscale to binary image.
10. **Noise Reduction**
  * **In Binary Images** - Erosion and Dilation as Morphological Transformations, and combining them to find resultant noise-reduced image.
  * **In Grayscale Images** - Blurring/Smoothening the Image using Mean, Median or Gaussian Filters.*
11. **Edge Detection** - Need for detecting Edges in an Image, **Naive** Edge Detection Algorithm, **Prewitt*** and **Canny** Edge Detection.
12. **Video Processing** - Video as a continous set of images/frames, processing video from file/camera, implementing trackbar to vary threshold to convert to binary.
13. **Colour Detection** - Need for colour detection, different types of colour spaces - RGB/HSV/HSL, Colour Detection in RGB Colour Space and in HSV Colour Space.
14. **Blob Detection** - Detection of Blobs in a Binary Image using **Naive Algorithm**** , **Breadth-First-Search** by implementing a queue. Also a brief idea on how to use **Depth-First-Search**(or Recursion) to do the same.
15. **Shape Detection** - Need for Shape Detection, **Naive** Algorithms based on Geometrical Features of Shapes, Extracting **Contours** and Approximating Polygons for each contour extracted.
16. **Hardware** - Description of the complete working of the system, Explanation of Different Modules (Image Processing, Intelligence, and Controls), What is the final result of the Image Processing that is done,
Introduction to **Microcontroller(AVR/Arduino)** and **Motor Driver**, **Serial Communication** (Basics, Baud Rate), Integrating Serial Communication in your code.

\*Not Covered in First Phase <br>
\*\*Not Covered in Second Phase

##Problem Statements:

  The problem statement given to **First Years**:

  *Given a virtual arena/feed of an arena in the form of a videogame, in which different types of coloured shapes are falling from the top, your aim is to navigate towards different shapes one after the other in a fixed order and collect as many shapes as possible.*

  The problem statement given to **Second Years**:

  *Given the feed of a camera attached to the robot at the front, use Image Processing to follow a lane, and take turns at junctions and stop at the end.*
