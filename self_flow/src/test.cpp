#include "Agent.cpp"

int main(int argc, char *argv[])
{

  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
//  rclcpp::spin(std::make_shared<AgentNode>(argv[1]));
  rclcpp::executors::SingleThreadedExecutor executor;
  auto agent = std::make_shared<AgentNode>(argv[1]);
  executor.add_node(agent);
  executor.spin();

/////////////// MULTI NODE EXAMPLE
//  auto other = std::make_shared<NODE>(ARGS);
//  executor.add_node(other);
//  executor.spin();

  rclcpp::shutdown();

  return 0;
}


