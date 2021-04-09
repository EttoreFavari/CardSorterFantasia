#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


Mat src_gray;
int thresh = 100;
RNG rng(12345);


#define BLUR false

void thresh_callback(int, void*);


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Non abbastanza argomenti, selezionare immagine.\n";
        return -1;
    }
    char* pathfile = argv[1];
    Mat src = imread(pathfile, IMREAD_COLOR);
    if (src.empty()) {
        cerr << "This bitch empty! YEEET\n";
        return EXIT_FAILURE;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    if (BLUR) {
        blur(src_gray, src_gray, Size(3, 3));
    }


    namedWindow("Output", WINDOW_AUTOSIZE);
    const char* source_window = "Input";
    namedWindow(source_window);
    imshow(source_window, src);
    const int max_thresh = 255;
    createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);




    imshow("Input", src);
    imshow("Output", src_gray);
    waitKey();

    return 0;
}

Rect* big_Rect;

void thresh_callback(int, void*)
{
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);
    vector<vector<Point> > contours;
    findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f>centers(contours.size());
    vector<float>radius(contours.size());
    big_Rect = &boundRect[0];

    for (size_t i = 0; i < contours.size(); i++) {
        boundRect[i] = boundingRect(contours[i]);

       // cout << "arrivaqua\n";
        if ((big_Rect)->area() < boundRect[i].area()) {
            big_Rect = &boundRect[i];
        }
    }
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));

    rectangle(drawing, big_Rect->tl(), (big_Rect)->br(), color, 2);
    /*
        for( size_t i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
            drawContours( drawing, contours, (int)i, color );
            rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2 );
        }*/
    imshow("Contours", drawing);
}