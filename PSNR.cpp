#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv ;
int process_PSNR(IplImage* img1,IplImage* img2)
{
	int status = 1 ;
	try{
		//channel��
		printf("nChannels=> %d\n",img1->nChannels);
		//�Ϥ����e
		int w=img1->width;  
		int h=img1->height;  
		uchar* ptr1=(uchar*)img1->imageData;  
		uchar* ptr2=(uchar*)img2->imageData;  
		double mse=0;  

		for(int i=0;i<h;++i,ptr1+=w,ptr2+=w)  
		{  
			for(int j=0;j<w;++j)  
			{  
				mse+=(ptr1[j]-ptr2[j])*(ptr1[j]-ptr2[j]);  
			}  
		} 

		mse = mse/(w*h);  
		double psnr=10*log10(255*255/mse);  
		printf("------------------\n");
		printf("[mse=>  %f\n",mse);
		printf("[psnr=> %f\n",psnr);
		cvWaitKey(0);
		status= 0 ;

	}
	catch(Exception e)
	{
		printf("%d\n",e);
	}
    //�^��(0:���\,1:����)
	return status ;
}

int main()
{
	//��J�n�������i�Ϥ����|
	IplImage* img1= cvLoadImage("Pattern1.bmp",1);
	IplImage* img2= cvLoadImage("Pattern2.bmp",1);
	int status = process_PSNR(img1,img2);
	//0:���\
	printf("[STATUS =>%d\n",status);
}