#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNewsStationNode : public rclcpp::Node
{
public:
    RobotNewsStationNode() : Node("cpp_test"), counter_(0)
    {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), 
                                        std::bind(&RobotNewsStationNode::publisherNews, this));
        RCLCPP_INFO(this->get_logger(), "Robot news Station has been started.");

    }
private:

    void publisherNews()

    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hi, this is ") + robot_name_ + std::string("from the Robot News Station");
        publisher_->publish(msg);
        
    }

    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr  publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
