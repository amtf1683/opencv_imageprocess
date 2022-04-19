#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "time_count.hpp"

cv::Mat ChannelSwapAt(cv::Mat& origin_mat)
{
  cv::Mat rgb_mat(origin_mat.rows, origin_mat.cols, CV_8UC3);
  for(int height = 0; height < origin_mat.rows; height++)
  {
    for(int width = 0; width < origin_mat.cols; width++)
    {
      //几行几列
      rgb_mat.at<cv::Vec3b>(height, width)[0] = origin_mat.at<cv::Vec3b>(height, width)[2];
      rgb_mat.at<cv::Vec3b>(height, width)[1] = origin_mat.at<cv::Vec3b>(height, width)[1];
      rgb_mat.at<cv::Vec3b>(height, width)[2] = origin_mat.at<cv::Vec3b>(height, width)[0];
    }
  }
  return rgb_mat;
}

cv::Mat ChannelSwapPtr(cv::Mat& origin_mat)
{
  std::vector<cv::Mat> mat_channel;
  cv::split(origin_mat, mat_channel);
  cv::Mat sw_mat = mat_channel[0];
  mat_channel[0] = mat_channel[2];
  mat_channel[2] = sw_mat;
  cv::merge(mat_channel, origin_mat);
  return origin_mat;
}

cv::Mat ChannelSwapPtrPlus(cv::Mat& origin_mat)
{
  for(int height = 0; height < origin_mat.rows; height++)
  {
    for(int width = 0; width < origin_mat.cols; width++)
    {
      uchar* ptr = origin_mat.ptr<uchar>(height, width);
      uchar sw_ptr = ptr[2];
      ptr[2] = ptr[0];
      ptr[0] = sw_ptr;
    }
  }
  return origin_mat;
}

cv::Mat ChannelSwapPtrPlusPlus(cv::Mat& origin_mat)
{
  cv::Mat_<cv::Vec3b>::iterator it = origin_mat.begin<cv::Vec3b>() ;
	cv::Mat_<cv::Vec3b>::iterator itend = origin_mat.end<cv::Vec3b>() ;
	for(;it != itend ; ++ it)
	{
    uchar sw_data = (*it)[2];
		(*it)[2] = (*it)[0] ;
		(*it)[0] = sw_data ;
	}
  return origin_mat;
}

int main()
{
  cv::Mat bgr_mat = cv::imread("./test.jpg");
  TimerClock tc;
  tc.update();
  cv::Mat rgb_at_mat = ChannelSwapAt(bgr_mat);
  std::cout << "swap_channel_cost_time:" << tc.getTimerMicroSec() << " us" << std::endl;
  cv::imwrite("out_at_rgb.jpg", rgb_at_mat);

  cv::Mat bgr_prt_mat = cv::imread("./test.jpg");
  TimerClock tc_;
  tc_.update();
  cv::Mat rgb_ptr_mat = ChannelSwapPtrPlusPlus(bgr_prt_mat);
  std::cout << "swap_channel_cost_time:" << tc_.getTimerMicroSec() << " us" << std::endl;
  cv::imwrite("out_prt_rgb.jpg", rgb_ptr_mat);
  
  return 0;
}