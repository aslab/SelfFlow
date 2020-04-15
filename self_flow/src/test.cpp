#include "agentX.cpp"

int main(int argc, char *argv[])
{

  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;

//  if (argc>1)
//  {
  	std::string name(argv[1]);
	auto agent = std::make_shared<AgentNode>(name);
	executor.add_node(agent);

//  }
//  else
//  {
//	auto agent = std::make_shared<AgentNode>();
//	executor.add_node(agent);

//  }



//  auto other = std::make_shared<NODE>(ARGS);

//  executor.add_node(other);
  executor.spin();

  rclcpp::shutdown();

  return 0;
}


