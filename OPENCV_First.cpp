#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

 
using namespace cv;
using namespace std;

using namespace cv;
using namespace std;
int main (int argc , char ** argv){
	if (argc!=2){
		cout << "Usage : OpenCV_Test ImageToDisplay" << endl;
		return -1 ;
	}

	Mat img ;
	img =  imread( argv[1], CV_LOAD_IMAGE_COLOR);
	if(img.empty()){
		cout << "Could not open or find the image" << endl;
		return -1 ;
	}

	namedWindow("Image", CV_WINDOW_AUTOSIZE);
	imshow("Image",img);
	waitKey(0);
	return 0 ;
}