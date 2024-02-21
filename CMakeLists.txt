cmake_minimum_required(VERSION 3.8)
project(pub-sub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(cpp_node src/my_first_node.cpp)
ament_target_dependencies(cpp_node rclcpp)

add_executable(robot_news_station src/robot_news_station.cpp)
ament_target_dependencies(robot_news_station rclcpp example_interfaces)

add_executable(smartphone src/smartphone.cpp)
ament_target_dependencies(smartphone rclcpp example_interfaces)

add_executable(number_publisher src/number_publisher.cpp)
ament_target_dependencies(number_publisher rclcpp example_interfaces)

add_executable(number_counter src/number_counter.cpp)
ament_target_dependencies(number_counter rclcpp example_interfaces)

add_executable(my_cpp_pkg_node src/my_cpp_pkg_node.cpp)
ament_target_dependencies(my_cpp_pkg_node rclcpp example_interfaces)

add_executable(usb_cam_pub src/usb_cam_pub.cpp)
ament_target_dependencies(usb_cam_pub cv_bridge sensor_msgs std_msgs rclcpp image_transport)
target_link_libraries(usb_cam_pub ${OpenCV_LIBS})

add_executable(usb_cam_sub src/usb_cam_sub.cpp)
ament_target_dependencies(usb_cam_sub cv_bridge sensor_msgs std_msgs rclcpp image_transport)
target_link_libraries(usb_cam_sub ${OpenCV_LIBS})

add_executable(cam_pub src/cam_pub.cpp)
ament_target_dependencies(cam_pub cv_bridge sensor_msgs std_msgs rclcpp image_transport)
target_link_libraries(cam_pub ${OpenCV_LIBS})

include_directories(${OpenCV_INCLUDE_DIRS})



install(TARGETS
  cpp_node
  robot_news_station
  smartphone
  number_publisher
  number_counter
  my_cpp_pkg_node
  usb_cam_pub
  usb_cam_sub
  cam_pub
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
