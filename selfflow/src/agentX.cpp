#include <cstdint>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "selfflow/msg/taskdata.hpp"


#define UTILITY_T float
#define TIME_T int
#define AGENT_ID_T uint32_t
#define MY_MSG_TYPE selfflow::msg::Taskdata
#define MY_PUB_MSG_TYPE selfflow::msg::Taskdata
#define ID_T uint32_t
#define AGENT_NAME "test"
#define COMMON_TOPIC "/commontopic"


#include "tasklist.h"
#include "utility.cpp"



using namespace std::chrono_literals;
using std::placeholders::_1;

class AgentNode : public rclcpp::Node
{
private:

    bool timer_active;
    bool is_connected;

    bool sensorTrigger=false;
    unsigned int currentTimeUpdated=0;
    unsigned int currentTime=0;
    string topic;
    vector<MY_MSG_TYPE> public_task_register;


//    std::vector<task> tasks;

    rclcpp::Subscription<MY_MSG_TYPE>::SharedPtr NetSub;
    rclcpp::Subscription<MY_MSG_TYPE>::SharedPtr CommonNetSub;
    rclcpp::Publisher<MY_MSG_TYPE>::SharedPtr NetPub;
    rclcpp::Publisher<MY_MSG_TYPE>::SharedPtr CommonNetPub;
    rclcpp::TimerBase::SharedPtr timer;


    void CommonNetCallback(const MY_PUB_MSG_TYPE::SharedPtr message)
    {
 	if(is_connected && message->type==2)
	{
		MY_PUB_MSG_TYPE message_2;
		message_2.type=1;
		message_2.data=this->topic;
		CommonNetPub->publish(message_2); //publish topic name
	}
	if(!is_connected&&message->type==1)
	{
		topic=message.topic;
		this->connect();
	}

    }

    void NetCallback(const MY_MSG_TYPE::SharedPtr msg)
    {
	public_task_register.push_back(msg); //store msg
	task_queue.add_task(msg);
    }

    void timerCallback()
    {
	if(timer_active)
        {
		if(!is_connected)
                {
        	        topic= AGENT_NAME + "'s topic"
        	        this->connect();
			timer_active=0;
                }
	}
    }



public:
    AgentNode(): Node(nodeName())
    {

        currentTimeUpdated=time();
        currentTime=currentTimeUpdated;

	CommonNetSub = this->create_subscription<MY_MSG_TYPE>(COMMON_TOPIC, 1, std::bind(&AgentNode::CommonNetCallback, this, _1));
	CommonNetPub = this->create_publisher<MY_MSG_TYPE>(COMMON_TOPIC, 1);
        timer = this->create_wall_timer(10s, std::bind(&AgentNode::timerCallback, this));
    }

/*
    unsigned int time() const
    {
        auto now = std::chrono::steady_clock::now();
        auto now_sec = std::chrono::time_point_cast<std::chrono::seconds>(now);
        return now_sec.time_since_epoch().count();
    }

*/
    std::string nodeName()
    {
        currentTimeUpdated=time()&0x00ffffff;
        std::string nodeName(AGENT_NAME);
        std::string randId(string(currentTimeUpdated+int(999999.0f*(rand()/(float)RAND_MAX))));
        nodeName+=randId;
        return nodeName;
    }




    void find_network()
    {
	is_connected=0;
	MY_PUB_MSG_TYPE message;
	message.type=2;//request
	message.data=AGENT_NAME;
	CommonNetPub->publish(message);
	timer_active=1;
    }

    void connect()
    {
	NetSub = this->create_subscription<MY_MSG_TYPE>(topic, 1, std::bind(&AgentNode::NetCallback, this, _1));
	NetPub = this->create_publisher<MY_MSG_TYPE>(topic, 1);
	is_connected=1;
    }

};



