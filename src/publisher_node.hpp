#ifndef MY_ROS2_PACKAGE_PUBLISHER_NODE_HPP_
#define MY_ROS2_PACKAGE_PUBLISHER_NODE_HPP_


#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"


class NumberPublisherNode : public rclcpp::Node
{
public:
    NumberPublisherNode() : Node("number_publisher"), number_(0)
    {
        number_publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        number_timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                                std::bind(&NumberPublisherNode::publishNumber, this));
        RCLCPP_INFO(this->get_logger(), "Number publisher has been started.");

    }

private:
    void publishNumber()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = number_;
        number_publisher_->publish(msg);
        RCLCPP_INFO_STREAM(get_logger(), "sensor value " << number_);
        number_ ++ ;
    }

    int number_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr number_publisher_;
    rclcpp::TimerBase::SharedPtr number_timer_;
};

#endif // MY_ROS2_PACKAGE_PUBLISHER_NODE_HPP_