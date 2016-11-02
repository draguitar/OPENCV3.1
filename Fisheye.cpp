#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
//Ver.OPEN CV 3.1
/**
* 參閱網址：http://docs.opencv.org/master/db/d58/group__calib3d__fisheye.html
*           http://wiki.panotools.org/Fisheye_Projection
* 執行說明
* 目錄下
* command: Fisheye.exe 檔案路徑 "另存新檔檔名(含副檔名)"
* 例: Fisheye.exe .\Lenna.bmp "LennaNew.bmp"
*/
void sampleImage(const IplImage* arr, float index0, float index1, CvScalar& res){
    if(index0<0 || index1<0 || index0>(cvGetSize(arr).height-1) || index1>(cvGetSize(arr).width-1)){
        res.val[0]=0;
        res.val[1]=0;
        res.val[2]=0;
        res.val[3]=0;
        return;
    }
    float index0_fl=floor(index0);
    float index0_cl=ceil(index0);
    float index1_fl=floor(index1);
    float index1_cl=ceil(index1);
 
    CvScalar s1=cvGet2D(arr,(int)index0_fl,(int)index1_fl);
    CvScalar s2=cvGet2D(arr,(int)index0_fl,(int)index1_cl);
    CvScalar s3=cvGet2D(arr,(int)index0_cl,(int)index1_cl);
    CvScalar s4=cvGet2D(arr,(int)index0_cl,(int)index1_fl);
    float x = index0 - index0_fl;
    float y = index1 - index1_fl;
    res.val[0]= s1.val[0]*(1-x)*(1-y) + s2.val[0]*(1-x)*y + s3.val[0]*x*y + s4.val[0]*x*(1-y);
    res.val[1]= s1.val[1]*(1-x)*(1-y) + s2.val[1]*(1-x)*y + s3.val[1]*x*y + s4.val[1]*x*(1-y);
    res.val[2]= s1.val[2]*(1-x)*(1-y) + s2.val[2]*(1-x)*y + s3.val[2]*x*y + s4.val[2]*x*(1-y);
    res.val[3]= s1.val[3]*(1-x)*(1-y) + s2.val[3]*(1-x)*y + s3.val[3]*x*y + s4.val[3]*x*(1-y);
}
float x_scale;
float y_scale;
float x_shift;
float y_shift;
float getRadialX(float x,float y,float cx,float cy,float k){
    x = (x*x_scale+x_shift);
    y = (y*y_scale+y_shift);
    float res = x+((x-cx)*k*((x-cx)*(x-cx)+(y-cy)*(y-cy)));
    return res;
}
float getRadialY(float x,float y,float cx,float cy,float k){
    x = (x*x_scale+x_shift);
    y = (y*y_scale+y_shift);
    float res = y+((y-cy)*k*((x-cx)*(x-cx)+(y-cy)*(y-cy)));
    return res;
}
float thresh = 1;
float calc_shift(float x1,float x2,float cx,float k){
    float x3 = x1+(x2-x1)*0.5;
    float res1 = x1+((x1-cx)*k*((x1-cx)*(x1-cx)));
    float res3 = x3+((x3-cx)*k*((x3-cx)*(x3-cx)));
    std::cerr<<"x1: "<<x1<<" - "<<res1<<" x3: "<<x3<<" - "<<res3<<std::endl;
    if(res1>-thresh && res1 < thresh)
        return x1;
    if(res3<0){
        return calc_shift(x3,x2,cx,k);
    }
    else{
        return calc_shift(x1,x3,cx,k);
    }
}
int main(int argc, char** argv){
    IplImage* src = cvLoadImage( argv[1], 1 );
    IplImage* dst = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
    IplImage* dst2 = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
    float K = 0.0001 ;
    //float K=atof(argv[3]);
    /*float centerX=atoi(argv[4]);
    float centerY=atoi(argv[5]);*/
    int width = cvGetSize(src).width;
    int height = cvGetSize(src).height;
    //圓心
    float centerX = width / 2 ;
    float centerY = height / 2 ;
    x_shift = calc_shift(0,centerX-1,centerX,K);
    float newcenterX = width-centerX;
    float x_shift_2 = calc_shift(0,newcenterX-1,newcenterX,K);
 
    y_shift = calc_shift(0,centerY-1,centerY,K);
    float newcenterY = height-centerY;
    float y_shift_2 = calc_shift(0,newcenterY-1,newcenterY,K);
    x_scale = (width-x_shift-x_shift_2)/width;
    y_scale = (height-y_shift-y_shift_2)/height;
 
    std::cerr<<x_shift<<" "<<y_shift<<" "<<x_scale<<" "<<y_scale<<std::endl;
    std::cerr<<cvGetSize(src).height<<std::endl;
    std::cerr<<cvGetSize(src).width<<std::endl;
 
    for(int j=0;j<cvGetSize(dst).height;j++){
        for(int i=0;i<cvGetSize(dst).width;i++){
            CvScalar s;
            float x = getRadialX((float)i,(float)j,centerX,centerY,K);
            float y = getRadialY((float)i,(float)j,centerX,centerY,K);
            sampleImage(src,y,x,s);
            cvSet2D(dst,j,i,s);
        }
    }
 
    cvSaveImage(argv[2],dst,0);
    cvShowImage(argv[2],dst);
    waitKey(0);
}
