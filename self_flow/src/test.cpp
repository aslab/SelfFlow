#include "agentX.cpp"

int main(int argc, char *argv[])
{

  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AgentNode>(argv[1]));


/////////////// MULTI NODE EXAMPLE
//  auto other = std::make_shared<NODE>(ARGS);
//  executor.add_node(other);
//  executor.spin();

  rclcpp::shutdown();

  return 0;
}


