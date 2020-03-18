#include "tasklist.h"
#include "rclcpp/rclcpp.hpp"
#define AGENT_NAME

class AgentNode : public rclcpp::Node
{
private:

    std::vector<task> tasks;

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr TimeTopic;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr PubTopic;
    rclcpp::TimerBase::SharedPtr timer;

public:
    AgentNode(): Node(nodeName())
    {
        currentTimeUpdated=time();
        currentTime=currentTimeUpdated;
        AnySub = this->create_subscription<std_msgs::msg::Bool>(AnyTopic, 1, std::bind(&AgentNode::AnyCallback, this, _1));
        AnyPub = this->create_publisher<std_msgs::msg::Float32>(AnyTopic, 1);
        timer = this->create_wall_timer(5s, std::bind(&AgentNode::timerCallback, this));
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

    void sensorCallback(const std_msgs::msg::Bool::SharedPtr sensTrigger)
    {
        currentTimeUpdated=time();
        sensorTrigger=sensTrigger->data;
    }

    void simulationTimeCallback(const std_msgs::msg::Float32::SharedPtr simTime)
    {
        simulationTime=simTime->data;
    }

    void timerCallback()
    {
//	recalculate task utilities and change task if necessary. can be disabled if required by task

    }

    void evaluate_objective_callback(){

	clear_tasks();
	security();
	pwr_mgmt(); //publish(pwr)
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




