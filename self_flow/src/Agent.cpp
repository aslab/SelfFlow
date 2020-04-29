#include <cstdint>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "self_flow/msg/task_auction.hpp"
#include "self_flow/msg/task_bid.hpp"
#include "self_flow/msg/task_assign.hpp"

#define UTILITY_T double
#define TIME_T int
#define AGENT_ID_T uint32_t
#define ID_T uint32_t

#define AUCTION_TOPIC "/self_flow/auction_task"
#define BID_TOPIC "/self_flow/bid_task"
#define ASSIGN_TOPIC "/self_flow/assign_tasks"
//Note: the assign_tasks topic will be replaced with a ros2 action server



using namespace std::chrono_literals;
using std::placeholders::_1;

class AgentNode : public rclcpp::Node
{
private:

    bool auction_pending=0;
    std::string atid;
    std::string best_bidder;
    double best_bid=0.0;
    bool busy=0;
    std::string my_name;
    size_t count_;



    rclcpp::Subscription<self_flow::msg::TaskAuction>::SharedPtr AuctionTopicSub;
    rclcpp::Subscription<self_flow::msg::TaskBid>::SharedPtr BidTopicSub;
    rclcpp::Subscription<self_flow::msg::TaskAssign>::SharedPtr AssignTopicSub;
    rclcpp::Publisher<self_flow::msg::TaskAuction>::SharedPtr AuctionTopicPub;
    rclcpp::Publisher<self_flow::msg::TaskBid>::SharedPtr BidTopicPub;
    rclcpp::Publisher<self_flow::msg::TaskAssign>::SharedPtr AssignTopicPub;

    rclcpp::TimerBase::SharedPtr timer;

public:

    AgentNode(std::string name): Node(name), count_(0)
    {
	my_name=name;
        AuctionTopicPub = this->create_publisher<self_flow::msg::TaskAuction>(AUCTION_TOPIC, 1);
        BidTopicPub = this->create_publisher<self_flow::msg::TaskBid>(BID_TOPIC, 1);
        AssignTopicPub = this->create_publisher<self_flow::msg::TaskAssign>(ASSIGN_TOPIC, 1);
        AuctionTopicSub = this->create_subscription<self_flow::msg::TaskAuction>(AUCTION_TOPIC, 1, std::bind(&AgentNode::AuctionCallback, this, _1));
        BidTopicSub = this->create_subscription<self_flow::msg::TaskBid>(BID_TOPIC, 1, std::bind(&AgentNode::BidCallback, this, _1));
        AssignTopicSub = this->create_subscription<self_flow::msg::TaskAssign>(ASSIGN_TOPIC, 1, std::bind(&AgentNode::AssignCallback, this, _1));
        timer = this->create_wall_timer(10s, std::bind(&AgentNode::timerCallback, this));
    }

    void AuctionTask(std::string id, double w1, double w2, double w3, double w4)
    {
	auto msg=self_flow::msg::TaskAuction();
	msg.id=id;
	msg.w1=w1;
	msg.w2=w2;
	msg.w3=w3;
	msg.w4=w4;
	auction_pending=1;
	AuctionTopicPub->publish(msg);
	RCLCPP_INFO(this->get_logger(), "Auctioned task");
    }

    void BidTask(std::string id)
    {
	auto reply=self_flow::msg::TaskBid();
	msg.agent=my_name;
	msg.id=id;
	msg.utility=result;
	BidTopicPub->publish(msg);
    }


    void AssignTask()
    {
	//check for myself first?
	//use action client instead
	auto msg=self_flow::msg::TaskAssign();
	msg.id=atid;
	msg.agent=best_bidder;
	AssignTopicPub->publish(msg);
    }

    void AuctionCallback(const self_flow::msg::TaskAuction::SharedPtr msg)
    {
	double ut=map_sort(msg.id)->utility(msg.w1, msg.w2, msg.w3, msg.w4)
	if(ut>0.1 && !busy)
	{
		auto reply=self_flow::msg::TaskBid();
		reply.utility=ut;
		reply.id=msg.id;
		reply.agent=my_name;
		BidTopicPub->publish(reply);
	}
    }

    void BidCallback(const self_flow::msg::TaskBid::SharedPtr msg)
    {
	if(auction_pending && msg->id==atid)
	{
		if(msg->utility>best_bid)
		{
			best_bid=msg->utility;
			best_bidder=msg->agent;
		}
	}
    }

    void AssignCallback(const self_flow::msg::TaskAssign::SharedPtr msg)
    {
	if(msg->agent==my_name)
	{
		busy=1;
		map_sort(msg.id)->execute; //replace with call to action server
		busy=0;
	}
    }


    void timerCallback()
    {
	if(auction_pending)
	{
		auction_pending=0;
		AssignTask();
	}
    }

};




