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

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <memory>

using namespace std::chrono_literals;
using namespace cv;

class MinimalImageCapture {
public:
    MinimalImageCapture() {
        captureImage();
    }

private:
    void captureImage() {
        constexpr int width = 1280;
        constexpr int height = 720;
        constexpr int channels = 3;
        cv::Mat frame;

        // Open a pipe to read frames from ffmpeg
        FILE* pipe = popen("ffmpeg -f v4l2 -video_size 1280x720 -i /dev/video3 -f image2pipe -pix_fmt rgb24 -vcodec rawvideo -", "r");
        if (!pipe) {
            std::cerr << "Error: Failed to open pipe." << std::endl;
            return;
        }

        // Read frame from pipe
        frame = cv::Mat(height, width, CV_8UC3);
        size_t bytes_read = fread(frame.data, 1, width * height * channels, pipe);
        if (bytes_read != width * height * channels) {
            std::cerr << "Error: Failed to read frame from pipe." << std::endl;
            pclose(pipe);
            return;
        }

        pclose(pipe);

        // Save the frame as a PNG file
        std::string filename = "captured_image.png";
        cv::imwrite(filename, frame);
        std::cout << "Saved image as " << filename << std::endl;
    }
};

int main() {
    MinimalImageCapture image_capture;
    return 0;
}
