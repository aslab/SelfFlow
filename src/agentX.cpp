#include "tasklist.h"
#include "rclcpp/rclcpp.hpp"
#define AGENT_NAME

class AgentNode : public rclcpp::Node
{
private:

    bool timer_active;

    std::vector<task> tasks;

    rclcpp::Subscription<MY_MSG_TYPE>::SharedPtr NetSub;
    rclcpp::Subscription<MY_MSG_TYPE>::SharedPtr CommonNetSub;
    rclcpp::Publisher<MY_MSG_TYPE>::SharedPtr NetPub;
    rclcpp::Publisher<MY_MSG_TYPE>::SharedPtr CommonNetPub;
    rclcpp::TimerBase::SharedPtr timer;



public:
    AgentNode(): Node(nodeName())
    {
/*
        currentTimeUpdated=time();
        currentTime=currentTimeUpdated;
*/
	CommonNetSub = this->create_subscription<MY_MSG_TYPE>(CommonTopic, 1, std::bind(&AgentNode::CommonNetCallback, this, _1));
	CommonNetPub = this->create_publisher<MY_MSG_TYPE>(CommonTopic, 1);
        timer = this->create_wall_timer(5s, std::bind(&AgentNode::timerCallback, this));
	find_network();
    }

    unsigned int time() const
    {
        auto now = std::chrono::steady_clock::now();
        auto now_sec = std::chrono::time_point_cast<std::chrono::seconds>(now);
        return now_sec.time_since_epoch().count();
    }

    std::string nodeName()
    {
        currentTimeUpdated=time()&0x00ffffff;
        std::string nodeName(AGENT_NAME);
        std::string randId(boost::lexical_cast<std::string>(currentTimeUpdated+int(999999.0f*(rand()/(float)RAND_MAX))));
        nodeName+=randId;
        return nodeName;
    }



    // Topic subscription callbacks:

    find_network(){
        NetSub = this->create_subscription<MY_MSG_TYPE>(TopicName(), 1, std::bind(&AgentNode::NetCallback, this, _1));

    }

    void CommonNetCallback(){

	//find a network or try to add new members to network

    }

    void NetCallback(const MY_MSG_TYPE::SharedPtr msg)
    {

	//process message and continue


    }

    void timerCallback()
    {
//	recalculate task utilities and change task if necessary. can be disabled if required by task
	if(timer_active){
	    evaluate_objective();
	}
    }

    void evaluate_objective(){ //needs work

	clear_tasks();
	security();
	pwr_mgmt();
	comply(.5);
	task best=find_best(tasks);
	best.execute();
    }
};

int main(int argc, char *argv[])
{

    std::cout << "Starting " << AGENT_NAME << std::endl;

    rclcpp::spin(std::make_shared<AgentNode>());

    std::cout << "Shutting down "<< AGENT_NAME << std::endl;

    rclcpp::shutdown();

    return 0;
}




