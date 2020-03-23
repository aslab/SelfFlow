#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <boost/lexical_cast.hpp>
#include "std_msgs/msg/bool.hpp"

#include "tasklist.h"

#define AGENT_NAME "test"
#define MY_MSG_TYPE std_msgs::msg::Bool
#define TOPIC	"testtopic"
#define COMMON_TOPIC "commontopic"
#define EMPTY int i=0;

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



//    std::vector<task> tasks;

    rclcpp::Subscription<MY_MSG_TYPE>::SharedPtr NetSub;
    rclcpp::Subscription<MY_MSG_TYPE>::SharedPtr CommonNetSub;
    rclcpp::Publisher<MY_MSG_TYPE>::SharedPtr NetPub;
    rclcpp::Publisher<MY_MSG_TYPE>::SharedPtr CommonNetPub;
    rclcpp::TimerBase::SharedPtr timer;


    void CommonNetCallback(const MY_PUB_MSG_TYPE::SharedPtr message){
 	if(is_connected){
		if(message.type==1){
			find_network();
		}
		else{
		MY_PUB_MSG_TYPE message_2;
		message_2.type=1;
		message_2.data=this->topic;
		CommonNetPub->publish(message_2); //publish topic name

	}
	else{
		if(message.type==1)
		topic=message.topic;
		is_connected=1;
	}

    }

    void NetCallback(const MY_MSG_TYPE::SharedPtr msg){

        //process message and continue


    }

    void timerCallback(){
        if(!is_connected){
            find_network();
        }
//      recalculate task utilities and change task if necessary. can be disabled if required by task
        if(timer_active){
            evaluate_objective();
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
// here?	find_network();
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




    void find_network(){
	is_connected=0;
	MY_PUB_MSG_TYPE message;
	message.type=2;//request
	message.data=AGENT_NAME
	CommonNetPub->publish(message)
	sleep(10)
	if(!is_connected){
		topic= AGENT_NAME + "'s topic"
		is_connected=1;
	}
        NetSub = this->create_subscription<MY_MSG_TYPE>(topic, 1, std::bind(&AgentNode::NetCallback, this, _1));
        NetPub = this->create_publisher<MY_MSG_TYPE>(topic, 1);
    }

    void evaluate_objective(){ //needs work
	EMPTY
//	clear_tasks();
//	security();
//	pwr_mgmt();
//	comply(.5);
//	task best=find_best(tasks);
//	best.execute();
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




