#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv ;
int process(int x,int y,int sizeA,int sizeB,String path)
{
	int status = 1 ;
	try{
		Mat img= imread(path);
		Mat roi = img( Rect(x,y,sizeA,sizeB)) ;
		CvScalar s;
		//宣告 IplImage*型別的img02
		IplImage *img02 ;               
		//Matimg的位置丟給img02
		img02 = &IplImage(roi);         
		cvNamedWindow("img02",0);
		cvShowImage("img02",img02);
		waitKey(0);

		//image長寬
		double width=img02->width;
		double height=img02->height;

		//uchar Tdata[512][512][1];
		double sum = 0.0 ;
		int i,j;
	
		for(i=0;i<width;i++){ 
			for(j=0;j<height;j++){
				 //讀每個pixel的灰階值
				s = cvGet2D(img02,i,j);
				//Tdata[i][j][0]=img02->imageData[i*img02->width+j];
				sum = sum +s.val[0] ;
			}
		}
		double powSum,delta,standard,mn ;
		printf("[SUM]=>%f\n",sum);
		mn = (sum/(width*height)) ;
		printf("[MEAN]=>%f\n",mn);

		powSum = 0.0 ;
		delta = 0.0 ;
		for(i=0;i<width;i++){
			for(j=0;j<height;j++){
				s = cvGet2D(img02,i,j); //讀每個pixel的灰階值
				//Tdata[i][j][0]=img02->imageData[i*img02->width+j];
				delta = (s.val[0]-mn) ;
				powSum += pow(delta,2) ;
			}
		}
		double n = (width * height) - 1 ;
		//printf("[powSum]=>%f\n",powSum);
		standard = (powSum / ((width * height) - 1)) ;
		standard = sqrt(standard);
		printf("[standard]%f\n",standard);
		//save file
		cvSave("ROI.txt",img02);
		status = 0 ;
	}catch(Exception e){
		printf("%d\n",e);
	}
	//回傳(0:成功,1:失敗)
	return status ;
}

int main()
{
	//依不同需求填入不同路徑及ROI範圍
	//圖片路徑
	String path = "Lenna.bmp" ;
	//起始座標
	int x = 440 ;
	int y = 300 ;
	int sizeA = 4 ;
	int sizeB = 4 ;
	int status = process(x,y,sizeA,sizeB,path);
	//0:成功
	printf("[STATUS =>%d\n",status);
}