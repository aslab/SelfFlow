
#include "Agent.cpp"
#include "AgentPositionTracker.cpp"

int main(int argc, char *argv[])
{

  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  rclcpp::executors::SingleThreadedExecutor executor;

  //if(argc<2)
  //{
  //	std::cout << "Please input node name parameter"<<std::endl;
  //	return 1;
  //}

  auto agent = std::make_shared<AgentNode>("agent_core");
  auto agent_tracker= std::make_shared<AgentPositionTracker>();
  executor.add_node(agent);
  executor.add_node(agent_tracker);

/////////////// MULTI NODE EXAMPLE
//  auto action_server = std::make_shared<NODE>(ARGS);
//  executor.add_node(action_server);
  executor.spin();

  rclcpp::shutdown();

  return 0;
}



