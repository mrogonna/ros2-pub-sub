#include <chrono>
#include <memory>
#include "cv_bridge/cv_bridge.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/header.hpp"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <opencv2/core/types.hpp>
#include <opencv2/core/hal/interface.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>


using namespace std::chrono_literals;
using namespace cv;

class MinimalPublisher : public rclcpp::Node {

public:

MinimalPublisher() : Node("minimal_publisher"), count_(0), cap(3){

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    publisher_ = this->create_publisher<sensor_msgs::msg::Image>("topic", qos_profile);
    timer_ = this->create_wall_timer(10ms, std::bind(&MinimalPublisher::timer_callback, this));
    cv::VideoCapture cap(0, cv::CAP_FFMPEG);
    
}
private:

void timer_callback() {

    cv_bridge::CvImagePtr cv_ptr;

    cv::Mat img(cv::Size(1280,720), CV_8UC3);
    cv::randu(img, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
    cap >> img;
    sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", img).toImageMsg();
    publisher_->publish(*msg.get());
    RCLCPP_INFO(this->get_logger(), "publishing");
}
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  size_t count_;
  cv::VideoCapture cap;
};

int main(int argc, char *argv[]) {

  printf("Starting...");
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
