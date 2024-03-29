#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
using namespace cv;

#ifndef __ROTATION_H__
#define __ROTATION_H__

//The margine whitch white or black is considered a color
#define MARGINE_PERCENTAGE 10

#define MARGINE_BLACK 256*MARGINE_PERCENTAGE/100
#define MARGINE_WHITE 256*(100-MARGINE_PERCENTAGE)/100

//real height and lenghts of a magic card
#define REAL_H_C 88.0 //mm
#define REAL_L_C 63.0 //mm
//two rateo of the lenght of the card from the lenght of a real magic card
#define C_RATEO_HL (REAL_H_C/REAL_L_C)
#define C_RATEO_LH (REAL_L_C/REAL_H_C)


//definition of white and black
#define WHITE 255
#define BLACK 0


//the threshold for the Canny
const int thresh_min = 250;
const int thresh_max = 500;

//@param the image that needs to be rotated
//@return the image rotated
//Mat rotate_card(Mat img);

//Expands the image the border of the card
//for the recognition of the rectangle
void control_borders();

//finds the rectangle in the image
void find_contours();

//Take only the rectangle that has the card
//@return
Mat copy_to_cropped_rectangle();

//Finds the bigger rectangle in the vector of points
//@param vector of vector of points
//@return The points that has the bigger rectangle
RotatedRect find_bigger_rectangle( vector<vector<Point>> contours );

#endif
