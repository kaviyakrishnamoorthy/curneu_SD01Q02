#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "iostream"
 
using namespace cv;
using namespace std;
 
int main( )
{
    Mat src1,src2;
 int a;

 
 int b[100];
 Scalar intensity1=0;

 //Read the Image
    src1 = imread("i4.png", CV_LOAD_IMAGE_GRAYSCALE);
 src2 = src1.clone();

 //If image not found 
 if (!src1.data)                                                                          
     {  
      cout << "No image data \n";  
      return -1;  
     } 

  cout<<"Enter the mask Size =";
  cin>>a;

 //for loop for counting the number of rows and columns and displaying the pixel value.
   for (int i = 0; i < src1.rows-a; i++) 
   { 
    for (int j = 0; j < src1.cols-a; j++) 
     { 

   Scalar intensity2;
   int x=-1;
   for (int p = 0; p<a; p++) 
       { 
    
       for (int q = 0; q<a; q++) 
        { 

      intensity1 = src1.at<uchar>(i+p,j+q); 
      b[++x] =intensity1.val[0];
    }
  
 }
   int temp;
    for (int z=0;z<a*a;z++){
   for (int y=0;y<a*a;y++){
   if(b[y]>b[y++]){
    temp=b[y++];
      b[y++]=b[y];
      b[y]=temp;
   }
  }
    }
    src2.at<uchar>(i+(a-1)/2,j+(a-1)/2)=b[((a*a)-1)/2];
     } 
   }

  //Display the original image
   namedWindow("Original Image");                
   imshow("Original Image", src1); 

  //Display the Filtered Image 
 namedWindow("Filtered Image");     
 imshow("Filtered Image", src2);  
 waitKey(0);
 return 0;
}
