#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
using namespace cv ;

int main()
{
	double totalValue=0;
	double psnr=0.0;
	IplImage *srcImage = cvLoadImage("Pattern1.bmp",1);
	IplImage *dstImage = cvLoadImage("Pattern3.bmp",1);

	printf("\n[1]：%d\n",srcImage->nChannels);
	printf("\n[2]：%d\n",dstImage->nChannels);

	int NR(srcImage->height),NC(srcImage->width);
	if (srcImage->width!=dstImage->width||srcImage->height!=dstImage->height)
	{
		std::cout<<"usage: Two images must have same size!"<<std::endl;
		return false;
	}
	else if (srcImage->nChannels!=dstImage->nChannels)
	{
		std::cout<<"usage:Two images must have same channels\n 1 dimension\n 3 dimension\n";
		return false;
	}
	
	//若圖片是灰階，直接算totalValue 
	else if (srcImage->nChannels==1||dstImage->nChannels==1)
	{
		for (int i=0;i<NR;i++)
		{
			for (int j=0;j<NC;j++)
			{
				double s1 = cvGetReal2D(srcImage,i,j);//取得像素值
				double s2 = cvGetReal2D(dstImage,i,j);
				double sub = s1-s2;
				totalValue +=pow(sub,2);
			}
		}

	}
	//若圖片是彩色，先轉灰階後，計算totalValue
	else if(srcImage->nChannels==3||dstImage->nChannels==3)
	{
		IplImage *srcData = 0, *dstData= 0;
		srcData = cvCreateImage( cvSize(NR, NC), IPL_DEPTH_8U, 1 );
		dstData = cvCreateImage( cvSize(NR, NC), IPL_DEPTH_8U, 1 );
		cvCvtColor(srcImage,srcData,CV_BGR2GRAY);
		cvCvtColor(dstImage,dstData,CV_BGR2GRAY);
		for (int i=0;i<NR;i++)
		{
			for (int j=0;j<NC;j++)
			{
				double s1 = cvGetReal2D(srcData,i,j);//取得像素值
				double s2 = cvGetReal2D(dstData,i,j);
				double sub = s1-s2;
				totalValue +=pow(sub,2);
			}
		}

	}
	if (fabs(totalValue) < 1e-6)
	{
		psnr = 0;
	}
	else
	{
		double meanValue = totalValue/(NR*NC);
		psnr = 10*log((255*255)/meanValue);
	}
	printf("\n計算PSNR為：%f\n",psnr);
	system("pause");
	//return TRUE;

}