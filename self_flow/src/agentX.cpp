#include <cstdint>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "self_flow/msg/taskdata.hpp"
#include "self_flow/msg/common.hpp"


#define UTILITY_T double
#define TIME_T int
#define AGENT_ID_T uint32_t
#define MY_MSG_TYPE self_flow::msg::Taskdata
#define MY_PUB_MSG_TYPE self_flow::msg::Common
#define ID_T uint32_t
#define COMMON_TOPIC "testnet"


#include "tasklist.h"
#include "utility.cpp"



using namespace std::chrono_literals;
using std::placeholders::_1;

class AgentNode : public rclcpp::Node
{
private:

    bool timer_active=1;
    bool is_connected;

    std::string topic="DefaultTopic";
    std::string nodeName;
    size_t count_;

    std::vector<MY_MSG_TYPE> public_task_register;

    task_queue tasks;

    rclcpp::Subscription<MY_MSG_TYPE>::SharedPtr NetSub;
    rclcpp::Subscription<MY_PUB_MSG_TYPE>::SharedPtr CommonNetSub;
    rclcpp::Publisher<MY_MSG_TYPE>::SharedPtr NetPub;
    rclcpp::Publisher<MY_PUB_MSG_TYPE>::SharedPtr CommonNetPub;
    rclcpp::TimerBase::SharedPtr timer;


    void CommonNetCallback(const MY_PUB_MSG_TYPE::SharedPtr message)
    {
 	if(is_connected && message->type==2)
	{
		auto reply = self_flow::msg::Common();
		reply.type=1;
		reply.data="test";
		this->CommonNetPub->publish(reply); //publish topic name
	}
	if(!is_connected&&message->type==1)
	{
		topic=std::string(message->data);
		this->connect();
	}

    }

    void NetCallback(const MY_MSG_TYPE::SharedPtr msg)
    {
	public_task_register.push_back(*msg); //store msg
	tasks.store_task(*msg);
    }

    void timerCallback()
    {
	if(!is_connected)
	{
		if (count_<10)find_network();
	        else
		{
			topic= std::string(nodeName);
			topic+= "_topic";
       	        	this->connect();
		}
	}
    }


public:
    AgentNode(std::string name): Node(name), count_(0)
    {
	nodeName=name;
        CommonNetPub = this->create_publisher<MY_PUB_MSG_TYPE>(COMMON_TOPIC, 1);
        CommonNetSub = this->create_subscription<MY_PUB_MSG_TYPE>(COMMON_TOPIC, 1, std::bind(&AgentNode::CommonNetCallback, this, _1));
        timer = this->create_wall_timer(1s, std::bind(&AgentNode::timerCallback, this));
    }


    unsigned int time() const
    {
        auto now = std::chrono::steady_clock::now();
        auto now_sec = std::chrono::time_point_cast<std::chrono::seconds>(now);
        return now_sec.time_since_epoch().count();
    }


    void find_network()
    {
	auto message = self_flow::msg::Common();
        message.data = nodeName; // + std::to_string(this->count_++);
	message.type=2; //request
        RCLCPP_INFO(this->get_logger(), "Looking for other agents...");
	this->count_++;
        this->CommonNetPub->publish(message);
    }

    void connect()
    {
	NetPub = this->create_publisher<MY_MSG_TYPE>(topic, 1);
	NetSub = this->create_subscription<MY_MSG_TYPE>(topic, 1, std::bind(&AgentNode::NetCallback, this, _1));
	is_connected=1;
	std::cout << "Connected to topic: " << this->topic << std::endl ;
    }

};




