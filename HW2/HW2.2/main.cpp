#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void recogniseStickersByThreshold(Mat image,vector<Rect> &stickers) {
    Mat image_hsv;
   
    vector< vector<Point> > contours;
    cvtColor(image, image_hsv, COLOR_BGR2HSV ); // Преобразуем в hsv
    Mat tmp_img(image.size(),CV_8U);
    Scalar min_max_scals[4] = { Scalar(12,50,220), Scalar(16,255,255), Scalar(25,0,100), Scalar(60,80,255)};
    // Выделение подходящих по цвету областей. Цвет задается константой :)
    for (int i=0; i<4; i+=2) {
    inRange(image_hsv, min_max_scals[i], min_max_scals[i+1], tmp_img);
   
    // "Замазать" огрехи в при выделении по цвету
    dilate(tmp_img,tmp_img,Mat(),Point(-1,-1),3);
    erode(tmp_img,tmp_img,Mat(),Point(-1,-1),1);
    //Выделение непрерывных областей
    findContours(tmp_img,contours,RETR_EXTERNAL, CHAIN_APPROX_NONE);
    if (contours.size()==1) {
    //Для каждой области определяем ограничивающий прямоугольник
    Rect rect=boundingRect(contours[0]);
    stickers.push_back(rect);
    }
    }
}

int main(){

    VideoCapture cap("test_video.mp4"); // open the video file for reading
    if ( !cap.isOpened() ) return -1;

    //cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms
    double fps = cap.get(CAP_PROP_FPS); //get the frames per seconds of the video
    cout << "Frame per seconds : " << fps << endl;



    namedWindow("MyVideo",WINDOW_AUTOSIZE); //create a window called "MyVideo"
    while(1) {

        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video
        if (!bSuccess) {
        cout << "Cannot read the frame from video file" << endl;
        break;
        }
        vector<Rect> x;
        recogniseStickersByThreshold(frame,x);
        for (int i=0; i<x.size(); i++) {
        rectangle(frame, x[i], Scalar(0,0,255),2);
        }
        resize(frame,frame, Size(800,600));
        imshow("MyVideo", frame); //show the frame in "MyVideo" window
        if(waitKey(30) == 27) {
        break;
        }
    }
}