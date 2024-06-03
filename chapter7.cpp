#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
///////////////////  identify objects` shape  //////////////////////

void getContours(Mat img, Mat imgDilate) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDilate, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contours, -1, Scalar(255, 0, 255), 3);
    //to filter not target one

    vector<vector<Point>> conPoly(contours.size()); //declare contours` polygon
    vector<Rect> boundRect(contours.size());
    string objectType;
    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);//calculate area
        cout << area << endl;
        if (area>1000) {
            float peri = arcLength(contours[i], true); //declare perimeter and calculate the archway length
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//approximate the polygon(  , max error,closure )
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 3);
            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);

            //(img,top-left,bottom-right,bgr,thickness)
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

            int objCor = (int)conPoly[i].size();
            if (objCor == 3) objectType = "Tri";
            else if (objCor == 4) {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                if (aspRatio > 0.95 && aspRatio < 1.05) objectType = "Square";
                else objectType = "Rect";
            }
            else if (objCor > 4) objectType = "Circle";
            putText(img,objectType,{boundRect[i].x,boundRect[i].y-2}, FONT_HERSHEY_TRIPLEX, 0.5, Scalar(89, 50, 255), 1.5);
        }
    }
}

void main() {

    string path = "Resources/shapes.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDilate;

    //preprocessing

    //imgGray
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    //Gaussian Blur
    GaussianBlur(imgGray, imgBlur, Size(3, 5), 3, 0);
    //edge detection
    Canny(imgBlur, imgCanny, 150, 50);
    //dilatiom
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 5));
    dilate(imgCanny, imgDilate, kernel);

    getContours(img, imgDilate);

    imshow("Image", img);
    waitKey(0);//add a delay,'0'==infinity

}