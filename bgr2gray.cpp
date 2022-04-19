#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "time_count.hpp"
//Y = 0.2126*R + 0.7152*G + 0.0722.B
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

cv::Mat Bgr2GrayPlus(cv::Mat& img)
{
  int width = img.cols;
  int height = img.rows;
  std::vector<cv::Mat> mat_channel;
  cv::split(img, mat_channel);
  cv::Mat gray = cv::Mat::zeros(height, width, CV_8UC1);
  gray = 0.2126 * mat_channel[2] + 0.7152 * mat_channel[1] + 0.0722 * mat_channel[0];
  return gray;
}

int main()
{
  cv::Mat img = cv::imread("./test.jpg");
  TimerClock tc;
  tc.update();
  cv::Mat gray = Bgr2Gray(img);
  std::cout << "swap_channel_cost_time:" << tc.getTimerMicroSec() << " us" << std::endl;
  cv::imwrite("./gray.jpg", gray);

  TimerClock tc_;
  tc_.update();
  cv::Mat gray_ = Bgr2GrayPlus(img);
  std::cout << "swap_channel_cost_time:" << tc_.getTimerMicroSec() << " us" << std::endl;
  cv::imwrite("./gray_plus.jpg", gray_);
  return 0;
}
