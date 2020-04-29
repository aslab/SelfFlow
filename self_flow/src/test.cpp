#include "Agent.cpp"

int main(int argc, char *argv[])
{

  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
//  rclcpp::spin(std::make_shared<AgentNode>(argv[1]));
  rclcpp::executors::SingleThreadedExecutor executor;
  auto agent = std::make_shared<AgentNode>(argv[1]);
  executor.add_node(agent);

/////////////// MULTI NODE EXAMPLE
//  auto action_server = std::make_shared<NODE>(ARGS);
//  executor.add_node(action_server);
  executor.spin();

  rclcpp::shutdown();

  return 0;
}


