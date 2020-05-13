#include "Agent.cpp"

int main(int argc, char *argv[])
{

  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);


  rclcpp::executors::SingleThreadedExecutor executor;

  if(argc!=2)
  {
	std::cout << "Please input node name parameter"<<std::endl;
	return 1;
  }

  auto agent = std::make_shared<AgentNode>(argv[1]);
  executor.add_node(agent);

/////////////// MULTI NODE EXAMPLE
//  auto action_server = std::make_shared<NODE>(ARGS);
//  executor.add_node(action_server);
  executor.spin();

  rclcpp::shutdown();

  return 0;
}


