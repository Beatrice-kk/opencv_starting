#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;
/////////////////// object detect //////////////////////
//
void main() {

    string path = "Resources/test.png";
    Mat img = imread(path);

    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");
    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);
    for (int i = 0; i < faces.size(); i++) {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(100, 100, 255), 5);
    }
    
    imshow("Image", img);
    waitKey(0);//add a delay,'0'==infinity

}