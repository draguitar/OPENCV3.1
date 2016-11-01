#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void Show_Image(Mat&, const string &);


/*

generate the twirl effect

*/

#include <time.h>

using namespace std;
using namespace cv;

#define pi 3.1415926

int main()
{
    string Img_name("Bug.bmp");
    Mat Img;
    Img=imread(Img_name);

    Mat Img_out(Img.size(), CV_8UC3);
    Img.copyTo(Img_out);

    int width=Img.cols;
    int height=Img.rows;

    float angle = pi/3;
    float centreX = 0.5;
    float centreY = 0.5;
    float radius = 0;

    if (radius==0) radius=std::min(width, height)/2;

    float icentreX=width*centreX;
    float icentreY=height*centreY;
    float radius2=radius*radius;

    float dx,dy,new_x,new_y;
    float p,q,x1,y1;
    float distance, distance2;
    float a;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {

             dx=x-icentreX;
             dy=y-icentreY;

             distance2=dx*dx+dy*dy;

             if (distance2>radius2)
             {
                 new_x=x;
                 new_y=y;
             }
             else
             {
                 distance=sqrt(distance2);
                 a = std::atan2(dy, dx) + angle * (radius-distance) / radius;
                 new_x = icentreX + distance*cos(a);
                 new_y = icentreY + distance*sin(a);
             }

            if(new_x<0)         new_x=0;
            if(new_x>=width-1)  new_x=width-2;
            if(new_y<0)         new_y=0;
            if(new_y>=height-1) new_y=height-2;

            x1=(int)new_x;
            y1=(int)new_y;

            p=new_x-x1;
            q=new_y-y1;

            for (int k=0; k<3; k++)
            {
                Img_out.at<Vec3b>(y, x)[k]=(1-p)*(1-q)*Img.at<Vec3b>(y1, x1)[k]+
                                        (p)*(1-q)*Img.at<Vec3b>(y1,x1+1)[k]+
                                        (1-p)*(q)*Img.at<Vec3b>(y1+1,x1)[k]+
                                        (p)*(q)*Img.at<Vec3b>(y1+1,x1+1)[k];
            }

        }
    }

    Show_Image(Img_out, "out");
    cout<<"All is well"<<endl;

    //Sava 圖片
	imwrite("Out.jpg", Img_out);

    waitKey();
}


// define the show image
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

void Show_Image(Mat& Image, const string& str)
{
    namedWindow(str.c_str(),CV_WINDOW_AUTOSIZE);
    imshow(str.c_str(), Image);

}
