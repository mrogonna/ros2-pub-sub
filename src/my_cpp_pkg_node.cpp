/*#include "rclcpp/rclcpp.hpp"
#include "include/my_cpp_pkg/subscriber_node.hpp"
#include "include/my_cpp_pkg/publisher_node.hpp"

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);

  auto publisher_node = std::make_shared<NumberPublisherNode>();
  auto subscriber_node = std::make_shared<NumberCounterNode>();

  rclcpp::spin(publisher_node);
  rclcpp::spin(subscriber_node);

  rclcpp::shutdown();
  return 0;
}


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
*/

#include "rclcpp/rclcpp.hpp"
#include <thread>
#include "subscriber_node.hpp"
#include "publisher_node.hpp"

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);

  // Create a separate thread for the subscriber
  std::thread subscriber_thread([]() {
    rclcpp::spin(std::make_shared<NumberCounterNode>());
  });

  // Create and run the publisher in the main thread
  auto publisher_node = std::make_shared<NumberPublisherNode>();
  rclcpp::spin(publisher_node);

  // Wait for the subscriber thread to finish
  if (subscriber_thread.joinable()) {
    subscriber_thread.join();
  }

  rclcpp::shutdown();
  return 0;
}