#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void recogniseStickersByThreshold(Mat &image,vector<vector<Point>> &Line1, vector<vector<Point>> &Line2) {
    Mat image_hsv;
   
    vector<vector<Point> > contours;
    cvtColor(image, image_hsv, COLOR_BGR2HSV ); // Преобразуем в hsv
    Mat tmp_img(image.size(),CV_8U);
    Scalar min_max_scals[4] = { Scalar(12,50,220), Scalar(25,0,100), Scalar(16,255,255), Scalar(60,80,255)};
    // Выделение подходящих по цвету областей. Цвет задается константой :)
    for (int i=0; i<2; i++) {
    inRange(image_hsv, min_max_scals[i], min_max_scals[i+2], tmp_img);
   
    // "Замазать" огрехи в при выделении по цвету
    dilate(tmp_img,tmp_img,Mat(),Point(-1,-1),3);
    erode(tmp_img,tmp_img,Mat(),Point(-1,-1),1);
    //Выделение непрерывных областей
    findContours(tmp_img,contours,RETR_EXTERNAL, CHAIN_APPROX_NONE);
    if (contours.size()==1) {
    //Для каждой области определяем ограничивающий прямоугольник
    Rect rect=boundingRect(contours[0]);
    int x1 = rect.x;
    int y1 = rect.y;

    int w = rect.width;
    int h = rect.height;

    int x4,y2;
    y2 = y1 + h;
    x4 = x1 + w;

    int xc = (x1+x4)/2;
    int yc = (y1+y2)/2;

    Line1[i].push_back(Point(xc,yc));

    int size = 5;
    if (Line1[i].size()>size){
        vector <int> mas;
        for (int j=0;j<size;j++)
            mas.push_back(0);

            int sumx = 0;
            int index = 0;

            for (int j=0; j<Line1[i].size(); j++) {
                sumx -=mas[index];
                mas[index] = Line1[i][j].y;
                sumx += mas[index];
                index++;
                if (index >= size)
                index = 0;
            }
            Line2[i].push_back(Point(Line1[i].back().x, sumx/size));
            
            for (int j=0; j<Line2[i].size()-1; j++)
            line (image,Line2[i][j+1], Line2[i][j], Scalar(0,0,255),2);
    }
            for (int j=0; j<Line1[i].size()-1;j++)
                line(image,Line1[i][j+1],Line1[i][j], Scalar(0,0,255),2);

            rectangle(image, rect, Scalar(0,255,0),2);
            
        }
    }   
}

int main(){

    VideoCapture cap("test_video.mp4"); // open the video file for reading
    if ( !cap.isOpened() ) return -1;

    //cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms
    double fps = cap.get(CAP_PROP_FPS); //get the frames per seconds of the video
    cout << "Frame per seconds : " << fps << endl;

    vector<vector<Point>> Line1;
    vector<vector<Point>> Line2;
    vector<Point> x;


    for (int i=0; i<2; i++) {
        Line1.push_back(x);
        Line2.push_back(x);
    }

    namedWindow("MyVideo",WINDOW_AUTOSIZE); //create a window called "MyVideo"
    while(1) {

        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video
        if (!bSuccess) {
        cout << "Cannot read the frame from video file" << endl;
        break;
        }
        
        recogniseStickersByThreshold(frame,Line1,Line2);
        resize(frame,frame, Size(800,600));
        imshow("MyVideo", frame); //show the frame in "MyVideo" window
        if(waitKey(30) == 27) {
        break;
        }
    }
}
