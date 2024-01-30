#ifndef MY_ROS2_PACKAGE_SUBSCRIBER_NODE_HPP_
#define MY_ROS2_PACKAGE_SUBSCRIBER_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberCounterNode : public rclcpp::Node
{
public:
    NumberCounterNode() : Node("number_counter"), counter_(0)
    {
        //counter_publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        number_subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10, std::bind(&NumberCounterNode::callbackNumber, this, std::placeholders::_1));
    }

private:
    void callbackNumber(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        counter_ += msg->data;
        RCLCPP_INFO_STREAM(this->get_logger(), msg->data);   
        //auto newMsg = example_interfaces::msg::Int64();
        //newMsg.data = counter_;
        //counter_publisher_->publish(newMsg);
    }

    int counter_;
    // rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr counter_publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr number_subscriber_;
};

#endif // MY_ROS2_PACKAGE_SUBSCRIBER_NODE_HPP_