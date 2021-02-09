#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>


using namespace std::chrono_literals;

int request_position(std::string location)
{
  char * argv[1];
  rclcpp::init(1, argv);
  auto node = rclcpp::Node::make_shared("");
  auto publisher = node->create_publisher<std_msgs::msg::String>("/self_flow/tracker", 10);
  std_msgs::msg::String message;

  if (rclcpp::ok()) {
    message.data = location;
    RCLCPP_INFO(node->get_logger(), "Publishing location request: '%s'", message.data.c_str());
    try {
      publisher->publish(message);
      rclcpp::spin_some(node);
    } catch (const rclcpp::exceptions::RCLError & e) {
      RCLCPP_ERROR(
        node->get_logger(),
        "unexpectedly failed with %s",
        e.what());
    }
  }
  rclcpp::shutdown();
  return 0;
}
