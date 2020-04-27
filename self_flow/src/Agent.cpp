#include <cstdint>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "self_flow/msg/taskdata.hpp"


#define UTILITY_T double
#define TIME_T int
#define AGENT_ID_T uint32_t
#define ID_T uint32_t

#define AUCTION_TOPIC "/self_flow/auction_task"
#define BID_TOPIC "/self_flow/bid_task"
#define ASSIGN_TOPIC "/self_flow/assign_tasks"
//Note: the assign_tasks topic will be replaced with a ros2 action server


#define AUCTION_MSG_TYPE self_flow::msg::TaskAuction
#define BID_MSG_TYPE self_flow::msg::TaskBid
#define ASSIGN_MSG_TYPE self_flow::msg::TaskAssign


#include "tasklist.h"
#include "utility.cpp"



using namespace std::chrono_literals;
using std::placeholders::_1;

class AgentNode : public rclcpp::Node
{
private:

    bool timer_active=1;
    bool is_connected;

    std::string nodeName;
    size_t count_;

//    std::vector<TASK_MSG_TYPE> public_task_log;

    task_queue tasks;

    rclcpp::Subscription<AUCTION_MSG_TYPE>::SharedPtr AuctionTopicSub;
    rclcpp::Subscription<BID_MSG_TYPE>::SharedPtr BidTopicSub;
    rclcpp::Subscription<ASSIGN_MSG_TYPE>::SharedPtr AssignTopicSub;
    rclcpp::Publisher<AUCTION_MSG_TYPE>::SharedPtr AuctionTopicPub;
    rclcpp::Publisher<BID_MSG_TYPE>::SharedPtr BidTopicPub;
    rclcpp::Publisher<ASSIGN_MSG_TYPE>::SharedPtr AssignTopicPub;

    rclcpp::TimerBase::SharedPtr timer;

    void AuctionTask()
    {
//	publish task and wait 10 secs, AssignTask
    }

    void BidTask()
    {
//	publish utility
    }

    void AssignTask()
    {
//	rank all bidders and Assign to best
    }

    void AuctionCallback(const AUCTION_MSG_TYPE::SharedPtr msg)
    {
	tasks.store_task(*msg);
//	if i can do it BidTask()
    }

    void BidCallback(const BID_MSG_TYPE::SharedPtr msg)
   {
//	if my auction store
   }

    void AssignCallback(const ASSIGN_MSG_TYPE::SharedPtr msg)
    {
//	if im chosen start task
    }


    void timerCallback()
    {
    }


public:
    AgentNode(std::string name): Node(name), count_(0)
    {
	nodeName=name;
        AuctionTopicPub = this->create_publisher<AUCTION_MSG_TYPE>(AUCTION_TOPIC, 1);
        BidTopicPub = this->create_publisher<BID_MSG_TYPE>(BID_TOPIC, 1);
        AssignTopicPub = this->create_publisher<ASSIGN_MSG_TYPE>(ASSIGN_TOPIC, 1);
        AuctionTopicSub = this->create_subscription<AUCTION_MSG_TYPE>(AUCTION_TOPIC, 1, std::bind(&AgentNode::AuctionCallback, this, _1));
        BidTopicSub = this->create_subscription<BID_MSG_TYPE>(BID_TOPIC, 1, std::bind(&AgentNode::BidCallback, this, _1));
        AssignTopicSub = this->create_subscription<ASSIGN_MSG_TYPE>(ASSIGN_TOPIC, 1, std::bind(&AgentNode::AssignCallback, this, _1));
        timer = this->create_wall_timer(1s, std::bind(&AgentNode::timerCallback, this));
    }


};




