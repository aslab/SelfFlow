#include "agentX.cpp"

int main(int argc, char *argv[])
{

  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;

  auto agent = std::make_shared<AgentX>();
  auto other = std::make_shared<NODE>(ARGS);

  executor.add_node(agent);
  executor.add_node(other);
  executor.spin();

  rclcpp::shutdown();

  return 0;
}


