#if 0
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


// BGR -> Gray
cv::Mat BGR2GRAY(cv::Mat img){
  // get height and width
  int width = img.cols;
  int height = img.rows;

  // prepare output
  cv::Mat out = cv::Mat::zeros(height, width, CV_8UC1);

  // each y, x
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      // BGR -> Gray
      out.at<uchar>(y, x) = 0.2126 * (float)img.at<cv::Vec3b>(y, x)[2] \
        + 0.7152 * (float)img.at<cv::Vec3b>(y, x)[1] \
        + 0.0722 * (float)img.at<cv::Vec3b>(y, x)[0];
    }
  }

  return out;
}

// Gray -> Binary
cv::Mat Binarize(cv::Mat gray, int th){
  int width = gray.cols;
  int height = gray.rows;

  // prepare output
  cv::Mat out = cv::Mat::zeros(height, width, CV_8UC1);

  // each y, x
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      // Binarize
      if (gray.at<uchar>(y, x) > th){
        out.at<uchar>(y, x) = 255;
      } else {
        out.at<uchar>(y, x) = 0;
      }
    
    }
  }

  return out;
}


int main(int argc, const char* argv[]){
  // read image
  cv::Mat img = cv::imread("imori.jpg", cv::IMREAD_COLOR);

  // BGR -> Gray
  cv::Mat gray = BGR2GRAY(img);

  // Gray -> Binary
  cv::Mat out = Binarize(gray, 128);

  //cv::imwrite("out.jpg", out);
  cv::imshow("sample", out);
  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}
#endif



#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include "time_count.hpp"

cv::Mat Bgr2Gray(cv::Mat& img)
{
  int width = img.cols;
  int height = img.rows;
  cv::Mat gray = cv::Mat::zeros(height, width, CV_8UC1);
  for(int y = 0; y < height; y++)
  {
    for(int x = 0; x < width; x++)
    {
      gray.at<uchar>(y, x) = 0.2126 * static_cast<float>(img.at<cv::Vec3b>(y, x)[2])\
      + 0.7152 * static_cast<float>(img.at<cv::Vec3b>(y, x)[1])\
      + 0.0722 * static_cast<float>(img.at<cv::Vec3b>(y, x)[0]);
    }
  }
  return gray;
}

cv::Mat Gray2Binary(cv::Mat& gray, int threshold)
{
  int width = gray.cols;
  int height = gray.rows;
  cv::Mat binary_mat = cv::Mat::zeros(height, width, CV_8UC1);
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      int val = gray.at<uchar>(i, j);
      if(val > threshold)
        binary_mat.at<uchar>(i, j) = 255;
      else
        binary_mat.at<uchar>(i, j) = 0;
    }
  }
  return binary_mat;
}

cv::Mat Gray2BinaryPlus(cv::Mat& gray, int threshold)
{
  int nRows = gray.rows ;
	int nCols = gray.cols * gray.channels() ;
	if(gray.isContinuous())
	{
		nCols = nRows * nCols ;
		nRows = 1 ;
	}
  std::cout << "nrows:" << nRows << std::endl;
	for(int h = 0 ; h < nRows ; ++ h)
	{
		uchar *ptr = gray.ptr<uchar>(h) ;
		for(int w = 0 ; w < nCols ; ++ w)
		{
			if(*ptr > threshold)
      {
        *ptr++ = 255;
      }
      else
      {
        *ptr++ = 0;
      }
		}
	}
  return gray;
}

int main()
{
  cv::Mat img = cv::imread("test.jpg");
  std::cout << "img.step:" << img.step << " " << img.cols << " " << img.rows << std::endl;
  cv::Mat gray = Bgr2Gray(img);
  TimerClock tc;
  tc.update();
  cv::Mat binary = Gray2Binary(gray, 127);
  std::cout << "time_cost:" << tc.getTimerMicroSec() << std::endl;
  cv::imwrite("./binary.jpg", binary);

  TimerClock tc_;
  tc_.update();
  cv::Mat binary_ = Gray2BinaryPlus(gray, 127);
  std::cout << "time_cost_:" << tc_.getTimerMicroSec() << std::endl;
  cv::imwrite("./binary_plus.jpg", binary);
  return 0;
}



















// using namespace cv;
// int main()
// {
//   cv::Mat image = imread("test.jpg") ;
	
// 	//单通道多通道都适用
// 	int nRows = image.rows ;
// 	int nCols = image.cols * image.channels() ;
 
// 	if(image.isContinuous())
// 	{
// 		nCols = nRows * nCols ;
// 		nRows = 1 ;
// 	}
//   std::cout << "nrows:" << nRows << std::endl;
// 	for(int h = 0 ; h < nRows ; ++ h)
// 	{
// 		uchar *ptr = image.ptr<uchar>(h) ;
// 		for(int w = 0 ; w < nCols ; ++ w)
// 		{
// 			//ptr[w] = 128 ;
// 			*ptr ++ = *ptr;
// 		}
// 	}
//   cv::imwrite("zzzzzzzzzzzzzzzzzz.jpg", image);
//   return 0;
// }